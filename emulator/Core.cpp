#include "Core.h"

void Core_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  Core_DataMem__mem.randomize(&__rand_seed);
  Core_InstructionMem__mem.randomize(&__rand_seed);
  Core_RegFile__rf_reg_file.randomize(&__rand_seed);
  Core__exec_instr_reg.randomize(&__rand_seed);
  Core__exec_pc_reg.randomize(&__rand_seed);
  Core__fetch_pc_reg.randomize(&__rand_seed);
  Core__exec_pc4_reg.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = 0;
  clk.values[0] = 0;
}


int Core_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (!reset.to_bool()) print( std::cerr );
  mod_t::dump( reset );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void Core_t::print ( FILE* f ) {
}
void Core_t::print ( std::ostream& s ) {
}


void Core_t::dump_init ( FILE* f ) {
  fputs("$timescale 1ps $end\n", f);
  fputs("$scope module Core $end\n", f);
  fputs("$var wire 1 \x21 clk $end\n", f);
  fputs("$var wire 1 \x22 reset $end\n", f);
  fputs("$var wire 32 \x5e exec_instr_reg $end\n", f);
  fputs("$var wire 32 \x5f exec_pc_reg $end\n", f);
  fputs("$var wire 32 \x68 fetch_pc_reg $end\n", f);
  fputs("$var wire 32 \x69 exec_pc4_reg $end\n", f);
  fputs("$scope module MuxPC $end\n", f);
  fputs("$var wire 3 \x38 io_pc_sel $end\n", f);
  fputs("$var wire 32 \x60 io_pc_excp $end\n", f);
  fputs("$var wire 32 \x62 io_pc_jmp $end\n", f);
  fputs("$var wire 32 \x64 io_pc_br $end\n", f);
  fputs("$var wire 32 \x65 io_pc_jalr $end\n", f);
  fputs("$var wire 32 \x66 io_pc_pc4 $end\n", f);
  fputs("$var wire 32 \x67 io_pc_out $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module RegFile $end\n", f);
  fputs("$var wire 1 \x28 io_rf_wen $end\n", f);
  fputs("$var wire 5 \x3d io_rf_ra2 $end\n", f);
  fputs("$var wire 5 \x3e io_rf_ra1 $end\n", f);
  fputs("$var wire 5 \x3f io_rf_wa $end\n", f);
  fputs("$var wire 32 \x42 io_rf_rd2 $end\n", f);
  fputs("$var wire 32 \x49 io_rf_rd1 $end\n", f);
  fputs("$var wire 32 \x5c io_rf_wd $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module ImmGen $end\n", f);
  fputs("$var wire 32 \x45 io_instr $end\n", f);
  fputs("$var wire 32 \x46 io_immu_sxt $end\n", f);
  fputs("$var wire 32 \x4e io_imms_sxt $end\n", f);
  fputs("$var wire 32 \x50 io_immi_sxt $end\n", f);
  fputs("$var wire 32 \x61 io_immj_sxt $end\n", f);
  fputs("$var wire 32 \x63 io_immb_sxt $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module Decoder $end\n", f);
  fputs("$var wire 1 \x23 io_ctl_mem_en $end\n", f);
  fputs("$var wire 1 \x26 io_ctl_rf_wen $end\n", f);
  fputs("$var wire 1 \x27 io_ctl_val_inst $end\n", f);
  fputs("$var wire 2 \x2d io_ctl_mem_func $end\n", f);
  fputs("$var wire 2 \x2f io_ctl_opa_sel $end\n", f);
  fputs("$var wire 2 \x31 io_ctl_opb_sel $end\n", f);
  fputs("$var wire 2 \x33 io_ctl_wb_sel $end\n", f);
  fputs("$var wire 3 \x35 io_ctl_msk_sel $end\n", f);
  fputs("$var wire 3 \x36 io_ctl_csr_cmd $end\n", f);
  fputs("$var wire 4 \x39 io_ctl_alu_func $end\n", f);
  fputs("$var wire 4 \x3b io_ctl_br_type $end\n", f);
  fputs("$var wire 32 \x44 io_dec_instr $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module MuxOpA $end\n", f);
  fputs("$var wire 2 \x30 io_opa_sel $end\n", f);
  fputs("$var wire 32 \x47 io_opa_imz $end\n", f);
  fputs("$var wire 32 \x48 io_opa_imu $end\n", f);
  fputs("$var wire 32 \x4a io_opa_rsa $end\n", f);
  fputs("$var wire 32 \x4b io_opa_alu_in $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module MuxOpB $end\n", f);
  fputs("$var wire 2 \x32 io_opb_sel $end\n", f);
  fputs("$var wire 32 \x4d io_opb_pc $end\n", f);
  fputs("$var wire 32 \x4f io_opb_ims $end\n", f);
  fputs("$var wire 32 \x51 io_opb_imi $end\n", f);
  fputs("$var wire 32 \x52 io_opb_rsb $end\n", f);
  fputs("$var wire 32 \x53 io_opb_alu_in $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module Alu $end\n", f);
  fputs("$var wire 1 \x25 io_zero $end\n", f);
  fputs("$var wire 4 \x3a io_op $end\n", f);
  fputs("$var wire 32 \x4c io_a $end\n", f);
  fputs("$var wire 32 \x54 io_b $end\n", f);
  fputs("$var wire 32 \x55 io_out $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module InstructionMem $end\n", f);
  fputs("$var wire 10 \x41 io_addr $end\n", f);
  fputs("$var wire 32 \x5d io_data $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module DataMem $end\n", f);
  fputs("$var wire 1 \x24 io_mem_en $end\n", f);
  fputs("$var wire 2 \x2e io_mem_func $end\n", f);
  fputs("$var wire 10 \x40 io_addr $end\n", f);
  fputs("$var wire 32 \x43 io_wr_data $end\n", f);
  fputs("$var wire 32 \x56 io_rd_data $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module MuxWB $end\n", f);
  fputs("$var wire 2 \x34 io_wb_sel $end\n", f);
  fputs("$var wire 32 \x57 io_wb_mem $end\n", f);
  fputs("$var wire 32 \x58 io_wb_csr $end\n", f);
  fputs("$var wire 32 \x59 io_wb_pc4 $end\n", f);
  fputs("$var wire 32 \x5a io_wb_alu $end\n", f);
  fputs("$var wire 32 \x5b io_wb_wd $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$scope module BranchLogic $end\n", f);
  fputs("$var wire 1 \x29 io_br_ltu $end\n", f);
  fputs("$var wire 1 \x2a io_br_lt $end\n", f);
  fputs("$var wire 1 \x2b io_br_eq $end\n", f);
  fputs("$var wire 1 \x2c io_excp $end\n", f);
  fputs("$var wire 3 \x37 io_pc_sel $end\n", f);
  fputs("$var wire 4 \x3c io_ctl_br_type $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$enddefinitions $end\n", f);
  fputs("$dumpvars\n", f);
  fputs("$end\n", f);
  fputs("#0\n", f);
  if (clk.cnt == 0) {
    clk.values[0] = 1;
    dat_dump<1>(f, clk, 0x21);
  }
  dat_t<1> reset = LIT<1>(1);
  dat_dump<1>(f, reset, 0x22);
  dat_dump<1>(f, Core_Decoder__io_ctl_mem_en, 0x23);
  Core_Decoder__io_ctl_mem_en__prev = Core_Decoder__io_ctl_mem_en;
  dat_dump<1>(f, Core_DataMem__io_mem_en, 0x24);
  Core_DataMem__io_mem_en__prev = Core_DataMem__io_mem_en;
  dat_dump<1>(f, Core_Alu__io_zero, 0x25);
  Core_Alu__io_zero__prev = Core_Alu__io_zero;
  dat_dump<1>(f, Core_Decoder__io_ctl_rf_wen, 0x26);
  Core_Decoder__io_ctl_rf_wen__prev = Core_Decoder__io_ctl_rf_wen;
  dat_dump<1>(f, Core_Decoder__io_ctl_val_inst, 0x27);
  Core_Decoder__io_ctl_val_inst__prev = Core_Decoder__io_ctl_val_inst;
  dat_dump<1>(f, Core_RegFile__io_rf_wen, 0x28);
  Core_RegFile__io_rf_wen__prev = Core_RegFile__io_rf_wen;
  dat_dump<1>(f, Core_BranchLogic__io_br_ltu, 0x29);
  Core_BranchLogic__io_br_ltu__prev = Core_BranchLogic__io_br_ltu;
  dat_dump<1>(f, Core_BranchLogic__io_br_lt, 0x2a);
  Core_BranchLogic__io_br_lt__prev = Core_BranchLogic__io_br_lt;
  dat_dump<1>(f, Core_BranchLogic__io_br_eq, 0x2b);
  Core_BranchLogic__io_br_eq__prev = Core_BranchLogic__io_br_eq;
  dat_dump<1>(f, Core_BranchLogic__io_excp, 0x2c);
  Core_BranchLogic__io_excp__prev = Core_BranchLogic__io_excp;
  dat_dump<1>(f, Core_Decoder__io_ctl_mem_func, 0x2d);
  Core_Decoder__io_ctl_mem_func__prev = Core_Decoder__io_ctl_mem_func;
  dat_dump<1>(f, Core_DataMem__io_mem_func, 0x2e);
  Core_DataMem__io_mem_func__prev = Core_DataMem__io_mem_func;
  dat_dump<1>(f, Core_Decoder__io_ctl_opa_sel, 0x2f);
  Core_Decoder__io_ctl_opa_sel__prev = Core_Decoder__io_ctl_opa_sel;
  dat_dump<1>(f, Core_MuxOpA__io_opa_sel, 0x30);
  Core_MuxOpA__io_opa_sel__prev = Core_MuxOpA__io_opa_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_opb_sel, 0x31);
  Core_Decoder__io_ctl_opb_sel__prev = Core_Decoder__io_ctl_opb_sel;
  dat_dump<1>(f, Core_MuxOpB__io_opb_sel, 0x32);
  Core_MuxOpB__io_opb_sel__prev = Core_MuxOpB__io_opb_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_wb_sel, 0x33);
  Core_Decoder__io_ctl_wb_sel__prev = Core_Decoder__io_ctl_wb_sel;
  dat_dump<1>(f, Core_MuxWB__io_wb_sel, 0x34);
  Core_MuxWB__io_wb_sel__prev = Core_MuxWB__io_wb_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_msk_sel, 0x35);
  Core_Decoder__io_ctl_msk_sel__prev = Core_Decoder__io_ctl_msk_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_csr_cmd, 0x36);
  Core_Decoder__io_ctl_csr_cmd__prev = Core_Decoder__io_ctl_csr_cmd;
  dat_dump<1>(f, Core_BranchLogic__io_pc_sel, 0x37);
  Core_BranchLogic__io_pc_sel__prev = Core_BranchLogic__io_pc_sel;
  dat_dump<1>(f, Core_MuxPC__io_pc_sel, 0x38);
  Core_MuxPC__io_pc_sel__prev = Core_MuxPC__io_pc_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_alu_func, 0x39);
  Core_Decoder__io_ctl_alu_func__prev = Core_Decoder__io_ctl_alu_func;
  dat_dump<1>(f, Core_Alu__io_op, 0x3a);
  Core_Alu__io_op__prev = Core_Alu__io_op;
  dat_dump<1>(f, Core_Decoder__io_ctl_br_type, 0x3b);
  Core_Decoder__io_ctl_br_type__prev = Core_Decoder__io_ctl_br_type;
  dat_dump<1>(f, Core_BranchLogic__io_ctl_br_type, 0x3c);
  Core_BranchLogic__io_ctl_br_type__prev = Core_BranchLogic__io_ctl_br_type;
  dat_dump<1>(f, Core_RegFile__io_rf_ra2, 0x3d);
  Core_RegFile__io_rf_ra2__prev = Core_RegFile__io_rf_ra2;
  dat_dump<1>(f, Core_RegFile__io_rf_ra1, 0x3e);
  Core_RegFile__io_rf_ra1__prev = Core_RegFile__io_rf_ra1;
  dat_dump<1>(f, Core_RegFile__io_rf_wa, 0x3f);
  Core_RegFile__io_rf_wa__prev = Core_RegFile__io_rf_wa;
  dat_dump<1>(f, Core_DataMem__io_addr, 0x40);
  Core_DataMem__io_addr__prev = Core_DataMem__io_addr;
  dat_dump<1>(f, Core_InstructionMem__io_addr, 0x41);
  Core_InstructionMem__io_addr__prev = Core_InstructionMem__io_addr;
  dat_dump<1>(f, Core_RegFile__io_rf_rd2, 0x42);
  Core_RegFile__io_rf_rd2__prev = Core_RegFile__io_rf_rd2;
  dat_dump<1>(f, Core_DataMem__io_wr_data, 0x43);
  Core_DataMem__io_wr_data__prev = Core_DataMem__io_wr_data;
  dat_dump<1>(f, Core_Decoder__io_dec_instr, 0x44);
  Core_Decoder__io_dec_instr__prev = Core_Decoder__io_dec_instr;
  dat_dump<1>(f, Core_ImmGen__io_instr, 0x45);
  Core_ImmGen__io_instr__prev = Core_ImmGen__io_instr;
  dat_dump<1>(f, Core_ImmGen__io_immu_sxt, 0x46);
  Core_ImmGen__io_immu_sxt__prev = Core_ImmGen__io_immu_sxt;
  dat_dump<1>(f, Core_MuxOpA__io_opa_imz, 0x47);
  Core_MuxOpA__io_opa_imz__prev = Core_MuxOpA__io_opa_imz;
  dat_dump<1>(f, Core_MuxOpA__io_opa_imu, 0x48);
  Core_MuxOpA__io_opa_imu__prev = Core_MuxOpA__io_opa_imu;
  dat_dump<1>(f, Core_RegFile__io_rf_rd1, 0x49);
  Core_RegFile__io_rf_rd1__prev = Core_RegFile__io_rf_rd1;
  dat_dump<1>(f, Core_MuxOpA__io_opa_rsa, 0x4a);
  Core_MuxOpA__io_opa_rsa__prev = Core_MuxOpA__io_opa_rsa;
  dat_dump<1>(f, Core_MuxOpA__io_opa_alu_in, 0x4b);
  Core_MuxOpA__io_opa_alu_in__prev = Core_MuxOpA__io_opa_alu_in;
  dat_dump<1>(f, Core_Alu__io_a, 0x4c);
  Core_Alu__io_a__prev = Core_Alu__io_a;
  dat_dump<1>(f, Core_MuxOpB__io_opb_pc, 0x4d);
  Core_MuxOpB__io_opb_pc__prev = Core_MuxOpB__io_opb_pc;
  dat_dump<1>(f, Core_ImmGen__io_imms_sxt, 0x4e);
  Core_ImmGen__io_imms_sxt__prev = Core_ImmGen__io_imms_sxt;
  dat_dump<1>(f, Core_MuxOpB__io_opb_ims, 0x4f);
  Core_MuxOpB__io_opb_ims__prev = Core_MuxOpB__io_opb_ims;
  dat_dump<1>(f, Core_ImmGen__io_immi_sxt, 0x50);
  Core_ImmGen__io_immi_sxt__prev = Core_ImmGen__io_immi_sxt;
  dat_dump<1>(f, Core_MuxOpB__io_opb_imi, 0x51);
  Core_MuxOpB__io_opb_imi__prev = Core_MuxOpB__io_opb_imi;
  dat_dump<1>(f, Core_MuxOpB__io_opb_rsb, 0x52);
  Core_MuxOpB__io_opb_rsb__prev = Core_MuxOpB__io_opb_rsb;
  dat_dump<1>(f, Core_MuxOpB__io_opb_alu_in, 0x53);
  Core_MuxOpB__io_opb_alu_in__prev = Core_MuxOpB__io_opb_alu_in;
  dat_dump<1>(f, Core_Alu__io_b, 0x54);
  Core_Alu__io_b__prev = Core_Alu__io_b;
  dat_dump<1>(f, Core_Alu__io_out, 0x55);
  Core_Alu__io_out__prev = Core_Alu__io_out;
  dat_dump<1>(f, Core_DataMem__io_rd_data, 0x56);
  Core_DataMem__io_rd_data__prev = Core_DataMem__io_rd_data;
  dat_dump<1>(f, Core_MuxWB__io_wb_mem, 0x57);
  Core_MuxWB__io_wb_mem__prev = Core_MuxWB__io_wb_mem;
  dat_dump<1>(f, Core_MuxWB__io_wb_csr, 0x58);
  Core_MuxWB__io_wb_csr__prev = Core_MuxWB__io_wb_csr;
  dat_dump<1>(f, Core_MuxWB__io_wb_pc4, 0x59);
  Core_MuxWB__io_wb_pc4__prev = Core_MuxWB__io_wb_pc4;
  dat_dump<1>(f, Core_MuxWB__io_wb_alu, 0x5a);
  Core_MuxWB__io_wb_alu__prev = Core_MuxWB__io_wb_alu;
  dat_dump<1>(f, Core_MuxWB__io_wb_wd, 0x5b);
  Core_MuxWB__io_wb_wd__prev = Core_MuxWB__io_wb_wd;
  dat_dump<1>(f, Core_RegFile__io_rf_wd, 0x5c);
  Core_RegFile__io_rf_wd__prev = Core_RegFile__io_rf_wd;
  dat_dump<1>(f, Core_InstructionMem__io_data, 0x5d);
  Core_InstructionMem__io_data__prev = Core_InstructionMem__io_data;
  dat_dump<1>(f, Core__exec_instr_reg, 0x5e);
  Core__exec_instr_reg__prev = Core__exec_instr_reg;
  dat_dump<1>(f, Core__exec_pc_reg, 0x5f);
  Core__exec_pc_reg__prev = Core__exec_pc_reg;
  dat_dump<1>(f, Core_MuxPC__io_pc_excp, 0x60);
  Core_MuxPC__io_pc_excp__prev = Core_MuxPC__io_pc_excp;
  dat_dump<1>(f, Core_ImmGen__io_immj_sxt, 0x61);
  Core_ImmGen__io_immj_sxt__prev = Core_ImmGen__io_immj_sxt;
  dat_dump<1>(f, Core_MuxPC__io_pc_jmp, 0x62);
  Core_MuxPC__io_pc_jmp__prev = Core_MuxPC__io_pc_jmp;
  dat_dump<1>(f, Core_ImmGen__io_immb_sxt, 0x63);
  Core_ImmGen__io_immb_sxt__prev = Core_ImmGen__io_immb_sxt;
  dat_dump<1>(f, Core_MuxPC__io_pc_br, 0x64);
  Core_MuxPC__io_pc_br__prev = Core_MuxPC__io_pc_br;
  dat_dump<1>(f, Core_MuxPC__io_pc_jalr, 0x65);
  Core_MuxPC__io_pc_jalr__prev = Core_MuxPC__io_pc_jalr;
  dat_dump<1>(f, Core_MuxPC__io_pc_pc4, 0x66);
  Core_MuxPC__io_pc_pc4__prev = Core_MuxPC__io_pc_pc4;
  dat_dump<1>(f, Core_MuxPC__io_pc_out, 0x67);
  Core_MuxPC__io_pc_out__prev = Core_MuxPC__io_pc_out;
  dat_dump<1>(f, Core__fetch_pc_reg, 0x68);
  Core__fetch_pc_reg__prev = Core__fetch_pc_reg;
  dat_dump<1>(f, Core__exec_pc4_reg, 0x69);
  Core__exec_pc4_reg__prev = Core__exec_pc4_reg;
  fputs("#1\n", f);
  if (clk.cnt == 0) {
    clk.values[0] = 0;
    dat_dump<1>(f, clk, 0x21);
  }
}


void Core_t::dump ( FILE* f, val_t t, dat_t<1> reset ) {
  if (t == 0L) return dump_init(f);
  fprintf(f, "#%lu\n", t << 1);
  if (clk.cnt == 0)  goto L0;
K0:  if (reset != reset__prev)  goto L1;
K1:  if (Core_Decoder__io_ctl_mem_en != Core_Decoder__io_ctl_mem_en__prev)  goto L2;
K2:  if (Core_DataMem__io_mem_en != Core_DataMem__io_mem_en__prev)  goto L3;
K3:  if (Core_Alu__io_zero != Core_Alu__io_zero__prev)  goto L4;
K4:  if (Core_Decoder__io_ctl_rf_wen != Core_Decoder__io_ctl_rf_wen__prev)  goto L5;
K5:  if (Core_Decoder__io_ctl_val_inst != Core_Decoder__io_ctl_val_inst__prev)  goto L6;
K6:  if (Core_RegFile__io_rf_wen != Core_RegFile__io_rf_wen__prev)  goto L7;
K7:  if (Core_BranchLogic__io_br_ltu != Core_BranchLogic__io_br_ltu__prev)  goto L8;
K8:  if (Core_BranchLogic__io_br_lt != Core_BranchLogic__io_br_lt__prev)  goto L9;
K9:  if (Core_BranchLogic__io_br_eq != Core_BranchLogic__io_br_eq__prev)  goto L10;
K10:  if (Core_BranchLogic__io_excp != Core_BranchLogic__io_excp__prev)  goto L11;
K11:  if (Core_Decoder__io_ctl_mem_func != Core_Decoder__io_ctl_mem_func__prev)  goto L12;
K12:  if (Core_DataMem__io_mem_func != Core_DataMem__io_mem_func__prev)  goto L13;
K13:  if (Core_Decoder__io_ctl_opa_sel != Core_Decoder__io_ctl_opa_sel__prev)  goto L14;
K14:  if (Core_MuxOpA__io_opa_sel != Core_MuxOpA__io_opa_sel__prev)  goto L15;
K15:  if (Core_Decoder__io_ctl_opb_sel != Core_Decoder__io_ctl_opb_sel__prev)  goto L16;
K16:  if (Core_MuxOpB__io_opb_sel != Core_MuxOpB__io_opb_sel__prev)  goto L17;
K17:  if (Core_Decoder__io_ctl_wb_sel != Core_Decoder__io_ctl_wb_sel__prev)  goto L18;
K18:  if (Core_MuxWB__io_wb_sel != Core_MuxWB__io_wb_sel__prev)  goto L19;
K19:  if (Core_Decoder__io_ctl_msk_sel != Core_Decoder__io_ctl_msk_sel__prev)  goto L20;
K20:  if (Core_Decoder__io_ctl_csr_cmd != Core_Decoder__io_ctl_csr_cmd__prev)  goto L21;
K21:  if (Core_BranchLogic__io_pc_sel != Core_BranchLogic__io_pc_sel__prev)  goto L22;
K22:  if (Core_MuxPC__io_pc_sel != Core_MuxPC__io_pc_sel__prev)  goto L23;
K23:  if (Core_Decoder__io_ctl_alu_func != Core_Decoder__io_ctl_alu_func__prev)  goto L24;
K24:  if (Core_Alu__io_op != Core_Alu__io_op__prev)  goto L25;
K25:  if (Core_Decoder__io_ctl_br_type != Core_Decoder__io_ctl_br_type__prev)  goto L26;
K26:  if (Core_BranchLogic__io_ctl_br_type != Core_BranchLogic__io_ctl_br_type__prev)  goto L27;
K27:  if (Core_RegFile__io_rf_ra2 != Core_RegFile__io_rf_ra2__prev)  goto L28;
K28:  if (Core_RegFile__io_rf_ra1 != Core_RegFile__io_rf_ra1__prev)  goto L29;
K29:  if (Core_RegFile__io_rf_wa != Core_RegFile__io_rf_wa__prev)  goto L30;
K30:  if (Core_DataMem__io_addr != Core_DataMem__io_addr__prev)  goto L31;
K31:  if (Core_InstructionMem__io_addr != Core_InstructionMem__io_addr__prev)  goto L32;
K32:  if (Core_RegFile__io_rf_rd2 != Core_RegFile__io_rf_rd2__prev)  goto L33;
K33:  if (Core_DataMem__io_wr_data != Core_DataMem__io_wr_data__prev)  goto L34;
K34:  if (Core_Decoder__io_dec_instr != Core_Decoder__io_dec_instr__prev)  goto L35;
K35:  if (Core_ImmGen__io_instr != Core_ImmGen__io_instr__prev)  goto L36;
K36:  if (Core_ImmGen__io_immu_sxt != Core_ImmGen__io_immu_sxt__prev)  goto L37;
K37:  if (Core_MuxOpA__io_opa_imz != Core_MuxOpA__io_opa_imz__prev)  goto L38;
K38:  if (Core_MuxOpA__io_opa_imu != Core_MuxOpA__io_opa_imu__prev)  goto L39;
K39:  if (Core_RegFile__io_rf_rd1 != Core_RegFile__io_rf_rd1__prev)  goto L40;
K40:  if (Core_MuxOpA__io_opa_rsa != Core_MuxOpA__io_opa_rsa__prev)  goto L41;
K41:  if (Core_MuxOpA__io_opa_alu_in != Core_MuxOpA__io_opa_alu_in__prev)  goto L42;
K42:  if (Core_Alu__io_a != Core_Alu__io_a__prev)  goto L43;
K43:  if (Core_MuxOpB__io_opb_pc != Core_MuxOpB__io_opb_pc__prev)  goto L44;
K44:  if (Core_ImmGen__io_imms_sxt != Core_ImmGen__io_imms_sxt__prev)  goto L45;
K45:  if (Core_MuxOpB__io_opb_ims != Core_MuxOpB__io_opb_ims__prev)  goto L46;
K46:  if (Core_ImmGen__io_immi_sxt != Core_ImmGen__io_immi_sxt__prev)  goto L47;
K47:  if (Core_MuxOpB__io_opb_imi != Core_MuxOpB__io_opb_imi__prev)  goto L48;
K48:  if (Core_MuxOpB__io_opb_rsb != Core_MuxOpB__io_opb_rsb__prev)  goto L49;
K49:  if (Core_MuxOpB__io_opb_alu_in != Core_MuxOpB__io_opb_alu_in__prev)  goto L50;
K50:  if (Core_Alu__io_b != Core_Alu__io_b__prev)  goto L51;
K51:  if (Core_Alu__io_out != Core_Alu__io_out__prev)  goto L52;
K52:  if (Core_DataMem__io_rd_data != Core_DataMem__io_rd_data__prev)  goto L53;
K53:  if (Core_MuxWB__io_wb_mem != Core_MuxWB__io_wb_mem__prev)  goto L54;
K54:  if (Core_MuxWB__io_wb_csr != Core_MuxWB__io_wb_csr__prev)  goto L55;
K55:  if (Core_MuxWB__io_wb_pc4 != Core_MuxWB__io_wb_pc4__prev)  goto L56;
K56:  if (Core_MuxWB__io_wb_alu != Core_MuxWB__io_wb_alu__prev)  goto L57;
K57:  if (Core_MuxWB__io_wb_wd != Core_MuxWB__io_wb_wd__prev)  goto L58;
K58:  if (Core_RegFile__io_rf_wd != Core_RegFile__io_rf_wd__prev)  goto L59;
K59:  if (Core_InstructionMem__io_data != Core_InstructionMem__io_data__prev)  goto L60;
K60:  if (Core__exec_instr_reg != Core__exec_instr_reg__prev)  goto L61;
K61:  if (Core__exec_pc_reg != Core__exec_pc_reg__prev)  goto L62;
K62:  if (Core_MuxPC__io_pc_excp != Core_MuxPC__io_pc_excp__prev)  goto L63;
K63:  if (Core_ImmGen__io_immj_sxt != Core_ImmGen__io_immj_sxt__prev)  goto L64;
K64:  if (Core_MuxPC__io_pc_jmp != Core_MuxPC__io_pc_jmp__prev)  goto L65;
K65:  if (Core_ImmGen__io_immb_sxt != Core_ImmGen__io_immb_sxt__prev)  goto L66;
K66:  if (Core_MuxPC__io_pc_br != Core_MuxPC__io_pc_br__prev)  goto L67;
K67:  if (Core_MuxPC__io_pc_jalr != Core_MuxPC__io_pc_jalr__prev)  goto L68;
K68:  if (Core_MuxPC__io_pc_pc4 != Core_MuxPC__io_pc_pc4__prev)  goto L69;
K69:  if (Core_MuxPC__io_pc_out != Core_MuxPC__io_pc_out__prev)  goto L70;
K70:  if (Core__fetch_pc_reg != Core__fetch_pc_reg__prev)  goto L71;
K71:  if (Core__exec_pc4_reg != Core__exec_pc4_reg__prev)  goto L72;
K72:  fprintf(f, "#%lu\n", (t << 1) + 1);
  if (clk.cnt == 0)  goto Z0;
C0:  return;
L0:
  clk.values[0] = 1;
  dat_dump<1>(f, clk, 0x21);
  goto K0;
L1:
  reset__prev = reset;
  dat_dump<1>(f, reset, 0x22);
  goto K1;
L2:
  Core_Decoder__io_ctl_mem_en__prev = Core_Decoder__io_ctl_mem_en;
  dat_dump<1>(f, Core_Decoder__io_ctl_mem_en, 0x23);
  goto K2;
L3:
  Core_DataMem__io_mem_en__prev = Core_DataMem__io_mem_en;
  dat_dump<1>(f, Core_DataMem__io_mem_en, 0x24);
  goto K3;
L4:
  Core_Alu__io_zero__prev = Core_Alu__io_zero;
  dat_dump<1>(f, Core_Alu__io_zero, 0x25);
  goto K4;
L5:
  Core_Decoder__io_ctl_rf_wen__prev = Core_Decoder__io_ctl_rf_wen;
  dat_dump<1>(f, Core_Decoder__io_ctl_rf_wen, 0x26);
  goto K5;
L6:
  Core_Decoder__io_ctl_val_inst__prev = Core_Decoder__io_ctl_val_inst;
  dat_dump<1>(f, Core_Decoder__io_ctl_val_inst, 0x27);
  goto K6;
L7:
  Core_RegFile__io_rf_wen__prev = Core_RegFile__io_rf_wen;
  dat_dump<1>(f, Core_RegFile__io_rf_wen, 0x28);
  goto K7;
L8:
  Core_BranchLogic__io_br_ltu__prev = Core_BranchLogic__io_br_ltu;
  dat_dump<1>(f, Core_BranchLogic__io_br_ltu, 0x29);
  goto K8;
L9:
  Core_BranchLogic__io_br_lt__prev = Core_BranchLogic__io_br_lt;
  dat_dump<1>(f, Core_BranchLogic__io_br_lt, 0x2a);
  goto K9;
L10:
  Core_BranchLogic__io_br_eq__prev = Core_BranchLogic__io_br_eq;
  dat_dump<1>(f, Core_BranchLogic__io_br_eq, 0x2b);
  goto K10;
L11:
  Core_BranchLogic__io_excp__prev = Core_BranchLogic__io_excp;
  dat_dump<1>(f, Core_BranchLogic__io_excp, 0x2c);
  goto K11;
L12:
  Core_Decoder__io_ctl_mem_func__prev = Core_Decoder__io_ctl_mem_func;
  dat_dump<1>(f, Core_Decoder__io_ctl_mem_func, 0x2d);
  goto K12;
L13:
  Core_DataMem__io_mem_func__prev = Core_DataMem__io_mem_func;
  dat_dump<1>(f, Core_DataMem__io_mem_func, 0x2e);
  goto K13;
L14:
  Core_Decoder__io_ctl_opa_sel__prev = Core_Decoder__io_ctl_opa_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_opa_sel, 0x2f);
  goto K14;
L15:
  Core_MuxOpA__io_opa_sel__prev = Core_MuxOpA__io_opa_sel;
  dat_dump<1>(f, Core_MuxOpA__io_opa_sel, 0x30);
  goto K15;
L16:
  Core_Decoder__io_ctl_opb_sel__prev = Core_Decoder__io_ctl_opb_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_opb_sel, 0x31);
  goto K16;
L17:
  Core_MuxOpB__io_opb_sel__prev = Core_MuxOpB__io_opb_sel;
  dat_dump<1>(f, Core_MuxOpB__io_opb_sel, 0x32);
  goto K17;
L18:
  Core_Decoder__io_ctl_wb_sel__prev = Core_Decoder__io_ctl_wb_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_wb_sel, 0x33);
  goto K18;
L19:
  Core_MuxWB__io_wb_sel__prev = Core_MuxWB__io_wb_sel;
  dat_dump<1>(f, Core_MuxWB__io_wb_sel, 0x34);
  goto K19;
L20:
  Core_Decoder__io_ctl_msk_sel__prev = Core_Decoder__io_ctl_msk_sel;
  dat_dump<1>(f, Core_Decoder__io_ctl_msk_sel, 0x35);
  goto K20;
L21:
  Core_Decoder__io_ctl_csr_cmd__prev = Core_Decoder__io_ctl_csr_cmd;
  dat_dump<1>(f, Core_Decoder__io_ctl_csr_cmd, 0x36);
  goto K21;
L22:
  Core_BranchLogic__io_pc_sel__prev = Core_BranchLogic__io_pc_sel;
  dat_dump<1>(f, Core_BranchLogic__io_pc_sel, 0x37);
  goto K22;
L23:
  Core_MuxPC__io_pc_sel__prev = Core_MuxPC__io_pc_sel;
  dat_dump<1>(f, Core_MuxPC__io_pc_sel, 0x38);
  goto K23;
L24:
  Core_Decoder__io_ctl_alu_func__prev = Core_Decoder__io_ctl_alu_func;
  dat_dump<1>(f, Core_Decoder__io_ctl_alu_func, 0x39);
  goto K24;
L25:
  Core_Alu__io_op__prev = Core_Alu__io_op;
  dat_dump<1>(f, Core_Alu__io_op, 0x3a);
  goto K25;
L26:
  Core_Decoder__io_ctl_br_type__prev = Core_Decoder__io_ctl_br_type;
  dat_dump<1>(f, Core_Decoder__io_ctl_br_type, 0x3b);
  goto K26;
L27:
  Core_BranchLogic__io_ctl_br_type__prev = Core_BranchLogic__io_ctl_br_type;
  dat_dump<1>(f, Core_BranchLogic__io_ctl_br_type, 0x3c);
  goto K27;
L28:
  Core_RegFile__io_rf_ra2__prev = Core_RegFile__io_rf_ra2;
  dat_dump<1>(f, Core_RegFile__io_rf_ra2, 0x3d);
  goto K28;
L29:
  Core_RegFile__io_rf_ra1__prev = Core_RegFile__io_rf_ra1;
  dat_dump<1>(f, Core_RegFile__io_rf_ra1, 0x3e);
  goto K29;
L30:
  Core_RegFile__io_rf_wa__prev = Core_RegFile__io_rf_wa;
  dat_dump<1>(f, Core_RegFile__io_rf_wa, 0x3f);
  goto K30;
L31:
  Core_DataMem__io_addr__prev = Core_DataMem__io_addr;
  dat_dump<1>(f, Core_DataMem__io_addr, 0x40);
  goto K31;
L32:
  Core_InstructionMem__io_addr__prev = Core_InstructionMem__io_addr;
  dat_dump<1>(f, Core_InstructionMem__io_addr, 0x41);
  goto K32;
L33:
  Core_RegFile__io_rf_rd2__prev = Core_RegFile__io_rf_rd2;
  dat_dump<1>(f, Core_RegFile__io_rf_rd2, 0x42);
  goto K33;
L34:
  Core_DataMem__io_wr_data__prev = Core_DataMem__io_wr_data;
  dat_dump<1>(f, Core_DataMem__io_wr_data, 0x43);
  goto K34;
L35:
  Core_Decoder__io_dec_instr__prev = Core_Decoder__io_dec_instr;
  dat_dump<1>(f, Core_Decoder__io_dec_instr, 0x44);
  goto K35;
L36:
  Core_ImmGen__io_instr__prev = Core_ImmGen__io_instr;
  dat_dump<1>(f, Core_ImmGen__io_instr, 0x45);
  goto K36;
L37:
  Core_ImmGen__io_immu_sxt__prev = Core_ImmGen__io_immu_sxt;
  dat_dump<1>(f, Core_ImmGen__io_immu_sxt, 0x46);
  goto K37;
L38:
  Core_MuxOpA__io_opa_imz__prev = Core_MuxOpA__io_opa_imz;
  dat_dump<1>(f, Core_MuxOpA__io_opa_imz, 0x47);
  goto K38;
L39:
  Core_MuxOpA__io_opa_imu__prev = Core_MuxOpA__io_opa_imu;
  dat_dump<1>(f, Core_MuxOpA__io_opa_imu, 0x48);
  goto K39;
L40:
  Core_RegFile__io_rf_rd1__prev = Core_RegFile__io_rf_rd1;
  dat_dump<1>(f, Core_RegFile__io_rf_rd1, 0x49);
  goto K40;
L41:
  Core_MuxOpA__io_opa_rsa__prev = Core_MuxOpA__io_opa_rsa;
  dat_dump<1>(f, Core_MuxOpA__io_opa_rsa, 0x4a);
  goto K41;
L42:
  Core_MuxOpA__io_opa_alu_in__prev = Core_MuxOpA__io_opa_alu_in;
  dat_dump<1>(f, Core_MuxOpA__io_opa_alu_in, 0x4b);
  goto K42;
L43:
  Core_Alu__io_a__prev = Core_Alu__io_a;
  dat_dump<1>(f, Core_Alu__io_a, 0x4c);
  goto K43;
L44:
  Core_MuxOpB__io_opb_pc__prev = Core_MuxOpB__io_opb_pc;
  dat_dump<1>(f, Core_MuxOpB__io_opb_pc, 0x4d);
  goto K44;
L45:
  Core_ImmGen__io_imms_sxt__prev = Core_ImmGen__io_imms_sxt;
  dat_dump<1>(f, Core_ImmGen__io_imms_sxt, 0x4e);
  goto K45;
L46:
  Core_MuxOpB__io_opb_ims__prev = Core_MuxOpB__io_opb_ims;
  dat_dump<1>(f, Core_MuxOpB__io_opb_ims, 0x4f);
  goto K46;
L47:
  Core_ImmGen__io_immi_sxt__prev = Core_ImmGen__io_immi_sxt;
  dat_dump<1>(f, Core_ImmGen__io_immi_sxt, 0x50);
  goto K47;
L48:
  Core_MuxOpB__io_opb_imi__prev = Core_MuxOpB__io_opb_imi;
  dat_dump<1>(f, Core_MuxOpB__io_opb_imi, 0x51);
  goto K48;
L49:
  Core_MuxOpB__io_opb_rsb__prev = Core_MuxOpB__io_opb_rsb;
  dat_dump<1>(f, Core_MuxOpB__io_opb_rsb, 0x52);
  goto K49;
L50:
  Core_MuxOpB__io_opb_alu_in__prev = Core_MuxOpB__io_opb_alu_in;
  dat_dump<1>(f, Core_MuxOpB__io_opb_alu_in, 0x53);
  goto K50;
L51:
  Core_Alu__io_b__prev = Core_Alu__io_b;
  dat_dump<1>(f, Core_Alu__io_b, 0x54);
  goto K51;
L52:
  Core_Alu__io_out__prev = Core_Alu__io_out;
  dat_dump<1>(f, Core_Alu__io_out, 0x55);
  goto K52;
L53:
  Core_DataMem__io_rd_data__prev = Core_DataMem__io_rd_data;
  dat_dump<1>(f, Core_DataMem__io_rd_data, 0x56);
  goto K53;
L54:
  Core_MuxWB__io_wb_mem__prev = Core_MuxWB__io_wb_mem;
  dat_dump<1>(f, Core_MuxWB__io_wb_mem, 0x57);
  goto K54;
L55:
  Core_MuxWB__io_wb_csr__prev = Core_MuxWB__io_wb_csr;
  dat_dump<1>(f, Core_MuxWB__io_wb_csr, 0x58);
  goto K55;
L56:
  Core_MuxWB__io_wb_pc4__prev = Core_MuxWB__io_wb_pc4;
  dat_dump<1>(f, Core_MuxWB__io_wb_pc4, 0x59);
  goto K56;
L57:
  Core_MuxWB__io_wb_alu__prev = Core_MuxWB__io_wb_alu;
  dat_dump<1>(f, Core_MuxWB__io_wb_alu, 0x5a);
  goto K57;
L58:
  Core_MuxWB__io_wb_wd__prev = Core_MuxWB__io_wb_wd;
  dat_dump<1>(f, Core_MuxWB__io_wb_wd, 0x5b);
  goto K58;
L59:
  Core_RegFile__io_rf_wd__prev = Core_RegFile__io_rf_wd;
  dat_dump<1>(f, Core_RegFile__io_rf_wd, 0x5c);
  goto K59;
L60:
  Core_InstructionMem__io_data__prev = Core_InstructionMem__io_data;
  dat_dump<1>(f, Core_InstructionMem__io_data, 0x5d);
  goto K60;
L61:
  Core__exec_instr_reg__prev = Core__exec_instr_reg;
  dat_dump<1>(f, Core__exec_instr_reg, 0x5e);
  goto K61;
L62:
  Core__exec_pc_reg__prev = Core__exec_pc_reg;
  dat_dump<1>(f, Core__exec_pc_reg, 0x5f);
  goto K62;
L63:
  Core_MuxPC__io_pc_excp__prev = Core_MuxPC__io_pc_excp;
  dat_dump<1>(f, Core_MuxPC__io_pc_excp, 0x60);
  goto K63;
L64:
  Core_ImmGen__io_immj_sxt__prev = Core_ImmGen__io_immj_sxt;
  dat_dump<1>(f, Core_ImmGen__io_immj_sxt, 0x61);
  goto K64;
L65:
  Core_MuxPC__io_pc_jmp__prev = Core_MuxPC__io_pc_jmp;
  dat_dump<1>(f, Core_MuxPC__io_pc_jmp, 0x62);
  goto K65;
L66:
  Core_ImmGen__io_immb_sxt__prev = Core_ImmGen__io_immb_sxt;
  dat_dump<1>(f, Core_ImmGen__io_immb_sxt, 0x63);
  goto K66;
L67:
  Core_MuxPC__io_pc_br__prev = Core_MuxPC__io_pc_br;
  dat_dump<1>(f, Core_MuxPC__io_pc_br, 0x64);
  goto K67;
L68:
  Core_MuxPC__io_pc_jalr__prev = Core_MuxPC__io_pc_jalr;
  dat_dump<1>(f, Core_MuxPC__io_pc_jalr, 0x65);
  goto K68;
L69:
  Core_MuxPC__io_pc_pc4__prev = Core_MuxPC__io_pc_pc4;
  dat_dump<1>(f, Core_MuxPC__io_pc_pc4, 0x66);
  goto K69;
L70:
  Core_MuxPC__io_pc_out__prev = Core_MuxPC__io_pc_out;
  dat_dump<1>(f, Core_MuxPC__io_pc_out, 0x67);
  goto K70;
L71:
  Core__fetch_pc_reg__prev = Core__fetch_pc_reg;
  dat_dump<1>(f, Core__fetch_pc_reg, 0x68);
  goto K71;
L72:
  Core__exec_pc4_reg__prev = Core__exec_pc4_reg;
  dat_dump<1>(f, Core__exec_pc4_reg, 0x69);
  goto K72;
Z0:
  clk.values[0] = 0;
  dat_dump<1>(f, clk, 0x21);
  goto C0;
}




void Core_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  val_t Core__rsb_addr;
  { Core__rsb_addr = Core__exec_instr_reg.values[0] >> 20;}
  Core__rsb_addr = Core__rsb_addr & 0x1fL;
  { Core_RegFile__io_rf_ra2.values[0] = Core__rsb_addr;}
  val_t T0;
  { T0 = Core_RegFile__rf_reg_file.get(Core_RegFile__io_rf_ra2.values[0], 0);}
  val_t T1;
  T1 = Core_RegFile__io_rf_ra2.values[0] != 0x0L;
  val_t T2;
  { T2 = TERNARY(T1, T0, 0x0L);}
  { Core_RegFile__io_rf_rd2.values[0] = T2;}
  { Core_DataMem__io_wr_data.values[0] = Core_RegFile__io_rf_rd2.values[0];}
  { Core_Decoder__io_dec_instr.values[0] = Core__exec_instr_reg.values[0];}
  val_t T3;
  { T3 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T4;
  T4 = T3 == 0x2023L;
  val_t T5;
  { T5 = TERNARY(T4, 0x1L, 0x0L);}
  val_t T6;
  { T6 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T7;
  T7 = T6 == 0x1023L;
  val_t T8;
  { T8 = TERNARY(T7, 0x1L, T5);}
  val_t T9;
  { T9 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T10;
  T10 = T9 == 0x23L;
  val_t T11;
  { T11 = TERNARY(T10, 0x1L, T8);}
  val_t T12;
  { T12 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T13;
  T13 = T12 == 0x2003L;
  val_t T14;
  { T14 = TERNARY(T13, 0x0L, T11);}
  val_t T15;
  { T15 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T16;
  T16 = T15 == 0x5003L;
  val_t T17;
  { T17 = TERNARY(T16, 0x0L, T14);}
  val_t T18;
  { T18 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T19;
  T19 = T18 == 0x1003L;
  val_t T20;
  { T20 = TERNARY(T19, 0x0L, T17);}
  val_t T21;
  { T21 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T22;
  T22 = T21 == 0x4003L;
  val_t T23;
  { T23 = TERNARY(T22, 0x0L, T20);}
  val_t T24;
  { T24 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T25;
  T25 = T24 == 0x3L;
  val_t T26;
  { T26 = TERNARY(T25, 0x0L, T23);}
  val_t T27;
  { T27 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T28;
  T28 = T27 == 0x6063L;
  val_t T29;
  { T29 = TERNARY(T28, 0x0L, T26);}
  val_t T30;
  { T30 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T31;
  T31 = T30 == 0x4063L;
  val_t T32;
  { T32 = TERNARY(T31, 0x0L, T29);}
  val_t T33;
  { T33 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T34;
  T34 = T33 == 0x7063L;
  val_t T35;
  { T35 = TERNARY(T34, 0x0L, T32);}
  val_t T36;
  { T36 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T37;
  T37 = T36 == 0x5063L;
  val_t T38;
  { T38 = TERNARY(T37, 0x0L, T35);}
  val_t T39;
  { T39 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T40;
  T40 = T39 == 0x1063L;
  val_t T41;
  { T41 = TERNARY(T40, 0x0L, T38);}
  val_t T42;
  { T42 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T43;
  T43 = T42 == 0x63L;
  val_t T44;
  { T44 = TERNARY(T43, 0x0L, T41);}
  val_t T45;
  { T45 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T46;
  T46 = T45 == 0x67L;
  val_t T47;
  { T47 = TERNARY(T46, 0x0L, T44);}
  val_t T48;
  { T48 = Core_Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T49;
  T49 = T48 == 0x6fL;
  val_t T50;
  { T50 = TERNARY(T49, 0x0L, T47);}
  val_t T51;
  { T51 = Core_Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T52;
  T52 = T51 == 0x17L;
  val_t T53;
  { T53 = TERNARY(T52, 0x0L, T50);}
  val_t T54;
  { T54 = Core_Decoder__io_dec_instr.values[0] & 0x7fL;}
  val_t T55;
  T55 = T54 == 0x37L;
  val_t Core_Decoder__ctl_mem_func;
  { Core_Decoder__ctl_mem_func = TERNARY(T55, 0x0L, T53);}
  { Core_Decoder__io_ctl_mem_func.values[0] = Core_Decoder__ctl_mem_func;}
  { Core_DataMem__io_mem_func.values[0] = Core_Decoder__io_ctl_mem_func.values[0];}
  val_t T56;
  T56 = Core_DataMem__io_mem_func.values[0] == 0x1L;
  val_t T57;
  { T57 = TERNARY(T7, 0x1L, T4);}
  val_t T58;
  { T58 = TERNARY(T10, 0x1L, T57);}
  val_t T59;
  { T59 = TERNARY(T13, 0x1L, T58);}
  val_t T60;
  { T60 = TERNARY(T16, 0x1L, T59);}
  val_t T61;
  { T61 = TERNARY(T19, 0x1L, T60);}
  val_t T62;
  { T62 = TERNARY(T22, 0x1L, T61);}
  val_t T63;
  { T63 = TERNARY(T25, 0x1L, T62);}
  val_t T64;
  { T64 = TERNARY(T28, 0x0L, T63);}
  val_t T65;
  { T65 = TERNARY(T31, 0x0L, T64);}
  val_t T66;
  { T66 = TERNARY(T34, 0x0L, T65);}
  val_t T67;
  { T67 = TERNARY(T37, 0x0L, T66);}
  val_t T68;
  { T68 = TERNARY(T40, 0x0L, T67);}
  val_t T69;
  { T69 = TERNARY(T43, 0x0L, T68);}
  val_t T70;
  { T70 = TERNARY(T46, 0x0L, T69);}
  val_t T71;
  { T71 = TERNARY(T49, 0x0L, T70);}
  val_t T72;
  { T72 = TERNARY(T52, 0x0L, T71);}
  val_t Core_Decoder__ctl_mem_en;
  { Core_Decoder__ctl_mem_en = TERNARY(T55, 0x0L, T72);}
  { Core_Decoder__io_ctl_mem_en.values[0] = Core_Decoder__ctl_mem_en;}
  { Core_DataMem__io_mem_en.values[0] = Core_Decoder__io_ctl_mem_en.values[0];}
  { T73.values[0] = Core_DataMem__io_mem_en.values[0] & T56;}
  { Core_ImmGen__io_instr.values[0] = Core__exec_instr_reg.values[0];}
  val_t T74;
  { T74 = Core_ImmGen__io_instr.values[0] >> 12;}
  T74 = T74 & 0xfffffL;
  val_t Core_ImmGen__immu;
  { Core_ImmGen__immu = 0x0L | T74 << 12;}
  { Core_ImmGen__io_immu_sxt.values[0] = Core_ImmGen__immu;}
  { Core_MuxOpA__io_opa_imz.values[0] = Core_ImmGen__io_immu_sxt.values[0];}
  val_t T75;
  { T75 = TERNARY(T52, 0x1L, 0x0L);}
  val_t Core_Decoder__ctl_opa_sel;
  { Core_Decoder__ctl_opa_sel = TERNARY(T55, 0x1L, T75);}
  { Core_Decoder__io_ctl_opa_sel.values[0] = Core_Decoder__ctl_opa_sel;}
  { Core_MuxOpA__io_opa_sel.values[0] = Core_Decoder__io_ctl_opa_sel.values[0];}
  val_t T76;
  T76 = Core_MuxOpA__io_opa_sel.values[0] == 0x2L;
  val_t T77;
  { T77 = TERNARY(T76, Core_MuxOpA__io_opa_imz.values[0], 0x0L);}
  { Core_MuxOpA__io_opa_imu.values[0] = Core_ImmGen__io_immu_sxt.values[0];}
  val_t T78;
  T78 = Core_MuxOpA__io_opa_sel.values[0] == 0x1L;
  val_t T79;
  { T79 = TERNARY_1(T78, Core_MuxOpA__io_opa_imu.values[0], T77);}
  val_t Core__rsa_addr;
  { Core__rsa_addr = Core__exec_instr_reg.values[0] >> 15;}
  Core__rsa_addr = Core__rsa_addr & 0x1fL;
  { Core_RegFile__io_rf_ra1.values[0] = Core__rsa_addr;}
  val_t T80;
  { T80 = Core_RegFile__rf_reg_file.get(Core_RegFile__io_rf_ra1.values[0], 0);}
  val_t T81;
  T81 = Core_RegFile__io_rf_ra1.values[0] != 0x0L;
  val_t T82;
  { T82 = TERNARY(T81, T80, 0x0L);}
  { Core_RegFile__io_rf_rd1.values[0] = T82;}
  { Core_MuxOpA__io_opa_rsa.values[0] = Core_RegFile__io_rf_rd1.values[0];}
  val_t T83;
  T83 = Core_MuxOpA__io_opa_sel.values[0] == 0x0L;
  val_t T84;
  { T84 = TERNARY_1(T83, Core_MuxOpA__io_opa_rsa.values[0], T79);}
  { Core_MuxOpA__io_opa_alu_in.values[0] = T84;}
  { Core_Alu__io_a.values[0] = Core_MuxOpA__io_opa_alu_in.values[0];}
  val_t T85;
  { T85 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T86;
  T86 = T85 == 0x7033L;
  val_t T87;
  { T87 = TERNARY(T86, 0x3L, 0x0L);}
  val_t T88;
  { T88 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T89;
  T89 = T88 == 0x6033L;
  val_t T90;
  { T90 = TERNARY(T89, 0x4L, T87);}
  val_t T91;
  { T91 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T92;
  T92 = T91 == 0x40005033L;
  val_t T93;
  { T93 = TERNARY(T92, 0xeL, T90);}
  val_t T94;
  { T94 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T95;
  T95 = T94 == 0x5033L;
  val_t T96;
  { T96 = TERNARY(T95, 0xdL, T93);}
  val_t T97;
  { T97 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T98;
  T98 = T97 == 0x4033L;
  val_t T99;
  { T99 = TERNARY(T98, 0x5L, T96);}
  val_t T100;
  { T100 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T101;
  T101 = T100 == 0x3033L;
  val_t T102;
  { T102 = TERNARY(T101, 0x7L, T99);}
  val_t T103;
  { T103 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T104;
  T104 = T103 == 0x2033L;
  val_t T105;
  { T105 = TERNARY(T104, 0x6L, T102);}
  val_t T106;
  { T106 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T107;
  T107 = T106 == 0x1033L;
  val_t T108;
  { T108 = TERNARY(T107, 0xcL, T105);}
  val_t T109;
  { T109 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T110;
  T110 = T109 == 0x40000033L;
  val_t T111;
  { T111 = TERNARY(T110, 0x2L, T108);}
  val_t T112;
  { T112 = Core_Decoder__io_dec_instr.values[0] & 0xfe00707fL;}
  val_t T113;
  T113 = T112 == 0x33L;
  val_t T114;
  { T114 = TERNARY(T113, 0x1L, T111);}
  val_t T115;
  { T115 = Core_Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T116;
  T116 = T115 == 0x40005013L;
  val_t T117;
  { T117 = TERNARY(T116, 0xeL, T114);}
  val_t T118;
  { T118 = Core_Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T119;
  T119 = T118 == 0x5013L;
  val_t T120;
  { T120 = TERNARY(T119, 0xdL, T117);}
  val_t T121;
  { T121 = Core_Decoder__io_dec_instr.values[0] & 0xfc00707fL;}
  val_t T122;
  T122 = T121 == 0x1013L;
  val_t T123;
  { T123 = TERNARY(T122, 0xcL, T120);}
  val_t T124;
  { T124 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T125;
  T125 = T124 == 0x7013L;
  val_t T126;
  { T126 = TERNARY(T125, 0x3L, T123);}
  val_t T127;
  { T127 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T128;
  T128 = T127 == 0x6013L;
  val_t T129;
  { T129 = TERNARY(T128, 0x4L, T126);}
  val_t T130;
  { T130 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T131;
  T131 = T130 == 0x4013L;
  val_t T132;
  { T132 = TERNARY(T131, 0x5L, T129);}
  val_t T133;
  { T133 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T134;
  T134 = T133 == 0x3013L;
  val_t T135;
  { T135 = TERNARY(T134, 0x7L, T132);}
  val_t T136;
  { T136 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T137;
  T137 = T136 == 0x2013L;
  val_t T138;
  { T138 = TERNARY(T137, 0x6L, T135);}
  val_t T139;
  { T139 = Core_Decoder__io_dec_instr.values[0] & 0x707fL;}
  val_t T140;
  T140 = T139 == 0x13L;
  val_t T141;
  { T141 = TERNARY(T140, 0x1L, T138);}
  val_t T142;
  { T142 = TERNARY(T4, 0x1L, T141);}
  val_t T143;
  { T143 = TERNARY(T7, 0x1L, T142);}
  val_t T144;
  { T144 = TERNARY(T10, 0x1L, T143);}
  val_t T145;
  { T145 = TERNARY(T13, 0x1L, T144);}
  val_t T146;
  { T146 = TERNARY(T16, 0x1L, T145);}
  val_t T147;
  { T147 = TERNARY(T19, 0x1L, T146);}
  val_t T148;
  { T148 = TERNARY(T22, 0x1L, T147);}
  val_t T149;
  { T149 = TERNARY(T25, 0x1L, T148);}
  val_t T150;
  { T150 = TERNARY(T28, 0x0L, T149);}
  val_t T151;
  { T151 = TERNARY(T31, 0x0L, T150);}
  val_t T152;
  { T152 = TERNARY(T34, 0x0L, T151);}
  val_t T153;
  { T153 = TERNARY(T37, 0x0L, T152);}
  val_t T154;
  { T154 = TERNARY(T40, 0x0L, T153);}
  val_t T155;
  { T155 = TERNARY(T43, 0x0L, T154);}
  val_t T156;
  { T156 = TERNARY(T46, 0x0L, T155);}
  val_t T157;
  { T157 = TERNARY(T49, 0x0L, T156);}
  val_t T158;
  { T158 = TERNARY(T52, 0x1L, T157);}
  val_t Core_Decoder__ctl_alu_func;
  { Core_Decoder__ctl_alu_func = TERNARY(T55, 0xfL, T158);}
  { Core_Decoder__io_ctl_alu_func.values[0] = Core_Decoder__ctl_alu_func;}
  { Core_Alu__io_op.values[0] = Core_Decoder__io_ctl_alu_func.values[0];}
  val_t T159;
  T159 = Core_Alu__io_op.values[0] == 0xfL;
  val_t T160;
  { T160 = TERNARY(T159, Core_Alu__io_a.values[0], 0x0L);}
  { Core_MuxOpB__io_opb_pc.values[0] = Core__exec_pc_reg.values[0];}
  val_t T161;
  { T161 = TERNARY(T86, 0x2L, 0x0L);}
  val_t T162;
  { T162 = TERNARY(T89, 0x2L, T161);}
  val_t T163;
  { T163 = TERNARY(T92, 0x2L, T162);}
  val_t T164;
  { T164 = TERNARY(T95, 0x2L, T163);}
  val_t T165;
  { T165 = TERNARY(T98, 0x2L, T164);}
  val_t T166;
  { T166 = TERNARY(T101, 0x2L, T165);}
  val_t T167;
  { T167 = TERNARY(T104, 0x2L, T166);}
  val_t T168;
  { T168 = TERNARY(T107, 0x2L, T167);}
  val_t T169;
  { T169 = TERNARY(T110, 0x2L, T168);}
  val_t T170;
  { T170 = TERNARY(T113, 0x2L, T169);}
  val_t T171;
  { T171 = TERNARY(T116, 0x2L, T170);}
  val_t T172;
  { T172 = TERNARY(T119, 0x2L, T171);}
  val_t T173;
  { T173 = TERNARY(T122, 0x2L, T172);}
  val_t T174;
  { T174 = TERNARY(T125, 0x2L, T173);}
  val_t T175;
  { T175 = TERNARY(T128, 0x2L, T174);}
  val_t T176;
  { T176 = TERNARY(T131, 0x2L, T175);}
  val_t T177;
  { T177 = TERNARY(T134, 0x2L, T176);}
  val_t T178;
  { T178 = TERNARY(T137, 0x2L, T177);}
  val_t T179;
  { T179 = TERNARY(T140, 0x2L, T178);}
  val_t T180;
  { T180 = TERNARY(T4, 0x3L, T179);}
  val_t T181;
  { T181 = TERNARY(T7, 0x3L, T180);}
  val_t T182;
  { T182 = TERNARY(T10, 0x3L, T181);}
  val_t T183;
  { T183 = TERNARY(T13, 0x2L, T182);}
  val_t T184;
  { T184 = TERNARY(T16, 0x2L, T183);}
  val_t T185;
  { T185 = TERNARY(T19, 0x2L, T184);}
  val_t T186;
  { T186 = TERNARY(T22, 0x2L, T185);}
  val_t T187;
  { T187 = TERNARY(T25, 0x2L, T186);}
  val_t T188;
  { T188 = TERNARY(T28, 0x0L, T187);}
  val_t T189;
  { T189 = TERNARY(T31, 0x0L, T188);}
  val_t T190;
  { T190 = TERNARY(T34, 0x0L, T189);}
  val_t T191;
  { T191 = TERNARY(T37, 0x0L, T190);}
  val_t T192;
  { T192 = TERNARY(T40, 0x0L, T191);}
  val_t T193;
  { T193 = TERNARY(T43, 0x0L, T192);}
  val_t T194;
  { T194 = TERNARY(T46, 0x2L, T193);}
  val_t T195;
  { T195 = TERNARY(T49, 0x0L, T194);}
  val_t T196;
  { T196 = TERNARY(T52, 0x1L, T195);}
  val_t Core_Decoder__ctl_opb_sel;
  { Core_Decoder__ctl_opb_sel = TERNARY(T55, 0x0L, T196);}
  { Core_Decoder__io_ctl_opb_sel.values[0] = Core_Decoder__ctl_opb_sel;}
  { Core_MuxOpB__io_opb_sel.values[0] = Core_Decoder__io_ctl_opb_sel.values[0];}
  val_t T197;
  T197 = Core_MuxOpB__io_opb_sel.values[0] == 0x1L;
  val_t T198;
  { T198 = TERNARY(T197, Core_MuxOpB__io_opb_pc.values[0], 0x0L);}
  val_t T199;
  { T199 = Core_ImmGen__io_instr.values[0] >> 7;}
  T199 = T199 & 0x1fL;
  val_t T200;
  { T200 = Core_ImmGen__io_instr.values[0] >> 25;}
  T200 = T200 & 0x7fL;
  val_t Core_ImmGen__imms;
  { Core_ImmGen__imms = T199 | T200 << 5;}
  val_t Core_ImmGen__immi;
  { Core_ImmGen__immi = Core_ImmGen__io_instr.values[0] >> 20;}
  Core_ImmGen__immi = Core_ImmGen__immi & 0xfffL;
  val_t T201;
  T201 = (Core_ImmGen__immi >> 11) & 1;
  val_t T202;
  { T202 = TERNARY(T201, 0xfffffL, 0x0L);}
  val_t T203;
  { T203 = Core_ImmGen__imms | T202 << 12;}
  { Core_ImmGen__io_imms_sxt.values[0] = T203;}
  { Core_MuxOpB__io_opb_ims.values[0] = Core_ImmGen__io_imms_sxt.values[0];}
  val_t T204;
  T204 = Core_MuxOpB__io_opb_sel.values[0] == 0x3L;
  val_t T205;
  { T205 = TERNARY_1(T204, Core_MuxOpB__io_opb_ims.values[0], T198);}
  val_t T206;
  T206 = (Core_ImmGen__immi >> 11) & 1;
  val_t T207;
  { T207 = TERNARY(T206, 0xfffffL, 0x0L);}
  val_t T208;
  { T208 = Core_ImmGen__immi | T207 << 12;}
  { Core_ImmGen__io_immi_sxt.values[0] = T208;}
  { Core_MuxOpB__io_opb_imi.values[0] = Core_ImmGen__io_immi_sxt.values[0];}
  val_t T209;
  T209 = Core_MuxOpB__io_opb_sel.values[0] == 0x2L;
  val_t T210;
  { T210 = TERNARY_1(T209, Core_MuxOpB__io_opb_imi.values[0], T205);}
  { Core_MuxOpB__io_opb_rsb.values[0] = Core_RegFile__io_rf_rd2.values[0];}
  val_t T211;
  T211 = Core_MuxOpB__io_opb_sel.values[0] == 0x0L;
  val_t T212;
  { T212 = TERNARY_1(T211, Core_MuxOpB__io_opb_rsb.values[0], T210);}
  { Core_MuxOpB__io_opb_alu_in.values[0] = T212;}
  { Core_Alu__io_b.values[0] = Core_MuxOpB__io_opb_alu_in.values[0];}
  val_t T213;
  { T213 = Core_Alu__io_b.values[0];}
  T213 = T213 & 0x1fL;
  val_t T214;
  T214 = sval_t(Core_Alu__io_a.values[0] << 32) >> (32 + T213);
  T214 = T214 & 0xffffffffL;
  val_t T215;
  T215 = Core_Alu__io_op.values[0] == 0xeL;
  val_t T216;
  { T216 = TERNARY_1(T215, T214, T160);}
  val_t T217;
  T217 = Core_Alu__io_a.values[0] >> T213;
  val_t T218;
  T218 = Core_Alu__io_op.values[0] == 0xdL;
  val_t T219;
  { T219 = TERNARY_1(T218, T217, T216);}
  val_t T220;
  T220 = Core_Alu__io_a.values[0] << T213;
  T220 = T220 & 0x7fffffffffffffffL;
  val_t T221;
  { T221 = T220;}
  T221 = T221 & 0xffffffffL;
  val_t T222;
  T222 = Core_Alu__io_op.values[0] == 0xcL;
  val_t T223;
  { T223 = TERNARY_1(T222, T221, T219);}
  val_t T224;
  T224 = Core_Alu__io_b.values[0]<=Core_Alu__io_a.values[0];
  val_t T225;
  { T225 = T224 | 0x0L << 1;}
  val_t T226;
  T226 = Core_Alu__io_op.values[0] == 0xbL;
  val_t T227;
  { T227 = TERNARY_1(T226, T225, T223);}
  val_t T228;
  T228 = (Core_Alu__io_b.values[0] >> 31) & 1;
  val_t T229;
  T229 = Core_Alu__io_b.values[0]<=Core_Alu__io_a.values[0];
  val_t T230;
  T230 = (Core_Alu__io_a.values[0] >> 31) & 1;
  val_t T231;
  T231 = T228 == T230;
  val_t T232;
  { T232 = TERNARY_1(T231, T229, T228);}
  val_t T233;
  { T233 = T232 | 0x0L << 1;}
  val_t T234;
  T234 = Core_Alu__io_op.values[0] == 0xaL;
  val_t T235;
  { T235 = TERNARY_1(T234, T233, T227);}
  val_t T236;
  T236 = Core_Alu__io_a.values[0] != Core_Alu__io_b.values[0];
  val_t T237;
  { T237 = T236 | 0x0L << 1;}
  val_t T238;
  T238 = Core_Alu__io_op.values[0] == 0x9L;
  val_t T239;
  { T239 = TERNARY_1(T238, T237, T235);}
  val_t T240;
  T240 = Core_Alu__io_a.values[0] == Core_Alu__io_b.values[0];
  val_t T241;
  { T241 = T240 | 0x0L << 1;}
  val_t T242;
  T242 = Core_Alu__io_op.values[0] == 0x8L;
  val_t T243;
  { T243 = TERNARY_1(T242, T241, T239);}
  val_t T244;
  T244 = Core_Alu__io_a.values[0]<Core_Alu__io_b.values[0];
  val_t T245;
  { T245 = T244 | 0x0L << 1;}
  val_t T246;
  T246 = Core_Alu__io_op.values[0] == 0x7L;
  val_t T247;
  { T247 = TERNARY_1(T246, T245, T243);}
  val_t T248;
  T248 = (Core_Alu__io_a.values[0] >> 31) & 1;
  val_t T249;
  T249 = Core_Alu__io_a.values[0]<Core_Alu__io_b.values[0];
  val_t T250;
  T250 = (Core_Alu__io_b.values[0] >> 31) & 1;
  val_t T251;
  T251 = T248 == T250;
  val_t T252;
  { T252 = TERNARY_1(T251, T249, T248);}
  val_t T253;
  { T253 = T252 | 0x0L << 1;}
  val_t T254;
  T254 = Core_Alu__io_op.values[0] == 0x6L;
  val_t T255;
  { T255 = TERNARY_1(T254, T253, T247);}
  val_t T256;
  { T256 = Core_Alu__io_a.values[0] ^ Core_Alu__io_b.values[0];}
  val_t T257;
  T257 = Core_Alu__io_op.values[0] == 0x5L;
  val_t T258;
  { T258 = TERNARY_1(T257, T256, T255);}
  val_t T259;
  { T259 = Core_Alu__io_a.values[0] | Core_Alu__io_b.values[0];}
  val_t T260;
  T260 = Core_Alu__io_op.values[0] == 0x4L;
  val_t T261;
  { T261 = TERNARY_1(T260, T259, T258);}
  val_t T262;
  { T262 = Core_Alu__io_a.values[0] & Core_Alu__io_b.values[0];}
  val_t T263;
  T263 = Core_Alu__io_op.values[0] == 0x3L;
  val_t T264;
  { T264 = TERNARY_1(T263, T262, T261);}
  val_t T265;
  { T265 = Core_Alu__io_a.values[0]-Core_Alu__io_b.values[0];}
  T265 = T265 & 0xffffffffL;
  val_t T266;
  T266 = Core_Alu__io_op.values[0] == 0x2L;
  val_t T267;
  { T267 = TERNARY_1(T266, T265, T264);}
  val_t T268;
  { T268 = Core_Alu__io_a.values[0]+Core_Alu__io_b.values[0];}
  T268 = T268 & 0xffffffffL;
  val_t T269;
  T269 = Core_Alu__io_op.values[0] == 0x1L;
  val_t T270;
  { T270 = TERNARY_1(T269, T268, T267);}
  { Core_Alu__io_out.values[0] = T270;}
  val_t T271;
  { T271 = Core_Alu__io_out.values[0];}
  T271 = T271 & 0x3ffL;
  { Core_DataMem__io_addr.values[0] = T271;}
  val_t T272;
  T272 = Core_Alu__io_out.values[0] == 0x0L;
  val_t T273;
  { T273 = TERNARY(T272, 0x1L, 0x0L);}
  { Core_Alu__io_zero.values[0] = T273;}
  val_t T274;
  { T274 = TERNARY(T7, 0x1L, 0x2L);}
  val_t T275;
  { T275 = TERNARY(T10, 0x0L, T274);}
  val_t T276;
  { T276 = TERNARY(T13, 0x2L, T275);}
  val_t T277;
  { T277 = TERNARY(T16, 0x4L, T276);}
  val_t T278;
  { T278 = TERNARY(T19, 0x1L, T277);}
  val_t T279;
  { T279 = TERNARY(T22, 0x3L, T278);}
  val_t T280;
  { T280 = TERNARY(T25, 0x0L, T279);}
  val_t T281;
  { T281 = TERNARY(T28, 0x2L, T280);}
  val_t T282;
  { T282 = TERNARY(T31, 0x2L, T281);}
  val_t T283;
  { T283 = TERNARY(T34, 0x2L, T282);}
  val_t T284;
  { T284 = TERNARY(T37, 0x2L, T283);}
  val_t T285;
  { T285 = TERNARY(T40, 0x2L, T284);}
  val_t T286;
  { T286 = TERNARY(T43, 0x2L, T285);}
  val_t T287;
  { T287 = TERNARY(T46, 0x2L, T286);}
  val_t T288;
  { T288 = TERNARY(T49, 0x2L, T287);}
  val_t T289;
  { T289 = TERNARY(T52, 0x2L, T288);}
  val_t Core_Decoder__ctl_msk_sel;
  { Core_Decoder__ctl_msk_sel = TERNARY(T55, 0x2L, T289);}
  { Core_Decoder__io_ctl_msk_sel.values[0] = Core_Decoder__ctl_msk_sel;}
  { Core_Decoder__io_ctl_csr_cmd.values[0] = 0x0L;}
  val_t T290;
  { T290 = Core_DataMem__mem.get(Core_DataMem__io_addr.values[0], 0);}
  val_t T291;
  T291 = Core_DataMem__io_mem_func.values[0] == 0x0L;
  val_t T292;
  { T292 = Core_DataMem__io_mem_en.values[0] & T291;}
  val_t T293;
  { T293 = TERNARY(T292, T290, 0x0L);}
  { Core_DataMem__io_rd_data.values[0] = T293;}
  { Core_MuxWB__io_wb_mem.values[0] = Core_DataMem__io_rd_data.values[0];}
  val_t T294;
  { T294 = TERNARY(T13, 0x3L, 0x0L);}
  val_t T295;
  { T295 = TERNARY(T16, 0x3L, T294);}
  val_t T296;
  { T296 = TERNARY(T19, 0x3L, T295);}
  val_t T297;
  { T297 = TERNARY(T22, 0x3L, T296);}
  val_t T298;
  { T298 = TERNARY(T25, 0x3L, T297);}
  val_t T299;
  { T299 = TERNARY(T28, 0x0L, T298);}
  val_t T300;
  { T300 = TERNARY(T31, 0x0L, T299);}
  val_t T301;
  { T301 = TERNARY(T34, 0x0L, T300);}
  val_t T302;
  { T302 = TERNARY(T37, 0x0L, T301);}
  val_t T303;
  { T303 = TERNARY(T40, 0x0L, T302);}
  val_t T304;
  { T304 = TERNARY(T43, 0x0L, T303);}
  val_t T305;
  { T305 = TERNARY(T46, 0x2L, T304);}
  val_t T306;
  { T306 = TERNARY(T49, 0x2L, T305);}
  val_t T307;
  { T307 = TERNARY(T52, 0x0L, T306);}
  val_t Core_Decoder__ctl_wb_sel;
  { Core_Decoder__ctl_wb_sel = TERNARY(T55, 0x0L, T307);}
  { Core_Decoder__io_ctl_wb_sel.values[0] = Core_Decoder__ctl_wb_sel;}
  { Core_MuxWB__io_wb_sel.values[0] = Core_Decoder__io_ctl_wb_sel.values[0];}
  val_t T308;
  T308 = Core_MuxWB__io_wb_sel.values[0] == 0x3L;
  val_t T309;
  { T309 = TERNARY(T308, Core_MuxWB__io_wb_mem.values[0], 0x0L);}
  { Core_MuxWB__io_wb_csr.values[0] = Core_Alu__io_out.values[0];}
  val_t T310;
  T310 = Core_MuxWB__io_wb_sel.values[0] == 0x1L;
  val_t T311;
  { T311 = TERNARY_1(T310, Core_MuxWB__io_wb_csr.values[0], T309);}
  { Core_MuxWB__io_wb_pc4.values[0] = Core__exec_pc4_reg.values[0];}
  val_t T312;
  T312 = Core_MuxWB__io_wb_sel.values[0] == 0x2L;
  val_t T313;
  { T313 = TERNARY_1(T312, Core_MuxWB__io_wb_pc4.values[0], T311);}
  { Core_MuxWB__io_wb_alu.values[0] = Core_Alu__io_out.values[0];}
  val_t T314;
  T314 = Core_MuxWB__io_wb_sel.values[0] == 0x0L;
  val_t T315;
  { T315 = TERNARY_1(T314, Core_MuxWB__io_wb_alu.values[0], T313);}
  { Core_MuxWB__io_wb_wd.values[0] = T315;}
  { Core_RegFile__io_rf_wd.values[0] = Core_MuxWB__io_wb_wd.values[0];}
  val_t Core__rd_addr;
  { Core__rd_addr = Core__exec_instr_reg.values[0] >> 7;}
  Core__rd_addr = Core__rd_addr & 0x1fL;
  { Core_RegFile__io_rf_wa.values[0] = Core__rd_addr;}
  val_t T316;
  T316 = Core_RegFile__io_rf_wa.values[0] != 0x0L;
  val_t T317;
  { T317 = TERNARY(T89, 0x1L, T86);}
  val_t T318;
  { T318 = TERNARY(T92, 0x1L, T317);}
  val_t T319;
  { T319 = TERNARY(T95, 0x1L, T318);}
  val_t T320;
  { T320 = TERNARY(T98, 0x1L, T319);}
  val_t T321;
  { T321 = TERNARY(T101, 0x1L, T320);}
  val_t T322;
  { T322 = TERNARY(T104, 0x1L, T321);}
  val_t T323;
  { T323 = TERNARY(T107, 0x1L, T322);}
  val_t T324;
  { T324 = TERNARY(T110, 0x1L, T323);}
  val_t T325;
  { T325 = TERNARY(T113, 0x1L, T324);}
  val_t T326;
  { T326 = TERNARY(T116, 0x1L, T325);}
  val_t T327;
  { T327 = TERNARY(T119, 0x1L, T326);}
  val_t T328;
  { T328 = TERNARY(T122, 0x1L, T327);}
  val_t T329;
  { T329 = TERNARY(T125, 0x1L, T328);}
  val_t T330;
  { T330 = TERNARY(T128, 0x1L, T329);}
  val_t T331;
  { T331 = TERNARY(T131, 0x1L, T330);}
  val_t T332;
  { T332 = TERNARY(T134, 0x1L, T331);}
  val_t T333;
  { T333 = TERNARY(T137, 0x1L, T332);}
  val_t T334;
  { T334 = TERNARY(T140, 0x1L, T333);}
  val_t T335;
  { T335 = TERNARY(T4, 0x0L, T334);}
  val_t T336;
  { T336 = TERNARY(T7, 0x0L, T335);}
  val_t T337;
  { T337 = TERNARY(T10, 0x0L, T336);}
  val_t T338;
  { T338 = TERNARY(T13, 0x1L, T337);}
  val_t T339;
  { T339 = TERNARY(T16, 0x1L, T338);}
  val_t T340;
  { T340 = TERNARY(T19, 0x1L, T339);}
  val_t T341;
  { T341 = TERNARY(T22, 0x1L, T340);}
  val_t T342;
  { T342 = TERNARY(T25, 0x1L, T341);}
  val_t T343;
  { T343 = TERNARY(T28, 0x0L, T342);}
  val_t T344;
  { T344 = TERNARY(T31, 0x0L, T343);}
  val_t T345;
  { T345 = TERNARY(T34, 0x0L, T344);}
  val_t T346;
  { T346 = TERNARY(T37, 0x0L, T345);}
  val_t T347;
  { T347 = TERNARY(T40, 0x0L, T346);}
  val_t T348;
  { T348 = TERNARY(T43, 0x0L, T347);}
  val_t T349;
  { T349 = TERNARY(T46, 0x1L, T348);}
  val_t T350;
  { T350 = TERNARY(T49, 0x1L, T349);}
  val_t T351;
  { T351 = TERNARY(T52, 0x1L, T350);}
  val_t Core_Decoder__ctl_rf_wen;
  { Core_Decoder__ctl_rf_wen = TERNARY(T55, 0x1L, T351);}
  { Core_Decoder__io_ctl_rf_wen.values[0] = Core_Decoder__ctl_rf_wen;}
  val_t T352;
  { T352 = TERNARY(T89, 0x1L, T86);}
  val_t T353;
  { T353 = TERNARY(T92, 0x1L, T352);}
  val_t T354;
  { T354 = TERNARY(T95, 0x1L, T353);}
  val_t T355;
  { T355 = TERNARY(T98, 0x1L, T354);}
  val_t T356;
  { T356 = TERNARY(T101, 0x1L, T355);}
  val_t T357;
  { T357 = TERNARY(T104, 0x1L, T356);}
  val_t T358;
  { T358 = TERNARY(T107, 0x1L, T357);}
  val_t T359;
  { T359 = TERNARY(T110, 0x1L, T358);}
  val_t T360;
  { T360 = TERNARY(T113, 0x1L, T359);}
  val_t T361;
  { T361 = TERNARY(T116, 0x1L, T360);}
  val_t T362;
  { T362 = TERNARY(T119, 0x1L, T361);}
  val_t T363;
  { T363 = TERNARY(T122, 0x1L, T362);}
  val_t T364;
  { T364 = TERNARY(T125, 0x1L, T363);}
  val_t T365;
  { T365 = TERNARY(T128, 0x1L, T364);}
  val_t T366;
  { T366 = TERNARY(T131, 0x1L, T365);}
  val_t T367;
  { T367 = TERNARY(T134, 0x1L, T366);}
  val_t T368;
  { T368 = TERNARY(T137, 0x1L, T367);}
  val_t T369;
  { T369 = TERNARY(T140, 0x1L, T368);}
  val_t T370;
  { T370 = TERNARY(T4, 0x1L, T369);}
  val_t T371;
  { T371 = TERNARY(T7, 0x1L, T370);}
  val_t T372;
  { T372 = TERNARY(T10, 0x1L, T371);}
  val_t T373;
  { T373 = TERNARY(T13, 0x1L, T372);}
  val_t T374;
  { T374 = TERNARY(T16, 0x1L, T373);}
  val_t T375;
  { T375 = TERNARY(T19, 0x1L, T374);}
  val_t T376;
  { T376 = TERNARY(T22, 0x1L, T375);}
  val_t T377;
  { T377 = TERNARY(T25, 0x1L, T376);}
  val_t T378;
  { T378 = TERNARY(T28, 0x1L, T377);}
  val_t T379;
  { T379 = TERNARY(T31, 0x1L, T378);}
  val_t T380;
  { T380 = TERNARY(T34, 0x1L, T379);}
  val_t T381;
  { T381 = TERNARY(T37, 0x1L, T380);}
  val_t T382;
  { T382 = TERNARY(T40, 0x1L, T381);}
  val_t T383;
  { T383 = TERNARY(T43, 0x1L, T382);}
  val_t T384;
  { T384 = TERNARY(T46, 0x1L, T383);}
  val_t T385;
  { T385 = TERNARY(T49, 0x1L, T384);}
  val_t T386;
  { T386 = TERNARY(T52, 0x1L, T385);}
  val_t Core_Decoder__ctl_val_inst;
  { Core_Decoder__ctl_val_inst = TERNARY(T55, 0x1L, T386);}
  { Core_Decoder__io_ctl_val_inst.values[0] = Core_Decoder__ctl_val_inst;}
  val_t Core__stall;
  { Core__stall = Core_Decoder__io_ctl_val_inst.values[0] ^ 0x1L;}
  val_t T387;
  { T387 = TERNARY(Core__stall, 0x0L, Core_Decoder__io_ctl_rf_wen.values[0]);}
  { Core_RegFile__io_rf_wen.values[0] = T387;}
  { T388.values[0] = Core_RegFile__io_rf_wen.values[0] & T316;}
  val_t T389;
  { T389 = TERNARY_1(Core__stall, Core__exec_instr_reg.values[0], Core__exec_instr_reg.values[0]);}
  val_t Core__halt;
  { Core__halt = Core_Decoder__io_ctl_val_inst.values[0] ^ 0x1L;}
  val_t T390;
  { T390 = Core__halt ^ 0x1L;}
  val_t T391;
  { T391 = TERNARY(T28, 0x6L, 0x0L);}
  val_t T392;
  { T392 = TERNARY(T31, 0x5L, T391);}
  val_t T393;
  { T393 = TERNARY(T34, 0x4L, T392);}
  val_t T394;
  { T394 = TERNARY(T37, 0x3L, T393);}
  val_t T395;
  { T395 = TERNARY(T40, 0x2L, T394);}
  val_t T396;
  { T396 = TERNARY(T43, 0x1L, T395);}
  val_t T397;
  { T397 = TERNARY(T46, 0x8L, T396);}
  val_t T398;
  { T398 = TERNARY(T49, 0x7L, T397);}
  val_t T399;
  { T399 = TERNARY(T52, 0x0L, T398);}
  val_t Core_Decoder__ctl_br_type;
  { Core_Decoder__ctl_br_type = TERNARY(T55, 0x0L, T399);}
  { Core_Decoder__io_ctl_br_type.values[0] = Core_Decoder__ctl_br_type;}
  { Core_BranchLogic__io_ctl_br_type.values[0] = Core_Decoder__io_ctl_br_type.values[0];}
  val_t T400;
  T400 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x8L;
  val_t T401;
  { T401 = TERNARY(T400, 0x1L, 0x0L);}
  val_t T402;
  T402 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x7L;
  val_t T403;
  { T403 = TERNARY(T402, 0x3L, T401);}
  val_t T404;
  T404 = Core_RegFile__io_rf_rd1.values[0]<Core_RegFile__io_rf_rd2.values[0];
  { Core_BranchLogic__io_br_ltu.values[0] = T404;}
  val_t T405;
  { T405 = TERNARY(Core_BranchLogic__io_br_ltu.values[0], 0x2L, 0x0L);}
  val_t T406;
  T406 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x6L;
  val_t T407;
  { T407 = TERNARY_1(T406, T405, T403);}
  val_t T408;
  T408 = (Core_RegFile__io_rf_rd1.values[0] >> 31) & 1;
  val_t T409;
  T409 = Core_RegFile__io_rf_rd1.values[0]<Core_RegFile__io_rf_rd2.values[0];
  val_t T410;
  T410 = (Core_RegFile__io_rf_rd2.values[0] >> 31) & 1;
  val_t T411;
  T411 = T408 == T410;
  val_t T412;
  { T412 = TERNARY_1(T411, T409, T408);}
  { Core_BranchLogic__io_br_lt.values[0] = T412;}
  val_t T413;
  { T413 = TERNARY(Core_BranchLogic__io_br_lt.values[0], 0x2L, 0x0L);}
  val_t T414;
  T414 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x5L;
  val_t T415;
  { T415 = TERNARY_1(T414, T413, T407);}
  val_t T416;
  { T416 = Core_BranchLogic__io_br_ltu.values[0] ^ 0x1L;}
  val_t T417;
  { T417 = TERNARY(T416, 0x2L, 0x0L);}
  val_t T418;
  T418 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x4L;
  val_t T419;
  { T419 = TERNARY_1(T418, T417, T415);}
  val_t T420;
  { T420 = Core_BranchLogic__io_br_lt.values[0] ^ 0x1L;}
  val_t T421;
  { T421 = TERNARY(T420, 0x2L, 0x0L);}
  val_t T422;
  T422 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x3L;
  val_t T423;
  { T423 = TERNARY_1(T422, T421, T419);}
  val_t T424;
  T424 = Core_RegFile__io_rf_rd1.values[0] == Core_RegFile__io_rf_rd2.values[0];
  { Core_BranchLogic__io_br_eq.values[0] = T424;}
  val_t T425;
  { T425 = TERNARY(Core_BranchLogic__io_br_eq.values[0], 0x2L, 0x0L);}
  val_t T426;
  T426 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x1L;
  val_t T427;
  { T427 = TERNARY_1(T426, T425, T423);}
  val_t T428;
  { T428 = Core_BranchLogic__io_br_eq.values[0] ^ 0x1L;}
  val_t T429;
  { T429 = TERNARY(T428, 0x2L, 0x0L);}
  val_t T430;
  T430 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x2L;
  val_t T431;
  { T431 = TERNARY_1(T430, T429, T427);}
  val_t T432;
  T432 = Core_BranchLogic__io_ctl_br_type.values[0] == 0x0L;
  val_t T433;
  { T433 = TERNARY(T432, 0x0L, T431);}
  { Core_BranchLogic__io_excp.values[0] = Core__halt;}
  val_t T434;
  { T434 = TERNARY(Core_BranchLogic__io_excp.values[0], 0x4L, T433);}
  { Core_BranchLogic__io_pc_sel.values[0] = T434;}
  val_t T435;
  T435 = Core_BranchLogic__io_pc_sel.values[0] == 0x0L;
  val_t Core__kill_the_fetch;
  { Core__kill_the_fetch = T435 ^ 0x1L;}
  val_t T436;
  { T436 = Core__kill_the_fetch & T390;}
  val_t T437;
  { T437 = Core__stall ^ 0x1L;}
  val_t T438;
  { T438 = T437 & T436;}
  val_t T439;
  { T439 = TERNARY(T438, 0x4033L, T389);}
  val_t T440;
  { T440 = Core__kill_the_fetch & Core__halt;}
  val_t T441;
  { T441 = Core__stall | T436;}
  val_t T442;
  { T442 = T441 ^ 0x1L;}
  val_t T443;
  { T443 = T442 & T440;}
  val_t T444;
  { T444 = TERNARY_1(T443, Core__exec_instr_reg.values[0], T439);}
  val_t T445;
  { T445 = Core__fetch_pc_reg.values[0];}
  T445 = T445 & 0x3ffL;
  { Core_InstructionMem__io_addr.values[0] = T445;}
  val_t T446;
  { T446 = Core_InstructionMem__mem.get(Core_InstructionMem__io_addr.values[0], 0);}
  { Core_InstructionMem__io_data.values[0] = T446;}
  val_t T447;
  { T447 = T441 | T440;}
  val_t T448;
  { T448 = T447 ^ 0x1L;}
  val_t T449;
  { T449 = TERNARY_1(T448, Core_InstructionMem__io_data.values[0], T444);}
  { T450.values[0] = TERNARY(reset.values[0], 0x4033L, T449);}
  val_t T451;
  { T451 = TERNARY_1(Core__stall, Core__exec_pc_reg.values[0], Core__exec_pc_reg.values[0]);}
  val_t T452;
  { T452 = TERNARY(T438, 0x0L, T451);}
  val_t T453;
  { T453 = TERNARY_1(T443, Core__exec_pc_reg.values[0], T452);}
  val_t T454;
  { T454 = TERNARY_1(T448, Core__fetch_pc_reg.values[0], T453);}
  { T455.values[0] = TERNARY(reset.values[0], 0x0L, T454);}
  { Core_MuxPC__io_pc_excp.values[0] = 0x0L;}
  { Core_MuxPC__io_pc_sel.values[0] = Core_BranchLogic__io_pc_sel.values[0];}
  val_t T456;
  T456 = Core_MuxPC__io_pc_sel.values[0] == 0x4L;
  val_t T457;
  { T457 = TERNARY(T456, Core_MuxPC__io_pc_excp.values[0], 0x0L);}
  val_t T458;
  { T458 = Core_ImmGen__io_instr.values[0] >> 21;}
  T458 = T458 & 0x3ffL;
  val_t T459;
  T459 = (Core_ImmGen__io_instr.values[0] >> 20) & 1;
  val_t T460;
  { T460 = T458 | T459 << 10;}
  val_t T461;
  { T461 = Core_ImmGen__io_instr.values[0] >> 12;}
  T461 = T461 & 0xffL;
  val_t T462;
  T462 = (Core_ImmGen__io_instr.values[0] >> 31) & 1;
  val_t T463;
  { T463 = T461 | T462 << 8;}
  val_t Core_ImmGen__immj;
  { Core_ImmGen__immj = T460 | T463 << 11;}
  val_t T464;
  T464 = (Core_ImmGen__immj >> 19) & 1;
  val_t T465;
  { T465 = TERNARY(T464, 0x7ffL, 0x0L);}
  val_t T466;
  { T466 = Core_ImmGen__immj | T465 << 20;}
  val_t T467;
  { T467 = T466 | 0x0L << 31;}
  { Core_ImmGen__io_immj_sxt.values[0] = T467;}
  val_t Core__exec_pc_jmp;
  { Core__exec_pc_jmp = Core__exec_pc_reg.values[0]+Core_ImmGen__io_immj_sxt.values[0];}
  Core__exec_pc_jmp = Core__exec_pc_jmp & 0xffffffffL;
  { Core_MuxPC__io_pc_jmp.values[0] = Core__exec_pc_jmp;}
  val_t T468;
  T468 = Core_MuxPC__io_pc_sel.values[0] == 0x3L;
  val_t T469;
  { T469 = TERNARY_1(T468, Core_MuxPC__io_pc_jmp.values[0], T457);}
  val_t T470;
  { T470 = Core_ImmGen__io_instr.values[0] >> 8;}
  T470 = T470 & 0xfL;
  val_t T471;
  { T471 = Core_ImmGen__io_instr.values[0] >> 25;}
  T471 = T471 & 0x3fL;
  val_t T472;
  { T472 = T470 | T471 << 4;}
  val_t T473;
  T473 = (Core_ImmGen__io_instr.values[0] >> 7) & 1;
  val_t T474;
  T474 = (Core_ImmGen__io_instr.values[0] >> 31) & 1;
  val_t T475;
  { T475 = T473 | T474 << 1;}
  val_t Core_ImmGen__immb;
  { Core_ImmGen__immb = T472 | T475 << 10;}
  val_t T476;
  T476 = (Core_ImmGen__immb >> 11) & 1;
  val_t T477;
  { T477 = TERNARY(T476, 0x7ffffL, 0x0L);}
  val_t T478;
  { T478 = 0x0L | T477 << 1;}
  val_t T479;
  { T479 = T478 | 0x0L << 20;}
  { Core_ImmGen__io_immb_sxt.values[0] = T479;}
  val_t Core__exec_pc_br;
  { Core__exec_pc_br = Core__exec_pc_reg.values[0]+Core_ImmGen__io_immb_sxt.values[0];}
  Core__exec_pc_br = Core__exec_pc_br & 0xffffffffL;
  { Core_MuxPC__io_pc_br.values[0] = Core__exec_pc_br;}
  val_t T480;
  T480 = Core_MuxPC__io_pc_sel.values[0] == 0x2L;
  val_t T481;
  { T481 = TERNARY_1(T480, Core_MuxPC__io_pc_br.values[0], T469);}
  val_t Core__exec_pc_jalr;
  { Core__exec_pc_jalr = Core_RegFile__io_rf_rd1.values[0]+Core_ImmGen__io_immi_sxt.values[0];}
  Core__exec_pc_jalr = Core__exec_pc_jalr & 0xffffffffL;
  { Core_MuxPC__io_pc_jalr.values[0] = Core__exec_pc_jalr;}
  val_t T482;
  T482 = Core_MuxPC__io_pc_sel.values[0] == 0x1L;
  val_t T483;
  { T483 = TERNARY_1(T482, Core_MuxPC__io_pc_jalr.values[0], T481);}
  val_t Core__fetch_pc4_reg;
  { Core__fetch_pc4_reg = Core__fetch_pc_reg.values[0]+0x1L;}
  Core__fetch_pc4_reg = Core__fetch_pc4_reg & 0xffffffffL;
  { Core_MuxPC__io_pc_pc4.values[0] = Core__fetch_pc4_reg;}
  val_t T484;
  T484 = Core_MuxPC__io_pc_sel.values[0] == 0x0L;
  val_t T485;
  { T485 = TERNARY_1(T484, Core_MuxPC__io_pc_pc4.values[0], T483);}
  { Core_MuxPC__io_pc_out.values[0] = T485;}
  val_t T486;
  { T486 = Core__stall ^ 0x1L;}
  val_t T487;
  { T487 = TERNARY_1(T486, Core_MuxPC__io_pc_out.values[0], Core__fetch_pc_reg.values[0]);}
  { T488.values[0] = TERNARY(reset.values[0], 0x0L, T487);}
  { T489.values[0] = TERNARY(reset.values[0], 0x0L, Core__fetch_pc4_reg);}
}


void Core_t::clock_hi ( dat_t<1> reset ) {
  { if (T73.values[0]) Core_DataMem__mem.put(Core_DataMem__io_addr.values[0], 0, Core_DataMem__io_wr_data.values[0]);}
  { if (T388.values[0]) Core_RegFile__rf_reg_file.put(Core_RegFile__io_rf_wa.values[0], 0, Core_RegFile__io_rf_wd.values[0]);}
  dat_t<32> Core__exec_instr_reg__shadow = T450;
  dat_t<32> Core__exec_pc_reg__shadow = T455;
  dat_t<32> Core__fetch_pc_reg__shadow = T488;
  dat_t<32> Core__exec_pc4_reg__shadow = T489;
  Core__exec_instr_reg = T450;
  Core__exec_pc_reg = T455;
  Core__fetch_pc_reg = T488;
  Core__exec_pc4_reg = T489;
}


void Core_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  Core_t* mod = dynamic_cast<Core_t*>(module);
  assert(mod);
  sim_data.signals.push_back(new dat_api<5>(&mod->Core_RegFile__io_rf_ra2));
  sim_data.signal_map["Core.RegFile.io_rf_ra2"] = 0;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_RegFile__io_rf_rd2));
  sim_data.signal_map["Core.RegFile.io_rf_rd2"] = 1;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_DataMem__io_wr_data));
  sim_data.signal_map["Core.DataMem.io_wr_data"] = 2;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_Decoder__io_dec_instr));
  sim_data.signal_map["Core.Decoder.io_dec_instr"] = 3;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_Decoder__io_ctl_mem_func));
  sim_data.signal_map["Core.Decoder.io_ctl_mem_func"] = 4;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_DataMem__io_mem_func));
  sim_data.signal_map["Core.DataMem.io_mem_func"] = 5;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_Decoder__io_ctl_mem_en));
  sim_data.signal_map["Core.Decoder.io_ctl_mem_en"] = 6;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_DataMem__io_mem_en));
  sim_data.signal_map["Core.DataMem.io_mem_en"] = 7;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_instr));
  sim_data.signal_map["Core.ImmGen.io_instr"] = 8;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_immu_sxt));
  sim_data.signal_map["Core.ImmGen.io_immu_sxt"] = 9;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpA__io_opa_imz));
  sim_data.signal_map["Core.MuxOpA.io_opa_imz"] = 10;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_Decoder__io_ctl_opa_sel));
  sim_data.signal_map["Core.Decoder.io_ctl_opa_sel"] = 11;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_MuxOpA__io_opa_sel));
  sim_data.signal_map["Core.MuxOpA.io_opa_sel"] = 12;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpA__io_opa_imu));
  sim_data.signal_map["Core.MuxOpA.io_opa_imu"] = 13;
  sim_data.signals.push_back(new dat_api<5>(&mod->Core_RegFile__io_rf_ra1));
  sim_data.signal_map["Core.RegFile.io_rf_ra1"] = 14;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_RegFile__io_rf_rd1));
  sim_data.signal_map["Core.RegFile.io_rf_rd1"] = 15;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpA__io_opa_rsa));
  sim_data.signal_map["Core.MuxOpA.io_opa_rsa"] = 16;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpA__io_opa_alu_in));
  sim_data.signal_map["Core.MuxOpA.io_opa_alu_in"] = 17;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_Alu__io_a));
  sim_data.signal_map["Core.Alu.io_a"] = 18;
  sim_data.signals.push_back(new dat_api<4>(&mod->Core_Decoder__io_ctl_alu_func));
  sim_data.signal_map["Core.Decoder.io_ctl_alu_func"] = 19;
  sim_data.signals.push_back(new dat_api<4>(&mod->Core_Alu__io_op));
  sim_data.signal_map["Core.Alu.io_op"] = 20;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpB__io_opb_pc));
  sim_data.signal_map["Core.MuxOpB.io_opb_pc"] = 21;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_Decoder__io_ctl_opb_sel));
  sim_data.signal_map["Core.Decoder.io_ctl_opb_sel"] = 22;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_MuxOpB__io_opb_sel));
  sim_data.signal_map["Core.MuxOpB.io_opb_sel"] = 23;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_imms_sxt));
  sim_data.signal_map["Core.ImmGen.io_imms_sxt"] = 24;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpB__io_opb_ims));
  sim_data.signal_map["Core.MuxOpB.io_opb_ims"] = 25;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_immi_sxt));
  sim_data.signal_map["Core.ImmGen.io_immi_sxt"] = 26;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpB__io_opb_imi));
  sim_data.signal_map["Core.MuxOpB.io_opb_imi"] = 27;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpB__io_opb_rsb));
  sim_data.signal_map["Core.MuxOpB.io_opb_rsb"] = 28;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxOpB__io_opb_alu_in));
  sim_data.signal_map["Core.MuxOpB.io_opb_alu_in"] = 29;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_Alu__io_b));
  sim_data.signal_map["Core.Alu.io_b"] = 30;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_Alu__io_out));
  sim_data.signal_map["Core.Alu.io_out"] = 31;
  sim_data.signals.push_back(new dat_api<10>(&mod->Core_DataMem__io_addr));
  sim_data.signal_map["Core.DataMem.io_addr"] = 32;
  std::string Core_DataMem__mem_path = "Core.DataMem.mem";
  for (size_t i = 0 ; i < 1024 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->Core_DataMem__mem.contents[i]));
    sim_data.signal_map[Core_DataMem__mem_path+"["+itos(i,false)+"]"] = 33+i;
  }
  std::string Core_InstructionMem__mem_path = "Core.InstructionMem.mem";
  for (size_t i = 0 ; i < 1024 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->Core_InstructionMem__mem.contents[i]));
    sim_data.signal_map[Core_InstructionMem__mem_path+"["+itos(i,false)+"]"] = 1057+i;
  }
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_Alu__io_zero));
  sim_data.signal_map["Core.Alu.io_zero"] = 2081;
  sim_data.signals.push_back(new dat_api<3>(&mod->Core_Decoder__io_ctl_msk_sel));
  sim_data.signal_map["Core.Decoder.io_ctl_msk_sel"] = 2082;
  sim_data.signals.push_back(new dat_api<3>(&mod->Core_Decoder__io_ctl_csr_cmd));
  sim_data.signal_map["Core.Decoder.io_ctl_csr_cmd"] = 2083;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_DataMem__io_rd_data));
  sim_data.signal_map["Core.DataMem.io_rd_data"] = 2084;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxWB__io_wb_mem));
  sim_data.signal_map["Core.MuxWB.io_wb_mem"] = 2085;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_Decoder__io_ctl_wb_sel));
  sim_data.signal_map["Core.Decoder.io_ctl_wb_sel"] = 2086;
  sim_data.signals.push_back(new dat_api<2>(&mod->Core_MuxWB__io_wb_sel));
  sim_data.signal_map["Core.MuxWB.io_wb_sel"] = 2087;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxWB__io_wb_csr));
  sim_data.signal_map["Core.MuxWB.io_wb_csr"] = 2088;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxWB__io_wb_pc4));
  sim_data.signal_map["Core.MuxWB.io_wb_pc4"] = 2089;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxWB__io_wb_alu));
  sim_data.signal_map["Core.MuxWB.io_wb_alu"] = 2090;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxWB__io_wb_wd));
  sim_data.signal_map["Core.MuxWB.io_wb_wd"] = 2091;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_RegFile__io_rf_wd));
  sim_data.signal_map["Core.RegFile.io_rf_wd"] = 2092;
  sim_data.signals.push_back(new dat_api<5>(&mod->Core_RegFile__io_rf_wa));
  sim_data.signal_map["Core.RegFile.io_rf_wa"] = 2093;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_Decoder__io_ctl_rf_wen));
  sim_data.signal_map["Core.Decoder.io_ctl_rf_wen"] = 2094;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_Decoder__io_ctl_val_inst));
  sim_data.signal_map["Core.Decoder.io_ctl_val_inst"] = 2095;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_RegFile__io_rf_wen));
  sim_data.signal_map["Core.RegFile.io_rf_wen"] = 2096;
  std::string Core_RegFile__rf_reg_file_path = "Core.RegFile.rf_reg_file";
  for (size_t i = 0 ; i < 32 ; i++) {
    sim_data.signals.push_back(new dat_api<32>(&mod->Core_RegFile__rf_reg_file.contents[i]));
    sim_data.signal_map[Core_RegFile__rf_reg_file_path+"["+itos(i,false)+"]"] = 2097+i;
  }
  sim_data.signals.push_back(new dat_api<4>(&mod->Core_Decoder__io_ctl_br_type));
  sim_data.signal_map["Core.Decoder.io_ctl_br_type"] = 2129;
  sim_data.signals.push_back(new dat_api<4>(&mod->Core_BranchLogic__io_ctl_br_type));
  sim_data.signal_map["Core.BranchLogic.io_ctl_br_type"] = 2130;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_BranchLogic__io_br_ltu));
  sim_data.signal_map["Core.BranchLogic.io_br_ltu"] = 2131;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_BranchLogic__io_br_lt));
  sim_data.signal_map["Core.BranchLogic.io_br_lt"] = 2132;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_BranchLogic__io_br_eq));
  sim_data.signal_map["Core.BranchLogic.io_br_eq"] = 2133;
  sim_data.signals.push_back(new dat_api<1>(&mod->Core_BranchLogic__io_excp));
  sim_data.signal_map["Core.BranchLogic.io_excp"] = 2134;
  sim_data.signals.push_back(new dat_api<3>(&mod->Core_BranchLogic__io_pc_sel));
  sim_data.signal_map["Core.BranchLogic.io_pc_sel"] = 2135;
  sim_data.signals.push_back(new dat_api<10>(&mod->Core_InstructionMem__io_addr));
  sim_data.signal_map["Core.InstructionMem.io_addr"] = 2136;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_InstructionMem__io_data));
  sim_data.signal_map["Core.InstructionMem.io_data"] = 2137;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core__exec_instr_reg));
  sim_data.signal_map["Core.exec_instr_reg"] = 2138;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core__exec_pc_reg));
  sim_data.signal_map["Core.exec_pc_reg"] = 2139;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_excp));
  sim_data.signal_map["Core.MuxPC.io_pc_excp"] = 2140;
  sim_data.signals.push_back(new dat_api<3>(&mod->Core_MuxPC__io_pc_sel));
  sim_data.signal_map["Core.MuxPC.io_pc_sel"] = 2141;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_immj_sxt));
  sim_data.signal_map["Core.ImmGen.io_immj_sxt"] = 2142;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_jmp));
  sim_data.signal_map["Core.MuxPC.io_pc_jmp"] = 2143;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_ImmGen__io_immb_sxt));
  sim_data.signal_map["Core.ImmGen.io_immb_sxt"] = 2144;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_br));
  sim_data.signal_map["Core.MuxPC.io_pc_br"] = 2145;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_jalr));
  sim_data.signal_map["Core.MuxPC.io_pc_jalr"] = 2146;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_pc4));
  sim_data.signal_map["Core.MuxPC.io_pc_pc4"] = 2147;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core_MuxPC__io_pc_out));
  sim_data.signal_map["Core.MuxPC.io_pc_out"] = 2148;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core__fetch_pc_reg));
  sim_data.signal_map["Core.fetch_pc_reg"] = 2149;
  sim_data.signals.push_back(new dat_api<32>(&mod->Core__exec_pc4_reg));
  sim_data.signal_map["Core.exec_pc4_reg"] = 2150;
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
