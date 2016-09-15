#include "InstructionMem.h"

void InstructionMem_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  InstructionMem__mem.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int InstructionMem_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void InstructionMem_t::print ( FILE* f ) {
}
void InstructionMem_t::print ( std::ostream& s ) {
}


void InstructionMem_t::dump_init ( FILE* f ) {
}


void InstructionMem_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void InstructionMem_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  { T0 = InstructionMem__io_addr.values[0];}
  T0 = T0 & 0x3ffL;
  val_t T1;
  { T1 = InstructionMem__mem.get(T0, 0);}
  { InstructionMem__io_data.values[0] = T1;}
}


void InstructionMem_t::clock_hi ( dat_t<1> reset ) {
}


void InstructionMem_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  InstructionMem_t* mod = dynamic_cast<InstructionMem_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->InstructionMem__io_addr));
  sim_data.outputs.push_back(new dat_api<32>(&mod->InstructionMem__io_data));
  std::string InstructionMem__mem_path = "InstructionMem.mem";
  for (size_t i = 0 ; i < 1024 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->InstructionMem__mem.contents[i]));
    sim_data.signal_map[InstructionMem__mem_path+"["+itos(i,false)+"]"] = 0+i;
  }
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
