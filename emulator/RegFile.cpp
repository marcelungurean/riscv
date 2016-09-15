#include "RegFile.h"

void RegFile_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  RegFile__rf_reg_file.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int RegFile_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void RegFile_t::print ( FILE* f ) {
}
void RegFile_t::print ( std::ostream& s ) {
}


void RegFile_t::dump_init ( FILE* f ) {
}


void RegFile_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void RegFile_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  { T0 = RegFile__rf_reg_file.get(RegFile__io_rf_ra1.values[0], 0);}
  val_t T1;
  T1 = RegFile__io_rf_ra1.values[0] != 0x0L;
  val_t T2;
  { T2 = TERNARY(T1, T0, 0x0L);}
  { RegFile__io_rf_rd1.values[0] = T2;}
  val_t T3;
  T3 = RegFile__io_rf_wa.values[0] != 0x0L;
  { T4.values[0] = RegFile__io_rf_wen.values[0] & T3;}
  val_t T5;
  { T5 = RegFile__rf_reg_file.get(RegFile__io_rf_ra2.values[0], 0);}
  val_t T6;
  T6 = RegFile__io_rf_ra2.values[0] != 0x0L;
  val_t T7;
  { T7 = TERNARY(T6, T5, 0x0L);}
  { RegFile__io_rf_rd2.values[0] = T7;}
}


void RegFile_t::clock_hi ( dat_t<1> reset ) {
  { if (T4.values[0]) RegFile__rf_reg_file.put(RegFile__io_rf_wa.values[0], 0, RegFile__io_rf_wd.values[0]);}
}


void RegFile_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  RegFile_t* mod = dynamic_cast<RegFile_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<5>(&mod->RegFile__io_rf_ra1));
  sim_data.inputs.push_back(new dat_api<5>(&mod->RegFile__io_rf_ra2));
  sim_data.inputs.push_back(new dat_api<5>(&mod->RegFile__io_rf_wa));
  sim_data.inputs.push_back(new dat_api<1>(&mod->RegFile__io_rf_wen));
  sim_data.inputs.push_back(new dat_api<32>(&mod->RegFile__io_rf_wd));
  sim_data.outputs.push_back(new dat_api<32>(&mod->RegFile__io_rf_rd1));
  sim_data.outputs.push_back(new dat_api<32>(&mod->RegFile__io_rf_rd2));
  std::string RegFile__rf_reg_file_path = "RegFile.rf_reg_file";
  for (size_t i = 0 ; i < 32 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->RegFile__rf_reg_file.contents[i]));
    sim_data.signal_map[RegFile__rf_reg_file_path+"["+itos(i,false)+"]"] = 0+i;
  }
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
