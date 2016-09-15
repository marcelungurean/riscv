#ifndef __BranchLogic__
#define __BranchLogic__

#include "emulator.h"

class BranchLogic_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> BranchLogic__io_br_ltu;
  dat_t<1> BranchLogic__io_br_lt;
  dat_t<1> BranchLogic__io_br_eq;
  dat_t<1> BranchLogic__io_excp;
  dat_t<3> BranchLogic__io_pc_sel;
  dat_t<4> BranchLogic__io_ctl_br_type;
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
class BranchLogic_api_t : public emul_api_t {
 public:
  BranchLogic_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
