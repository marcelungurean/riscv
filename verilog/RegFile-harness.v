module test;
  reg[4:0] io_rf_ra1 = 0;
  reg[4:0] io_rf_ra2 = 0;
  reg[4:0] io_rf_wa = 0;
  reg[0:0] io_rf_wen = 0;
  reg[31:0] io_rf_wd = 0;
  wire[31:0] io_rf_rd1;
  wire[31:0] io_rf_rd2;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  RegFile RegFile(
    .clk(clk),
    .io_rf_ra1(io_rf_ra1),
    .io_rf_ra2(io_rf_ra2),
    .io_rf_wa(io_rf_wa),
    .io_rf_wen(io_rf_wen),
    .io_rf_wd(io_rf_wd),
    .io_rf_rd1(io_rf_rd1),
    .io_rf_rd2(io_rf_rd2));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_rf_ra1, io_rf_ra2, io_rf_wa, io_rf_wen, io_rf_wd);
    $init_outs(io_rf_rd1, io_rf_rd2);
    $init_sigs(RegFile);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, RegFile);
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
