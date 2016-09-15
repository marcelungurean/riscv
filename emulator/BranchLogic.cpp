#include "BranchLogic.h"

void BranchLogic_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int BranchLogic_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void BranchLogic_t::print ( FILE* f ) {
}
void BranchLogic_t::print ( std::ostream& s ) {
}


void BranchLogic_t::dump_init ( FILE* f ) {
}


void BranchLogic_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void BranchLogic_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  T0 = BranchLogic__io_ctl_br_type.values[0] == 0x8L;
  val_t T1;
  { T1 = TERNARY(T0, 0x1L, 0x0L);}
  val_t T2;
  T2 = BranchLogic__io_ctl_br_type.values[0] == 0x7L;
  val_t T3;
  { T3 = TERNARY(T2, 0x3L, T1);}
  val_t T4;
  { T4 = TERNARY(BranchLogic__io_br_ltu.values[0], 0x2L, 0x0L);}
  val_t T5;
  T5 = BranchLogic__io_ctl_br_type.values[0] == 0x6L;
  val_t T6;
  { T6 = TERNARY_1(T5, T4, T3);}
  val_t T7;
  { T7 = TERNARY(BranchLogic__io_br_lt.values[0], 0x2L, 0x0L);}
  val_t T8;
  T8 = BranchLogic__io_ctl_br_type.values[0] == 0x5L;
  val_t T9;
  { T9 = TERNARY_1(T8, T7, T6);}
  val_t T10;
  { T10 = BranchLogic__io_br_ltu.values[0] ^ 0x1L;}
  val_t T11;
  { T11 = TERNARY(T10, 0x2L, 0x0L);}
  val_t T12;
  T12 = BranchLogic__io_ctl_br_type.values[0] == 0x4L;
  val_t T13;
  { T13 = TERNARY_1(T12, T11, T9);}
  val_t T14;
  { T14 = BranchLogic__io_br_lt.values[0] ^ 0x1L;}
  val_t T15;
  { T15 = TERNARY(T14, 0x2L, 0x0L);}
  val_t T16;
  T16 = BranchLogic__io_ctl_br_type.values[0] == 0x3L;
  val_t T17;
  { T17 = TERNARY_1(T16, T15, T13);}
  val_t T18;
  { T18 = TERNARY(BranchLogic__io_br_eq.values[0], 0x2L, 0x0L);}
  val_t T19;
  T19 = BranchLogic__io_ctl_br_type.values[0] == 0x1L;
  val_t T20;
  { T20 = TERNARY_1(T19, T18, T17);}
  val_t T21;
  { T21 = BranchLogic__io_br_eq.values[0] ^ 0x1L;}
  val_t T22;
  { T22 = TERNARY(T21, 0x2L, 0x0L);}
  val_t T23;
  T23 = BranchLogic__io_ctl_br_type.values[0] == 0x2L;
  val_t T24;
  { T24 = TERNARY_1(T23, T22, T20);}
  val_t T25;
  T25 = BranchLogic__io_ctl_br_type.values[0] == 0x0L;
  val_t T26;
  { T26 = TERNARY(T25, 0x0L, T24);}
  val_t T27;
  { T27 = TERNARY(BranchLogic__io_excp.values[0], 0x4L, T26);}
  { BranchLogic__io_pc_sel.values[0] = T27;}
}


void BranchLogic_t::clock_hi ( dat_t<1> reset ) {
}


void BranchLogic_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  BranchLogic_t* mod = dynamic_cast<BranchLogic_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<1>(&mod->BranchLogic__io_excp));
  sim_data.inputs.push_back(new dat_api<4>(&mod->BranchLogic__io_ctl_br_type));
  sim_data.inputs.push_back(new dat_api<1>(&mod->BranchLogic__io_br_eq));
  sim_data.inputs.push_back(new dat_api<1>(&mod->BranchLogic__io_br_lt));
  sim_data.inputs.push_back(new dat_api<1>(&mod->BranchLogic__io_br_ltu));
  sim_data.outputs.push_back(new dat_api<3>(&mod->BranchLogic__io_pc_sel));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
