module MuxPC(
    input [2:0] io_pc_sel,
    input [31:0] io_pc_pc4,
    input [31:0] io_pc_jalr,
    input [31:0] io_pc_br,
    input [31:0] io_pc_jmp,
    input [31:0] io_pc_excp,
    output[31:0] io_pc_out
);

  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  wire[31:0] T3;
  wire[31:0] T4;
  wire[31:0] T5;
  wire T6;
  wire[31:0] T7;
  wire T8;
  wire[31:0] T9;
  wire T10;
  wire[31:0] T11;
  wire T12;
  wire[31:0] T13;
  wire T14;


  assign io_pc_out = T0;
  assign T0 = T14 ? T13 : T1;
  assign T1 = T12 ? T11 : T2;
  assign T2 = T10 ? T9 : T3;
  assign T3 = T8 ? T7 : T4;
  assign T4 = T6 ? T5 : 32'h0;
  assign T5 = io_pc_excp;
  assign T6 = io_pc_sel == 3'h4;
  assign T7 = io_pc_jmp;
  assign T8 = io_pc_sel == 3'h3;
  assign T9 = io_pc_br;
  assign T10 = io_pc_sel == 3'h2;
  assign T11 = io_pc_jalr;
  assign T12 = io_pc_sel == 3'h1;
  assign T13 = io_pc_pc4;
  assign T14 = io_pc_sel == 3'h0;
endmodule

