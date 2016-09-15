#include "Alu.h"

void Alu_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int Alu_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void Alu_t::print ( FILE* f ) {
}
void Alu_t::print ( std::ostream& s ) {
}


void Alu_t::dump_init ( FILE* f ) {
}


void Alu_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void Alu_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  T0 = Alu__io_op.values[0] == 0xfL;
  val_t T1;
  { T1 = TERNARY(T0, Alu__io_a.values[0], 0x0L);}
  val_t T2;
  { T2 = Alu__io_b.values[0];}
  T2 = T2 & 0x1fL;
  val_t T3;
  T3 = sval_t(Alu__io_a.values[0] << 32) >> (32 + T2);
  T3 = T3 & 0xffffffffL;
  val_t T4;
  T4 = Alu__io_op.values[0] == 0xeL;
  val_t T5;
  { T5 = TERNARY_1(T4, T3, T1);}
  val_t T6;
  T6 = Alu__io_a.values[0] >> T2;
  val_t T7;
  T7 = Alu__io_op.values[0] == 0xdL;
  val_t T8;
  { T8 = TERNARY_1(T7, T6, T5);}
  val_t T9;
  T9 = Alu__io_a.values[0] << T2;
  T9 = T9 & 0x7fffffffffffffffL;
  val_t T10;
  { T10 = T9;}
  T10 = T10 & 0xffffffffL;
  val_t T11;
  T11 = Alu__io_op.values[0] == 0xcL;
  val_t T12;
  { T12 = TERNARY_1(T11, T10, T8);}
  val_t T13;
  T13 = Alu__io_b.values[0]<=Alu__io_a.values[0];
  val_t T14;
  { T14 = T13 | 0x0L << 1;}
  val_t T15;
  T15 = Alu__io_op.values[0] == 0xbL;
  val_t T16;
  { T16 = TERNARY_1(T15, T14, T12);}
  val_t T17;
  T17 = (Alu__io_b.values[0] >> 31) & 1;
  val_t T18;
  T18 = Alu__io_b.values[0]<=Alu__io_a.values[0];
  val_t T19;
  T19 = (Alu__io_a.values[0] >> 31) & 1;
  val_t T20;
  T20 = T17 == T19;
  val_t T21;
  { T21 = TERNARY_1(T20, T18, T17);}
  val_t T22;
  { T22 = T21 | 0x0L << 1;}
  val_t T23;
  T23 = Alu__io_op.values[0] == 0xaL;
  val_t T24;
  { T24 = TERNARY_1(T23, T22, T16);}
  val_t T25;
  T25 = Alu__io_a.values[0] != Alu__io_b.values[0];
  val_t T26;
  { T26 = T25 | 0x0L << 1;}
  val_t T27;
  T27 = Alu__io_op.values[0] == 0x9L;
  val_t T28;
  { T28 = TERNARY_1(T27, T26, T24);}
  val_t T29;
  T29 = Alu__io_a.values[0] == Alu__io_b.values[0];
  val_t T30;
  { T30 = T29 | 0x0L << 1;}
  val_t T31;
  T31 = Alu__io_op.values[0] == 0x8L;
  val_t T32;
  { T32 = TERNARY_1(T31, T30, T28);}
  val_t T33;
  T33 = Alu__io_a.values[0]<Alu__io_b.values[0];
  val_t T34;
  { T34 = T33 | 0x0L << 1;}
  val_t T35;
  T35 = Alu__io_op.values[0] == 0x7L;
  val_t T36;
  { T36 = TERNARY_1(T35, T34, T32);}
  val_t T37;
  T37 = (Alu__io_a.values[0] >> 31) & 1;
  val_t T38;
  T38 = Alu__io_a.values[0]<Alu__io_b.values[0];
  val_t T39;
  T39 = (Alu__io_b.values[0] >> 31) & 1;
  val_t T40;
  T40 = T37 == T39;
  val_t T41;
  { T41 = TERNARY_1(T40, T38, T37);}
  val_t T42;
  { T42 = T41 | 0x0L << 1;}
  val_t T43;
  T43 = Alu__io_op.values[0] == 0x6L;
  val_t T44;
  { T44 = TERNARY_1(T43, T42, T36);}
  val_t T45;
  { T45 = Alu__io_a.values[0] ^ Alu__io_b.values[0];}
  val_t T46;
  T46 = Alu__io_op.values[0] == 0x5L;
  val_t T47;
  { T47 = TERNARY_1(T46, T45, T44);}
  val_t T48;
  { T48 = Alu__io_a.values[0] | Alu__io_b.values[0];}
  val_t T49;
  T49 = Alu__io_op.values[0] == 0x4L;
  val_t T50;
  { T50 = TERNARY_1(T49, T48, T47);}
  val_t T51;
  { T51 = Alu__io_a.values[0] & Alu__io_b.values[0];}
  val_t T52;
  T52 = Alu__io_op.values[0] == 0x3L;
  val_t T53;
  { T53 = TERNARY_1(T52, T51, T50);}
  val_t T54;
  { T54 = Alu__io_a.values[0]-Alu__io_b.values[0];}
  T54 = T54 & 0xffffffffL;
  val_t T55;
  T55 = Alu__io_op.values[0] == 0x2L;
  val_t T56;
  { T56 = TERNARY_1(T55, T54, T53);}
  val_t T57;
  { T57 = Alu__io_a.values[0]+Alu__io_b.values[0];}
  T57 = T57 & 0xffffffffL;
  val_t T58;
  T58 = Alu__io_op.values[0] == 0x1L;
  val_t T59;
  { T59 = TERNARY_1(T58, T57, T56);}
  { Alu__io_out.values[0] = T59;}
  val_t T60;
  T60 = Alu__io_out.values[0] == 0x0L;
  val_t T61;
  { T61 = TERNARY(T60, 0x1L, 0x0L);}
  { Alu__io_zero.values[0] = T61;}
}


void Alu_t::clock_hi ( dat_t<1> reset ) {
}


void Alu_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  Alu_t* mod = dynamic_cast<Alu_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->Alu__io_a));
  sim_data.inputs.push_back(new dat_api<32>(&mod->Alu__io_b));
  sim_data.inputs.push_back(new dat_api<4>(&mod->Alu__io_op));
  sim_data.outputs.push_back(new dat_api<32>(&mod->Alu__io_out));
  sim_data.outputs.push_back(new dat_api<1>(&mod->Alu__io_zero));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
