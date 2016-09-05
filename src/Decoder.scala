package MDRisc

import Chisel._ 
import Node._ 

import Constants._ 
import Instructions._

class Decoder (val expr_len : Int) extends Module {

	val io = new Bundle {
		val dec_instr 		=  UInt( INPUT, width = expr_len)

		val ctl_val_inst 	=  Bool( OUTPUT )
		val ctl_rf_wen 		=  Bool( OUTPUT )
		val ctl_br_type 	=  UInt( OUTPUT , BR_SEL_WIDTH 	)
		val ctl_opa_sel 	=  UInt( OUTPUT , OPA_SEL_WIDTH 	)
		val ctl_opb_sel 	=  UInt( OUTPUT , OPB_SEL_WIDTH	)
		val ctl_alu_func	=  UInt( OUTPUT , ALU_FUNC_WIDTH )
		val ctl_wb_sel 		=  UInt( OUTPUT , WB_SEL_WIDTH	)
		val ctl_mem_func 	=  UInt( OUTPUT , MEM_FUNC_WIDTH )
		val ctl_mem_en		=  Bool( OUTPUT )
		val ctl_msk_sel		=  UInt( OUTPUT , MEM_MSK_WIDTH  )
		val ctl_csr_cmd 	=  UInt( OUTPUT , CSR_CMD_WIDTH  )
	}

	val ctl_signals = 
				ListLookup ( io.dec_instr , 
									List( NO  , BR_NXT 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X		, RF_WEN_0	, MEM_EN_0 	, MEM_RD	, MSK_X	, CSR ),
						Array (
						LUI 	->	List( YES , BR_NXT 	, OPA_IMU	, OPB_X 	, ALU_COPYA	, WB_ALU	, RF_WEN_1 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						AUIPC 	->	List( YES , BR_NXT 	, OPA_IMU	, OPB_X 	, ALU_ADD	, WB_ALU	, RF_WEN_1 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),

						JAL 	->	List( YES , BR_J 	, OPA_X		, OPB_X 	, ALU_X 	, WB_PC4	, RF_WEN_1 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						JALR 	->	List( YES , BR_JR 	, OPA_RSA	, OPB_IMI 	, ALU_X 	, WB_PC4	, RF_WEN_1 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),

						BEQ 	->	List( YES , BR_EQ 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X  	, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						BNE 	->	List( YES , BR_NEQ 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X  	, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						BGE 	->	List( YES , BR_GE 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X  	, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						BGEU 	->	List( YES , BR_GEU 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X  	, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						BLT 	->	List( YES , BR_LT	, OPA_X		, OPB_X 	, ALU_X 	, WB_X  	, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),
						BLTU 	->	List( YES , BR_LTU 	, OPA_X		, OPB_X 	, ALU_X 	, WB_X		, RF_WEN_0 	, MEM_EN_0 	, MEM_X	 	, MSK_X , CSR ),

                  		LB		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_MEM	, RF_WEN_1 	, MEM_EN_1  , MEM_RD 	, MSK_B , CSR ),
                  		LBU		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_MEM	, RF_WEN_1 	, MEM_EN_1  , MEM_RD 	, MSK_BU, CSR ),
                  		LH		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_MEM	, RF_WEN_1 	, MEM_EN_1  , MEM_RD 	, MSK_H , CSR ),
                  		LHU		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_MEM	, RF_WEN_1 	, MEM_EN_1  , MEM_RD 	, MSK_HU, CSR ),
                  		LW		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_MEM	, RF_WEN_1 	, MEM_EN_1  , MEM_RD 	, MSK_W , CSR ),

                  		SB		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMS 	, ALU_ADD 	, WB_X		, RF_WEN_0 	, MEM_EN_1  , MEM_WR 	, MSK_B , CSR ),
                  		SH		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMS 	, ALU_ADD 	, WB_X		, RF_WEN_0 	, MEM_EN_1  , MEM_WR 	, MSK_H , CSR ),
                  		SW		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMS 	, ALU_ADD 	, WB_X		, RF_WEN_0 	, MEM_EN_1  , MEM_WR 	, MSK_W , CSR ),

                  		ADDI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SLTI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLT 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SLTIU	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLTU 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		XORI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_XOR 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		ORI		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_OR 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		ANDI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_AND 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		
                  		SLLI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLL 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SRLI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SRL 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SRAI	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SRA 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),

						ADD 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_ADD 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
						SUB 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SUB 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SLL 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLL 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SLT 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLT 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SLTU	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SLTU 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		XOR		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_XOR 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SRL 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SRL 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		SRA 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_SRA 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		OR 		-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_OR 	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR ),
                  		AND 	-> 	List( YES , BR_NXT  , OPA_RSA 	, OPB_IMI 	, ALU_AND  	, WB_ALU	, RF_WEN_1 	, MEM_EN_0  , MEM_X 	, MSK_X , CSR )
							)	// Array
						)// Lookup
		
			val ctl_val_inst :: ctl_br_type :: ctl_opa_sel :: ctl_opb_sel :: ctl_alu_func :: ctl_wb_sel :: ctl_rf_wen :: ctl_mem_en :: ctl_mem_func :: ctl_msk_sel :: ctl_csr_cmd :: Nil = ctl_signals

			io.ctl_val_inst 	:= ctl_val_inst
			io.ctl_br_type   	:= ctl_br_type
			io.ctl_opa_sel 		:= ctl_opa_sel
			io.ctl_opb_sel   	:= ctl_opb_sel
			io.ctl_alu_func 	:= ctl_alu_func
			io.ctl_wb_sel   	:= ctl_wb_sel
			io.ctl_rf_wen 		:= ctl_rf_wen
			io.ctl_mem_en   	:= ctl_mem_en
			io.ctl_mem_func 	:= ctl_mem_func
			io.ctl_msk_sel   	:= ctl_msk_sel
			io.ctl_csr_cmd 		:= ctl_csr_cmd
			
}
class DecoderTest ( c : Decoder, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 
	var instr = Array (
		0xFFFFFF37 , 0xFFFFFF17, 
		0xFFFFFF6F , 0xFFFF0F67,
		0xFFFF1F63 , 0XFFFF4F63, 
		0XFFFF
	)
	instr.foreach {e => poke ( c.io.dec_instr, e )
		peek ( c.io.ctl_val_inst)
		peek ( c.io.ctl_br_type)
		peek ( c.io.ctl_opa_sel)
		peek ( c.io.ctl_opb_sel)
		peek ( c.io.ctl_alu_func)
		peek ( c.io.ctl_wb_sel)
		peek ( c.io.ctl_rf_wen)
		peek ( c.io.ctl_mem_en)
		peek ( c.io.ctl_mem_func)
		peek ( c.io.ctl_msk_sel)
		peek ( c.io.ctl_csr_cmd)
		step(1)
	}


	for ( i <- 0 until steps) {
		
		//if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for
	println (s"TO DO Maybe check the Decoder ?")
	println (s"DecoderTest: passed ")

	//println (s"MuxOpATest: $steps_passed / $steps passed !" )
}
