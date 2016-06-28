package MDRisc {

import Chisel._ 
import Node._ 

import Constants._ 

class MuxOpA ( val expr_len : Int ) extends Module { 

	val io = new Bundle { 
		val opa_sel = UInt ( INPUT , 2)
		val opa_rsa = UInt ( INPUT , width = expr_len )
		val opa_imz = UInt ( INPUT , width = expr_len )
		val opa_imu	= UInt ( INPUT , width = expr_len )

		val opa_alu_in = UInt ( OUTPUT , width = expr_len)
	}

	val mux_out = UInt (width=expr_len)

	mux_out := MuxCase (OPA_X, Array (
					(io.opa_sel === OPA_RSA)	-> io.opa_rsa.toUInt,
					(io.opa_sel === OPA_IMU)	-> io.opa_imu.toUInt,
					(io.opa_sel	=== OPA_IMZ) 	-> io.opa_imz.toUInt
					)) 

	io.opa_alu_in := mux_out 
}

class MuxOpATest ( c : MuxOpA, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 

	for ( i <- 0 until steps) {
		val sel = rnd.nextInt(4)
		val rsa = rnd.nextInt()
		val imu = rnd.nextInt() 
		val imz = rnd.nextInt() 
		poke(c.io.opa_sel,sel)
		poke(c.io.opa_rsa,rsa)
		poke(c.io.opa_imz,imz)
		poke(c.io.opa_imu,imu)
		step(1)
		val exp_out =	if ( sel == int(OPA_RSA) ) { rsa }
				   else if ( sel == int(OPA_IMU) ) { imu }
				   else if ( sel == int(OPA_IMZ) ) { imz }
				   else { 0 }
		if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for
	println (s"MuxOpATest: $steps_passed / $steps passed !" )
}

}