module MuxOpA(
    input [1:0] io_opa_sel,
    input [31:0] io_opa_rsa,
    input [31:0] io_opa_imz,
    input [31:0] io_opa_imu,
    output[31:0] io_opa_alu_in
);

  wire[31:0] mux_out;
  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  wire[31:0] T3;
  wire T4;
  wire[31:0] T5;
  wire T6;
  wire[31:0] T7;
  wire T8;


  assign io_opa_alu_in = mux_out;
  assign mux_out = T0;
  assign T0 = T8 ? T7 : T1;
  assign T1 = T6 ? T5 : T2;
  assign T2 = T4 ? T3 : 32'h0;
  assign T3 = io_opa_imz;
  assign T4 = io_opa_sel == 2'h2;
  assign T5 = io_opa_imu;
  assign T6 = io_opa_sel == 2'h1;
  assign T7 = io_opa_rsa;
  assign T8 = io_opa_sel == 2'h0;
endmodule

