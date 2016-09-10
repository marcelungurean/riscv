module test;
  reg[1:0] io_wb_sel = 0;
  reg[31:0] io_wb_alu = 0;
  reg[31:0] io_wb_pc4 = 0;
  reg[31:0] io_wb_csr = 0;
  reg[31:0] io_wb_mem = 0;
  wire[31:0] io_wb_wd;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  MuxWB MuxWB(
    .io_wb_sel(io_wb_sel),
    .io_wb_alu(io_wb_alu),
    .io_wb_pc4(io_wb_pc4),
    .io_wb_csr(io_wb_csr),
    .io_wb_mem(io_wb_mem),
    .io_wb_wd(io_wb_wd));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_wb_sel, io_wb_alu, io_wb_pc4, io_wb_csr, io_wb_mem);
    $init_outs(io_wb_wd);
    $init_sigs(MuxWB);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, MuxWB);
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
