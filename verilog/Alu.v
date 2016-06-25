module Alu(
    input [31:0] io_a,
    input [31:0] io_b,
    input [3:0] io_op,
    output[31:0] io_out,
    output io_zero
);

  wire T0;
  wire T1;
  wire[31:0] alu_out;
  wire[31:0] T2;
  wire[31:0] T3;
  wire[31:0] T4;
  wire[31:0] T5;
  wire[31:0] T6;
  wire[31:0] T7;
  wire[31:0] T8;
  wire[31:0] T9;
  wire[31:0] T10;
  wire[31:0] T11;
  wire[31:0] T12;
  wire T13;
  wire[31:0] T14;
  wire[31:0] T15;
  wire[4:0] alu_shamt;
  wire[4:0] T16;
  wire[31:0] T17;
  wire T18;
  wire[31:0] T19;
  wire[31:0] T20;
  wire T21;
  wire[31:0] T22;
  wire[31:0] T23;
  wire[62:0] T24;
  wire T25;
  wire[31:0] T49;
  wire T26;
  wire T27;
  wire T28;
  wire[31:0] T50;
  wire T29;
  wire T30;
  wire[31:0] T31;
  wire[31:0] T32;
  wire T33;
  wire[31:0] T34;
  wire[31:0] T35;
  wire T36;
  wire[31:0] T37;
  wire[31:0] T38;
  wire T39;
  wire[31:0] T40;
  wire[31:0] T41;
  wire T42;
  wire[31:0] T43;
  wire[31:0] T44;
  wire T45;
  wire[31:0] T46;
  wire[31:0] T47;
  wire T48;


  assign io_zero = T0;
  assign T0 = T1 ? 1'h1 : 1'h0;
  assign T1 = io_out == 32'h0;
  assign io_out = alu_out;
  assign alu_out = T2;
  assign T2 = T48 ? T46 : T3;
  assign T3 = T45 ? T43 : T4;
  assign T4 = T42 ? T40 : T5;
  assign T5 = T39 ? T37 : T6;
  assign T6 = T36 ? T34 : T7;
  assign T7 = T33 ? T50 : T8;
  assign T8 = T28 ? T49 : T9;
  assign T9 = T25 ? T22 : T10;
  assign T10 = T21 ? T19 : T11;
  assign T11 = T18 ? T14 : T12;
  assign T12 = T13 ? io_a : 32'h0;
  assign T13 = io_op == 4'hb;
  assign T14 = T15;
  assign T15 = $signed(T17) >>> alu_shamt;
  assign alu_shamt = T16;
  assign T16 = io_b[4:0];
  assign T17 = io_a;
  assign T18 = io_op == 4'ha;
  assign T19 = T20;
  assign T20 = io_a >> alu_shamt;
  assign T21 = io_op == 4'h9;
  assign T22 = T23;
  assign T23 = T24[31:0];
  assign T24 = io_a << alu_shamt;
  assign T25 = io_op == 4'h8;
  assign T49 = {31'h0, T26};
  assign T26 = T27;
  assign T27 = io_a < io_b;
  assign T28 = io_op == 4'h7;
  assign T50 = {31'h0, T29};
  assign T29 = T30;
  assign T30 = $signed(T32) < $signed(T31);
  assign T31 = io_b;
  assign T32 = io_a;
  assign T33 = io_op == 4'h6;
  assign T34 = T35;
  assign T35 = io_a ^ io_b;
  assign T36 = io_op == 4'h5;
  assign T37 = T38;
  assign T38 = io_a | io_b;
  assign T39 = io_op == 4'h4;
  assign T40 = T41;
  assign T41 = io_a & io_b;
  assign T42 = io_op == 4'h3;
  assign T43 = T44;
  assign T44 = io_a - io_b;
  assign T45 = io_op == 4'h2;
  assign T46 = T47;
  assign T47 = io_a + io_b;
  assign T48 = io_op == 4'h1;
endmodule
