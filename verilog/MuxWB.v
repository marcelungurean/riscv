module MuxWB(
    input [1:0] io_wb_sel,
    input [31:0] io_wb_alu,
    input [31:0] io_wb_pc4,
    input [31:0] io_wb_csr,
    input [31:0] io_wb_mem,
    output[31:0] io_wb_wd
);

  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  wire[31:0] T3;
  wire[31:0] T4;
  wire T5;
  wire[31:0] T6;
  wire T7;
  wire[31:0] T8;
  wire T9;
  wire[31:0] T10;
  wire T11;


  assign io_wb_wd = T0;
  assign T0 = T11 ? T10 : T1;
  assign T1 = T9 ? T8 : T2;
  assign T2 = T7 ? T6 : T3;
  assign T3 = T5 ? T4 : 32'h0;
  assign T4 = io_wb_mem;
  assign T5 = io_wb_sel == 2'h3;
  assign T6 = io_wb_csr;
  assign T7 = io_wb_sel == 2'h1;
  assign T8 = io_wb_pc4;
  assign T9 = io_wb_sel == 2'h2;
  assign T10 = io_wb_alu;
  assign T11 = io_wb_sel == 2'h0;
endmodule

