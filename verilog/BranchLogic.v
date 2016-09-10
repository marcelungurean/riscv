module BranchLogic(
    input  io_excp,
    input [3:0] io_ctl_br_type,
    input  io_br_eq,
    input  io_br_lt,
    input  io_br_ltu,
    output[2:0] io_pc_sel
);

  wire[2:0] T0;
  wire[2:0] T1;
  wire[2:0] T2;
  wire[2:0] T3;
  wire[2:0] T4;
  wire[2:0] T5;
  wire[2:0] T6;
  wire[2:0] T7;
  wire[2:0] T8;
  wire[2:0] T9;
  wire T10;
  wire T11;
  wire[2:0] T12;
  wire T13;
  wire[2:0] T14;
  wire T15;
  wire[2:0] T16;
  wire T17;
  wire T18;
  wire[2:0] T19;
  wire T20;
  wire T21;
  wire[2:0] T22;
  wire T23;
  wire[2:0] T24;
  wire T25;
  wire T26;
  wire T27;


  assign io_pc_sel = T0;
  assign T0 = io_excp ? 3'h4 : T1;
  assign T1 = T27 ? 3'h0 : T2;
  assign T2 = T26 ? T24 : T3;
  assign T3 = T23 ? T22 : T4;
  assign T4 = T21 ? T19 : T5;
  assign T5 = T18 ? T16 : T6;
  assign T6 = T15 ? T14 : T7;
  assign T7 = T13 ? T12 : T8;
  assign T8 = T11 ? 3'h3 : T9;
  assign T9 = T10 ? 3'h1 : 3'h0;
  assign T10 = io_ctl_br_type == 4'h8;
  assign T11 = io_ctl_br_type == 4'h7;
  assign T12 = io_br_ltu ? 3'h2 : 3'h0;
  assign T13 = io_ctl_br_type == 4'h6;
  assign T14 = io_br_lt ? 3'h2 : 3'h0;
  assign T15 = io_ctl_br_type == 4'h5;
  assign T16 = T17 ? 3'h2 : 3'h0;
  assign T17 = io_br_ltu ^ 1'h1;
  assign T18 = io_ctl_br_type == 4'h4;
  assign T19 = T20 ? 3'h2 : 3'h0;
  assign T20 = io_br_lt ^ 1'h1;
  assign T21 = io_ctl_br_type == 4'h3;
  assign T22 = io_br_eq ? 3'h2 : 3'h0;
  assign T23 = io_ctl_br_type == 4'h1;
  assign T24 = T25 ? 3'h2 : 3'h0;
  assign T25 = io_br_eq ^ 1'h1;
  assign T26 = io_ctl_br_type == 4'h2;
  assign T27 = io_ctl_br_type == 4'h0;
endmodule

