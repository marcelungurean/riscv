package MDRisc 
package constants { 

import Chisel._ 
import Node._

trait OpConstants {
val YES	= Bool (true) 
val	NO	= Bool (false) 

// ALU op signals 
val ALU_FUNC_WIDTH = 4 

val ALU_X 		= UInt (0 , ALU_FUNC_WIDTH)
val ALU_ADD		= UInt (1 , ALU_FUNC_WIDTH)
val ALU_SUB 	= UInt (2 , ALU_FUNC_WIDTH)
val ALU_AND 	= UInt (3 , ALU_FUNC_WIDTH)
val ALU_OR		= UInt (4 , ALU_FUNC_WIDTH)
val ALU_XOR 	= UInt (5 , ALU_FUNC_WIDTH)
val ALU_SLT 	= UInt (6 , ALU_FUNC_WIDTH)
val ALU_SLTU 	= UInt (7 , ALU_FUNC_WIDTH)
val ALU_SEQ 	= UInt (8 , ALU_FUNC_WIDTH)
val ALU_SNEQ 	= UInt (9 , ALU_FUNC_WIDTH)
val ALU_SGE 	= UInt (10 , ALU_FUNC_WIDTH) 
val ALU_SGEU 	= UInt (11 , ALU_FUNC_WIDTH)
val ALU_SLL 	= UInt (12 , ALU_FUNC_WIDTH)
val ALU_SRL 	= UInt (13 , ALU_FUNC_WIDTH)
val ALU_SRA 	= UInt (14 , ALU_FUNC_WIDTH)
val ALU_COPYA 	= UInt (15 , ALU_FUNC_WIDTH)

// OPA  - opa_sel
// ALU OPA & OPB 
val OPA_SEL_WIDTH = 2 
val OPA_RSA 	= UInt(0, OPA_SEL_WIDTH)
val OPA_IMU		= UInt(1, OPA_SEL_WIDTH) 	// immediate for U-type	
val	OPA_IMZ	 	= UInt(2, OPA_SEL_WIDTH)	// not used for now // zero-extended immediate for CSRI  
val OPA_X		= UInt(0, OPA_SEL_WIDTH)
// OPB  - opb_sel 
val OPB_SEL_WIDTH = 2 
val OPB_RSB 	= UInt(0, OPB_SEL_WIDTH) 	// 
val OPB_PC		= UInt(1, OPB_SEL_WIDTH)	// program counter 
val OPB_IMI		= UInt(2, OPB_SEL_WIDTH) 	// immediate for I-type		
val OPB_IMS		= UInt(3, OPB_SEL_WIDTH)	// immediate for S-type 
val OPB_X 		= UInt(0, OPB_SEL_WIDTH) 

// PC ins - pc_sel 
val PC_SEL_WIDTH = 3 
val PC_PC4		= UInt(0, PC_SEL_WIDTH)
val PC_JALR		= UInt(1, PC_SEL_WIDTH)
val PC_BR		= UInt(2, PC_SEL_WIDTH)
val PC_JMP		= UInt(3, PC_SEL_WIDTH)
val PC_EXCP		= UInt(4, PC_SEL_WIDTH)
val PC_X		= UInt(0, PC_SEL_WIDTH)

// write back 
val WB_SEL_WIDTH = 2 
val WB_ALU 		= UInt(0, WB_SEL_WIDTH)
val WB_CSR		= UInt(1, WB_SEL_WIDTH) 
val WB_PC4 		= UInt(2, WB_SEL_WIDTH) 
val WB_MEM		= UInt(3, WB_SEL_WIDTH)
val WB_X		= UInt(0, WB_SEL_WIDTH)

//  Register file write enable 
val RF_WEN_0	= Bool(false)
val RF_WEN_1	= Bool(true)
val RF_WEN_X	= Bool(false)

// Memory 
val MEM_EN_0	= Bool(false)
val MEM_EN_1	= Bool(true)
val MEM_EN_X 	= Bool(false) 	

val MEM_FUNC_WIDTH = 2 

val MEM_X 		= UInt(0, MEM_FUNC_WIDTH)
val MEM_RD 		= UInt(0, MEM_FUNC_WIDTH)
val MEM_WR 		= UInt(1, MEM_FUNC_WIDTH)
val MEM_FEN 	= UInt(2, MEM_FUNC_WIDTH)

val BR_SEL_WIDTH = 4 
val BR_NXT 		= UInt(0,BR_SEL_WIDTH)
val BR_EQ		= UInt(1,BR_SEL_WIDTH)
val BR_NEQ		= UInt(2,BR_SEL_WIDTH)
val BR_GE		= UInt(3,BR_SEL_WIDTH)
val BR_GEU 		= UInt(4,BR_SEL_WIDTH)
val BR_LT 		= UInt(5,BR_SEL_WIDTH)
val BR_LTU 		= UInt(6,BR_SEL_WIDTH)
val BR_J 		= UInt(7,BR_SEL_WIDTH)
val BR_JR		= UInt(8,BR_SEL_WIDTH)

val MEM_MSK_WIDTH = 3 
val MSK_B 		= UInt(0,MEM_MSK_WIDTH)
val	MSK_H 		= UInt(1,MEM_MSK_WIDTH)
val MSK_W 		= UInt(2,MEM_MSK_WIDTH)
val MSK_BU 		= UInt(3,MEM_MSK_WIDTH)
val MSK_HU 		= UInt(4,MEM_MSK_WIDTH)
val MSK_X 		= UInt(2,MEM_MSK_WIDTH)


val CSR_CMD_WIDTH = 3 
val CSR = UInt (0, CSR_CMD_WIDTH)

val BUBBLE  = Bits(0x4033, 32)

val RSA_MSB = 19 
val RSA_LSB = 15 
val RSB_MSB = 24
val RSB_LSB = 20 
val RD_MSB 	= 11 
val RD_LSB 	= 7 

} 

trait RVSpecConsts
}