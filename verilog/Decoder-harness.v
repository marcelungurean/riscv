module test;
  reg[31:0] io_dec_instr = 0;
  wire[0:0] io_ctl_val_inst;
  wire[0:0] io_ctl_rf_wen;
  wire[3:0] io_ctl_br_type;
  wire[1:0] io_ctl_opa_sel;
  wire[1:0] io_ctl_opb_sel;
  wire[3:0] io_ctl_alu_func;
  wire[1:0] io_ctl_wb_sel;
  wire[1:0] io_ctl_mem_func;
  wire[0:0] io_ctl_mem_en;
  wire[2:0] io_ctl_msk_sel;
  wire[2:0] io_ctl_csr_cmd;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  Decoder Decoder(
    .io_dec_instr(io_dec_instr),
    .io_ctl_val_inst(io_ctl_val_inst),
    .io_ctl_rf_wen(io_ctl_rf_wen),
    .io_ctl_br_type(io_ctl_br_type),
    .io_ctl_opa_sel(io_ctl_opa_sel),
    .io_ctl_opb_sel(io_ctl_opb_sel),
    .io_ctl_alu_func(io_ctl_alu_func),
    .io_ctl_wb_sel(io_ctl_wb_sel),
    .io_ctl_mem_func(io_ctl_mem_func),
    .io_ctl_mem_en(io_ctl_mem_en),
    .io_ctl_msk_sel(io_ctl_msk_sel),
    .io_ctl_csr_cmd(io_ctl_csr_cmd));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_dec_instr);
    $init_outs(io_ctl_val_inst, io_ctl_rf_wen, io_ctl_br_type, io_ctl_opa_sel, io_ctl_opb_sel, io_ctl_alu_func, io_ctl_wb_sel, io_ctl_mem_func, io_ctl_mem_en, io_ctl_msk_sel, io_ctl_csr_cmd);
    $init_sigs(Decoder);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, Decoder);
      $dumpoff;
      vcdon = 0;
    end
    if ($value$plusargs("vpdfile=%s", vpdfile)) begin
      $vcdplusfile(vpdfile);
      $vcdpluson(0);
      $vcdplusautoflushon;
    end
    if ($test$plusargs("vpdmem")) begin
      $vcdplusmemon;
    end
  end

  always @(negedge clk) begin
    $tick();
  end

endmodule
