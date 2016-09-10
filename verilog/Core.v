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

module Decoder(
    input [31:0] io_dec_instr,
    output io_ctl_val_inst,
    output io_ctl_rf_wen,
    output[3:0] io_ctl_br_type,
    output[1:0] io_ctl_opa_sel,
    output[1:0] io_ctl_opb_sel,
    output[3:0] io_ctl_alu_func,
    output[1:0] io_ctl_wb_sel,
    output[1:0] io_ctl_mem_func,
    output io_ctl_mem_en,
    output[2:0] io_ctl_msk_sel,
    output[2:0] io_ctl_csr_cmd
);

  wire[2:0] ctl_msk_sel;
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
  wire[2:0] T10;
  wire[2:0] T11;
  wire[2:0] T12;
  wire[2:0] T13;
  wire[2:0] T14;
  wire[2:0] T15;
  wire T16;
  wire[31:0] T17;
  wire T18;
  wire[31:0] T19;
  wire T20;
  wire[31:0] T21;
  wire T22;
  wire[31:0] T23;
  wire T24;
  wire[31:0] T25;
  wire T26;
  wire[31:0] T27;
  wire T28;
  wire[31:0] T29;
  wire T30;
  wire[31:0] T31;
  wire T32;
  wire[31:0] T33;
  wire T34;
  wire[31:0] T35;
  wire T36;
  wire[31:0] T37;
  wire T38;
  wire[31:0] T39;
  wire T40;
  wire[31:0] T41;
  wire T42;
  wire[31:0] T43;
  wire T44;
  wire[31:0] T45;
  wire T46;
  wire[31:0] T47;
  wire T48;
  wire[31:0] T49;
  wire ctl_mem_en;
  wire T50;
  wire T51;
  wire T52;
  wire T53;
  wire T54;
  wire T55;
  wire T56;
  wire T57;
  wire T58;
  wire T59;
  wire T60;
  wire T61;
  wire T62;
  wire T63;
  wire T64;
  wire T65;
  wire T66;
  wire[31:0] T67;
  wire[1:0] ctl_mem_func;
  wire[1:0] T68;
  wire[1:0] T69;
  wire[1:0] T70;
  wire[1:0] T71;
  wire[1:0] T72;
  wire[1:0] T73;
  wire[1:0] T74;
  wire[1:0] T75;
  wire[1:0] T76;
  wire[1:0] T77;
  wire[1:0] T78;
  wire[1:0] T79;
  wire[1:0] T80;
  wire[1:0] T81;
  wire[1:0] T82;
  wire[1:0] T83;
  wire[1:0] T84;
  wire[1:0] ctl_wb_sel;
  wire[1:0] T85;
  wire[1:0] T86;
  wire[1:0] T87;
  wire[1:0] T88;
  wire[1:0] T89;
  wire[1:0] T90;
  wire[1:0] T91;
  wire[1:0] T92;
  wire[1:0] T93;
  wire[1:0] T94;
  wire[1:0] T95;
  wire[1:0] T96;
  wire[1:0] T97;
  wire[1:0] T98;
  wire[3:0] ctl_alu_func;
  wire[3:0] T99;
  wire[3:0] T100;
  wire[3:0] T101;
  wire[3:0] T102;
  wire[3:0] T103;
  wire[3:0] T104;
  wire[3:0] T105;
  wire[3:0] T106;
  wire[3:0] T107;
  wire[3:0] T108;
  wire[3:0] T109;
  wire[3:0] T110;
  wire[3:0] T111;
  wire[3:0] T112;
  wire[3:0] T113;
  wire[3:0] T114;
  wire[3:0] T115;
  wire[3:0] T116;
  wire[3:0] T117;
  wire[3:0] T118;
  wire[3:0] T119;
  wire[3:0] T120;
  wire[3:0] T121;
  wire[3:0] T122;
  wire[3:0] T123;
  wire[3:0] T124;
  wire[3:0] T125;
  wire[3:0] T126;
  wire[3:0] T127;
  wire[3:0] T128;
  wire[3:0] T129;
  wire[3:0] T130;
  wire[3:0] T131;
  wire[3:0] T132;
  wire[3:0] T133;
  wire[3:0] T134;
  wire T135;
  wire[31:0] T136;
  wire T137;
  wire[31:0] T138;
  wire T139;
  wire[31:0] T140;
  wire T141;
  wire[31:0] T142;
  wire T143;
  wire[31:0] T144;
  wire T145;
  wire[31:0] T146;
  wire T147;
  wire[31:0] T148;
  wire T149;
  wire[31:0] T150;
  wire T151;
  wire[31:0] T152;
  wire T153;
  wire[31:0] T154;
  wire T155;
  wire[31:0] T156;
  wire T157;
  wire[31:0] T158;
  wire T159;
  wire[31:0] T160;
  wire T161;
  wire[31:0] T162;
  wire T163;
  wire[31:0] T164;
  wire T165;
  wire[31:0] T166;
  wire T167;
  wire[31:0] T168;
  wire T169;
  wire[31:0] T170;
  wire T171;
  wire[31:0] T172;
  wire[1:0] ctl_opb_sel;
  wire[1:0] T173;
  wire[1:0] T174;
  wire[1:0] T175;
  wire[1:0] T176;
  wire[1:0] T177;
  wire[1:0] T178;
  wire[1:0] T179;
  wire[1:0] T180;
  wire[1:0] T181;
  wire[1:0] T182;
  wire[1:0] T183;
  wire[1:0] T184;
  wire[1:0] T185;
  wire[1:0] T186;
  wire[1:0] T187;
  wire[1:0] T188;
  wire[1:0] T189;
  wire[1:0] T190;
  wire[1:0] T191;
  wire[1:0] T192;
  wire[1:0] T193;
  wire[1:0] T194;
  wire[1:0] T195;
  wire[1:0] T196;
  wire[1:0] T197;
  wire[1:0] T198;
  wire[1:0] T199;
  wire[1:0] T200;
  wire[1:0] T201;
  wire[1:0] T202;
  wire[1:0] T203;
  wire[1:0] T204;
  wire[1:0] T205;
  wire[1:0] T206;
  wire[1:0] T207;
  wire[1:0] T208;
  wire[1:0] ctl_opa_sel;
  wire[1:0] T209;
  wire[3:0] ctl_br_type;
  wire[3:0] T210;
  wire[3:0] T211;
  wire[3:0] T212;
  wire[3:0] T213;
  wire[3:0] T214;
  wire[3:0] T215;
  wire[3:0] T216;
  wire[3:0] T217;
  wire[3:0] T218;
  wire ctl_rf_wen;
  wire T219;
  wire T220;
  wire T221;
  wire T222;
  wire T223;
  wire T224;
  wire T225;
  wire T226;
  wire T227;
  wire T228;
  wire T229;
  wire T230;
  wire T231;
  wire T232;
  wire T233;
  wire T234;
  wire T235;
  wire T236;
  wire T237;
  wire T238;
  wire T239;
  wire T240;
  wire T241;
  wire T242;
  wire T243;
  wire T244;
  wire T245;
  wire T246;
  wire T247;
  wire T248;
  wire T249;
  wire T250;
  wire T251;
  wire T252;
  wire T253;
  wire ctl_val_inst;
  wire T254;
  wire T255;
  wire T256;
  wire T257;
  wire T258;
  wire T259;
  wire T260;
  wire T261;
  wire T262;
  wire T263;
  wire T264;
  wire T265;
  wire T266;
  wire T267;
  wire T268;
  wire T269;
  wire T270;
  wire T271;
  wire T272;
  wire T273;
  wire T274;
  wire T275;
  wire T276;
  wire T277;
  wire T278;
  wire T279;
  wire T280;
  wire T281;
  wire T282;
  wire T283;
  wire T284;
  wire T285;
  wire T286;
  wire T287;
  wire T288;


  assign io_ctl_csr_cmd = 3'h0;
  assign io_ctl_msk_sel = ctl_msk_sel;
  assign ctl_msk_sel = T48 ? 3'h2 : T0;
  assign T0 = T46 ? 3'h2 : T1;
  assign T1 = T44 ? 3'h2 : T2;
  assign T2 = T42 ? 3'h2 : T3;
  assign T3 = T40 ? 3'h2 : T4;
  assign T4 = T38 ? 3'h2 : T5;
  assign T5 = T36 ? 3'h2 : T6;
  assign T6 = T34 ? 3'h2 : T7;
  assign T7 = T32 ? 3'h2 : T8;
  assign T8 = T30 ? 3'h2 : T9;
  assign T9 = T28 ? 3'h0 : T10;
  assign T10 = T26 ? 3'h3 : T11;
  assign T11 = T24 ? 3'h1 : T12;
  assign T12 = T22 ? 3'h4 : T13;
  assign T13 = T20 ? 3'h2 : T14;
  assign T14 = T18 ? 3'h0 : T15;
  assign T15 = T16 ? 3'h1 : 3'h2;
  assign T16 = T17 == 32'h1023;
  assign T17 = io_dec_instr & 32'h707f;
  assign T18 = T19 == 32'h23;
  assign T19 = io_dec_instr & 32'h707f;
  assign T20 = T21 == 32'h2003;
  assign T21 = io_dec_instr & 32'h707f;
  assign T22 = T23 == 32'h5003;
  assign T23 = io_dec_instr & 32'h707f;
  assign T24 = T25 == 32'h1003;
  assign T25 = io_dec_instr & 32'h707f;
  assign T26 = T27 == 32'h4003;
  assign T27 = io_dec_instr & 32'h707f;
  assign T28 = T29 == 32'h3;
  assign T29 = io_dec_instr & 32'h707f;
  assign T30 = T31 == 32'h6063;
  assign T31 = io_dec_instr & 32'h707f;
  assign T32 = T33 == 32'h4063;
  assign T33 = io_dec_instr & 32'h707f;
  assign T34 = T35 == 32'h7063;
  assign T35 = io_dec_instr & 32'h707f;
  assign T36 = T37 == 32'h5063;
  assign T37 = io_dec_instr & 32'h707f;
  assign T38 = T39 == 32'h1063;
  assign T39 = io_dec_instr & 32'h707f;
  assign T40 = T41 == 32'h63;
  assign T41 = io_dec_instr & 32'h707f;
  assign T42 = T43 == 32'h67;
  assign T43 = io_dec_instr & 32'h707f;
  assign T44 = T45 == 32'h6f;
  assign T45 = io_dec_instr & 32'h7f;
  assign T46 = T47 == 32'h17;
  assign T47 = io_dec_instr & 32'h7f;
  assign T48 = T49 == 32'h37;
  assign T49 = io_dec_instr & 32'h7f;
  assign io_ctl_mem_en = ctl_mem_en;
  assign ctl_mem_en = T48 ? 1'h0 : T50;
  assign T50 = T46 ? 1'h0 : T51;
  assign T51 = T44 ? 1'h0 : T52;
  assign T52 = T42 ? 1'h0 : T53;
  assign T53 = T40 ? 1'h0 : T54;
  assign T54 = T38 ? 1'h0 : T55;
  assign T55 = T36 ? 1'h0 : T56;
  assign T56 = T34 ? 1'h0 : T57;
  assign T57 = T32 ? 1'h0 : T58;
  assign T58 = T30 ? 1'h0 : T59;
  assign T59 = T28 ? 1'h1 : T60;
  assign T60 = T26 ? 1'h1 : T61;
  assign T61 = T24 ? 1'h1 : T62;
  assign T62 = T22 ? 1'h1 : T63;
  assign T63 = T20 ? 1'h1 : T64;
  assign T64 = T18 ? 1'h1 : T65;
  assign T65 = T16 ? 1'h1 : T66;
  assign T66 = T67 == 32'h2023;
  assign T67 = io_dec_instr & 32'h707f;
  assign io_ctl_mem_func = ctl_mem_func;
  assign ctl_mem_func = T48 ? 2'h0 : T68;
  assign T68 = T46 ? 2'h0 : T69;
  assign T69 = T44 ? 2'h0 : T70;
  assign T70 = T42 ? 2'h0 : T71;
  assign T71 = T40 ? 2'h0 : T72;
  assign T72 = T38 ? 2'h0 : T73;
  assign T73 = T36 ? 2'h0 : T74;
  assign T74 = T34 ? 2'h0 : T75;
  assign T75 = T32 ? 2'h0 : T76;
  assign T76 = T30 ? 2'h0 : T77;
  assign T77 = T28 ? 2'h0 : T78;
  assign T78 = T26 ? 2'h0 : T79;
  assign T79 = T24 ? 2'h0 : T80;
  assign T80 = T22 ? 2'h0 : T81;
  assign T81 = T20 ? 2'h0 : T82;
  assign T82 = T18 ? 2'h1 : T83;
  assign T83 = T16 ? 2'h1 : T84;
  assign T84 = T66 ? 2'h1 : 2'h0;
  assign io_ctl_wb_sel = ctl_wb_sel;
  assign ctl_wb_sel = T48 ? 2'h0 : T85;
  assign T85 = T46 ? 2'h0 : T86;
  assign T86 = T44 ? 2'h2 : T87;
  assign T87 = T42 ? 2'h2 : T88;
  assign T88 = T40 ? 2'h0 : T89;
  assign T89 = T38 ? 2'h0 : T90;
  assign T90 = T36 ? 2'h0 : T91;
  assign T91 = T34 ? 2'h0 : T92;
  assign T92 = T32 ? 2'h0 : T93;
  assign T93 = T30 ? 2'h0 : T94;
  assign T94 = T28 ? 2'h3 : T95;
  assign T95 = T26 ? 2'h3 : T96;
  assign T96 = T24 ? 2'h3 : T97;
  assign T97 = T22 ? 2'h3 : T98;
  assign T98 = T20 ? 2'h3 : 2'h0;
  assign io_ctl_alu_func = ctl_alu_func;
  assign ctl_alu_func = T48 ? 4'hf : T99;
  assign T99 = T46 ? 4'h1 : T100;
  assign T100 = T44 ? 4'h0 : T101;
  assign T101 = T42 ? 4'h0 : T102;
  assign T102 = T40 ? 4'h0 : T103;
  assign T103 = T38 ? 4'h0 : T104;
  assign T104 = T36 ? 4'h0 : T105;
  assign T105 = T34 ? 4'h0 : T106;
  assign T106 = T32 ? 4'h0 : T107;
  assign T107 = T30 ? 4'h0 : T108;
  assign T108 = T28 ? 4'h1 : T109;
  assign T109 = T26 ? 4'h1 : T110;
  assign T110 = T24 ? 4'h1 : T111;
  assign T111 = T22 ? 4'h1 : T112;
  assign T112 = T20 ? 4'h1 : T113;
  assign T113 = T18 ? 4'h1 : T114;
  assign T114 = T16 ? 4'h1 : T115;
  assign T115 = T66 ? 4'h1 : T116;
  assign T116 = T171 ? 4'h1 : T117;
  assign T117 = T169 ? 4'h6 : T118;
  assign T118 = T167 ? 4'h7 : T119;
  assign T119 = T165 ? 4'h5 : T120;
  assign T120 = T163 ? 4'h4 : T121;
  assign T121 = T161 ? 4'h3 : T122;
  assign T122 = T159 ? 4'hc : T123;
  assign T123 = T157 ? 4'hd : T124;
  assign T124 = T155 ? 4'he : T125;
  assign T125 = T153 ? 4'h1 : T126;
  assign T126 = T151 ? 4'h2 : T127;
  assign T127 = T149 ? 4'hc : T128;
  assign T128 = T147 ? 4'h6 : T129;
  assign T129 = T145 ? 4'h7 : T130;
  assign T130 = T143 ? 4'h5 : T131;
  assign T131 = T141 ? 4'hd : T132;
  assign T132 = T139 ? 4'he : T133;
  assign T133 = T137 ? 4'h4 : T134;
  assign T134 = T135 ? 4'h3 : 4'h0;
  assign T135 = T136 == 32'h7033;
  assign T136 = io_dec_instr & 32'hfe00707f;
  assign T137 = T138 == 32'h6033;
  assign T138 = io_dec_instr & 32'hfe00707f;
  assign T139 = T140 == 32'h40005033;
  assign T140 = io_dec_instr & 32'hfe00707f;
  assign T141 = T142 == 32'h5033;
  assign T142 = io_dec_instr & 32'hfe00707f;
  assign T143 = T144 == 32'h4033;
  assign T144 = io_dec_instr & 32'hfe00707f;
  assign T145 = T146 == 32'h3033;
  assign T146 = io_dec_instr & 32'hfe00707f;
  assign T147 = T148 == 32'h2033;
  assign T148 = io_dec_instr & 32'hfe00707f;
  assign T149 = T150 == 32'h1033;
  assign T150 = io_dec_instr & 32'hfe00707f;
  assign T151 = T152 == 32'h40000033;
  assign T152 = io_dec_instr & 32'hfe00707f;
  assign T153 = T154 == 32'h33;
  assign T154 = io_dec_instr & 32'hfe00707f;
  assign T155 = T156 == 32'h40005013;
  assign T156 = io_dec_instr & 32'hfc00707f;
  assign T157 = T158 == 32'h5013;
  assign T158 = io_dec_instr & 32'hfc00707f;
  assign T159 = T160 == 32'h1013;
  assign T160 = io_dec_instr & 32'hfc00707f;
  assign T161 = T162 == 32'h7013;
  assign T162 = io_dec_instr & 32'h707f;
  assign T163 = T164 == 32'h6013;
  assign T164 = io_dec_instr & 32'h707f;
  assign T165 = T166 == 32'h4013;
  assign T166 = io_dec_instr & 32'h707f;
  assign T167 = T168 == 32'h3013;
  assign T168 = io_dec_instr & 32'h707f;
  assign T169 = T170 == 32'h2013;
  assign T170 = io_dec_instr & 32'h707f;
  assign T171 = T172 == 32'h13;
  assign T172 = io_dec_instr & 32'h707f;
  assign io_ctl_opb_sel = ctl_opb_sel;
  assign ctl_opb_sel = T48 ? 2'h0 : T173;
  assign T173 = T46 ? 2'h0 : T174;
  assign T174 = T44 ? 2'h0 : T175;
  assign T175 = T42 ? 2'h2 : T176;
  assign T176 = T40 ? 2'h0 : T177;
  assign T177 = T38 ? 2'h0 : T178;
  assign T178 = T36 ? 2'h0 : T179;
  assign T179 = T34 ? 2'h0 : T180;
  assign T180 = T32 ? 2'h0 : T181;
  assign T181 = T30 ? 2'h0 : T182;
  assign T182 = T28 ? 2'h2 : T183;
  assign T183 = T26 ? 2'h2 : T184;
  assign T184 = T24 ? 2'h2 : T185;
  assign T185 = T22 ? 2'h2 : T186;
  assign T186 = T20 ? 2'h2 : T187;
  assign T187 = T18 ? 2'h3 : T188;
  assign T188 = T16 ? 2'h3 : T189;
  assign T189 = T66 ? 2'h3 : T190;
  assign T190 = T171 ? 2'h2 : T191;
  assign T191 = T169 ? 2'h2 : T192;
  assign T192 = T167 ? 2'h2 : T193;
  assign T193 = T165 ? 2'h2 : T194;
  assign T194 = T163 ? 2'h2 : T195;
  assign T195 = T161 ? 2'h2 : T196;
  assign T196 = T159 ? 2'h2 : T197;
  assign T197 = T157 ? 2'h2 : T198;
  assign T198 = T155 ? 2'h2 : T199;
  assign T199 = T153 ? 2'h2 : T200;
  assign T200 = T151 ? 2'h2 : T201;
  assign T201 = T149 ? 2'h2 : T202;
  assign T202 = T147 ? 2'h2 : T203;
  assign T203 = T145 ? 2'h2 : T204;
  assign T204 = T143 ? 2'h2 : T205;
  assign T205 = T141 ? 2'h2 : T206;
  assign T206 = T139 ? 2'h2 : T207;
  assign T207 = T137 ? 2'h2 : T208;
  assign T208 = T135 ? 2'h2 : 2'h0;
  assign io_ctl_opa_sel = ctl_opa_sel;
  assign ctl_opa_sel = T48 ? 2'h1 : T209;
  assign T209 = T46 ? 2'h1 : 2'h0;
  assign io_ctl_br_type = ctl_br_type;
  assign ctl_br_type = T48 ? 4'h0 : T210;
  assign T210 = T46 ? 4'h0 : T211;
  assign T211 = T44 ? 4'h7 : T212;
  assign T212 = T42 ? 4'h8 : T213;
  assign T213 = T40 ? 4'h1 : T214;
  assign T214 = T38 ? 4'h2 : T215;
  assign T215 = T36 ? 4'h3 : T216;
  assign T216 = T34 ? 4'h4 : T217;
  assign T217 = T32 ? 4'h5 : T218;
  assign T218 = T30 ? 4'h6 : 4'h0;
  assign io_ctl_rf_wen = ctl_rf_wen;
  assign ctl_rf_wen = T48 ? 1'h1 : T219;
  assign T219 = T46 ? 1'h1 : T220;
  assign T220 = T44 ? 1'h1 : T221;
  assign T221 = T42 ? 1'h1 : T222;
  assign T222 = T40 ? 1'h0 : T223;
  assign T223 = T38 ? 1'h0 : T224;
  assign T224 = T36 ? 1'h0 : T225;
  assign T225 = T34 ? 1'h0 : T226;
  assign T226 = T32 ? 1'h0 : T227;
  assign T227 = T30 ? 1'h0 : T228;
  assign T228 = T28 ? 1'h1 : T229;
  assign T229 = T26 ? 1'h1 : T230;
  assign T230 = T24 ? 1'h1 : T231;
  assign T231 = T22 ? 1'h1 : T232;
  assign T232 = T20 ? 1'h1 : T233;
  assign T233 = T18 ? 1'h0 : T234;
  assign T234 = T16 ? 1'h0 : T235;
  assign T235 = T66 ? 1'h0 : T236;
  assign T236 = T171 ? 1'h1 : T237;
  assign T237 = T169 ? 1'h1 : T238;
  assign T238 = T167 ? 1'h1 : T239;
  assign T239 = T165 ? 1'h1 : T240;
  assign T240 = T163 ? 1'h1 : T241;
  assign T241 = T161 ? 1'h1 : T242;
  assign T242 = T159 ? 1'h1 : T243;
  assign T243 = T157 ? 1'h1 : T244;
  assign T244 = T155 ? 1'h1 : T245;
  assign T245 = T153 ? 1'h1 : T246;
  assign T246 = T151 ? 1'h1 : T247;
  assign T247 = T149 ? 1'h1 : T248;
  assign T248 = T147 ? 1'h1 : T249;
  assign T249 = T145 ? 1'h1 : T250;
  assign T250 = T143 ? 1'h1 : T251;
  assign T251 = T141 ? 1'h1 : T252;
  assign T252 = T139 ? 1'h1 : T253;
  assign T253 = T137 ? 1'h1 : T135;
  assign io_ctl_val_inst = ctl_val_inst;
  assign ctl_val_inst = T48 ? 1'h1 : T254;
  assign T254 = T46 ? 1'h1 : T255;
  assign T255 = T44 ? 1'h1 : T256;
  assign T256 = T42 ? 1'h1 : T257;
  assign T257 = T40 ? 1'h1 : T258;
  assign T258 = T38 ? 1'h1 : T259;
  assign T259 = T36 ? 1'h1 : T260;
  assign T260 = T34 ? 1'h1 : T261;
  assign T261 = T32 ? 1'h1 : T262;
  assign T262 = T30 ? 1'h1 : T263;
  assign T263 = T28 ? 1'h1 : T264;
  assign T264 = T26 ? 1'h1 : T265;
  assign T265 = T24 ? 1'h1 : T266;
  assign T266 = T22 ? 1'h1 : T267;
  assign T267 = T20 ? 1'h1 : T268;
  assign T268 = T18 ? 1'h1 : T269;
  assign T269 = T16 ? 1'h1 : T270;
  assign T270 = T66 ? 1'h1 : T271;
  assign T271 = T171 ? 1'h1 : T272;
  assign T272 = T169 ? 1'h1 : T273;
  assign T273 = T167 ? 1'h1 : T274;
  assign T274 = T165 ? 1'h1 : T275;
  assign T275 = T163 ? 1'h1 : T276;
  assign T276 = T161 ? 1'h1 : T277;
  assign T277 = T159 ? 1'h1 : T278;
  assign T278 = T157 ? 1'h1 : T279;
  assign T279 = T155 ? 1'h1 : T280;
  assign T280 = T153 ? 1'h1 : T281;
  assign T281 = T151 ? 1'h1 : T282;
  assign T282 = T149 ? 1'h1 : T283;
  assign T283 = T147 ? 1'h1 : T284;
  assign T284 = T145 ? 1'h1 : T285;
  assign T285 = T143 ? 1'h1 : T286;
  assign T286 = T141 ? 1'h1 : T287;
  assign T287 = T139 ? 1'h1 : T288;
  assign T288 = T137 ? 1'h1 : T135;
endmodule

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
  wire[31:0] T13;
  wire[31:0] T14;
  wire[31:0] T15;
  wire[31:0] T16;
  wire T17;
  wire[31:0] T18;
  wire[31:0] T19;
  wire[4:0] alu_shamt;
  wire[4:0] T20;
  wire[31:0] T21;
  wire T22;
  wire[31:0] T23;
  wire[31:0] T24;
  wire T25;
  wire[31:0] T26;
  wire[31:0] T27;
  wire[62:0] T28;
  wire T29;
  wire[31:0] T67;
  wire T30;
  wire T31;
  wire T32;
  wire[31:0] T68;
  wire T33;
  wire T34;
  wire[31:0] T35;
  wire[31:0] T36;
  wire T37;
  wire[31:0] T69;
  wire T38;
  wire T39;
  wire T40;
  wire[31:0] T70;
  wire T41;
  wire T42;
  wire T43;
  wire[31:0] T71;
  wire T44;
  wire T45;
  wire T46;
  wire[31:0] T72;
  wire T47;
  wire T48;
  wire[31:0] T49;
  wire[31:0] T50;
  wire T51;
  wire[31:0] T52;
  wire[31:0] T53;
  wire T54;
  wire[31:0] T55;
  wire[31:0] T56;
  wire T57;
  wire[31:0] T58;
  wire[31:0] T59;
  wire T60;
  wire[31:0] T61;
  wire[31:0] T62;
  wire T63;
  wire[31:0] T64;
  wire[31:0] T65;
  wire T66;


  assign io_zero = T0;
  assign T0 = T1 ? 1'h1 : 1'h0;
  assign T1 = io_out == 32'h0;
  assign io_out = alu_out;
  assign alu_out = T2;
  assign T2 = T66 ? T64 : T3;
  assign T3 = T63 ? T61 : T4;
  assign T4 = T60 ? T58 : T5;
  assign T5 = T57 ? T55 : T6;
  assign T6 = T54 ? T52 : T7;
  assign T7 = T51 ? T72 : T8;
  assign T8 = T46 ? T71 : T9;
  assign T9 = T43 ? T70 : T10;
  assign T10 = T40 ? T69 : T11;
  assign T11 = T37 ? T68 : T12;
  assign T12 = T32 ? T67 : T13;
  assign T13 = T29 ? T26 : T14;
  assign T14 = T25 ? T23 : T15;
  assign T15 = T22 ? T18 : T16;
  assign T16 = T17 ? io_a : 32'h0;
  assign T17 = io_op == 4'hf;
  assign T18 = T19;
  assign T19 = $signed(T21) >>> alu_shamt;
  assign alu_shamt = T20;
  assign T20 = io_b[4:0];
  assign T21 = io_a;
  assign T22 = io_op == 4'he;
  assign T23 = T24;
  assign T24 = io_a >> alu_shamt;
  assign T25 = io_op == 4'hd;
  assign T26 = T27;
  assign T27 = T28[31:0];
  assign T28 = io_a << alu_shamt;
  assign T29 = io_op == 4'hc;
  assign T67 = {31'h0, T30};
  assign T30 = T31;
  assign T31 = io_b <= io_a;
  assign T32 = io_op == 4'hb;
  assign T68 = {31'h0, T33};
  assign T33 = T34;
  assign T34 = $signed(T36) <= $signed(T35);
  assign T35 = io_a;
  assign T36 = io_b;
  assign T37 = io_op == 4'ha;
  assign T69 = {31'h0, T38};
  assign T38 = T39;
  assign T39 = io_a != io_b;
  assign T40 = io_op == 4'h9;
  assign T70 = {31'h0, T41};
  assign T41 = T42;
  assign T42 = io_a == io_b;
  assign T43 = io_op == 4'h8;
  assign T71 = {31'h0, T44};
  assign T44 = T45;
  assign T45 = io_a < io_b;
  assign T46 = io_op == 4'h7;
  assign T72 = {31'h0, T47};
  assign T47 = T48;
  assign T48 = $signed(T50) < $signed(T49);
  assign T49 = io_b;
  assign T50 = io_a;
  assign T51 = io_op == 4'h6;
  assign T52 = T53;
  assign T53 = io_a ^ io_b;
  assign T54 = io_op == 4'h5;
  assign T55 = T56;
  assign T56 = io_a | io_b;
  assign T57 = io_op == 4'h4;
  assign T58 = T59;
  assign T59 = io_a & io_b;
  assign T60 = io_op == 4'h3;
  assign T61 = T62;
  assign T62 = io_a - io_b;
  assign T63 = io_op == 4'h2;
  assign T64 = T65;
  assign T65 = io_a + io_b;
  assign T66 = io_op == 4'h1;
endmodule

module InstructionMem(input clk,
    input [4:0] io_addr,
    output[31:0] io_data
);

  wire[31:0] T0;
  reg [31:0] mem [1023:0];
  wire[9:0] T1;

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
  assign T0 = mem[T1];
  assign T1 = {5'h0, io_addr};
endmodule

module DataMem(input clk,
    input [4:0] io_addr,
    input [31:0] io_wr_data,
    input [1:0] io_mem_func,
    input  io_mem_en,
    output[31:0] io_rd_data
);

  wire[31:0] T0;
  wire[31:0] T1;
  reg [31:0] mem [31:0];
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
    for (initvar = 0; initvar < 32; initvar = initvar+1)
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

module Core(input clk, input reset,

);

  wire T0;
  wire[31:0] T1;
  wire[31:0] T2;
  wire T3;
  wire[31:0] T4;
  wire[31:0] T5;
  wire T6;
  wire excp_illegal_instr;
  reg [31:0] exec_pc4_reg;
  wire[31:0] T22;
  wire[31:0] fetch_pc4_reg;
  reg [31:0] fetch_pc_reg;
  wire[31:0] T23;
  wire[31:0] T7;
  wire T8;
  wire stall;
  wire[4:0] T24;
  wire[4:0] T25;
  reg [31:0] exec_pc_reg;
  wire[31:0] T26;
  wire[31:0] T9;
  wire[31:0] T10;
  wire[31:0] T11;
  wire T12;
  wire kill_the_fetch;
  wire T13;
  wire T14;
  wire T15;
  wire T16;
  reg [31:0] exec_instr_reg;
  wire[31:0] T27;
  wire[31:0] T17;
  wire[31:0] T18;
  wire[31:0] T19;
  wire T20;
  wire[4:0] rd_addr;
  wire[4:0] T28;
  wire[9:0] rsb_addr;
  wire[4:0] rsa_addr;
  wire[31:0] exec_pc_jmp;
  wire[31:0] exec_pc_br;
  wire[31:0] exec_pc_jalr;
  wire[31:0] T21;
  wire[31:0] MuxPC_io_pc_out;
  wire[31:0] RegFile_io_rf_rd1;
  wire[31:0] RegFile_io_rf_rd2;
  wire[31:0] ImmGen_io_immi_sxt;
  wire[31:0] ImmGen_io_imms_sxt;
  wire[31:0] ImmGen_io_immb_sxt;
  wire[31:0] ImmGen_io_immu_sxt;
  wire[31:0] ImmGen_io_immj_sxt;
  wire Decoder_io_ctl_val_inst;
  wire Decoder_io_ctl_rf_wen;
  wire[3:0] Decoder_io_ctl_br_type;
  wire[1:0] Decoder_io_ctl_opa_sel;
  wire[1:0] Decoder_io_ctl_opb_sel;
  wire[3:0] Decoder_io_ctl_alu_func;
  wire[1:0] Decoder_io_ctl_wb_sel;
  wire[1:0] Decoder_io_ctl_mem_func;
  wire Decoder_io_ctl_mem_en;
  wire[31:0] MuxOpA_io_opa_alu_in;
  wire[31:0] MuxOpB_io_opb_alu_in;
  wire[31:0] Alu_io_out;
  wire[31:0] InstructionMem_io_data;
  wire[31:0] DataMem_io_rd_data;
  wire[31:0] MuxWB_io_wb_wd;
  wire[2:0] BranchLogic_io_pc_sel;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    exec_pc4_reg = {1{$random}};
    fetch_pc_reg = {1{$random}};
    exec_pc_reg = {1{$random}};
    exec_instr_reg = {1{$random}};
  end
// synthesis translate_on
`endif

  assign T0 = T2 < T1;
  assign T1 = RegFile_io_rf_rd2;
  assign T2 = RegFile_io_rf_rd1;
  assign T3 = $signed(T5) < $signed(T4);
  assign T4 = RegFile_io_rf_rd2;
  assign T5 = RegFile_io_rf_rd1;
  assign T6 = RegFile_io_rf_rd1 == RegFile_io_rf_rd2;
  assign excp_illegal_instr = Decoder_io_ctl_val_inst ^ 1'h1;
  assign T22 = reset ? 32'h0 : fetch_pc4_reg;
  assign fetch_pc4_reg = fetch_pc_reg + 32'h1;
  assign T23 = reset ? 32'h0 : T7;
  assign T7 = T8 ? MuxPC_io_pc_out : fetch_pc_reg;
  assign T8 = stall ^ 1'h1;
  assign stall = Decoder_io_ctl_mem_en & excp_illegal_instr;
  assign T24 = Alu_io_out[4:0];
  assign T25 = fetch_pc_reg[4:0];
  assign T26 = reset ? 32'h0 : T9;
  assign T9 = T15 ? fetch_pc_reg : T10;
  assign T10 = T12 ? 32'h0 : T11;
  assign T11 = stall ? exec_pc_reg : exec_pc_reg;
  assign T12 = T14 & kill_the_fetch;
  assign kill_the_fetch = T13 ^ 1'h1;
  assign T13 = BranchLogic_io_pc_sel == 3'h0;
  assign T14 = stall ^ 1'h1;
  assign T15 = T16 ^ 1'h1;
  assign T16 = stall | kill_the_fetch;
  assign T27 = reset ? 32'h4033 : T17;
  assign T17 = T15 ? InstructionMem_io_data : T18;
  assign T18 = T12 ? 32'h4033 : T19;
  assign T19 = stall ? exec_instr_reg : exec_instr_reg;
  assign T20 = stall ? 1'h0 : Decoder_io_ctl_rf_wen;
  assign rd_addr = exec_instr_reg[11:7];
  assign T28 = rsb_addr[4:0];
  assign rsb_addr = exec_instr_reg[24:15];
  assign rsa_addr = exec_instr_reg[19:15];
  assign exec_pc_jmp = exec_pc_reg + ImmGen_io_immj_sxt;
  assign exec_pc_br = exec_pc_reg + ImmGen_io_immb_sxt;
  assign exec_pc_jalr = T21 + ImmGen_io_immi_sxt;
  assign T21 = RegFile_io_rf_rd1;
  MuxPC MuxPC(
       .io_pc_sel( BranchLogic_io_pc_sel ),
       .io_pc_pc4( fetch_pc4_reg ),
       .io_pc_jalr( exec_pc_jalr ),
       .io_pc_br( exec_pc_br ),
       .io_pc_jmp( exec_pc_jmp ),
       .io_pc_excp( 32'h0 ),
       .io_pc_out( MuxPC_io_pc_out )
  );
  RegFile RegFile(.clk(clk),
       .io_rf_ra1( rsa_addr ),
       .io_rf_ra2( T28 ),
       .io_rf_wa( rd_addr ),
       .io_rf_wen( T20 ),
       .io_rf_wd( MuxWB_io_wb_wd ),
       .io_rf_rd1( RegFile_io_rf_rd1 ),
       .io_rf_rd2( RegFile_io_rf_rd2 )
  );
  ImmGen ImmGen(
       .io_instr( exec_instr_reg ),
       .io_immi_sxt( ImmGen_io_immi_sxt ),
       .io_imms_sxt( ImmGen_io_imms_sxt ),
       .io_immb_sxt( ImmGen_io_immb_sxt ),
       .io_immu_sxt( ImmGen_io_immu_sxt ),
       .io_immj_sxt( ImmGen_io_immj_sxt )
  );
  Decoder Decoder(
       .io_dec_instr( exec_instr_reg ),
       .io_ctl_val_inst( Decoder_io_ctl_val_inst ),
       .io_ctl_rf_wen( Decoder_io_ctl_rf_wen ),
       .io_ctl_br_type( Decoder_io_ctl_br_type ),
       .io_ctl_opa_sel( Decoder_io_ctl_opa_sel ),
       .io_ctl_opb_sel( Decoder_io_ctl_opb_sel ),
       .io_ctl_alu_func( Decoder_io_ctl_alu_func ),
       .io_ctl_wb_sel( Decoder_io_ctl_wb_sel ),
       .io_ctl_mem_func( Decoder_io_ctl_mem_func ),
       .io_ctl_mem_en( Decoder_io_ctl_mem_en )
       //.io_ctl_msk_sel(  )
       //.io_ctl_csr_cmd(  )
  );
  MuxOpA MuxOpA(
       .io_opa_sel( Decoder_io_ctl_opa_sel ),
       .io_opa_rsa( RegFile_io_rf_rd1 ),
       .io_opa_imz( ImmGen_io_immu_sxt ),
       .io_opa_imu( ImmGen_io_immu_sxt ),
       .io_opa_alu_in( MuxOpA_io_opa_alu_in )
  );
  MuxOpB MuxOpB(
       .io_opb_sel( Decoder_io_ctl_opb_sel ),
       .io_opb_rsb( RegFile_io_rf_rd2 ),
       .io_opb_imi( ImmGen_io_immi_sxt ),
       .io_opb_ims( ImmGen_io_imms_sxt ),
       .io_opb_pc( exec_pc_reg ),
       .io_opb_alu_in( MuxOpB_io_opb_alu_in )
  );
  Alu Alu(
       .io_a( MuxOpA_io_opa_alu_in ),
       .io_b( MuxOpB_io_opb_alu_in ),
       .io_op( Decoder_io_ctl_alu_func ),
       .io_out( Alu_io_out )
       //.io_zero(  )
  );
  InstructionMem InstructionMem(.clk(clk),
       .io_addr( T25 ),
       .io_data( InstructionMem_io_data )
  );
  DataMem DataMem(.clk(clk),
       .io_addr( T24 ),
       .io_wr_data( RegFile_io_rf_rd2 ),
       .io_mem_func( Decoder_io_ctl_mem_func ),
       .io_mem_en( Decoder_io_ctl_mem_en ),
       .io_rd_data( DataMem_io_rd_data )
  );
  MuxWB MuxWB(
       .io_wb_sel( Decoder_io_ctl_wb_sel ),
       .io_wb_alu( Alu_io_out ),
       .io_wb_pc4( exec_pc4_reg ),
       .io_wb_csr( Alu_io_out ),
       .io_wb_mem( DataMem_io_rd_data ),
       .io_wb_wd( MuxWB_io_wb_wd )
  );
  BranchLogic BranchLogic(
       .io_excp( excp_illegal_instr ),
       .io_ctl_br_type( Decoder_io_ctl_br_type ),
       .io_br_eq( T6 ),
       .io_br_lt( T3 ),
       .io_br_ltu( T0 ),
       .io_pc_sel( BranchLogic_io_pc_sel )
  );

  always @(posedge clk) begin
    if(reset) begin
      exec_pc4_reg <= 32'h0;
    end else begin
      exec_pc4_reg <= fetch_pc4_reg;
    end
    if(reset) begin
      fetch_pc_reg <= 32'h0;
    end else if(T8) begin
      fetch_pc_reg <= MuxPC_io_pc_out;
    end
    if(reset) begin
      exec_pc_reg <= 32'h0;
    end else if(T15) begin
      exec_pc_reg <= fetch_pc_reg;
    end else if(T12) begin
      exec_pc_reg <= 32'h0;
    end else if(stall) begin
      exec_pc_reg <= exec_pc_reg;
    end
    if(reset) begin
      exec_instr_reg <= 32'h4033;
    end else if(T15) begin
      exec_instr_reg <= InstructionMem_io_data;
    end else if(T12) begin
      exec_instr_reg <= 32'h4033;
    end else if(stall) begin
      exec_instr_reg <= exec_instr_reg;
    end
  end
endmodule

