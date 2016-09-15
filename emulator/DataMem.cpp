#include "DataMem.h"

void DataMem_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  DataMem__mem.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int DataMem_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void DataMem_t::print ( FILE* f ) {
}
void DataMem_t::print ( std::ostream& s ) {
}


void DataMem_t::dump_init ( FILE* f ) {
}


void DataMem_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
}




void DataMem_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t T0;
  T0 = DataMem__io_mem_func.values[0] == 0x1L;
  { T1.values[0] = DataMem__io_mem_en.values[0] & T0;}
  T2.values[0] = (DataMem__io_addr.values[0] >> 0) & 1;
  val_t T3;
  T3 = (DataMem__io_addr.values[0] >> 0) & 1;
  val_t T4;
  { T4 = DataMem__mem.get(T3, 0);}
  val_t T5;
  T5 = DataMem__io_mem_func.values[0] == 0x0L;
  val_t T6;
  { T6 = DataMem__io_mem_en.values[0] & T5;}
  val_t T7;
  { T7 = TERNARY(T6, T4, 0x0L);}
  { DataMem__io_rd_data.values[0] = T7;}
}


void DataMem_t::clock_hi ( dat_t<1> reset ) {
  { if (T1.values[0]) DataMem__mem.put(T2.values[0], 0, DataMem__io_wr_data.values[0]);}
}


void DataMem_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  DataMem_t* mod = dynamic_cast<DataMem_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->DataMem__io_addr));
  sim_data.inputs.push_back(new dat_api<32>(&mod->DataMem__io_wr_data));
  sim_data.inputs.push_back(new dat_api<2>(&mod->DataMem__io_mem_func));
  sim_data.inputs.push_back(new dat_api<1>(&mod->DataMem__io_mem_en));
  sim_data.outputs.push_back(new dat_api<32>(&mod->DataMem__io_rd_data));
  std::string DataMem__mem_path = "DataMem.mem";
  for (size_t i = 0 ; i < 1 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->DataMem__mem.contents[i]));
    sim_data.signal_map[DataMem__mem_path+"["+itos(i,false)+"]"] = 0+i;
  }
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
