package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class MuxOpB ( val expr_len : Int ) extends Module { 

	val io = new Bundle { 
		val opb_sel = UInt ( INPUT , 2)
		val opb_rsb = UInt ( INPUT , width = expr_len )
		val opb_imi = UInt ( INPUT , width = expr_len )
		val opb_ims	= UInt ( INPUT , width = expr_len )
		val opb_pc	= UInt ( INPUT , width = expr_len )

		val opb_alu_in = UInt ( OUTPUT , width = expr_len)
	}

	val mux_out = UInt (width=expr_len)

	mux_out := MuxCase (OPB_X, Array (
					(io.opb_sel === OPB_RSB)	-> io.opb_rsb.toUInt,
					(io.opb_sel === OPB_IMI)	-> io.opb_imi.toUInt,
					(io.opb_sel	=== OPB_IMS) 	-> io.opb_ims.toUInt,
					(io.opb_sel === OPB_PC)		-> io.opb_pc.toUInt
					)) 
	
	io.opb_alu_in := mux_out 
}

class MuxOpBTest (c:MuxOpB, val steps:Int ) extends Tester (c) {

	var steps_passed	= 0 

	for ( i <- 0 until steps) {
		val sel = rnd.nextInt(4)
		val rsb = rnd.nextInt()
		val imi = rnd.nextInt() 
		val ims = rnd.nextInt()
		val pc  = rnd.nextInt() 
		poke(c.io.opb_sel,sel)
		poke(c.io.opb_rsb,rsb)
		poke(c.io.opb_imi,imi)
		poke(c.io.opb_ims,ims)
		poke(c.io.opb_pc ,pc )
		step(1)
		val exp_out =	if ( sel == int(OPB_RSB) ) { rsb }
				   else if ( sel == int(OPB_IMI) ) { imi }
				   else if ( sel == int(OPB_IMS) ) { ims }
				   else if ( sel == int(OPB_PC)  ) { pc  }
				   else { 0 }
		if ( expect (c.io.opb_alu_in, exp_out) ) steps_passed += 1
	}//for
	println (s"MuxOpATest: $steps_passed / $steps passed !" )
}