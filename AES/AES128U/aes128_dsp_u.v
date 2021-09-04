
// choose file for in order to use DSP or logic XOR
`include "aes128_dsp_u_func.v"
//`include "aes128_xor_u_func.v"
`include "aes128_dsp_u_perm.v"

module aes128_dsp_u (
  input  wire          CLK,
  input  wire          RST,
  input  wire          START,
  input  wire [127:00] DIN,
         
  output wire [127:00] DOUT,
  output wire          DONE
);

  parameter K   = 128'h00000000000000000000000000000000;
  parameter K0  = 128'h62636363626363636263636362636363;
  parameter K1  = 128'h9B9898C9F9FBFBAA9B9898C9F9FBFBAA;
  parameter K2  = 128'h90973450696CCFFAF2F457330B0FAC99;
  parameter K3  = 128'hEE06DA7B876A1581759E42B27E91EE2B;
  parameter K4  = 128'h7F2E2B88F8443E098DDA7CBBF34B9290;
  parameter K5  = 128'hEC614B851425758C99FF09376AB49BA7;
  parameter K6  = 128'h217517873550620BACAF6B3CC61BF09B;
  parameter K7  = 128'h0EF903333BA9613897060A04511DFA9F;
  parameter K8  = 128'hB1D4D8E28A7DB9DA1D7BB3DE4C664941;
  parameter K9  = 128'hB4EF5BCB3E92E21123E951CF6F8F188E;  
  
  reg    [127:00] aes_din;
  reg    [070:00] done_delay;

  wire   [127:00] r0_dout, r1_dout, r2_dout, r3_dout, r4_dout, r5_dout, r6_dout, r7_dout, r8_dout, r9_dout;  
  wire   [127:00] r0_din, r1_din, r2_din, r3_din, r4_din, r5_din, r6_din, r7_din, r8_din, r9_din;  

  assign DOUT = DONE ? r9_dout : 128'd0;
  assign DONE = done_delay[70];
  
  // initial XOR of main key and plaintext
  always @(posedge CLK) begin
    if (RST) aes_din <= 0;
    else     aes_din <= DIN[127:00] ^ K[127:00];
  end

  always @(posedge CLK) begin
    if (RST) done_delay <= 0;
	else   	 done_delay[70:00] <= {done_delay[70:00], START};
  end

  // to use LUT-based XOR instead of DSPs, use  "aes128_xor_u_func" instead of "aes128_xor_u_func"
  
  // round 0
  aes128_dsp_u_perm perm_0 (.CLK(CLK), .DIN(aes_din), .DOUT(r0_din));
  aes128_dsp_u_func func_r0_0 (.CLK(CLK), .KEY(K0[127:096]), .DIN(r0_din[127:96]), .BCT(4'd0), .DOUT(r0_dout[127:096]));
  aes128_dsp_u_func func_r0_1 (.CLK(CLK), .KEY(K0[095:064]), .DIN(r0_din[95:64] ), .BCT(4'd0), .DOUT(r0_dout[095:064]));
  aes128_dsp_u_func func_r0_2 (.CLK(CLK), .KEY(K0[063:032]), .DIN(r0_din[63:32] ), .BCT(4'd0), .DOUT(r0_dout[063:032]));
  aes128_dsp_u_func func_r0_3 (.CLK(CLK), .KEY(K0[031:000]), .DIN(r0_din[31:00] ), .BCT(4'd0), .DOUT(r0_dout[031:000]));

  // round 1  
  aes128_dsp_u_perm perm_1 (.CLK(CLK), .DIN(r0_dout), .DOUT(r1_din));
  aes128_dsp_u_func func_r1_0 (.CLK(CLK), .KEY(K1[127:096]), .DIN(r1_din[127:96]), .BCT(4'd0), .DOUT(r1_dout[127:096]));
  aes128_dsp_u_func func_r1_1 (.CLK(CLK), .KEY(K1[095:064]), .DIN(r1_din[95:64] ), .BCT(4'd0), .DOUT(r1_dout[095:064]));
  aes128_dsp_u_func func_r1_2 (.CLK(CLK), .KEY(K1[063:032]), .DIN(r1_din[63:32] ), .BCT(4'd0), .DOUT(r1_dout[063:032]));
  aes128_dsp_u_func func_r1_3 (.CLK(CLK), .KEY(K1[031:000]), .DIN(r1_din[31:00] ), .BCT(4'd0), .DOUT(r1_dout[031:000]));

  // round 2  
  aes128_dsp_u_perm perm_2 (.CLK(CLK), .DIN(r1_dout), .DOUT(r2_din));
  aes128_dsp_u_func func_r2_0 (.CLK(CLK), .KEY(K2[127:096]), .DIN(r2_din[127:96]), .BCT(4'd0), .DOUT(r2_dout[127:096]));
  aes128_dsp_u_func func_r2_1 (.CLK(CLK), .KEY(K2[095:064]), .DIN(r2_din[95:64] ), .BCT(4'd0), .DOUT(r2_dout[095:064]));
  aes128_dsp_u_func func_r2_2 (.CLK(CLK), .KEY(K2[063:032]), .DIN(r2_din[63:32] ), .BCT(4'd0), .DOUT(r2_dout[063:032]));
  aes128_dsp_u_func func_r2_3 (.CLK(CLK), .KEY(K2[031:000]), .DIN(r2_din[31:00] ), .BCT(4'd0), .DOUT(r2_dout[031:000]));

  // round 3  
  aes128_dsp_u_perm perm_3 (.CLK(CLK), .DIN(r2_dout), .DOUT(r3_din));
  aes128_dsp_u_func func_r3_0 (.CLK(CLK), .KEY(K3[127:096]), .DIN(r3_din[127:96]), .BCT(4'd0), .DOUT(r3_dout[127:096]));
  aes128_dsp_u_func func_r3_1 (.CLK(CLK), .KEY(K3[095:064]), .DIN(r3_din[95:64] ), .BCT(4'd0), .DOUT(r3_dout[095:064]));
  aes128_dsp_u_func func_r3_2 (.CLK(CLK), .KEY(K3[063:032]), .DIN(r3_din[63:32] ), .BCT(4'd0), .DOUT(r3_dout[063:032]));
  aes128_dsp_u_func func_r3_3 (.CLK(CLK), .KEY(K3[031:000]), .DIN(r3_din[31:00] ), .BCT(4'd0), .DOUT(r3_dout[031:000]));
  
  // round 4  
  aes128_dsp_u_perm perm_4 (.CLK(CLK), .DIN(r3_dout), .DOUT(r4_din));
  aes128_dsp_u_func func_r4_0 (.CLK(CLK), .KEY(K4[127:096]), .DIN(r4_din[127:96]), .BCT(4'd0), .DOUT(r4_dout[127:096]));
  aes128_dsp_u_func func_r4_1 (.CLK(CLK), .KEY(K4[095:064]), .DIN(r4_din[95:64] ), .BCT(4'd0), .DOUT(r4_dout[095:064]));
  aes128_dsp_u_func func_r4_2 (.CLK(CLK), .KEY(K4[063:032]), .DIN(r4_din[63:32] ), .BCT(4'd0), .DOUT(r4_dout[063:032]));
  aes128_dsp_u_func func_r4_3 (.CLK(CLK), .KEY(K4[031:000]), .DIN(r4_din[31:00] ), .BCT(4'd0), .DOUT(r4_dout[031:000]));

  // round 5  
  aes128_dsp_u_perm perm_5 (.CLK(CLK), .DIN(r4_dout), .DOUT(r5_din));
  aes128_dsp_u_func func_r5_0 (.CLK(CLK), .KEY(K5[127:096]), .DIN(r5_din[127:96]), .BCT(4'd0), .DOUT(r5_dout[127:096]));
  aes128_dsp_u_func func_r5_1 (.CLK(CLK), .KEY(K5[095:064]), .DIN(r5_din[95:64] ), .BCT(4'd0), .DOUT(r5_dout[095:064]));
  aes128_dsp_u_func func_r5_2 (.CLK(CLK), .KEY(K5[063:032]), .DIN(r5_din[63:32] ), .BCT(4'd0), .DOUT(r5_dout[063:032]));
  aes128_dsp_u_func func_r5_3 (.CLK(CLK), .KEY(K5[031:000]), .DIN(r5_din[31:00] ), .BCT(4'd0), .DOUT(r5_dout[031:000]));

  // round 6                                                                                                               
  aes128_dsp_u_perm perm_6 (.CLK(CLK), .DIN(r5_dout), .DOUT(r6_din));
  aes128_dsp_u_func func_r6_0 (.CLK(CLK), .KEY(K6[127:096]), .DIN(r6_din[127:96]), .BCT(4'd0), .DOUT(r6_dout[127:096])); 
  aes128_dsp_u_func func_r6_1 (.CLK(CLK), .KEY(K6[095:064]), .DIN(r6_din[95:64] ), .BCT(4'd0), .DOUT(r6_dout[095:064])); 
  aes128_dsp_u_func func_r6_2 (.CLK(CLK), .KEY(K6[063:032]), .DIN(r6_din[63:32] ), .BCT(4'd0), .DOUT(r6_dout[063:032])); 
  aes128_dsp_u_func func_r6_3 (.CLK(CLK), .KEY(K6[031:000]), .DIN(r6_din[31:00] ), .BCT(4'd0), .DOUT(r6_dout[031:000])); 

  // round 7                                                                                                              
  aes128_dsp_u_perm perm_7 (.CLK(CLK), .DIN(r6_dout), .DOUT(r7_din));
  aes128_dsp_u_func func_r7_0 (.CLK(CLK), .KEY(K7[127:096]), .DIN(r7_din[127:96]), .BCT(4'd0), .DOUT(r7_dout[127:096]));
  aes128_dsp_u_func func_r7_1 (.CLK(CLK), .KEY(K7[095:064]), .DIN(r7_din[95:64] ), .BCT(4'd0), .DOUT(r7_dout[095:064]));
  aes128_dsp_u_func func_r7_2 (.CLK(CLK), .KEY(K7[063:032]), .DIN(r7_din[63:32] ), .BCT(4'd0), .DOUT(r7_dout[063:032]));
  aes128_dsp_u_func func_r7_3 (.CLK(CLK), .KEY(K7[031:000]), .DIN(r7_din[31:00] ), .BCT(4'd0), .DOUT(r7_dout[031:000]));
                 
  // round 8                                                                                                                                
  aes128_dsp_u_perm perm_8 (.CLK(CLK), .DIN(r7_dout), .DOUT(r8_din));
  aes128_dsp_u_func func_r8_0 (.CLK(CLK), .KEY(K8[127:096]), .DIN(r8_din[127:96]), .BCT(4'd0), .DOUT(r8_dout[127:096])); 
  aes128_dsp_u_func func_r8_1 (.CLK(CLK), .KEY(K8[095:064]), .DIN(r8_din[95:64] ), .BCT(4'd0), .DOUT(r8_dout[095:064])); 
  aes128_dsp_u_func func_r8_2 (.CLK(CLK), .KEY(K8[063:032]), .DIN(r8_din[63:32] ), .BCT(4'd0), .DOUT(r8_dout[063:032])); 
  aes128_dsp_u_func func_r8_3 (.CLK(CLK), .KEY(K8[031:000]), .DIN(r8_din[31:00] ), .BCT(4'd0), .DOUT(r8_dout[031:000])); 

  // round 9: notice that for this round BCT=F to indicate that this is the final round                                                                                                                  
  aes128_dsp_u_perm perm_9 (.CLK(CLK), .DIN(r8_dout), .DOUT(r9_din));
  aes128_dsp_u_func func_r9_0 (.CLK(CLK), .KEY(K9[127:096]), .DIN(r9_din[127:96]), .BCT(4'hF), .DOUT(r9_dout[127:096]));  
  aes128_dsp_u_func func_r9_1 (.CLK(CLK), .KEY(K9[095:064]), .DIN(r9_din[95:64] ), .BCT(4'hF), .DOUT(r9_dout[095:064]));  
  aes128_dsp_u_func func_r9_2 (.CLK(CLK), .KEY(K9[063:032]), .DIN(r9_din[63:32] ), .BCT(4'hF), .DOUT(r9_dout[063:032]));  
  aes128_dsp_u_func func_r9_3 (.CLK(CLK), .KEY(K9[031:000]), .DIN(r9_din[31:00] ), .BCT(4'hF), .DOUT(r9_dout[031:000]));  

endmodule

    
    
    