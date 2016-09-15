#ifndef __Decoder__
#define __Decoder__

#include "emulator.h"

class Decoder_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> Decoder__io_ctl_val_inst;
  dat_t<1> Decoder__io_ctl_rf_wen;
  dat_t<1> Decoder__io_ctl_mem_en;
  dat_t<2> Decoder__io_ctl_opa_sel;
  dat_t<2> Decoder__io_ctl_opb_sel;
  dat_t<2> Decoder__io_ctl_wb_sel;
  dat_t<2> Decoder__io_ctl_mem_func;
  dat_t<3> Decoder__io_ctl_msk_sel;
  dat_t<3> Decoder__io_ctl_csr_cmd;
  dat_t<4> Decoder__io_ctl_br_type;
  dat_t<4> Decoder__io_ctl_alu_func;
  dat_t<32> Decoder__io_dec_instr;
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
class Decoder_api_t : public emul_api_t {
 public:
  Decoder_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
