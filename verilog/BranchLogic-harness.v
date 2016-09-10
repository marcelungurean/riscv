module test;
  reg[0:0] io_excp = 0;
  reg[3:0] io_ctl_br_type = 0;
  reg[0:0] io_br_eq = 0;
  reg[0:0] io_br_lt = 0;
  reg[0:0] io_br_ltu = 0;
  wire[2:0] io_pc_sel;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  BranchLogic BranchLogic(
    .io_excp(io_excp),
    .io_ctl_br_type(io_ctl_br_type),
    .io_br_eq(io_br_eq),
    .io_br_lt(io_br_lt),
    .io_br_ltu(io_br_ltu),
    .io_pc_sel(io_pc_sel));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_excp, io_ctl_br_type, io_br_eq, io_br_lt, io_br_ltu);
    $init_outs(io_pc_sel);
    $init_sigs(BranchLogic);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, BranchLogic);
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
