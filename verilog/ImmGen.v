module ImmGen(
    input [31:0] io_instr,
    output[31:0] io_immi_sxt,
    output[31:0] io_imms_sxt,
    output[31:0] io_immb_sxt,
    output[31:0] io_immu_sxt,
    output[31:0] io_immj_sxt
);

  wire[31:0] T27;
  wire[30:0] T0;
  wire[19:0] immj;
  wire[10:0] T1;
  wire[9:0] T2;
  wire T3;
  wire[8:0] T4;
  wire[7:0] T5;
  wire T6;
  wire[10:0] T7;
  wire T8;
  wire[31:0] immu;
  wire[19:0] T9;
  wire[31:0] T28;
  wire[19:0] T10;
  wire[18:0] T11;
  wire T12;
  wire[11:0] immb;
  wire[9:0] T13;
  wire[3:0] T14;
  wire[5:0] T15;
  wire[1:0] T16;
  wire T17;
  wire T18;
  wire[31:0] T19;
  wire[11:0] imms;
  wire[4:0] T20;
  wire[6:0] T21;
  wire[19:0] T22;
  wire T23;
  wire[11:0] immi;
  wire[31:0] T24;
  wire[19:0] T25;
  wire T26;


  assign io_immj_sxt = T27;
  assign T27 = {1'h0, T0};
  assign T0 = {T7, immj};
  assign immj = {T4, T1};
  assign T1 = {T3, T2};
  assign T2 = io_instr[30:21];
  assign T3 = io_instr[20];
  assign T4 = {T6, T5};
  assign T5 = io_instr[19:12];
  assign T6 = io_instr[31];
  assign T7 = T8 ? 11'h7ff : 11'h0;
  assign T8 = immj[19];
  assign io_immu_sxt = immu;
  assign immu = {T9, 12'h0};
  assign T9 = io_instr[31:12];
  assign io_immb_sxt = T28;
  assign T28 = {12'h0, T10};
  assign T10 = {T11, 1'h0};
  assign T11 = T12 ? 19'h7ffff : 19'h0;
  assign T12 = immb[11];
  assign immb = {T16, T13};
  assign T13 = {T15, T14};
  assign T14 = io_instr[11:8];
  assign T15 = io_instr[30:25];
  assign T16 = {T18, T17};
  assign T17 = io_instr[7];
  assign T18 = io_instr[31];
  assign io_imms_sxt = T19;
  assign T19 = {T22, imms};
  assign imms = {T21, T20};
  assign T20 = io_instr[11:7];
  assign T21 = io_instr[31:25];
  assign T22 = T23 ? 20'hfffff : 20'h0;
  assign T23 = immi[11];
  assign immi = io_instr[31:20];
  assign io_immi_sxt = T24;
  assign T24 = {T25, immi};
  assign T25 = T26 ? 20'hfffff : 20'h0;
  assign T26 = immi[11];
endmodule

