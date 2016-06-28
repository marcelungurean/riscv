package MDRisc

import Chisel._ 
import Node._ 

import Constants._ 

class BranchLogic ( val expr_len : Int ) extends Module {

	val io = new Bundle { 
		val excp 		= Bool ( INPUT ) 
		val ctl_br_type	= UInt ( INPUT , BR_SEL_WIDTH )

		val br_eq 		= Bool ( INPUT )
		val br_lt 		= Bool ( INPUT )
		val br_ltu 		= Bool	(INPUT )  

		val pc_sel 		= UInt ( INPUT , PC_SEL_WIDTH )
	}

	io.pc_sel :=  Mux(io.excp, PC_EXCP, 
				Mux(io.ctl_br_type	===	BR_NXT		, PC_PC4	,
				Mux(io.ctl_br_type ===	BR_NEQ		, Mux(!io.br_eq,	PC_BR,	PC_PC4),
				Mux(io.ctl_br_type === BR_EQ   		, Mux( io.br_eq, 	PC_BR,  PC_PC4),
				Mux(io.ctl_br_type === BR_GE 	 	, Mux(!io.br_lt, 	PC_BR, 	PC_PC4),
				Mux(io.ctl_br_type === BR_GEU 		, Mux(!io.br_ltu, 	PC_BR,  PC_PC4),
				Mux(io.ctl_br_type === BR_LT 		, Mux( io.br_lt, 	PC_BR,  PC_PC4),
				Mux(io.ctl_br_type === BR_LTU 		, Mux( io.br_ltu, 	PC_BR,  PC_PC4),
				Mux(io.ctl_br_type === BR_J 		, PC_JMP 	,
				Mux(io.ctl_br_type === BR_JR 		, PC_JALR	, 	PC_PC4 ))))))))))

}