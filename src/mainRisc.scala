package MDRisc

import Chisel._
import Node._

object mainRisc {
  def main(args: Array[String]): Unit = { 
  	var tests_passed 	= 0 
  	var tests_cnt 		= 3 
  	val steps 			= 20 
  	val expr_len 		= 32 
  	val cArgs 	= s"$args(0) --backend c --targetDir ../emulator --compile --test --genHarness".split(" ")
  	val vArgs 	= s"$args(0) --backend v --targetDir ../verilog --genHarness".split(" ")

    var runArgs = args.slice(1, args.length) 
    runArgs = 	if ( args(1) == "c") {cArgs.slice(1,cArgs.length)} 
    	   else if ( args(1) == "v") {vArgs.slice(1,vArgs.length)}
    	   else {cArgs.slice(1,cArgs.length)}
    args(0) match {
    	 case "Alu"      => chiselMainTest(runArgs, () => Module(new Alu(32) 	)	){ c => new AluTest(c,steps)}
    	 case "MuxOpA"   => chiselMainTest(runArgs, () => Module(new MuxOpA(32)	)	){ c => new MuxOpATest(c,steps)}
    	 case "MuxOpB" 	 => chiselMainTest(runArgs, () => Module(new MuxOpB(32)  )	){ c => new MuxOpBTest(c,steps)}
    	 case "RegFile"	 => chiselMainTest(runArgs, () => Module(new RegFile(5,32) )	){ c => new RegFileTest(c,steps)}
    	 case "MuxPC" 	 => chiselMainTest(runArgs, () => Module(new MuxPC(32) )		){ c => new MuxPCTest(c,steps)}
    	 case "MuxWB"    => chiselMainTest(runArgs, () => Module(new MuxWB(32) )		){ c => new MuxWBTest(c,steps)}
    	 case "ImmGen"   => chiselMainTest(runArgs, () => Module(new ImmGen(32) )	){ c => new ImmGenTest(c,steps)}
    	 case "Decoder"  => chiselMainTest(runArgs, () => Module(new Decoder(32) ) ){ c => new DecoderTest(c,steps)}
       case "all"		   => {	
    					chiselMainTest(runArgs, () => Module(new Alu(32) 	)	){ c => new AluTest(c,steps)}
   						chiselMainTest(runArgs, () => Module(new MuxOpA(32)	)	){ c => new MuxOpATest(c,steps)} 
    					chiselMainTest(runArgs, () => Module(new MuxOpB(32) )	){ c => new MuxOpBTest(c,steps)}
    					chiselMainTest(runArgs, () => Module(new RegFile(5,32) )){ c => new RegFileTest(c,100)}
    					chiselMainTest(runArgs, () => Module(new MuxPC(32) )	){ c => new MuxPCTest(c,steps)}
    	}
    }
    println (s" $tests_passed / $tests_cnt tests PASSED !" )
  }
}