package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class MuxWB ( val expr_len : Int ) extends Module {

		val io = new Bundle { 
		val wb_sel 	= UInt ( INPUT , 2)
		val wb_alu 	= UInt ( INPUT , width = expr_len )
		val wb_pc4 	= UInt ( INPUT , width = expr_len )
		val wb_csr	= UInt ( INPUT , width = expr_len )
		val wb_mem	= UInt ( INPUT , width = expr_len )

		val wb_wd = UInt ( OUTPUT , width = expr_len)
	}
		io.wb_wd := MuxCase ( WB_X , Array ( 
					(io.wb_sel === WB_ALU) 		-> io.wb_alu.toUInt, 
					(io.wb_sel === WB_PC4) 		-> io.wb_pc4.toUInt,
					(io.wb_sel === WB_CSR) 		-> io.wb_csr.toUInt,
					(io.wb_sel === WB_MEM) 	 	-> io.wb_mem.toUInt
					))
}

class MuxWBTest ( c : MuxWB, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 
	for ( i <- 0 until steps) {
		val sel = rnd.nextInt(4)
		val alu = rnd.nextInt()
		val pc4 = rnd.nextInt() 
		val csr = rnd.nextInt()
		val mem = rnd.nextInt() 

		poke(c.io.wb_sel,sel)
		poke(c.io.wb_alu,alu)
		poke(c.io.wb_pc4,pc4)
		poke(c.io.wb_csr,csr)
		poke(c.io.wb_mem,mem)

		step(1)
		val exp_out =	if ( sel == int(WB_ALU) ) { alu }
				   else if ( sel == int(WB_PC4) ) { pc4 }
				   else if ( sel == int(WB_CSR) ) { csr }
				   else if ( sel == int(WB_MEM) ) { mem }
				   else { 0 }
		if ( expect (c.io.wb_wd, exp_out) ) steps_passed += 1
	}//for
	println (s"MuxOpATest: $steps_passed / $steps passed !" )
}
