module test;
  reg[2:0] io_pc_sel = 0;
  reg[31:0] io_pc_pc4 = 0;
  reg[31:0] io_pc_jalr = 0;
  reg[31:0] io_pc_br = 0;
  reg[31:0] io_pc_jmp = 0;
  reg[31:0] io_pc_excp = 0;
  wire[31:0] io_pc_out;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  MuxPC MuxPC(
    .io_pc_sel(io_pc_sel),
    .io_pc_pc4(io_pc_pc4),
    .io_pc_jalr(io_pc_jalr),
    .io_pc_br(io_pc_br),
    .io_pc_jmp(io_pc_jmp),
    .io_pc_excp(io_pc_excp),
    .io_pc_out(io_pc_out));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_pc_sel, io_pc_pc4, io_pc_jalr, io_pc_br, io_pc_jmp, io_pc_excp);
    $init_outs(io_pc_out);
    $init_sigs(MuxPC);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, MuxPC);
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
