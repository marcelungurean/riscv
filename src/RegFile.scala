package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class RegFile ( val	 addrw : Int , val expr_len : Int ) extends Module {

	val io = new Bundle { 
		val rf_ra1 	= UInt ( INPUT , width = addrw)		// read address for $rs1 
		val rf_ra2 	= UInt ( INPUT , width = addrw)		// read address for $rs2 
		val rf_wa 	= UInt ( INPUT , width = addrw)		// write address 
		val rf_wen 	= Bool ( INPUT )			// write enable 
		val rf_wd 	= UInt ( INPUT , width = expr_len)	// write data 

		val rf_rd1 	= UInt ( OUTPUT , width = expr_len) 	// read data from reg $rs1 
		val rf_rd2 	= UInt ( OUTPUT , width = expr_len)	// read data from reg $rs2 

	}

	val rf_reg_file = Mem ( Bits ( width = expr_len) , 32 )

	// read from rf 
	io.rf_rd1 := Mux ( ( io.rf_ra1 != UInt (0) ), 
							rf_reg_file(io.rf_ra1 ), 
							UInt (0, expr_len) )
	
	io.rf_rd2 := Mux ( ( io.rf_ra2 != UInt (0) ),
							rf_reg_file(io.rf_ra2 ),
							UInt (0, expr_len) )
	// write to rf  

	when ( (io.rf_wen) && (io.rf_wa != UInt(0) )) {      	// will need to add condition for csr exception 
		rf_reg_file (io.rf_wa) := io.rf_wd   
	}

}

class RegFileTest (c : RegFile, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 

	var regs = new Array[Int]( 1 << c.addrw )
	// write regs 
	for (i <- 0 until 32) {
		regs(i) = rnd.nextInt()
		poke(c.io.rf_wa,i)
		poke(c.io.rf_wd,regs(i))
		poke(c.io.rf_wen,1 )
		step(1)
	}
	// read regs
	for (i <- 0 until 32) {
		poke(c.io.rf_ra1,i)
		poke(c.io.rf_ra2,i)

		if ( i!=0 ) { 
			expect(c.io.rf_rd1,regs(i))
			expect(c.io.rf_rd2,regs(i))
		} else {
			expect(c.io.rf_rd1,0)
			expect(c.io.rf_rd2,0)
		}
		step(1)
	}

	for ( i <- 0 until steps ) {
		if ( rnd.nextInt % 2 == 0 ) { 
			// put random value at random register 
			val x = rnd.nextInt(32) 
			regs(x) = rnd.nextInt()
			poke(c.io.rf_wa,x)
			poke(c.io.rf_wd,regs(x))
			poke(c.io.rf_wen,1 )
			step(1)
		} else {
			val x = rnd.nextInt(32)
			val y = rnd.nextInt(32)
			poke(c.io.rf_ra1,x)
			poke(c.io.rf_ra2,y)
			if ( x!=0 ) { 
				if(expect(c.io.rf_rd1,regs(x))) steps_passed += 1
			} else {
				if(expect(c.io.rf_rd1,0))		steps_passed += 1
			}
			if ( y!=0 ) { 
				if(expect(c.io.rf_rd2,regs(y)))	steps_passed += 1
			} else {
				if(expect(c.io.rf_rd2,0))		steps_passed += 1
			}
		step(1)
		}
	}//for  

	println (s"RegFileTest: $steps_passed / $steps passed !" )
1}
