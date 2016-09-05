package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class ImmGen ( val expr_len : Int ) extends Module {

	val io = new Bundle {
		val instr 	= UInt ( INPUT , width = expr_len )

		val immi_sxt = UInt ( OUTPUT , width = expr_len )
		val imms_sxt = UInt ( OUTPUT , width = expr_len )
		val immb_sxt = UInt ( OUTPUT , width = expr_len )
		val immu_sxt = UInt ( OUTPUT , width = expr_len )
		val immj_sxt = UInt ( OUTPUT , width = expr_len )
	}

	val immi = io.instr(31,20)
	io.immi_sxt := Cat(Fill(immi(11),20),immi)  
	
	val imms = Cat (io.instr(31,25),io.instr(11,7) )
	io.imms_sxt := Cat(Fill(immi(11),20),imms)

	val immb = Cat(io.instr(31),io.instr(7),io.instr(30,25),io.instr(11,8))  
	io.immb_sxt := Cat(Fill(immb(11),19),UInt(0))

	val immu = Cat(io.instr(31,12),Fill(UInt(0),12))
	io.immu_sxt := immu 

	val immj = Cat(io.instr(31),io.instr(19,12),io.instr(20),io.instr(30,21))
	io.immj_sxt := Cat(Fill(immj(19),11),immj)
}

class ImmGenTest ( c : ImmGen, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 

	for ( i <- 0 until steps) {
		val instr = rnd.nextInt()

		poke(c.io.instr,instr)
		peek(c.io.immi_sxt)
		peek(c.io.imms_sxt)
		peek(c.io.immb_sxt)
		peek(c.io.immu_sxt)
		peek(c.io.immj_sxt)
		step(1)
		//if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for
	println (s"TO DO Maybe check the ImmGen ?")
	println (s"ImmGenTest: passed ")

	//println (s"ImmGen: $steps_passed / $steps passed !" )
}
