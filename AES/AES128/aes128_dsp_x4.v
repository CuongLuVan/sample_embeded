`include "aes128_dsp.v"

module aes128_dsp_x4 (

  input  wire          CLK,
  input  wire          RST,
  input  wire          START,
  input  wire [127:00] DIN,
  input  wire [127:00] KEY,
  
  output wire          DONE,
  output wire [127:00] DOUT

);

  wire  [127:00] dout_ar0, dout_ar1, dout_ar2;
 
  aes128_dsp ar0 (.CLK(CLK), .RST(RST), .START(START),    .DIN(DIN),      .KEY(KEY), .DONE(done_ar0), .DOUT(dout_ar0));
  aes128_dsp ar1 (.CLK(CLK), .RST(RST), .START(done_ar0), .DIN(dout_ar0), .KEY(KEY), .DONE(done_ar1), .DOUT(dout_ar1));
  aes128_dsp ar2 (.CLK(CLK), .RST(RST), .START(done_ar1), .DIN(dout_ar1), .KEY(KEY), .DONE(done_ar2), .DOUT(dout_ar2));
  aes128_dsp ar3 (.CLK(CLK), .RST(RST), .START(done_ar2), .DIN(dout_ar2), .KEY(KEY), .DONE(DONE    ), .DOUT(DOUT    ));

endmodule

