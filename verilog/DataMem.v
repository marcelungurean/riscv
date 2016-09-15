module DataMem(input clk,
    input [9:0] io_addr,
    input [31:0] io_wr_data,
    input [1:0] io_mem_func,
    input  io_mem_en,
    output[31:0] io_rd_data
);

  wire[31:0] T0;
  wire[31:0] T1;
  reg [31:0] mem [1023:0];
  wire[31:0] T2;
  wire T3;
  wire T4;
  wire T5;
  wire T6;

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

  assign io_rd_data = T0;
  assign T0 = T5 ? T1 : 32'h0;
  assign T1 = mem[io_addr];
  assign T3 = io_mem_en & T4;
  assign T4 = io_mem_func == 2'h1;
  assign T5 = io_mem_en & T6;
  assign T6 = io_mem_func == 2'h0;

  always @(posedge clk) begin
    if (T3)
      mem[io_addr] <= io_wr_data;
  end
endmodule

