#include "MuxOpB.h"

void MuxOpB_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int MuxOpB_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void MuxOpB_t::print ( FILE* f ) {
}
void MuxOpB_t::print ( std::ostream& s ) {
}


void MuxOpB_t::dump_init ( FILE* f ) {
}


void MuxOpB_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void MuxOpB_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  T0 = MuxOpB__io_opb_sel.values[0] == 0x1L;
  val_t T1;
  { T1 = TERNARY(T0, MuxOpB__io_opb_pc.values[0], 0x0L);}
  val_t T2;
  T2 = MuxOpB__io_opb_sel.values[0] == 0x3L;
  val_t T3;
  { T3 = TERNARY_1(T2, MuxOpB__io_opb_ims.values[0], T1);}
  val_t T4;
  T4 = MuxOpB__io_opb_sel.values[0] == 0x2L;
  val_t T5;
  { T5 = TERNARY_1(T4, MuxOpB__io_opb_imi.values[0], T3);}
  val_t T6;
  T6 = MuxOpB__io_opb_sel.values[0] == 0x0L;
  val_t T7;
  { T7 = TERNARY_1(T6, MuxOpB__io_opb_rsb.values[0], T5);}
  { MuxOpB__io_opb_alu_in.values[0] = T7;}
}


void MuxOpB_t::clock_hi ( dat_t<1> reset ) {
}


void MuxOpB_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  MuxOpB_t* mod = dynamic_cast<MuxOpB_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<2>(&mod->MuxOpB__io_opb_sel));
  sim_data.inputs.push_back(new dat_api<32>(&mod->MuxOpB__io_opb_rsb));
  sim_data.inputs.push_back(new dat_api<32>(&mod->MuxOpB__io_opb_imi));
  sim_data.inputs.push_back(new dat_api<32>(&mod->MuxOpB__io_opb_ims));
  sim_data.inputs.push_back(new dat_api<32>(&mod->MuxOpB__io_opb_pc));
  sim_data.outputs.push_back(new dat_api<32>(&mod->MuxOpB__io_opb_alu_in));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
