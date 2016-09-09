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

	var steps_passed = 0

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
	// 00110111
	// ???????????????? ?000 ???? ?110 0011
    // if ( (instr(0) & 0x37 ) == 0x37 ) println (s"LUI operation")
    // if ( (instr(1) & 0x17 ) == 0x17 ) println (s"AUIPC operation"


	instr.foreach { inst => 
 		if ( (inst & 0x7F ) == 0x37 )	   println (s"LUI operation")
    	else if ( (inst & 0x7F ) == 0x17 ) println (s"AUIPC operation")
    	else if ( (inst & 0x7F ) == 0x6F ) println (s"JAL operation")
    	else if ( (inst & 0x7F ) == 0x67 && ((inst >> 12) & 0x7) == 0) println (s"JALR operation")
    	
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 0) println (s"BEQ operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 1) println (s"BNE operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 4) println (s"BLT operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 5) println (s"BGE operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 6) println (s"BLTU operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 7) println (s"BGEU operation")

    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 0) println (s"LB operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 1) println (s"LH operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 2) println (s"LW operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 3) println (s"LD operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 4) println (s"LBU operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 5) println (s"LHU operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 6) println (s"LWU operation")

    	else if ( (inst & 0x7F ) == 0x23 && ((inst >> 12) & 0x7) == 0) println (s"SB operation")
    	else if ( (inst & 0x7F ) == 0x23 && ((inst >> 12) & 0x7) == 1) println (s"SH operation")
    	else if ( (inst & 0x7F ) == 0x23 && ((inst >> 12) & 0x7) == 2) println (s"SW operation")
    	else if ( (inst & 0x7F ) == 0x23 && ((inst >> 12) & 0x7) == 3) println (s"SD operation")

    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 0) println (s"ADDI operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 2) println (s"SLTI operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 3) println (s"SLTIU operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 4) println (s"XORI operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 6) println (s"ORI operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 7) println (s"ANDI operation")

    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 1 && ((inst >> 26) & 0x3F ) == 0x00 ) println (s"SLLI operation") 
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 5 && ((inst >> 26) & 0x3F ) == 0x00 ) println (s"SRLI operation")
    	else if ( (inst & 0x7F ) == 0x13 && ((inst >> 12) & 0x7) == 5 && ((inst >> 26) & 0x3F ) == 0x10 ) println (s"SRAI operation")

    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 0 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"ADD operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 0 && ((inst >> 25) & 0x7F ) == 0x40 ) println (s"SUB operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 1 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"SLL operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 2 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"SLT operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 3 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"SLTU operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 4 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"XOR operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 5 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"SRL operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 5 && ((inst >> 25) & 0x7F ) == 0x40 ) println (s"SRA operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 6 && ((inst >> 25) & 0x7F ) == 0x00 ) println (s"OR operation")
    	else if ( (inst & 0x7F ) == 0x33 && ((inst >> 12) & 0x7) == 7 && ((inst >> 26) & 0x7F ) == 0x00 ) println (s"AND operation")


    	else println (s"Unknown operation")
		poke ( c.io.dec_instr, inst )
		// peek ( c.io.ctl_val_inst)
		// peek ( c.io.ctl_br_type)
		// peek ( c.io.ctl_opa_sel)
		// peek ( c.io.ctl_opb_sel)
		// peek ( c.io.ctl_alu_func)
		// peek ( c.io.ctl_wb_sel)
		// peek ( c.io.ctl_rf_wen)
		// peek ( c.io.ctl_mem_en)
		// peek ( c.io.ctl_mem_func)
		// peek ( c.io.ctl_msk_sel)
		// peek ( c.io.ctl_csr_cmd)
		step(1)
	}

	for ( i <- 0 until steps) {
		var inst = rnd.nextInt() 
		if ( (inst & 0x7F ) == 0x37 )	   println (s"LUI operation")
    	else if ( (inst & 0x7F ) == 0x17 ) println (s"AUIPC operation")
    	else if ( (inst & 0x7F ) == 0x6F ) println (s"JAL operation")
    	else if ( (inst & 0x7F ) == 0x67 ) println (s"JALR operation")
    	
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 0) println (s"BEQ operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 1) println (s"BNE operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 4) println (s"BLT operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 5) println (s"BGE operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 6) println (s"BLTU operation")
    	else if ( (inst & 0x7F ) == 0x63 && ((inst >> 12) & 0x7) == 7) println (s"BGEU operation")

    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 0) println (s"LB operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 1) println (s"LH operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 2) println (s"LW operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 3) println (s"LD operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 4) println (s"LBU operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 5) println (s"LHU operation")
    	else if ( (inst & 0x7F ) == 0x03 && ((inst >> 12) & 0x7) == 6) println (s"LWU operation")

    	else println (s"Unknown operation")

		poke ( c.io.dec_instr, inst )
		// peek ( c.io.ctl_val_inst)
		// peek ( c.io.ctl_br_type)
		// peek ( c.io.ctl_opa_sel)
		// peek ( c.io.ctl_opb_sel)
		// peek ( c.io.ctl_alu_func)
		// peek ( c.io.ctl_wb_sel)
		// peek ( c.io.ctl_rf_wen)
		// peek ( c.io.ctl_mem_en)
		// peek ( c.io.ctl_mem_func)
		// peek ( c.io.ctl_msk_sel)
		// peek ( c.io.ctl_csr_cmd)
		step(1)
		//if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for

	println (s"TO DO Maybe check the Decoder ?")
	println (s"DecoderTest: passed ")

	//println (s"MuxOpATest: $steps_passed / $steps passed !" )
}
