`timescale 1 ps / 1 ps

// choose DSP or logic for XOR function
`include "aes128_dsp_func.v"
//`include "aes128_xor_func.v"
`include "aes128_dsp_fb_con.v"

module aes128_dsp (
  input  wire          CLK,
  input  wire          RST,
  input  wire          START,
  input  wire [127:00] DIN,
  input  wire [127:00] KEY,
  
  output reg           DONE,
  output wire [127:00] DOUT
);

  reg    [06:00]  count;
  reg    [03:00]  last;
  reg    [02:00]  zero_nbram;
  reg             ptx_ctrl;

  wire   [127:00] aes_din;
  wire   [127:00] aes_dout;

  // DONE is asserted for ALL 8 inuts regardless if they has valid inputs associated with them!
  assign DOUT = DONE ? aes_dout : 128'd0;
 
  aes128_dsp_fb_con perm_0 (.CLK(CLK     ), 
	   		    .DIN(aes_dout),  // 32
		  	    .DOUT(aes_din)); // 32

  // change _dsp_ to _xor_ for the following four intantiations for 32-bit XOR in logic
  aes128_dsp_func func_0 (.CLK(CLK              ), 
			  .KEY(KEY[127:96]      ),  // 32
			  .DIN(aes_din[127:96]  ),  // 32
			  .PTX(DIN[127:96]      ),  // 32
			  .POB(ptx_ctrl         ), 
			  .RXR(zero_nbram       ),  // 3
			  .BCT(last             ),  // 4
			  .DOUT(aes_dout[127:96])); // 32
						 
  aes128_dsp_func func_1 (.CLK(CLK              ), 
			  .KEY(KEY[95:64]       ), 
			  .DIN(aes_din[095:64]  ),
			  .PTX(DIN[095:64]      ),
			  .POB(ptx_ctrl         ), 
			  .RXR(zero_nbram       ),	
			  .BCT(last             ), 
			  .DOUT(aes_dout[95:64] ));
						 
  aes128_dsp_func func_2 (.CLK(CLK              ), 
			  .KEY(KEY[63:32]       ), 
			  .DIN(aes_din[063:32]  ), 
			  .PTX(DIN[063:32]      ),  
			  .POB(ptx_ctrl         ),
                          .RXR(zero_nbram       ),							 
			  .BCT(last             ), 
			  .DOUT(aes_dout[63:32] ));
						 
  aes128_dsp_func func_3 (.CLK(CLK              ), 
			  .KEY(KEY[31:00]       ), 
			  .DIN(aes_din[031:00]  ), 
			  .PTX(DIN[031:00]      ), 
			  .POB(ptx_ctrl         ),
                          .RXR(zero_nbram       ),						 
			  .BCT(last             ), 
			  .DOUT(aes_dout[31:00] ));
 
  always @(posedge CLK) begin
    if (RST | ~START) begin
      count        <= 0;
      ptx_ctrl     <= 1;
      zero_nbram   <= 3'b111;
      last         <= 4'b0000;
      DONE         <= 8'd0;
    end else begin
      zero_nbram[1:0] <= zero_nbram[2:1];
      last[2:0]       <= last[3:1];  // shift register for last round control
      
      if (START)  count <= count + 1;
      
      case (count)
        7'd8  : ptx_ctrl      <= 0;  // switch to feedback input after first round
        7'd9  : zero_nbram[2] <= 1'b0;
	7'd78 : last[3]       <= 1'b1;  // last round
        7'd86 : DONE <= 1;
	7'd94 : DONE <= 0;
      endcase
    end
  end

endmodule    