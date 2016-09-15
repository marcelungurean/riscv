module InstructionMem(input clk,
    input [9:0] io_addr,
    output[31:0] io_data
);

  wire[31:0] T0;
  reg [31:0] mem [1023:0];

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    for (initvar = 0; initvar < 1024; initvar = initvar+1)
      mem[initvar] = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_data = T0;
  assign T0 = mem[io_addr];
endmodule

