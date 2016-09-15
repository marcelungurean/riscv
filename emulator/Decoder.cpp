#include "Decoder.h"

void Decoder_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int Decoder_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void Decoder_t::print ( FILE* f ) {
}
void Decoder_t::print ( std::ostream& s ) {
}


void Decoder_t::dump_init ( FILE* f ) {
}


void Decoder_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void Decoder_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  { T0 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T1;
  T1 = T0 == 0x7033L;
  val_t T2;
  { T2 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T3;
  T3 = T2 == 0x6033L;
  val_t T4;
  { T4 = TERNARY(T3, 0x1L, T1);}
  val_t T5;
  { T5 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T6;
  T6 = T5 == 0x40005033L;
  val_t T7;
  { T7 = TERNARY(T6, 0x1L, T4);}
  val_t T8;
  { T8 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T9;
  T9 = T8 == 0x5033L;
  val_t T10;
  { T10 = TERNARY(T9, 0x1L, T7);}
  val_t T11;
  { T11 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T12;
  T12 = T11 == 0x4033L;
  val_t T13;
  { T13 = TERNARY(T12, 0x1L, T10);}
  val_t T14;
  { T14 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T15;
  T15 = T14 == 0x3033L;
  val_t T16;
  { T16 = TERNARY(T15, 0x1L, T13);}
  val_t T17;
  { T17 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T18;
  T18 = T17 == 0x2033L;
  val_t T19;
  { T19 = TERNARY(T18, 0x1L, T16);}
  val_t T20;
  { T20 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T21;
  T21 = T20 == 0x1033L;
  val_t T22;
  { T22 = TERNARY(T21, 0x1L, T19);}
  val_t T23;
  { T23 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T24;
  T24 = T23 == 0x40000033L;
  val_t T25;
  { T25 = TERNARY(T24, 0x1L, T22);}
  val_t T26;
  { T26 = Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T27;
  T27 = T26 == 0x33L;
  val_t T28;
  { T28 = TERNARY(T27, 0x1L, T25);}
  val_t T29;
  { T29 = Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T30;
  T30 = T29 == 0x40005013L;
  val_t T31;
  { T31 = TERNARY(T30, 0x1L, T28);}
  val_t T32;
  { T32 = Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T33;
  T33 = T32 == 0x5013L;
  val_t T34;
  { T34 = TERNARY(T33, 0x1L, T31);}
  val_t T35;
  { T35 = Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T36;
  T36 = T35 == 0x1013L;
  val_t T37;
  { T37 = TERNARY(T36, 0x1L, T34);}
  val_t T38;
  { T38 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T39;
  T39 = T38 == 0x7013L;
  val_t T40;
  { T40 = TERNARY(T39, 0x1L, T37);}
  val_t T41;
  { T41 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T42;
  T42 = T41 == 0x6013L;
  val_t T43;
  { T43 = TERNARY(T42, 0x1L, T40);}
  val_t T44;
  { T44 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T45;
  T45 = T44 == 0x4013L;
  val_t T46;
  { T46 = TERNARY(T45, 0x1L, T43);}
  val_t T47;
  { T47 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T48;
  T48 = T47 == 0x3013L;
  val_t T49;
  { T49 = TERNARY(T48, 0x1L, T46);}
  val_t T50;
  { T50 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T51;
  T51 = T50 == 0x2013L;
  val_t T52;
  { T52 = TERNARY(T51, 0x1L, T49);}
  val_t T53;
  { T53 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T54;
  T54 = T53 == 0x13L;
  val_t T55;
  { T55 = TERNARY(T54, 0x1L, T52);}
  val_t T56;
  { T56 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T57;
  T57 = T56 == 0x2023L;
  val_t T58;
  { T58 = TERNARY(T57, 0x1L, T55);}
  val_t T59;
  { T59 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T60;
  T60 = T59 == 0x1023L;
  val_t T61;
  { T61 = TERNARY(T60, 0x1L, T58);}
  val_t T62;
  { T62 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T63;
  T63 = T62 == 0x23L;
  val_t T64;
  { T64 = TERNARY(T63, 0x1L, T61);}
  val_t T65;
  { T65 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T66;
  T66 = T65 == 0x2003L;
  val_t T67;
  { T67 = TERNARY(T66, 0x1L, T64);}
  val_t T68;
  { T68 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T69;
  T69 = T68 == 0x5003L;
  val_t T70;
  { T70 = TERNARY(T69, 0x1L, T67);}
  val_t T71;
  { T71 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T72;
  T72 = T71 == 0x1003L;
  val_t T73;
  { T73 = TERNARY(T72, 0x1L, T70);}
  val_t T74;
  { T74 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T75;
  T75 = T74 == 0x4003L;
  val_t T76;
  { T76 = TERNARY(T75, 0x1L, T73);}
  val_t T77;
  { T77 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T78;
  T78 = T77 == 0x3L;
  val_t T79;
  { T79 = TERNARY(T78, 0x1L, T76);}
  val_t T80;
  { T80 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T81;
  T81 = T80 == 0x6063L;
  val_t T82;
  { T82 = TERNARY(T81, 0x1L, T79);}
  val_t T83;
  { T83 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T84;
  T84 = T83 == 0x4063L;
  val_t T85;
  { T85 = TERNARY(T84, 0x1L, T82);}
  val_t T86;
  { T86 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T87;
  T87 = T86 == 0x7063L;
  val_t T88;
  { T88 = TERNARY(T87, 0x1L, T85);}
  val_t T89;
  { T89 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T90;
  T90 = T89 == 0x5063L;
  val_t T91;
  { T91 = TERNARY(T90, 0x1L, T88);}
  val_t T92;
  { T92 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T93;
  T93 = T92 == 0x1063L;
  val_t T94;
  { T94 = TERNARY(T93, 0x1L, T91);}
  val_t T95;
  { T95 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T96;
  T96 = T95 == 0x63L;
  val_t T97;
  { T97 = TERNARY(T96, 0x1L, T94);}
  val_t T98;
  { T98 = Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T99;
  T99 = T98 == 0x67L;
  val_t T100;
  { T100 = TERNARY(T99, 0x1L, T97);}
  val_t T101;
  { T101 = Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T102;
  T102 = T101 == 0x6fL;
  val_t T103;
  { T103 = TERNARY(T102, 0x1L, T100);}
  val_t T104;
  { T104 = Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T105;
  T105 = T104 == 0x17L;
  val_t T106;
  { T106 = TERNARY(T105, 0x1L, T103);}
  val_t T107;
  { T107 = Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T108;
  T108 = T107 == 0x37L;
  val_t Decoder__ctl_val_inst;
  { Decoder__ctl_val_inst = TERNARY(T108, 0x1L, T106);}
  { Decoder__io_ctl_val_inst.values[0] = Decoder__ctl_val_inst;}
  val_t T109;
  { T109 = TERNARY(T3, 0x1L, T1);}
  val_t T110;
  { T110 = TERNARY(T6, 0x1L, T109);}
  val_t T111;
  { T111 = TERNARY(T9, 0x1L, T110);}
  val_t T112;
  { T112 = TERNARY(T12, 0x1L, T111);}
  val_t T113;
  { T113 = TERNARY(T15, 0x1L, T112);}
  val_t T114;
  { T114 = TERNARY(T18, 0x1L, T113);}
  val_t T115;
  { T115 = TERNARY(T21, 0x1L, T114);}
  val_t T116;
  { T116 = TERNARY(T24, 0x1L, T115);}
  val_t T117;
  { T117 = TERNARY(T27, 0x1L, T116);}
  val_t T118;
  { T118 = TERNARY(T30, 0x1L, T117);}
  val_t T119;
  { T119 = TERNARY(T33, 0x1L, T118);}
  val_t T120;
  { T120 = TERNARY(T36, 0x1L, T119);}
  val_t T121;
  { T121 = TERNARY(T39, 0x1L, T120);}
  val_t T122;
  { T122 = TERNARY(T42, 0x1L, T121);}
  val_t T123;
  { T123 = TERNARY(T45, 0x1L, T122);}
  val_t T124;
  { T124 = TERNARY(T48, 0x1L, T123);}
  val_t T125;
  { T125 = TERNARY(T51, 0x1L, T124);}
  val_t T126;
  { T126 = TERNARY(T54, 0x1L, T125);}
  val_t T127;
  { T127 = TERNARY(T57, 0x0L, T126);}
  val_t T128;
  { T128 = TERNARY(T60, 0x0L, T127);}
  val_t T129;
  { T129 = TERNARY(T63, 0x0L, T128);}
  val_t T130;
  { T130 = TERNARY(T66, 0x1L, T129);}
  val_t T131;
  { T131 = TERNARY(T69, 0x1L, T130);}
  val_t T132;
  { T132 = TERNARY(T72, 0x1L, T131);}
  val_t T133;
  { T133 = TERNARY(T75, 0x1L, T132);}
  val_t T134;
  { T134 = TERNARY(T78, 0x1L, T133);}
  val_t T135;
  { T135 = TERNARY(T81, 0x0L, T134);}
  val_t T136;
  { T136 = TERNARY(T84, 0x0L, T135);}
  val_t T137;
  { T137 = TERNARY(T87, 0x0L, T136);}
  val_t T138;
  { T138 = TERNARY(T90, 0x0L, T137);}
  val_t T139;
  { T139 = TERNARY(T93, 0x0L, T138);}
  val_t T140;
  { T140 = TERNARY(T96, 0x0L, T139);}
  val_t T141;
  { T141 = TERNARY(T99, 0x1L, T140);}
  val_t T142;
  { T142 = TERNARY(T102, 0x1L, T141);}
  val_t T143;
  { T143 = TERNARY(T105, 0x1L, T142);}
  val_t Decoder__ctl_rf_wen;
  { Decoder__ctl_rf_wen = TERNARY(T108, 0x1L, T143);}
  { Decoder__io_ctl_rf_wen.values[0] = Decoder__ctl_rf_wen;}
  val_t T144;
  { T144 = TERNARY(T81, 0x6L, 0x0L);}
  val_t T145;
  { T145 = TERNARY(T84, 0x5L, T144);}
  val_t T146;
  { T146 = TERNARY(T87, 0x4L, T145);}
  val_t T147;
  { T147 = TERNARY(T90, 0x3L, T146);}
  val_t T148;
  { T148 = TERNARY(T93, 0x2L, T147);}
  val_t T149;
  { T149 = TERNARY(T96, 0x1L, T148);}
  val_t T150;
  { T150 = TERNARY(T99, 0x8L, T149);}
  val_t T151;
  { T151 = TERNARY(T102, 0x7L, T150);}
  val_t T152;
  { T152 = TERNARY(T105, 0x0L, T151);}
  val_t Decoder__ctl_br_type;
  { Decoder__ctl_br_type = TERNARY(T108, 0x0L, T152);}
  { Decoder__io_ctl_br_type.values[0] = Decoder__ctl_br_type;}
  val_t T153;
  { T153 = TERNARY(T105, 0x1L, 0x0L);}
  val_t Decoder__ctl_opa_sel;
  { Decoder__ctl_opa_sel = TERNARY(T108, 0x1L, T153);}
  { Decoder__io_ctl_opa_sel.values[0] = Decoder__ctl_opa_sel;}
  val_t T154;
  { T154 = TERNARY(T1, 0x2L, 0x0L);}
  val_t T155;
  { T155 = TERNARY(T3, 0x2L, T154);}
  val_t T156;
  { T156 = TERNARY(T6, 0x2L, T155);}
  val_t T157;
  { T157 = TERNARY(T9, 0x2L, T156);}
  val_t T158;
  { T158 = TERNARY(T12, 0x2L, T157);}
  val_t T159;
  { T159 = TERNARY(T15, 0x2L, T158);}
  val_t T160;
  { T160 = TERNARY(T18, 0x2L, T159);}
  val_t T161;
  { T161 = TERNARY(T21, 0x2L, T160);}
  val_t T162;
  { T162 = TERNARY(T24, 0x2L, T161);}
  val_t T163;
  { T163 = TERNARY(T27, 0x2L, T162);}
  val_t T164;
  { T164 = TERNARY(T30, 0x2L, T163);}
  val_t T165;
  { T165 = TERNARY(T33, 0x2L, T164);}
  val_t T166;
  { T166 = TERNARY(T36, 0x2L, T165);}
  val_t T167;
  { T167 = TERNARY(T39, 0x2L, T166);}
  val_t T168;
  { T168 = TERNARY(T42, 0x2L, T167);}
  val_t T169;
  { T169 = TERNARY(T45, 0x2L, T168);}
  val_t T170;
  { T170 = TERNARY(T48, 0x2L, T169);}
  val_t T171;
  { T171 = TERNARY(T51, 0x2L, T170);}
  val_t T172;
  { T172 = TERNARY(T54, 0x2L, T171);}
  val_t T173;
  { T173 = TERNARY(T57, 0x3L, T172);}
  val_t T174;
  { T174 = TERNARY(T60, 0x3L, T173);}
  val_t T175;
  { T175 = TERNARY(T63, 0x3L, T174);}
  val_t T176;
  { T176 = TERNARY(T66, 0x2L, T175);}
  val_t T177;
  { T177 = TERNARY(T69, 0x2L, T176);}
  val_t T178;
  { T178 = TERNARY(T72, 0x2L, T177);}
  val_t T179;
  { T179 = TERNARY(T75, 0x2L, T178);}
  val_t T180;
  { T180 = TERNARY(T78, 0x2L, T179);}
  val_t T181;
  { T181 = TERNARY(T81, 0x0L, T180);}
  val_t T182;
  { T182 = TERNARY(T84, 0x0L, T181);}
  val_t T183;
  { T183 = TERNARY(T87, 0x0L, T182);}
  val_t T184;
  { T184 = TERNARY(T90, 0x0L, T183);}
  val_t T185;
  { T185 = TERNARY(T93, 0x0L, T184);}
  val_t T186;
  { T186 = TERNARY(T96, 0x0L, T185);}
  val_t T187;
  { T187 = TERNARY(T99, 0x2L, T186);}
  val_t T188;
  { T188 = TERNARY(T102, 0x0L, T187);}
  val_t T189;
  { T189 = TERNARY(T105, 0x1L, T188);}
  val_t Decoder__ctl_opb_sel;
  { Decoder__ctl_opb_sel = TERNARY(T108, 0x0L, T189);}
  { Decoder__io_ctl_opb_sel.values[0] = Decoder__ctl_opb_sel;}
  val_t T190;
  { T190 = TERNARY(T1, 0x3L, 0x0L);}
  val_t T191;
  { T191 = TERNARY(T3, 0x4L, T190);}
  val_t T192;
  { T192 = TERNARY(T6, 0xeL, T191);}
  val_t T193;
  { T193 = TERNARY(T9, 0xdL, T192);}
  val_t T194;
  { T194 = TERNARY(T12, 0x5L, T193);}
  val_t T195;
  { T195 = TERNARY(T15, 0x7L, T194);}
  val_t T196;
  { T196 = TERNARY(T18, 0x6L, T195);}
  val_t T197;
  { T197 = TERNARY(T21, 0xcL, T196);}
  val_t T198;
  { T198 = TERNARY(T24, 0x2L, T197);}
  val_t T199;
  { T199 = TERNARY(T27, 0x1L, T198);}
  val_t T200;
  { T200 = TERNARY(T30, 0xeL, T199);}
  val_t T201;
  { T201 = TERNARY(T33, 0xdL, T200);}
  val_t T202;
  { T202 = TERNARY(T36, 0xcL, T201);}
  val_t T203;
  { T203 = TERNARY(T39, 0x3L, T202);}
  val_t T204;
  { T204 = TERNARY(T42, 0x4L, T203);}
  val_t T205;
  { T205 = TERNARY(T45, 0x5L, T204);}
  val_t T206;
  { T206 = TERNARY(T48, 0x7L, T205);}
  val_t T207;
  { T207 = TERNARY(T51, 0x6L, T206);}
  val_t T208;
  { T208 = TERNARY(T54, 0x1L, T207);}
  val_t T209;
  { T209 = TERNARY(T57, 0x1L, T208);}
  val_t T210;
  { T210 = TERNARY(T60, 0x1L, T209);}
  val_t T211;
  { T211 = TERNARY(T63, 0x1L, T210);}
  val_t T212;
  { T212 = TERNARY(T66, 0x1L, T211);}
  val_t T213;
  { T213 = TERNARY(T69, 0x1L, T212);}
  val_t T214;
  { T214 = TERNARY(T72, 0x1L, T213);}
  val_t T215;
  { T215 = TERNARY(T75, 0x1L, T214);}
  val_t T216;
  { T216 = TERNARY(T78, 0x1L, T215);}
  val_t T217;
  { T217 = TERNARY(T81, 0x0L, T216);}
  val_t T218;
  { T218 = TERNARY(T84, 0x0L, T217);}
  val_t T219;
  { T219 = TERNARY(T87, 0x0L, T218);}
  val_t T220;
  { T220 = TERNARY(T90, 0x0L, T219);}
  val_t T221;
  { T221 = TERNARY(T93, 0x0L, T220);}
  val_t T222;
  { T222 = TERNARY(T96, 0x0L, T221);}
  val_t T223;
  { T223 = TERNARY(T99, 0x0L, T222);}
  val_t T224;
  { T224 = TERNARY(T102, 0x0L, T223);}
  val_t T225;
  { T225 = TERNARY(T105, 0x1L, T224);}
  val_t Decoder__ctl_alu_func;
  { Decoder__ctl_alu_func = TERNARY(T108, 0xfL, T225);}
  { Decoder__io_ctl_alu_func.values[0] = Decoder__ctl_alu_func;}
  val_t T226;
  { T226 = TERNARY(T66, 0x3L, 0x0L);}
  val_t T227;
  { T227 = TERNARY(T69, 0x3L, T226);}
  val_t T228;
  { T228 = TERNARY(T72, 0x3L, T227);}
  val_t T229;
  { T229 = TERNARY(T75, 0x3L, T228);}
  val_t T230;
  { T230 = TERNARY(T78, 0x3L, T229);}
  val_t T231;
  { T231 = TERNARY(T81, 0x0L, T230);}
  val_t T232;
  { T232 = TERNARY(T84, 0x0L, T231);}
  val_t T233;
  { T233 = TERNARY(T87, 0x0L, T232);}
  val_t T234;
  { T234 = TERNARY(T90, 0x0L, T233);}
  val_t T235;
  { T235 = TERNARY(T93, 0x0L, T234);}
  val_t T236;
  { T236 = TERNARY(T96, 0x0L, T235);}
  val_t T237;
  { T237 = TERNARY(T99, 0x2L, T236);}
  val_t T238;
  { T238 = TERNARY(T102, 0x2L, T237);}
  val_t T239;
  { T239 = TERNARY(T105, 0x0L, T238);}
  val_t Decoder__ctl_wb_sel;
  { Decoder__ctl_wb_sel = TERNARY(T108, 0x0L, T239);}
  { Decoder__io_ctl_wb_sel.values[0] = Decoder__ctl_wb_sel;}
  val_t T240;
  { T240 = TERNARY(T57, 0x1L, 0x0L);}
  val_t T241;
  { T241 = TERNARY(T60, 0x1L, T240);}
  val_t T242;
  { T242 = TERNARY(T63, 0x1L, T241);}
  val_t T243;
  { T243 = TERNARY(T66, 0x0L, T242);}
  val_t T244;
  { T244 = TERNARY(T69, 0x0L, T243);}
  val_t T245;
  { T245 = TERNARY(T72, 0x0L, T244);}
  val_t T246;
  { T246 = TERNARY(T75, 0x0L, T245);}
  val_t T247;
  { T247 = TERNARY(T78, 0x0L, T246);}
  val_t T248;
  { T248 = TERNARY(T81, 0x0L, T247);}
  val_t T249;
  { T249 = TERNARY(T84, 0x0L, T248);}
  val_t T250;
  { T250 = TERNARY(T87, 0x0L, T249);}
  val_t T251;
  { T251 = TERNARY(T90, 0x0L, T250);}
  val_t T252;
  { T252 = TERNARY(T93, 0x0L, T251);}
  val_t T253;
  { T253 = TERNARY(T96, 0x0L, T252);}
  val_t T254;
  { T254 = TERNARY(T99, 0x0L, T253);}
  val_t T255;
  { T255 = TERNARY(T102, 0x0L, T254);}
  val_t T256;
  { T256 = TERNARY(T105, 0x0L, T255);}
  val_t Decoder__ctl_mem_func;
  { Decoder__ctl_mem_func = TERNARY(T108, 0x0L, T256);}
  { Decoder__io_ctl_mem_func.values[0] = Decoder__ctl_mem_func;}
  val_t T257;
  { T257 = TERNARY(T60, 0x1L, T57);}
  val_t T258;
  { T258 = TERNARY(T63, 0x1L, T257);}
  val_t T259;
  { T259 = TERNARY(T66, 0x1L, T258);}
  val_t T260;
  { T260 = TERNARY(T69, 0x1L, T259);}
  val_t T261;
  { T261 = TERNARY(T72, 0x1L, T260);}
  val_t T262;
  { T262 = TERNARY(T75, 0x1L, T261);}
  val_t T263;
  { T263 = TERNARY(T78, 0x1L, T262);}
  val_t T264;
  { T264 = TERNARY(T81, 0x0L, T263);}
  val_t T265;
  { T265 = TERNARY(T84, 0x0L, T264);}
  val_t T266;
  { T266 = TERNARY(T87, 0x0L, T265);}
  val_t T267;
  { T267 = TERNARY(T90, 0x0L, T266);}
  val_t T268;
  { T268 = TERNARY(T93, 0x0L, T267);}
  val_t T269;
  { T269 = TERNARY(T96, 0x0L, T268);}
  val_t T270;
  { T270 = TERNARY(T99, 0x0L, T269);}
  val_t T271;
  { T271 = TERNARY(T102, 0x0L, T270);}
  val_t T272;
  { T272 = TERNARY(T105, 0x0L, T271);}
  val_t Decoder__ctl_mem_en;
  { Decoder__ctl_mem_en = TERNARY(T108, 0x0L, T272);}
  { Decoder__io_ctl_mem_en.values[0] = Decoder__ctl_mem_en;}
  val_t T273;
  { T273 = TERNARY(T60, 0x1L, 0x2L);}
  val_t T274;
  { T274 = TERNARY(T63, 0x0L, T273);}
  val_t T275;
  { T275 = TERNARY(T66, 0x2L, T274);}
  val_t T276;
  { T276 = TERNARY(T69, 0x4L, T275);}
  val_t T277;
  { T277 = TERNARY(T72, 0x1L, T276);}
  val_t T278;
  { T278 = TERNARY(T75, 0x3L, T277);}
  val_t T279;
  { T279 = TERNARY(T78, 0x0L, T278);}
  val_t T280;
  { T280 = TERNARY(T81, 0x2L, T279);}
  val_t T281;
  { T281 = TERNARY(T84, 0x2L, T280);}
  val_t T282;
  { T282 = TERNARY(T87, 0x2L, T281);}
  val_t T283;
  { T283 = TERNARY(T90, 0x2L, T282);}
  val_t T284;
  { T284 = TERNARY(T93, 0x2L, T283);}
  val_t T285;
  { T285 = TERNARY(T96, 0x2L, T284);}
  val_t T286;
  { T286 = TERNARY(T99, 0x2L, T285);}
  val_t T287;
  { T287 = TERNARY(T102, 0x2L, T286);}
  val_t T288;
  { T288 = TERNARY(T105, 0x2L, T287);}
  val_t Decoder__ctl_msk_sel;
  { Decoder__ctl_msk_sel = TERNARY(T108, 0x2L, T288);}
  { Decoder__io_ctl_msk_sel.values[0] = Decoder__ctl_msk_sel;}
  { Decoder__io_ctl_csr_cmd.values[0] = 0x0L;}
}


void Decoder_t::clock_hi ( dat_t<1> reset ) {
}


void Decoder_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  Decoder_t* mod = dynamic_cast<Decoder_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->Decoder__io_dec_instr));
  sim_data.outputs.push_back(new dat_api<1>(&mod->Decoder__io_ctl_val_inst));
  sim_data.outputs.push_back(new dat_api<1>(&mod->Decoder__io_ctl_rf_wen));
  sim_data.outputs.push_back(new dat_api<4>(&mod->Decoder__io_ctl_br_type));
  sim_data.outputs.push_back(new dat_api<2>(&mod->Decoder__io_ctl_opa_sel));
  sim_data.outputs.push_back(new dat_api<2>(&mod->Decoder__io_ctl_opb_sel));
  sim_data.outputs.push_back(new dat_api<4>(&mod->Decoder__io_ctl_alu_func));
  sim_data.outputs.push_back(new dat_api<2>(&mod->Decoder__io_ctl_wb_sel));
  sim_data.outputs.push_back(new dat_api<2>(&mod->Decoder__io_ctl_mem_func));
  sim_data.outputs.push_back(new dat_api<1>(&mod->Decoder__io_ctl_mem_en));
  sim_data.outputs.push_back(new dat_api<3>(&mod->Decoder__io_ctl_msk_sel));
  sim_data.outputs.push_back(new dat_api<3>(&mod->Decoder__io_ctl_csr_cmd));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
