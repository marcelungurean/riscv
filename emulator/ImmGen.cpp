#include "ImmGen.h"

void ImmGen_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int ImmGen_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void ImmGen_t::print ( FILE* f ) {
}
void ImmGen_t::print ( std::ostream& s ) {
}


void ImmGen_t::dump_init ( FILE* f ) {
}


void ImmGen_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void ImmGen_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t ImmGen__immi;
  { ImmGen__immi = ImmGen__io_instr.values[0] >> 20;}
  ImmGen__immi = ImmGen__immi & 0xfffL;
  val_t T0;
  T0 = (ImmGen__immi >> 11) & 1;
  val_t T1;
  { T1 = TERNARY(T0, 0xfffffL, 0x0L);}
  val_t T2;
  { T2 = ImmGen__immi | T1 << 12;}
  { ImmGen__io_immi_sxt.values[0] = T2;}
  val_t T3;
  { T3 = ImmGen__io_instr.values[0] >> 7;}
  T3 = T3 & 0x1fL;
  val_t T4;
  { T4 = ImmGen__io_instr.values[0] >> 25;}
  T4 = T4 & 0x7fL;
  val_t ImmGen__imms;
  { ImmGen__imms = T3 | T4 << 5;}
  val_t T5;
  T5 = (ImmGen__immi >> 11) & 1;
  val_t T6;
  { T6 = TERNARY(T5, 0xfffffL, 0x0L);}
  val_t T7;
  { T7 = ImmGen__imms | T6 << 12;}
  { ImmGen__io_imms_sxt.values[0] = T7;}
  val_t T8;
  { T8 = ImmGen__io_instr.values[0] >> 8;}
  T8 = T8 & 0xfL;
  val_t T9;
  { T9 = ImmGen__io_instr.values[0] >> 25;}
  T9 = T9 & 0x3fL;
  val_t T10;
  { T10 = T8 | T9 << 4;}
  val_t T11;
  T11 = (ImmGen__io_instr.values[0] >> 7) & 1;
  val_t T12;
  T12 = (ImmGen__io_instr.values[0] >> 31) & 1;
  val_t T13;
  { T13 = T11 | T12 << 1;}
  val_t ImmGen__immb;
  { ImmGen__immb = T10 | T13 << 10;}
  val_t T14;
  T14 = (ImmGen__immb >> 11) & 1;
  val_t T15;
  { T15 = TERNARY(T14, 0x7ffffL, 0x0L);}
  val_t T16;
  { T16 = 0x0L | T15 << 1;}
  val_t T17;
  { T17 = T16 | 0x0L << 20;}
  { ImmGen__io_immb_sxt.values[0] = T17;}
  val_t T18;
  { T18 = ImmGen__io_instr.values[0] >> 12;}
  T18 = T18 & 0xfffffL;
  val_t ImmGen__immu;
  { ImmGen__immu = 0x0L | T18 << 12;}
  { ImmGen__io_immu_sxt.values[0] = ImmGen__immu;}
  val_t T19;
  { T19 = ImmGen__io_instr.values[0] >> 21;}
  T19 = T19 & 0x3ffL;
  val_t T20;
  T20 = (ImmGen__io_instr.values[0] >> 20) & 1;
  val_t T21;
  { T21 = T19 | T20 << 10;}
  val_t T22;
  { T22 = ImmGen__io_instr.values[0] >> 12;}
  T22 = T22 & 0xffL;
  val_t T23;
  T23 = (ImmGen__io_instr.values[0] >> 31) & 1;
  val_t T24;
  { T24 = T22 | T23 << 8;}
  val_t ImmGen__immj;
  { ImmGen__immj = T21 | T24 << 11;}
  val_t T25;
  T25 = (ImmGen__immj >> 19) & 1;
  val_t T26;
  { T26 = TERNARY(T25, 0x7ffL, 0x0L);}
  val_t T27;
  { T27 = ImmGen__immj | T26 << 20;}
  val_t T28;
  { T28 = T27 | 0x0L << 31;}
  { ImmGen__io_immj_sxt.values[0] = T28;}
}


void ImmGen_t::clock_hi ( dat_t<1> reset ) {
}


void ImmGen_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  ImmGen_t* mod = dynamic_cast<ImmGen_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->ImmGen__io_instr));
  sim_data.outputs.push_back(new dat_api<32>(&mod->ImmGen__io_immi_sxt));
  sim_data.outputs.push_back(new dat_api<32>(&mod->ImmGen__io_imms_sxt));
  sim_data.outputs.push_back(new dat_api<32>(&mod->ImmGen__io_immb_sxt));
  sim_data.outputs.push_back(new dat_api<32>(&mod->ImmGen__io_immu_sxt));
  sim_data.outputs.push_back(new dat_api<32>(&mod->ImmGen__io_immj_sxt));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
