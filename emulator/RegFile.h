#ifndef __RegFile__
#define __RegFile__

#include "emulator.h"

class RegFile_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> RegFile__io_rf_wen;
  dat_t<1> T4;
  dat_t<5> RegFile__io_rf_ra1;
  dat_t<5> RegFile__io_rf_wa;
  dat_t<5> RegFile__io_rf_ra2;
  dat_t<32> RegFile__io_rf_rd1;
  dat_t<32> RegFile__io_rf_wd;
  dat_t<32> RegFile__io_rf_rd2;
  mem_t<32,32> RegFile__rf_reg_file;
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
class RegFile_api_t : public emul_api_t {
 public:
  RegFile_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
