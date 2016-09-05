package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class MuxPC ( val expr_len : Int ) extends Module {
	val io = new Bundle { 
		val pc_sel 	= UInt ( INPUT , 3 )
		val pc_pc4 	= UInt ( INPUT , width = expr_len )
		val pc_jalr = UInt ( INPUT , width = expr_len )
		val pc_br	= UInt ( INPUT , width = expr_len )
		val pc_jmp  = UInt ( INPUT , width = expr_len )
		val pc_excp  = UInt ( INPUT , width = expr_len )

		val pc_out  = UInt ( OUTPUT , width = expr_len )
	}
	io.pc_out := MuxCase ( PC_X , Array ( 
					(io.pc_sel === PC_PC4) 		-> io.pc_pc4.toUInt, 
					(io.pc_sel === PC_JALR) 	-> io.pc_jalr.toUInt,
					(io.pc_sel === PC_BR) 		-> io.pc_br.toUInt,
					(io.pc_sel === PC_JMP) 		-> io.pc_jmp.toUInt,
					(io.pc_sel === PC_EXCP) 	-> io.pc_excp.toUInt
					))
}

class MuxPCTest ( c : MuxPC, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 

	for ( i <- 0 until steps) {
		val sel = rnd.nextInt(6)
		val pc4 = rnd.nextInt()
		val jalr = rnd.nextInt() 
		val br = rnd.nextInt()
		val jmp = rnd.nextInt() 
		val excp = rnd.nextInt() 

		poke(c.io.pc_sel,sel)
		poke(c.io.pc_pc4,pc4)
		poke(c.io.pc_jalr,jalr)
		poke(c.io.pc_br,br)
		poke(c.io.pc_jmp,jmp)
		poke(c.io.pc_excp,excp)

		step(1)
		val exp_out =	if ( sel == int(PC_PC4) ) { pc4 }
				   else if ( sel == int(PC_JALR) ){ jalr }
				   else if ( sel == int(PC_BR) )  { br }
				   else if ( sel == int(PC_JMP) ) { jmp }
				   else if ( sel == int(PC_EXCP) ) { excp }
				   else { 0 }
		if ( expect (c.io.pc_out, exp_out) ) steps_passed += 1
	}//for 
	println (s"MuxPCTest: $steps_passed / $steps passed !" )
}
