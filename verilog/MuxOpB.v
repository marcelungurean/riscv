module MuxOpB(
    input [1:0] io_opb_sel,
    input [31:0] io_opb_rsb,
    input [31:0] io_opb_imi,
    input [31:0] io_opb_ims,
    input [31:0] io_opb_pc,
    output[31:0] io_opb_alu_in
);

  wire[31:0] mux_out;
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


  assign io_opb_alu_in = mux_out;
  assign mux_out = T0;
  assign T0 = T11 ? T10 : T1;
  assign T1 = T9 ? T8 : T2;
  assign T2 = T7 ? T6 : T3;
  assign T3 = T5 ? T4 : 32'h0;
  assign T4 = io_opb_pc;
  assign T5 = io_opb_sel == 2'h1;
  assign T6 = io_opb_ims;
  assign T7 = io_opb_sel == 2'h3;
  assign T8 = io_opb_imi;
  assign T9 = io_opb_sel == 2'h2;
  assign T10 = io_opb_rsb;
  assign T11 = io_opb_sel == 2'h0;
endmodule

