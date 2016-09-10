package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class Core ( val addrw : Int , val expr_len : Int ) extends Module { 
	val io = new Bundle {

		val mux_pc			= Module (new MuxPC 	( expr_len ))
		
		val register_file 	= Module(new RegFile 	( addrw , expr_len ))
		val imm_generator 	= Module(new ImmGen 	( expr_len ))
		val decoder 		= Module(new Decoder 	( expr_len ))

		val mux_op_a 		= Module(new MuxOpA 	( expr_len ))
		val mux_op_b 		= Module(new MuxOpB 	( expr_len ))

		val alu 			= Module(new Alu 		( expr_len ))

		val instr_mem		= Module(new InstructionMem 	(  addr_width = 10 , expr_len ))
		val data_mem 	 	= Module(new DataMem 			(  addr_width = 10 , expr_len ))

		val mux_wb 			= Module(new MuxWB 	( expr_len ))

		val br_logic 		= Module(new BranchLogic (expr_len)) 
	}

	// Control Path 
	val kill_the_fetch  	= !(io.br_logic.io.pc_sel === PC_PC4 )
	val stall 				= !(io.decoder.io.ctl_val_inst)	//( io.decoder.io.ctl_mem_en  ) 		// for now 
 
	val halt 				= !(io.decoder.io.ctl_val_inst) 
	// Data Path 

	// Pipeline Registers 
	val fetch_pc_reg 		= Reg (init=UInt(0,expr_len))

	val exec_pc_reg 		= Reg (init=UInt(0,expr_len))
	val exec_pc4_reg		= Reg (init=UInt(0,expr_len))
	val exec_instr_reg 		= Reg (init=BUBBLE )

	// Fetching Stage 
	
	// TODO add stall after memory implementation 
	when ( !stall ) { 
		fetch_pc_reg 		:= 	io.mux_pc.io.pc_out
	}
	val fetch_pc4_reg		= (fetch_pc_reg + (UInt(1,expr_len)))

	io.instr_mem.io.addr 		:= fetch_pc_reg
	val fetch_instr 			= io.instr_mem.io.data 

	when ( stall ) { 
		exec_instr_reg 	:= exec_instr_reg
		exec_pc_reg 	:= exec_pc_reg
	} .elsewhen (kill_the_fetch && !halt) {
		exec_instr_reg 	:= BUBBLE
		exec_pc_reg 	:= UInt(0,expr_len)
	} .elsewhen (kill_the_fetch && halt) {
		exec_instr_reg 	:= exec_instr_reg
		exec_pc_reg 	:= exec_pc_reg
	} .otherwise {
		exec_instr_reg 	:= fetch_instr 
		exec_pc_reg 	:= fetch_pc_reg 
	}

	exec_pc4_reg 		:= fetch_pc4_reg

	//Execution Stage

	//  < Reg file 
	val rsa_addr = exec_instr_reg (RSA_MSB,RSA_LSB)
	val rsb_addr = exec_instr_reg (RSB_MSB,RSB_LSB)
	val rd_addr  = exec_instr_reg (RD_MSB ,RD_LSB )
	val rd_data  = Bits ( width = expr_len )

	io.register_file.io.rf_ra1 	:= rsa_addr
	io.register_file.io.rf_ra2 	:= rsb_addr 
	io.register_file.io.rf_wa  	:= rd_addr 
	io.register_file.io.rf_wd 	:= io.mux_wb.io.wb_wd 
	io.register_file.io.rf_wen 	:= Mux ( stall , NO , io.decoder.io.ctl_rf_wen )  

	val rsa_data = io.register_file.io.rf_rd1 
	val rsb_data = io.register_file.io.rf_rd2 
	// Reg file > 

	// Imm_gen IN
	io.imm_generator.io.instr := exec_instr_reg 

	// Mux A IN 
	io.mux_op_a.io.opa_sel 	:= io.decoder.io.ctl_opa_sel
	io.mux_op_a.io.opa_rsa 	:= rsa_data
	io.mux_op_a.io.opa_imz  := io.imm_generator.io.immu_sxt // TODO change this to immz
	io.mux_op_a.io.opa_imu  := io.imm_generator.io.immu_sxt 

	// Mux B IN 
	io.mux_op_b.io.opb_sel  := io.decoder.io.ctl_opb_sel 
	io.mux_op_b.io.opb_rsb  := rsb_data 
	io.mux_op_b.io.opb_imi 	:= io.imm_generator.io.immi_sxt 
	io.mux_op_b.io.opb_ims	:= io.imm_generator.io.imms_sxt 
	io.mux_op_b.io.opb_pc 	:= exec_pc_reg

	// Alu IN 
	io.alu.io.op 	:= io.decoder.io.ctl_alu_func
	io.alu.io.a 	:= io.mux_op_a.io.opa_alu_in 
	io.alu.io.b 	:= io.mux_op_b.io.opb_alu_in 
	val alu_result 	= io.alu.io.out
	val alu_zero 	= io.alu.io.zero 
	// 

	io.mux_wb.io.wb_sel 	:= io.decoder.io.ctl_wb_sel 
	io.mux_wb.io.wb_alu	 	:= alu_result 
	io.mux_wb.io.wb_pc4 	:= exec_pc4_reg
	io.mux_wb.io.wb_csr 	:= alu_result 			//TODO Change to csr when available 
	io.mux_wb.io.wb_mem		:= io.data_mem.io.rd_data 

	//Branch Cond Generator 

	io.br_logic.io.excp 		:= halt
	io.br_logic.io.ctl_br_type 	:= io.decoder.io.ctl_br_type
	io.br_logic.io.br_eq 	:= ( rsa_data === rsb_data ) 
	io.br_logic.io.br_lt	:= ( rsa_data.toSInt < rsb_data.toSInt )
	io.br_logic.io.br_ltu	:= ( rsa_data.toUInt < rsb_data.toUInt )

	// Calculate Branch/Jump Target by adding the offset
	val exec_pc_br 	= exec_pc_reg + io.imm_generator.io.immb_sxt 
	val exec_pc_jmp = exec_pc_reg + io.imm_generator.io.immj_sxt
	val exec_pc_jalr= (rsa_data.toUInt + io.imm_generator.io.immi_sxt) 

	io.mux_pc.io.pc_sel 	:= io.br_logic.io.pc_sel
	io.mux_pc.io.pc_pc4		:= fetch_pc4_reg
	io.mux_pc.io.pc_br 		:= exec_pc_br
	io.mux_pc.io.pc_jmp		:= exec_pc_jmp 
	io.mux_pc.io.pc_jalr 	:= exec_pc_jalr
	io.mux_pc.io.pc_excp 	:= UInt(0)  			//TODO CSr

	io.decoder.io.dec_instr := exec_instr_reg 

	io.data_mem.io.addr 	:= alu_result 
	io.data_mem.io.wr_data  := io.register_file.io.rf_rd2
	io.data_mem.io.mem_func := io.decoder.io.ctl_mem_func
	io.data_mem.io.mem_en 	:= io.decoder.io.ctl_mem_en

}

class CoreTest ( c : Core, val steps : Int ) extends Tester (c) {

	var steps_passed = 0 
	var j = 0

	def build_I_ADDI (imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFF) << 20) | instr)
		instr = ((( rs 	    & 0x01F) << 15) | instr)
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( rd 	    & 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_I_Reg_Imm (imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
		// functions : 0 	2    3     4    6   7 
		//			   ADDI SLTI SLTIU XORI ORI ANDI
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFF) << 20) | instr)
		instr = ((( rs 	    & 0x01F) << 15) | instr)
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( rd 	    & 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_I_Reg_Imm_Shift(b30:Boolean=false, shft_val:Int=0x0, rs:Int=0x0, func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
		// functions : 1    5  	 5 & b30 
		// 			   SLLI SRLI SRAI
		var instr = 0x00000000
		if (b30) instr = 0x40000000
		printf ("shft_val:%d rs:%2d func:%d rd:%2d opcode:%8x \n", shft_val & 0x01F,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( shft_val & 0x01F) << 20) | instr)
		instr = ((( rs 	     & 0x01F) << 15) | instr)
		instr = ((( func     & 0x007) << 12) | instr)
		instr = ((( rd 	     & 0x01F) << 7 ) | instr)
		instr = (( opcode    & 0x07F )       | instr)
 		instr 
	}
	def build_I_Load (imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x03): BigInt = {
		// returns a instruction with Load format 
		// functions : 0  1  2  4   5
		//			   LB LH LW LBU LHU 
		var instr = 0x00000000
		printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFF) << 20) | instr)
		instr = ((( rs 	    & 0x01F) << 15) | instr)
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( rd 	    & 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_U_LUI (imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x37): BigInt = {
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFFFF) << 12) | instr)
		instr = ((( rd 	    & 0x01F)   << 7 ) | instr)
		instr = (( opcode   & 0x07F)          | instr)
 		instr 
	}
	def build_U_AUIPC (imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x17): BigInt = {
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFFFF) << 12) | instr)
		instr = ((( rd 	    & 0x01F)   << 7 ) | instr)
		instr = (( opcode   & 0x07F)          | instr)
 		instr 
	}
	def build_UJ_JAL(imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x6F): BigInt = {
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		
		instr = ((( imm_val & 0x80000) << 12) | instr)
		instr = ((( imm_val & 0x003FF) << 21) | instr)
		instr = ((( imm_val & 0x00400) << 10) | instr)
		instr = ((( imm_val & 0x7F800) << 1 ) | instr)
		instr = ((( rd 	    & 0x01F)   << 7 ) | instr)
		instr = (( opcode   & 0x07F)          | instr)
 		instr 
	}
	def build_I_JALR(imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x67): BigInt = {
		var instr = 0x00000000
		// printf ("imm_val:%4d rs:%2d func:%d rd:%2d opcode:%8x \n", imm_val & 0xFFF,rs & 0x01F, func & 0x007, rd & 0x01F, opcode & 0x07F )
		instr = ((( imm_val & 0xFFF) << 20) | instr)
		instr = ((( rs 	    & 0x01F) << 15) | instr)
		// instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( rd 	    & 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_SB_Branch( imm_val:Int = 0x0, rs2:Int = 0x0 , rs1:Int=0, func:Int=0, opcode:Int=0x63): BigInt = { 
		var instr = 0x00000000
		// functions: 0   1   4   5   6    7 
		// 			  BEQ BNE BLT BGE BLTU BGEU 
		instr = ((( imm_val & 0x800) << 20) | instr)
		instr = ((( imm_val & 0x3F0) << 21) | instr)
		instr = ((( rs2	    & 0x01F) << 20) | instr)
		instr = ((( rs1	    & 0x01F) << 15) | instr)
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( imm_val & 0x00F) << 8 ) | instr)
		instr = ((( imm_val & 0x400) >> 3 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_S_Store (imm_val:Int = 0x0, rs2:Int = 0x0 , rs1:Int = 0, func:Int=0, opcode:Int=0x23): BigInt = { 
		var instr = 0x00000000
		// functions: 0   1   2 
		//			  SB  SH  SW 
		instr = ((( imm_val & 0xFE0) << 20) | instr)
		instr = ((( rs2	    & 0x01F) << 20) | instr)  
		instr = ((( rs1	    & 0x01F) << 15) | instr) 
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( imm_val & 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}
	def build_R_Reg_Reg(b30:Boolean=false, rs2:Int=0x0, rs1:Int=0x0, func:Int=0, rd:Int=0, opcode:Int=0x33): BigInt = { 
		var instr = 0x00000000
		if (b30) 
			instr = 0x40000000
		// functions 0   0&b30 1   2   3    4   5   5&b30 6  7 
		//			 ADD SUB   SLL SLT SLTU XOR SRL SRA   OR AND
		instr = ((( rs2	    & 0x01F) << 20) | instr)  
		instr = ((( rs1	    & 0x01F) << 15) | instr) 
		instr = ((( func    & 0x007) << 12) | instr)
		instr = ((( rd 		& 0x01F) << 7 ) | instr)
		instr = (( opcode   & 0x07F )       | instr)
 		instr 
	}

	def get_nop () : BigInt = {
		var x = build_I_Reg_Imm()
		x
	}
	// def build_I_ADDI 		(imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
	// def build_I_Reg_Imm 		(imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
	// def build_I_Reg_Imm_Shift(b30:Boolean=false, shft_val:Int=0x0, rs:Int=0x0, func:Int=0, rd:Int=0, opcode:Int=0x13): BigInt = {
	// def build_I_Load (imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x03): BigInt = {
	// def build_U_LUI (imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x37): BigInt = {
	// def build_U_AUIPC (imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x17): BigInt = {
	// def build_UJ_JAL(imm_val:Int = 0x0, rd:Int=0, opcode:Int=0x6F): BigInt = {
	// def build_I_JALR(imm_val:Int = 0x0, rs:Int = 0x0 , func:Int=0, rd:Int=0, opcode:Int=0x67): BigInt = {
	// def build_SB_Branch( imm_val:Int = 0x0, rs2:Int = 0x0 , rs1:Int=0, func:Int=0, opcode:Int=0x63): BigInt = { 
	// def build_S_Store (imm_val:Int = 0x0, rs2:Int = 0x0 , rs1:Int = 0, func:Int=0, opcode:Int=0x23): BigInt = { 
	// def build_R_Reg_Reg(b30:Boolean=false, rs2:Int=0x0, rs1:Int=0x0, func:Int=0, rd:Int=0, opcode:Int=0x33): BigInt = { 
	// for ( i <- 0 until 32 ) {
	// 	var x = build_I_Reg_Imm ( imm_val=3, rs=i, func=0, rd=i+1 )
	// 	pokeAt(c.io.instr_mem.mem,x,i)
	// }

	var idx=0

	// test of regImm 
	/*
	var y = build_I_Reg_Imm (imm_val=5, rs=2, func=0, rd=3) // exp 5 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm (imm_val=2, rs=3, func=2, rd=4)		// exp 1
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1
	y = build_I_Reg_Imm (imm_val=6, rs=3, func=3, rd=5)		// exp 0 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1
	y = build_I_Reg_Imm (imm_val=0xC, rs=3, func=4, rd=6)	// exp 4 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1
	y = build_I_Reg_Imm (imm_val=0xB, rs=3, func=6, rd=7)	// exp F 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1
	y = build_I_Reg_Imm (imm_val=0x3A, rs=7, func=7, rd=2)	// exp A
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1
	for ( i <- 0 until 32 ) { peekAt(c.io.register_file.rf_reg_file,i)	}
	*/

	// test of imm shifting 
	/*
	var y = build_I_Reg_Imm (imm_val=0x404, rs=0, func=0, rd=1) // exp 5 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm_Shift (shft_val=21,rs=1,func=1,rd=2)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm_Shift (shft_val=3,rs=2,func=5,rd=3)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm_Shift (b30=true,shft_val=3,rs=2,func=5,rd=4)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm ()		//NOP OPERATION 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_I_Reg_Imm () 		//NOP OPERATION 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	*/

	// test LUI and AUIPC 
	/*
	var y = build_U_LUI ( imm_val=0x1234ABCD, rd=2 )
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_U_LUI ( imm_val=0xAB123CBD, rd=3 )
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = build_U_AUIPC (imm_val=0x4,rd=4)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = build_U_AUIPC (imm_val=0x8,rd=5)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	*/
	
	//test load and store 
	var y = build_U_LUI ( imm_val=0x1234ABCD, rd=2 )
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = build_U_LUI ( imm_val=0xAB123CBD, rd=3 )
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = build_S_Store (imm_val=0x2,rs2=2,rs1=0,func=2) 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = build_S_Store (imm_val=0x4,rs2=3,rs1=0,func=2) 
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = build_I_Load (imm_val=0x4,rs=0,func=2,rd=10)
	pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 

	y = get_nop() ; pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = get_nop() ; pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = get_nop() ; pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	y = get_nop() ; pokeAt(c.io.instr_mem.mem,y,idx) ; idx=idx+1 
	
	for ( i <- 0 until 10 ) {
		peek(c.io.mux_pc.io.pc_sel)
		peek(c.fetch_pc_reg)
		peek(c.exec_pc_reg)
		peek(c.exec_pc4_reg)
		peek(c.exec_instr_reg)

		peek(c.io.decoder.io.ctl_val_inst)
		peek(c.io.register_file.io.rf_ra1)
		peek(c.io.register_file.io.rf_ra2)		
		
		peek(c.io.decoder.io.ctl_alu_func)
		peek(c.io.decoder.io.ctl_wb_sel)
		peek(c.io.alu.io.out)
		
		peek(c.io.mux_wb.io.wb_alu)
		
		peek(c.io.register_file.io.rf_wa)
		peek(c.io.register_file.io.rf_wen)
		peek(c.io.register_file.io.rf_wd)

		peek(c.io.data_mem.io.addr)
		peek(c.io.data_mem.io.wr_data)
		peek(c.io.data_mem.io.mem_en)
		peek(c.io.data_mem.io.mem_func)

		step(1)
		for ( i <- 0 until 32 ) { peekAt(c.io.register_file.rf_reg_file,i)	}
	}
	for ( i <- 0 until 32 ) { peekAt(c.io.register_file.rf_reg_file,i)	}
	for ( i <- 0 until 32 ) { peekAt(c.io.data_mem.mem,i)	}

	println (s"Core: BIG TO DO !" )
	println (s"Core: not passed... yet !" )
}