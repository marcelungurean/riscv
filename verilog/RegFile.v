module RegFile(input clk,
    input [4:0] io_rf_ra1,
    input [4:0] io_rf_ra2,
    input [4:0] io_rf_wa,
    input  io_rf_wen,
    input [31:0] io_rf_wd,
    output[31:0] io_rf_rd1,
    output[31:0] io_rf_rd2
);

  wire[31:0] T0;
  wire[31:0] T1;
  reg [31:0] rf_reg_file [31:0];
  wire[31:0] T2;
  wire T3;
  wire T4;
  wire T5;
  wire[31:0] T6;
  wire[31:0] T7;
  wire T8;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    for (initvar = 0; initvar < 32; initvar = initvar+1)
      rf_reg_file[initvar] = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_rf_rd2 = T0;
  assign T0 = T5 ? T1 : 32'h0;
  assign T1 = rf_reg_file[io_rf_ra2];
  assign T3 = io_rf_wen & T4;
  assign T4 = io_rf_wa != 5'h0;
  assign T5 = io_rf_ra2 != 5'h0;
  assign io_rf_rd1 = T6;
  assign T6 = T8 ? T7 : 32'h0;
  assign T7 = rf_reg_file[io_rf_ra1];
  assign T8 = io_rf_ra1 != 5'h0;

  always @(posedge clk) begin
    if (T3)
      rf_reg_file[io_rf_wa] <= io_rf_wd;
  end
endmodule

