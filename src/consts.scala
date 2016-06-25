package MDRisc 
package constants { 

import Chisel._ 
import Node._

trait OpConstants {
val Y	= Bool (true) 
val	N 	= Bool (false) 

// ALU op signals 
val ALU_OP_WIDTH = 4 

val ALU_ADD = UInt (1 , 4)
val ALU_SUB = UInt (2 , 4)
val ALU_AND = UInt (3 , 4)
val ALU_OR	= UInt (4 , 4)
val ALU_XOR = UInt (5 , 4)
val ALU_SLT = UInt (6 , 4)
val ALU_SLTU = UInt (7 , 4)
val ALU_SLL = UInt (8 , 4)
val ALU_SRL = UInt (9 , 4)
val ALU_SRA = UInt (10 , 4)
val ALU_COPYA = UInt (11, 4)
val ALU_X = UInt (0 , 4)
} 
}