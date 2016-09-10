module test;
  reg[31:0] io_instr = 0;
  wire[31:0] io_immi_sxt;
  wire[31:0] io_imms_sxt;
  wire[31:0] io_immb_sxt;
  wire[31:0] io_immu_sxt;
  wire[31:0] io_immj_sxt;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  ImmGen ImmGen(
    .io_instr(io_instr),
    .io_immi_sxt(io_immi_sxt),
    .io_imms_sxt(io_imms_sxt),
    .io_immb_sxt(io_immb_sxt),
    .io_immu_sxt(io_immu_sxt),
    .io_immj_sxt(io_immj_sxt));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_instr);
    $init_outs(io_immi_sxt, io_imms_sxt, io_immb_sxt, io_immu_sxt, io_immj_sxt);
    $init_sigs(ImmGen);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, ImmGen);
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
