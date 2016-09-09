package MDRisc 

import Chisel._ 
import Node._ 

import Constants._ 

class InstrMemPortIo ( val addr_width : Int ,val data_width : Int ) extends Bundle {
	val addr 	= 	Bits ( INPUT  , width = addr_width )
	val data 	= 	Bits ( OUTPUT , width = data_width )
}

class InstructionMem ( val addr_width: Int , val data_width : Int ) extends Module {
	val io = new InstrMemPortIo ( addr_width , data_width )

	val mem = Mem (Bits ( width=data_width ) , 1024 )

	io.data := mem(io.addr) 
}	

class DataMemPortIo ( val addr_width : Int , val data_width : Int ) extends Bundle {

	val addr  		= Bits ( INPUT , addr_width )
	val wr_data	 	= Bits ( INPUT , data_width )
	val mem_func 	= UInt ( INPUT , MEM_FUNC_WIDTH)
	val mem_en 		= Bool ( INPUT )

	val rd_data 	= Bits ( OUTPUT , data_width )
}

class DataMem ( val addr_width: Int ,val data_width : Int ) extends Module {
	val io = new DataMemPortIo ( addr_width , data_width )
	val mem = Mem (Bits (width = data_width) , 1 << addr_width )

	io.rd_data := Mux ( ( io.mem_en && (io.mem_func === MEM_RD) ) , mem(io.addr), UInt(0x0,32) )
	
	when ( io.mem_en && ( io.mem_func === MEM_WR ) ) {
		mem(io.addr) := io.wr_data  
	}		
}
class InstructionMemTest ( c : InstructionMem, val steps : Int ) extends Tester (c) {
	var steps_passed	= 0 
	for ( i <- 0 until steps) {
		
		//if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for
	//println (s"InstructionMemTest: $steps_passed / $steps passed !" )
	println (s"InstructionMemTest: 0 / 0 passed !" )

}
class DataMemTest ( c : DataMem, val steps : Int ) extends Tester (c) {

	var steps_passed	= 0 

	for ( i <- 0 until steps) {
		
		//if ( expect (c.io.opa_alu_in, exp_out) ) steps_passed += 1
	}//for
	//println (s"DataMemTest: $steps_passed / $steps passed !" )
	println (s"DataMemTest: 0 / 0 passed !" )

}