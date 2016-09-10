module test;
  reg[1:0] io_opb_sel = 0;
  reg[31:0] io_opb_rsb = 0;
  reg[31:0] io_opb_imi = 0;
  reg[31:0] io_opb_ims = 0;
  reg[31:0] io_opb_pc = 0;
  wire[31:0] io_opb_alu_in;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  MuxOpB MuxOpB(
    .io_opb_sel(io_opb_sel),
    .io_opb_rsb(io_opb_rsb),
    .io_opb_imi(io_opb_imi),
    .io_opb_ims(io_opb_ims),
    .io_opb_pc(io_opb_pc),
    .io_opb_alu_in(io_opb_alu_in));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_opb_sel, io_opb_rsb, io_opb_imi, io_opb_ims, io_opb_pc);
    $init_outs(io_opb_alu_in);
    $init_sigs(MuxOpB);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, MuxOpB);
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
