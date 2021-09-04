`timescale 1 ps / 1 ps

module aes128_dsp_fb_con (
  input           CLK,
  input  [127:00] DIN, // plaintext
  
  output [127:00] DOUT  // this is the input to {c0,c1,c2,c3}
);
  
  // input 8-bit shift registers; 1 for c1, 2 for c2, 3 for c3 (non for c0)
  reg    [07:00]  e0_c1, e1_c1, e2_c1, e3_c1;
  reg    [15:00]  e0_c2, e1_c2, e2_c2, e3_c2; 
  reg    [23:00]  e0_c3, e1_c3, e2_c3, e3_c3;
  
  // for simulation
  initial begin
    e0_c1 = 0; e1_c1 = 0; e2_c1 = 0; e3_c1 = 0;
    e0_c2 = 0; e1_c2 = 0; e2_c2 = 0; e3_c2 = 0;
    e0_c3 = 0; e1_c3 = 0; e2_c3 = 0; e3_c3 = 0;   
  end
  
  always @(posedge CLK) begin
    e0_c1 <= DIN[87:80];
    e1_c1 <= DIN[55:48];
    e2_c1 <= DIN[23:16];
    e3_c1 <= DIN[119:112];
    
    e0_c2 <= {e0_c2[07:00],DIN[47:40]  };
    e1_c2 <= {e1_c2[07:00],DIN[15:08]  };
    e2_c2 <= {e2_c2[07:00],DIN[111:104]};
    e3_c2 <= {e3_c2[07:00],DIN[79:72]  };
    
    e0_c3 <= {e0_c3[15:00],DIN[07:00]  };
    e1_c3 <= {e1_c3[15:00],DIN[103:96] };
    e2_c3 <= {e2_c3[15:00],DIN[71:64]  };
    e3_c3 <= {e3_c3[15:00],DIN[39:32]  };  
  end

  assign DOUT[127:96] = {DIN[127:120], e0_c1[07:00], e0_c2[15:08], e0_c3[23:16]};
  assign DOUT[095:64] = {DIN[95:88],   e1_c1[07:00], e1_c2[15:08], e1_c3[23:16]};
  assign DOUT[063:32] = {DIN[63:56],   e2_c1[07:00], e2_c2[15:08], e2_c3[23:16]};
  assign DOUT[031:00] = {DIN[31:24],   e3_c1[07:00], e3_c2[15:08], e3_c3[23:16]};  

endmodule

