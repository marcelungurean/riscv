module test;
  reg[9:0] io_addr = 0;
  reg[31:0] io_wr_data = 0;
  reg[1:0] io_mem_func = 0;
  reg[0:0] io_mem_en = 0;
  wire[31:0] io_rd_data;
  reg clk = 0;
  integer clk_len;
  always #clk_len clk = ~clk;
  reg vcdon = 0;
  reg [1023:0] vcdfile = 0;
  reg [1023:0] vpdfile = 0;

  /*** DUT instantiation ***/
  DataMem DataMem(
    .clk(clk),
    .io_addr(io_addr),
    .io_wr_data(io_wr_data),
    .io_mem_func(io_mem_func),
    .io_mem_en(io_mem_en),
    .io_rd_data(io_rd_data));

  initial begin
    clk_len = `CLOCK_PERIOD;
    $init_clks(clk_len);
    $init_rsts();
    $init_ins(io_addr, io_wr_data, io_mem_func, io_mem_en);
    $init_outs(io_rd_data);
    $init_sigs(DataMem);
    /*** VCD & VPD dump ***/
    if ($value$plusargs("vcdfile=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, DataMem);
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
