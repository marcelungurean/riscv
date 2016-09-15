#ifndef __Core__
#define __Core__

#include "emulator.h"

class Core_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> Core_Decoder__io_ctl_mem_en;
  dat_t<1> Core_DataMem__io_mem_en;
  dat_t<1> T73;
  dat_t<1> Core_Alu__io_zero;
  dat_t<1> Core_Decoder__io_ctl_rf_wen;
  dat_t<1> Core_Decoder__io_ctl_val_inst;
  dat_t<1> Core_RegFile__io_rf_wen;
  dat_t<1> T388;
  dat_t<1> Core_BranchLogic__io_br_ltu;
  dat_t<1> Core_BranchLogic__io_br_lt;
  dat_t<1> Core_BranchLogic__io_br_eq;
  dat_t<1> Core_BranchLogic__io_excp;
  dat_t<1> reset;
  dat_t<2> Core_Decoder__io_ctl_mem_func;
  dat_t<2> Core_DataMem__io_mem_func;
  dat_t<2> Core_Decoder__io_ctl_opa_sel;
  dat_t<2> Core_MuxOpA__io_opa_sel;
  dat_t<2> Core_Decoder__io_ctl_opb_sel;
  dat_t<2> Core_MuxOpB__io_opb_sel;
  dat_t<2> Core_Decoder__io_ctl_wb_sel;
  dat_t<2> Core_MuxWB__io_wb_sel;
  dat_t<3> Core_Decoder__io_ctl_msk_sel;
  dat_t<3> Core_Decoder__io_ctl_csr_cmd;
  dat_t<3> Core_BranchLogic__io_pc_sel;
  dat_t<3> Core_MuxPC__io_pc_sel;
  dat_t<4> Core_Decoder__io_ctl_alu_func;
  dat_t<4> Core_Alu__io_op;
  dat_t<4> Core_Decoder__io_ctl_br_type;
  dat_t<4> Core_BranchLogic__io_ctl_br_type;
  dat_t<5> Core_RegFile__io_rf_ra2;
  dat_t<5> Core_RegFile__io_rf_ra1;
  dat_t<5> Core_RegFile__io_rf_wa;
  dat_t<10> Core_DataMem__io_addr;
  dat_t<10> Core_InstructionMem__io_addr;
  dat_t<32> Core_RegFile__io_rf_rd2;
  dat_t<32> Core_DataMem__io_wr_data;
  dat_t<32> Core_Decoder__io_dec_instr;
  dat_t<32> Core_ImmGen__io_instr;
  dat_t<32> Core_ImmGen__io_immu_sxt;
  dat_t<32> Core_MuxOpA__io_opa_imz;
  dat_t<32> Core_MuxOpA__io_opa_imu;
  dat_t<32> Core_RegFile__io_rf_rd1;
  dat_t<32> Core_MuxOpA__io_opa_rsa;
  dat_t<32> Core_MuxOpA__io_opa_alu_in;
  dat_t<32> Core_Alu__io_a;
  dat_t<32> Core_MuxOpB__io_opb_pc;
  dat_t<32> Core_ImmGen__io_imms_sxt;
  dat_t<32> Core_MuxOpB__io_opb_ims;
  dat_t<32> Core_ImmGen__io_immi_sxt;
  dat_t<32> Core_MuxOpB__io_opb_imi;
  dat_t<32> Core_MuxOpB__io_opb_rsb;
  dat_t<32> Core_MuxOpB__io_opb_alu_in;
  dat_t<32> Core_Alu__io_b;
  dat_t<32> Core_Alu__io_out;
  dat_t<32> Core_DataMem__io_rd_data;
  dat_t<32> Core_MuxWB__io_wb_mem;
  dat_t<32> Core_MuxWB__io_wb_csr;
  dat_t<32> Core_MuxWB__io_wb_pc4;
  dat_t<32> Core_MuxWB__io_wb_alu;
  dat_t<32> Core_MuxWB__io_wb_wd;
  dat_t<32> Core_RegFile__io_rf_wd;
  dat_t<32> Core_InstructionMem__io_data;
  dat_t<32> T450;
  dat_t<32> Core__exec_instr_reg;
  dat_t<32> T455;
  dat_t<32> Core__exec_pc_reg;
  dat_t<32> Core_MuxPC__io_pc_excp;
  dat_t<32> Core_ImmGen__io_immj_sxt;
  dat_t<32> Core_MuxPC__io_pc_jmp;
  dat_t<32> Core_ImmGen__io_immb_sxt;
  dat_t<32> Core_MuxPC__io_pc_br;
  dat_t<32> Core_MuxPC__io_pc_jalr;
  dat_t<32> Core_MuxPC__io_pc_pc4;
  dat_t<32> Core_MuxPC__io_pc_out;
  dat_t<32> T488;
  dat_t<32> Core__fetch_pc_reg;
  dat_t<32> T489;
  dat_t<32> Core__exec_pc4_reg;
  mem_t<32,1024> Core_DataMem__mem;
  mem_t<32,1024> Core_InstructionMem__mem;
  mem_t<32,32> Core_RegFile__rf_reg_file;
  dat_t<1> Core_Decoder__io_ctl_mem_en__prev;
  dat_t<1> Core_DataMem__io_mem_en__prev;
  dat_t<1> Core_Alu__io_zero__prev;
  dat_t<1> Core_Decoder__io_ctl_rf_wen__prev;
  dat_t<1> Core_Decoder__io_ctl_val_inst__prev;
  dat_t<1> Core_RegFile__io_rf_wen__prev;
  dat_t<1> Core_BranchLogic__io_br_ltu__prev;
  dat_t<1> Core_BranchLogic__io_br_lt__prev;
  dat_t<1> Core_BranchLogic__io_br_eq__prev;
  dat_t<1> Core_BranchLogic__io_excp__prev;
  dat_t<2> Core_Decoder__io_ctl_mem_func__prev;
  dat_t<2> Core_DataMem__io_mem_func__prev;
  dat_t<2> Core_Decoder__io_ctl_opa_sel__prev;
  dat_t<2> Core_MuxOpA__io_opa_sel__prev;
  dat_t<2> Core_Decoder__io_ctl_opb_sel__prev;
  dat_t<2> Core_MuxOpB__io_opb_sel__prev;
  dat_t<2> Core_Decoder__io_ctl_wb_sel__prev;
  dat_t<2> Core_MuxWB__io_wb_sel__prev;
  dat_t<3> Core_Decoder__io_ctl_msk_sel__prev;
  dat_t<3> Core_Decoder__io_ctl_csr_cmd__prev;
  dat_t<3> Core_BranchLogic__io_pc_sel__prev;
  dat_t<3> Core_MuxPC__io_pc_sel__prev;
  dat_t<4> Core_Decoder__io_ctl_alu_func__prev;
  dat_t<4> Core_Alu__io_op__prev;
  dat_t<4> Core_Decoder__io_ctl_br_type__prev;
  dat_t<4> Core_BranchLogic__io_ctl_br_type__prev;
  dat_t<5> Core_RegFile__io_rf_ra2__prev;
  dat_t<5> Core_RegFile__io_rf_ra1__prev;
  dat_t<5> Core_RegFile__io_rf_wa__prev;
  dat_t<10> Core_DataMem__io_addr__prev;
  dat_t<10> Core_InstructionMem__io_addr__prev;
  dat_t<32> Core_RegFile__io_rf_rd2__prev;
  dat_t<32> Core_DataMem__io_wr_data__prev;
  dat_t<32> Core_Decoder__io_dec_instr__prev;
  dat_t<32> Core_ImmGen__io_instr__prev;
  dat_t<32> Core_ImmGen__io_immu_sxt__prev;
  dat_t<32> Core_MuxOpA__io_opa_imz__prev;
  dat_t<32> Core_MuxOpA__io_opa_imu__prev;
  dat_t<32> Core_RegFile__io_rf_rd1__prev;
  dat_t<32> Core_MuxOpA__io_opa_rsa__prev;
  dat_t<32> Core_MuxOpA__io_opa_alu_in__prev;
  dat_t<32> Core_Alu__io_a__prev;
  dat_t<32> Core_MuxOpB__io_opb_pc__prev;
  dat_t<32> Core_ImmGen__io_imms_sxt__prev;
  dat_t<32> Core_MuxOpB__io_opb_ims__prev;
  dat_t<32> Core_ImmGen__io_immi_sxt__prev;
  dat_t<32> Core_MuxOpB__io_opb_imi__prev;
  dat_t<32> Core_MuxOpB__io_opb_rsb__prev;
  dat_t<32> Core_MuxOpB__io_opb_alu_in__prev;
  dat_t<32> Core_Alu__io_b__prev;
  dat_t<32> Core_Alu__io_out__prev;
  dat_t<32> Core_DataMem__io_rd_data__prev;
  dat_t<32> Core_MuxWB__io_wb_mem__prev;
  dat_t<32> Core_MuxWB__io_wb_csr__prev;
  dat_t<32> Core_MuxWB__io_wb_pc4__prev;
  dat_t<32> Core_MuxWB__io_wb_alu__prev;
  dat_t<32> Core_MuxWB__io_wb_wd__prev;
  dat_t<32> Core_RegFile__io_rf_wd__prev;
  dat_t<32> Core_InstructionMem__io_data__prev;
  dat_t<32> Core__exec_instr_reg__prev;
  dat_t<32> Core__exec_pc_reg__prev;
  dat_t<32> Core_MuxPC__io_pc_excp__prev;
  dat_t<32> Core_ImmGen__io_immj_sxt__prev;
  dat_t<32> Core_MuxPC__io_pc_jmp__prev;
  dat_t<32> Core_ImmGen__io_immb_sxt__prev;
  dat_t<32> Core_MuxPC__io_pc_br__prev;
  dat_t<32> Core_MuxPC__io_pc_jalr__prev;
  dat_t<32> Core_MuxPC__io_pc_pc4__prev;
  dat_t<32> Core_MuxPC__io_pc_out__prev;
  dat_t<32> Core__fetch_pc_reg__prev;
  dat_t<32> Core__exec_pc4_reg__prev;
  clk_t clk;
  dat_t<1> reset__prev;

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
class Core_api_t : public emul_api_t {
 public:
  Core_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
