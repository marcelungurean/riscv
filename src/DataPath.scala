package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class Core ( val addrw : Int , val expr_len : Int ) extends Module { 
	val io = new Bundle {

		val mux_pc			= new MuxPC 	( expr_len )
		
		// val instr_mem	= new IntructionMem 
		
		val register_file 	= new RegFile 	( addrw , expr_len )
		val imm_generator 	= new ImmGen 	( expr_len )
		val decoder 		= new Decoder 	( expr_len )

		val mux_op_a 		= new MuxOpA 	( expr_len )
		val mux_op_b 		= new MuxOpB 	( expr_len )

		val alu 			= new Alu 		( expr_len )

		// val data_mem 	= new DataMem 

		val mux_wb 			= new MuxWB 	( expr_len )

		val br_logic 		= new BranchLogic (expr_len) 
	}

	// Data Path 

	// Pipeline Registers 
	val fetch_pc_reg 		= Reg (init=UInt(0,expr_len))

	val exec_pc_reg 		= Reg (init=UInt(0,expr_len))
	val exec_pc4_reg		= Reg (init=UInt(0,expr_len))
	val exec_instr_reg 		= Reg (init=BUBBLE )

	// Fetching Stage 
	
	// TODO add stall after memory implementation 
	when (stall != UInt(0) ) { 
		fetch_pc_reg 		:= 	io.mux_pc.io.pc_out
	}
	val fetch_pc4_reg		= (fetch_pc_reg + (UInt(4,expr_len)))

	io.instr_mem.addr 		:= fetch_pc_reg
	val fetch_instr 		=  io.instr_mem.data 

	when (stall == UInt(1) ) { 
		exec_instr_reg 	:= exec_instr_reg
		exec_pc_reg 	:= exec_pc_reg
	} .elsewhen (kill == UInt(1)) {
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
	io.register_file.io.rf_wd 	:= rd_data
	io.register_file.io.rf_wen 	:= io.decoder.ctl_rf_wen 

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
	io.mux_op_b.io.opb_ims	:= io.imm_generator.io.immz_sxt 
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
	io.mux_wb.io.wb_mem		:= io.data_mem.rdata 

	//Branch Cond Generator 

	//io.br_logic.io.excp 	:= 
	io.br_logic.io.ctl_br_type := io.decoder.io.ctl_br_type
	io.br_logic.io.br_eq 	:= ( rsa_data === rsb_data ) 
	io.br_logic.io.br_lt	:= ( rsa_data.toSInt < rsb_data.toSInt )
	io.br_logic.io.br_ltu	:= ( rsa_data.toUInt < rsb_data.toUInt )

	// Calculate Branch/Jump Target by adding the offset
	val exec_pc_br 	= exec_pc_reg + io.imm_generator.io.immb_sxt 
	val exec_pc_jmp = exec_pc_reg + io.imm_generator.io.immj_sxt
	val exec_pc_jalr= (rsa_data.UInt + io.imm_generator.io.immi_sxt) 
	io.mux_pc.io.pc_sel 	:= io.br_logic.io.pc_sel
	io.mux_pc.io.pc_pc4		:= fetch_pc4_reg
	io.mux_pc.io.pc_br 		:= exec_pc_br
	io.mux_pc.io.pc_jmp		:= exec_pc_jmp 
	io.mux_pc.io.pc_jalr 	:= exec_pc_jalr
	io.mux_pc.io.pc_excp 	:= UInt(0)  			//TODO CSr


	// Control Path 
	val stall = 0 // for now 
}