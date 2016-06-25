package MDRisc {

import Chisel._ 
import Node._ 

import Constants._ 

class Alu ( val w: Int ) extends Module {

	val io = new Bundle { 
		val a 	= UInt (INPUT , width=w )
		val b  	= UInt (INPUT , width=w )
		val op 	= UInt (INPUT , ALU_OP_WIDTH )
		val out  = UInt (dir = OUTPUT , width=w)
		val zero = UInt (dir = OUTPUT , width=1 )
	}

	val alu_out = UInt (width=w)
	val alu_shamt = io.b(4,0).toUInt  

	alu_out := MuxCase (ALU_X, Array (
					(io.op === ALU_ADD)	->	(io.a + io.b).toUInt,							//adition 
					(io.op === ALU_SUB) -> 	(io.a - io.b).toUInt,							//substraction
					(io.op === ALU_AND) -> 	(io.a & io.b).toUInt,							
					(io.op === ALU_OR ) -> 	(io.a | io.b).toUInt,
					(io.op === ALU_XOR) ->  (io.a ^ io.b).toUInt,
					(io.op === ALU_SLT) ->  (io.a.toSInt < io.b.toSInt).toUInt,		// set less than (signed)
					(io.op === ALU_SLTU)-> 	(io.a < io.b).toUInt,					// set less than (unsigned) 
					(io.op === ALU_SLL) ->  ((io.a << alu_shamt)(w-1,0)).toUInt,	// shift 
					(io.op === ALU_SRL) -> 	(io.a >> alu_shamt).toUInt,
					(io.op === ALU_SRA) ->  (io.a.toSInt >> alu_shamt).toUInt,
					(io.op === ALU_COPYA)-> io.a 
					))

	io.out := alu_out 
	when (!io.out) { io.zero := UInt (1,1) }
	.otherwise (io.zero := UInt(0,1))

} // end Alu 

class AluTest (c:Alu) extends Tester (c) {
	var steps_cnt 		= 0 
	var steps_passed	= 0 

	for ( j <- 0 until 100) {
		val rnd0 = -1
		val rnd1 = -1//rnd.nextInt()
		val i 	 = rnd.nextInt(12)
		println("")
		poke(c.io.a,rnd0)
		poke(c.io.b,rnd1)
		poke(c.io.op, i )
		step(1)
		val rnd1_shamt = if ( rnd1 % 32 < 0 ) { ( rnd1 % 32 ) + 32 } else { rnd1 % 32 }
		println (rnd0)
		println (rnd1)
		println (rnd1_shamt)

		val result = if (int(i) == int(ALU_ADD)) 	{int(rnd0 + rnd1) }
				else if (int(i) == int(ALU_SUB)) 	{int(rnd0 - rnd1) }
				else if (int(i) == int(ALU_AND)) 	{int(rnd0 & rnd1) }
				else if (int(i) == int(ALU_OR)) 	{int(rnd0 | rnd1) }
				else if (int(i) == int(ALU_XOR)) 	{int(rnd0 ^ rnd1) }
				else if (int(i) == int(ALU_SLT))  	{int(rnd0 < rnd1) }
				else if (int(i) == int(ALU_SLTU)) 	{int(int(rnd0) < int(rnd1)) }
				else if (int(i) == int(ALU_SLL)) 	{int(rnd0 <<  rnd1_shamt) }
				else if (int(i) == int(ALU_SRL)) 	{int(rnd0 >>> rnd1_shamt ) } 			// Evrika !! Beware ... Headaches ahead.
				else if (int(i) == int(ALU_SRA)) 	{int(rnd0 >>  rnd1_shamt) }
				else if (int(i) ==	int(ALU_COPYA)) 	{int(rnd0) }
				else { int(ALU_X) }
		if ( expect (c.io.out.toBits,result) ) steps_passed += 1 
		val zero_exp = if (result == 0) 1 else 0
		expect (c.io.zero, zero_exp)
		steps_cnt += 1 
	}//for j 
	println (s"AluTest: $steps_passed / $steps_cnt passed !" )
}

}