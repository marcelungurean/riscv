module test;
  reg[1:0] io_opa_sel = 0;
  reg[31:0] io_opa_rsa = 0;
  reg[31:0] io_opa_imz = 0;
  reg[31:0] io_opa_imu = 0;
  wire[31:0] io_opa_alu_in;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  MuxOpA MuxOpA(
    .io_opa_sel(io_opa_sel),
    .io_opa_rsa(io_opa_rsa),
    .io_opa_imz(io_opa_imz),
    .io_opa_imu(io_opa_imu),
    .io_opa_alu_in(io_opa_alu_in));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_opa_sel, io_opa_rsa, io_opa_imz, io_opa_imu);
    $init_outs(io_opa_alu_in);
    $init_sigs(MuxOpA);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, MuxOpA);
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
