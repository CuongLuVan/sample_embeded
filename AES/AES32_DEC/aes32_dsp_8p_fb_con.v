
module aes32_dsp_8p_fb_con (
  input  wire         CLK,
  input  wire [31:00] DIN,  // feedback input
  input  wire [01:00] CTRL, // column control
  
  output wire [31:00] DOUT
);
  
  reg    [23:00] c0,c1,c2,c3;

  wire   [07:00] c0_out, c0_1, c0_2;
  wire   [07:00] c1_out, c1_1, c1_2;
  wire   [07:00] c2_out, c2_1, c2_2;
  wire   [07:00] c3_out, c3_1, c3_2;

  assign DOUT = {c0_out, c1_out, c2_out, c3_out};

  // assign data into column shift registers according to CTRL[1:0]
  assign c0_out = (CTRL[1:0] == 2'b00) ? DIN[31:24] : c0[07:00];
  assign c0_1   = (CTRL[1:0] == 2'b00) ? DIN[07:00] : c0[15:08];
  assign c0_2   = (CTRL[1:0] == 2'b00) ? DIN[15:08] : c0[23:16];

  assign c1_out = (CTRL[1:0] == 2'b01) ? DIN[23:16] : c1[07:00];
  assign c1_1   = (CTRL[1:0] == 2'b01) ? DIN[31:24] : c1[15:08];
  assign c1_2   = (CTRL[1:0] == 2'b01) ? DIN[07:00] : c1[23:16];

  assign c2_out = (CTRL[1:0] == 2'b10) ? DIN[15:08] : c2[07:00];
  assign c2_1   = (CTRL[1:0] == 2'b10) ? DIN[23:16] : c2[15:08];
  assign c2_2   = (CTRL[1:0] == 2'b10) ? DIN[31:24] : c2[23:16];
  
  assign c3_out = (CTRL[1:0] == 2'b11) ? DIN[07:00] : c3[07:00];
  assign c3_1   = (CTRL[1:0] == 2'b11) ? DIN[15:08] : c3[15:08];
  assign c3_2   = (CTRL[1:0] == 2'b11) ? DIN[23:16] : c3[23:16];

  always @(posedge CLK) begin
    c0 <= {DIN[23:16], c0_2, c0_1};
    c1 <= {DIN[15:08], c1_2, c1_1};
    c2 <= {DIN[07:00], c2_2, c2_1};
    c3 <= {DIN[31:24], c3_2, c3_1};
  end
  
endmodule
