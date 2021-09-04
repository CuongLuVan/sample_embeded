`timescale 1 ps / 1 ps

`include "aes32_dsp_cmac_func.v"
`include "aes32_dsp_cmac_fb_con.v"

module aes32_dsp_cmac (
  input               CLK,
  input               RST,
  input               START,
  input       [31:00] DIN, 
  input       [31:00] KEY,
  input       [15:00] MSG,   // the number of blocks to MAC
  
  output      [31:00] DOUT,
  output  reg         DONE
);

  // state machine constants
  parameter S0=4'd0, S1=4'd1, S2=4'd2, S3=4'd3, S4=4'd4, S5=4'd5, S6=4'd6, S7=4'd7, S8=4'd8, S9=4'd9;

  // input signal buffer for simulation timing
  reg    [31:00] din_reg, key_reg;
  reg            start_reg;

  reg    [31:00] dout0, dout1, dout2; // registers to store content during feedback
  reg    [03:00] count_rnd;           // count rounds
  reg    [03:00] count_msg;           // count message blocks
  reg    [02:00] count_ptext;         // count plaintext input for fist round
  reg    [03:00] sm_state;            // state machine register
  
  reg    [01:00] aes_mux_sel;         // controls which feedback registers are loaded
  reg    [03:00] bram_ctrl;           // control for T-table selection
  reg    [03:00] last;                // last round selection
  reg    [02:00] rst_ab;              // reset AB DSP input registers for propegation
  reg    [03:00] tshift;              // control for shifting output of BRAM
  reg            fback_nkey;          // chooses between feedback(H) or key(L) inputs
  reg            ptext_nbram;         // chooses between plaintext(H) input or bram(L) output
  reg            ptext_nfback;        // chooses between plaintext or feedback
 
  wire   [31:00] aes_din;             // input to the AES function
  wire   [31:00] aes_dout;            // output of the AES function
  wire   [31:00] aes_cin;             // carries feedback/key to C port of dspa0

  assign DOUT = DONE ? aes_dout : 32'd0;
  
  // the feedback controler
  aes32_dsp_cmac_fb_con fbc_0 (.CLK  (CLK          ), 
                               .CTRL (aes_mux_sel  ), 
                               .DIN  (aes_dout     ), 
                 
                               .DOUT (aes_din      ));

  // choose between plaintext input or key for C port of column 0
  assign aes_cin = fback_nkey ? dout2 : key_reg;
    
  // the basic function of the AES (quarter round) 
  aes32_dsp_cmac_func f_0 (.CLK   (CLK              ),
                           .RST   (RST              ),
                           .CIN   (aes_cin          ),  // input to C port of dsp0a
                           .DIN   (aes_din          ),  // input to A:B port of dsp0a 
                           .PTX   (din_reg          ),  // plaintext input
                           .BCT   ({bram_ctrl, last}),  // BRAM and last round control signals (address)
                           .TSH   (tshift           ),  // T-table shift control 
                           .POB   (ptext_nbram      ),  // choose plaintext or bram content
						   .RAB   (rst_ab           ),  // reset signals for A:B ports of DSP0b,1a,1b 
						   .FBK   (dout2            ),  // feedback input
						   .POF   (ptext_nfback     ),  // control plaintext (H) or feedbakc (L) 
               
                           .DOUT  (aes_dout         )); // output
                     
  always @(posedge CLK) begin
    din_reg   <= DIN;
	key_reg   <= KEY;
	start_reg <= START;
  end

  // Note that some of the control logic is verbose, and can be *written* more compactly 
  // (like "aes_mux_sel", for example). I have written it the way it is below for clarity; 
  // it should not affect performance since the synthesizer will optimize it.
  always @(posedge CLK)
  begin
    if (RST) 
    begin
      count_rnd    <= 0;
      count_ptext  <= 0;
      count_msg    <= 0;
      sm_state     <= S0;
      fback_nkey   <= 0;
      ptext_nbram  <= 1;
      ptext_nfback <= 1;
      aes_mux_sel  <= 2'b00;
      bram_ctrl    <= 4'b0101;
      tshift       <= 4'b0101;
      last         <= 4'b0000;
      rst_ab       <= 3'b111;
      DONE         <= 0;
    end  
    else
    begin

      // shift right last round control
      last[2:0]      <= last[3:1];
	  // shift right plaintext input control
	  rst_ab[1:0]    <= rst_ab[2:1];
	  // 32 bit shift register for storing output for feedback 
	  dout0 <= aes_dout;
	  dout1 <= dout0;
	  dout2 <= dout1;
		
      case (sm_state)
      
        S0  :  begin
		 if (MSG == 16'd1) count_rnd    <= 4'hF;
		 else              count_rnd    <= 4'h0;
                 aes_mux_sel    <= 2'b00;  
                 tshift         <= 4'b0101;
                 bram_ctrl      <= 4'b0101;
                 fback_nkey     <= 1'b0;
		 ptext_nbram    <= 1'b1;
                 if (start_reg == 1'b1) sm_state     <= S1;
                 else                   sm_state     <= S0;  
               end        
 
        S1  :  begin
		 if (count_ptext == 3'd5) begin // wait to align plaintext input after it has gone through DSPs
		   sm_state       <= S2;
		   count_ptext    <= 0;
    		  end else
		    count_ptext <= count_ptext + 4'd1;
    	       end
 
        S2  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b1010;
                 tshift         <= 4'b1111;
                 sm_state       <= S3;
               end

        S3  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b1010;
                 tshift         <= 4'b0000;
                 sm_state       <= S4;

               end

        S4  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b1111;
                 sm_state       <= S5;
					  
                 // plaintext input to first dsp48 for next invocation (a0)
                 if (count_rnd >= 4'hA) ptext_nbram    <= 1'b1;
		 else    		ptext_nbram    <= 1'b0;
					  
                 // pass plaintext and convert to key input to first dsp48 for next invocation (a0) 					  
		 if (count_rnd == 4'hA) begin 
		   fback_nkey     <= 1'b1;
		   ptext_nfback   <= 1'b1;
		 end else begin
  		   fback_nkey     <= 1'b0;
		   ptext_nfback   <= 1'b0;
		 end  
               end        

        S5  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b0000;
                 sm_state       <= S6;
					  
		 // control reset of A:B input registers so XORs from dsp0a can pass through
                 if (count_rnd >= 4'hA) rst_ab[2]      <= 1'b1;
		 else			rst_ab[2]      <= 1'b0;
					  
               end
                 
        S6  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b1010;
                 tshift         <= 4'b1111;
                 sm_state       <= S7;
               end  
               
        S7  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b1010;
                 tshift         <= 4'b0000;
                 sm_state       <= S8;
               end

        S8  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b1111;
                 sm_state       <= S9;
               end

        S9  :  begin
                 aes_mux_sel    <= aes_mux_sel + 1;
                 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b0000;
					  
		 if (count_rnd == 4'h8) last[3] <= 1;
		 else                   last[3] <= 0;					  
					  
		 // add an extra feedback pass before the last AES invocation
		 if (((count_rnd == 4'hB) & !(count_msg == MSG - 2)) | (count_rnd == 4'hC)) begin
  	           count_rnd    <= 0;
		   count_msg    <= count_msg + 1;
		 end else
		   count_rnd    <= count_rnd + 1;
 		 
                  if ((count_msg == MSG - 1) & (count_rnd == 4'h9)) DONE <= 1;
		  else                                              DONE <= 0;	  
				 
		  if (DONE) sm_state     <= S0;			   
		  else      sm_state     <= S2;	 
               end	  
					
        default : begin
                    sm_state <= S0;
                  end
      endcase
    end             
  end

endmodule
