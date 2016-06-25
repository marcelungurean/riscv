package MDRisc

import Chisel._
import Node._

object mainRisc {
  def main(args: Array[String]): Unit = { 
    val tutArgs = args.slice(1, args.length) 

        chiselMainTest(tutArgs, () => Module(new Alu(32))){
          c => new AluTest(c)}

  }
}