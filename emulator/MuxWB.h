#ifndef __MuxWB__
#define __MuxWB__

#include "emulator.h"

class MuxWB_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<2> MuxWB__io_wb_sel;
  dat_t<32> MuxWB__io_wb_mem;
  dat_t<32> MuxWB__io_wb_csr;
  dat_t<32> MuxWB__io_wb_pc4;
  dat_t<32> MuxWB__io_wb_alu;
  dat_t<32> MuxWB__io_wb_wd;
  clk_t clk;

  void init ( val_t rand_init = 0 );
  void clock_lo ( dat_t<1> reset, bool assert_fire=true );
  void clock_hi ( dat_t<1> reset );
  int clock ( dat_t<1> reset );
  void print ( FILE* f );
  void print ( std::ostream& s );
  void dump ( FILE* f, val_t t, dat_t<1> reset=LIT<1>(0) );
  void dump_init ( FILE* f );

};

#include "emul_api.h"
class MuxWB_api_t : public emul_api_t {
 public:
  MuxWB_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
