module test;
  reg[31:0] io_a = 0;
  reg[31:0] io_b = 0;
  reg[3:0] io_op = 0;
  wire[31:0] io_out;
  wire[0:0] io_zero;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  Alu Alu(
    .io_a(io_a),
    .io_b(io_b),
    .io_op(io_op),
    .io_out(io_out),
    .io_zero(io_zero));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_a, io_b, io_op);
    $init_outs(io_out, io_zero);
    $init_sigs(Alu);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, Alu);
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
