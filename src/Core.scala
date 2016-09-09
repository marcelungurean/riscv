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

		val instr_mem		= Module(new InstructionMem 	(  addrw , expr_len ))
		val data_mem 	 	= Module(new DataMem 			(  addrw , expr_len ))

		val mux_wb 			= Module(new MuxWB 	( expr_len ))

		val br_logic 		= Module(new BranchLogic (expr_len)) 
	}

	// Control Path 
	val stall 				= io.decoder.io.ctl_mem_en			// for now 
	val kill_the_fetch  	= !(io.br_logic.io.pc_sel === PC_PC4)
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

	io.instr_mem.io.addr 	:= fetch_pc_reg
	val fetch_instr 		=  io.instr_mem.io.data 

	when ( stall ) { 
		exec_instr_reg 	:= exec_instr_reg
		exec_pc_reg 	:= exec_pc_reg
	} .elsewhen (kill_the_fetch ) {
		exec_instr_reg 	:= BUBBLE
		exec_pc_reg 	:= UInt(0,expr_len)
	} .otherwise {
		exec_instr_reg 	:= fetch_instr 
		exec_pc_reg 	:= fetch_pc_reg 
	}

	exec_pc4_reg 		:= fetch_pc4_reg

	//Execution Stage

	//  < Reg file 
	val rsa_addr = exec_instr_reg (RSA_MSB,RSA_LSB)
	val rsb_addr = exec_instr_reg (RSB_MSB,RSA_LSB)
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
	io.mux_op_a.io.opa_sel 	:= io.decoder.ctl_opa_sel
	io.mux_op_a.io.opa_rsa 	:= rsa_data
	io.mux_op_a.io.opa_imz  := io.imm_generator.io.immu_sxt // TODO change this to immz
	io.mux_op_a.io.opa_imu  := io.imm_generator.io.immu_sxt 

	// Mux B IN 
	io.mux_op_b.io.opb_sel  := io.decoder.ctl_opb_sel 
	io.mux_op_b.io.opb_rsb  := rsb_data 
	io.mux_op_b.io.opb_imi 	:= io.imm_generator.io.immi_sxt 
	io.mux_op_b.io.opb_ims	:= io.imm_generator.io.imms_sxt 
	io.mux_op_b.io.opb_pc 	:= exec_pc_reg

	// Alu IN 
	io.alu.io.op 	:= io.decoder.ctl_alu_func
	io.alu.io.a 	:= io.mux_op_a.io.opa_alu_in 
	io.alu.io.b 	:= io.mux_op_b.io.opb_alu_in 
	val alu_result 	= io.alu.io.out
	val alu_zero 	= io.alu.io.zero 
	// 

	io.mux_wb.io.wb_sel 	:= io.decoder.ctl_wb_sel 
	io.mux_wb.io.wb_alu	 	:= alu_result 
	io.mux_wb.io.wb_pc4 	:= exec_pc4_reg
	io.mux_wb.io.wb_csr 	:= alu_result 			//TODO Change to csr when available 
	io.mux_wb.io.wb_mem		:= io.data_mem.io.rd_data 

	//Branch Cond Generator 

	//io.br_logic.io.excp 	:= 
	io.br_logic.io.ctl_br_type := io.decoder.io.ctl_br_type
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
}

class CoreTest ( c : Core, val steps : Int ) extends Tester (c) {

	var steps_passed = 0 
	var j = 0
	var instr = Array (
		0xFFFFFF37 ,0xFFFFFFB7,0xFFFFFFC7,0xFFFFFF57, // LUI TEST 
		0xFFFFFF17 ,0XFFFF4F97,0xFFFFFF87,0xFFFFFFA7, // AUIPC 
		0xFFFFFF6F ,0XFFFFEF97,0xFFFFFF6F,0xFFFFFF67, // JAL 
		0xFFFF8F63 ,0XFFFF8FE3,0xFFFF0FE3,0xFFFF1F63, // JALR 
		0xFFFF9F63 ,0XFFFFAFE3,0xFFFFBFE3,0xFFFFCF63, // BRANCH 
		0xFFFF1F63 ,0XFFFF2FE3,0xFFFF3FE3,0xFFFF4F63,
		0xFFFF5F63 ,0XFFFF6FE3,0xFFFF7FE3,0xFFFF8F63,
		0xFFFFFF17 ,0XFFFF4F97,0xFFFFFF87,0xFFFFFFA7, // BRANCH 

		0x12340F03 ,0x12348F03,0x53429f03,0x54338F83,
		0x12340F13 ,0x12348F23,0x53429f43,0x54338F53, // 
		0x12340F83 ,0x12340D83,0x12348303,0x12340203,
		0x1234FF83 ,0x1234ED83,0x1234D303,0x12320203,
		0x12341F83 ,0x12342D83,0x12343303,0x12344203,
		0x12345F83 ,0x12346D83,0x12347303,0x12328203,
		
		0x12349F83 ,0x1234AD83,0x1234B303,0x1232C203,
		0x1234AF83 ,0x1234ED83,0x1234E303,0x1232F203,

		0x1234FFA3 ,0x1234ED23,0x1234D3A3,0x12320223 

		//0xFFFFFF6F , 0xFFFF0F67,
		//0xFFFF1F63 , 0XFFFF4F63, 
		//0xABCD1234 , 0xABCD4003
	)
/*
	instr.foreach {
		d => 		
		pokeAt(c.io.instr_mem.mem,d,j)
		step(1)
		peek(c.fetch_pc_reg)
		peek(c.exec_pc_reg)
		peek(c.exec_pc4_reg)
		peek(c.exec_instr_reg)
		peekAt(c.io.instr_mem.mem,j)
		peek(c.io.decoder.io.ctl_val_inst)
		peek(c.io.decoder.io.ctl_br_type)
		peek(c.io.decoder.io.ctl_opa_sel)
		peek(c.io.decoder.io.ctl_opb_sel)
		peek(c.io.decoder.io.ctl_alu_func)
		peek(c.io.decoder.io.ctl_wb_sel)
		peek(c.io.mux_pc.io.pc_sel)
		j = j + 1 
	}
*/
	var addi_test = Array (
		0x00108113,  0x00110193,  0x00118213,  0x00820293
	)
	var andi_test = Array (
		0x00108113,  0x00110193,  0x00118213,  0x00820293
	)
	var ori_test = Array (
		0x00108113,  0x00110193,  0x00118213,  0x00820293
	)
	var xori_test = Array (
		0x00108113,  0x00110193,  0x00118213,  0x00820293
	)
	addi_test.foreach {
		d => 		
		pokeAt(c.io.instr_mem.mem,d,j)
		step(1)
		peekAt(c.io.instr_mem.mem,j)
		peek(c.fetch_pc_reg)
		peek(c.exec_pc_reg)
		peek(c.exec_pc4_reg)
		peek(c.exec_instr_reg)
		peek(c.io.decoder.io.ctl_val_inst)
		peek(c.io.decoder.io.ctl_opa_sel)
		peek(c.io.decoder.io.ctl_opb_sel)
		peek(c.io.decoder.io.ctl_alu_func)
		peek(c.io.decoder.io.ctl_wb_sel)

		peek(c.io.alu.io.out)
		
		peek(c.io.mux_wb.io.wb_alu)
		peek(c.io.mux_wb.io.wb_alu)

		peek(c.io.register_file.io.rf_wa)
		peek(c.io.register_file.io.rf_wen)
		peek(c.io.register_file.io.rf_wd)

		peek(c.io.mux_pc.io.pc_sel)
		j = j + 1 
	}
	step(2)
	// for ( i <- 0 until 32 ) { 
	// 	peekAt(c.io.register_file.rf_reg_file,i)
	// }

	// for ( i <- 0 until 10 ){ 
	// 	var d = rnd.nextInt()
	// 	pokeAt(c.io.instr_mem.mem,d,i)
	// 	step(1)
	// 	peek(c.fetch_pc_reg)
	// 	peek(c.exec_pc_reg)
	// 	peek(c.exec_pc4_reg)
	// 	peek(c.exec_instr_reg)

	// 	peekAt(c.io.instr_mem.mem,i)
	// 	peek(c.io.decoder.io.ctl_val_inst)
	// 	peek(c.io.decoder.io.ctl_br_type)
	// 	peek(c.io.decoder.io.ctl_opa_sel)
	// 	peek(c.io.decoder.io.ctl_opb_sel)
	// 	peek(c.io.decoder.io.ctl_alu_func)
	// 	peek(c.io.decoder.io.ctl_wb_sel)
	// 	peek(c.io.mux_pc.io.pc_sel)

	// 	// peek(c.io.decoder.io.ctl_rf_wen)
	// 	// peek(c.io.decoder.io.ctl_mem_en)
	// 	// peek(c.io.decoder.io.ctl_mem_func)
	// 	// peek(c.io.decoder.io.ctl_msk_sel)
	// 	// peek(c.io.decoder.io.ctl_csr_cmd)	
	// }

	for ( i <- 0 until 32 ) { 
		peekAt(c.io.register_file.rf_reg_file,i)
	}
	println (s"Core: BIG TO DO !" )
	println (s"Core: not passed... yet !" )
}

/* 
	ADDI 
	opcode = 0x13 
	func   = 0 
				imm		   rs    f	  rd   opcode
 	ADDI   b????????????   ????? 000 ????? 0010011"
	ADDI 	0000 0000 0000 00001 000 00010 0010011  = 0x00008113,
	ADDI 	0000 0000 0000 00010 000 00011 0010011	= 0x00010193,
	ADDI 	0000 0000 0000 00011 000 00100 0010011  = 0x00018213,
	ADDI 	0000 0000 1000 00100 000 00100 0010011  = 0x00820293,
	
	ADDI 	0000 0000 0000 0000 1000  0001 0001 0011 = 0x00008113 
	
	
*/