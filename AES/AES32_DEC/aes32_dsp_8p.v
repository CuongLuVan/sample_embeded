
// Choose between XOR or DSP
`include "aes32_dsp_8p_func_dec.v"
`include "aes32_dsp_8p_fb_con.v"

module aes32_dsp_8p (
  input  wire          CLK,
  input  wire          RST,
  input  wire          START,
  input  wire  [31:00] DIN,
  input  wire  [31:00] KEY,

  output reg           DONE,
  output wire  [31:00] DOUT  // output is valid when HIGH
);

  // state machine parameters
  parameter S0=4'd0, S1=4'd1, S2=4'd2, S3=4'd3, S4=4'd4, S5=4'd5, S6=4'd6, S7=4'd7, S8=4'd8, S9=4'd9;

  // inpup registers
  //reg    [31:00] din_reg, key_reg;
  //reg            start_reg;

  reg    [05:00] count_rnd;    // count AES rounds
  reg    [03:00] count_ptext;  // used for delay at plaintext input
  reg    [03:00] sm_state;     // state machine register
  reg    [01:00] aes_mux_sel;  // select column to load feedback
  reg    [03:00] bram_ctrl;    // select (BRAM address bits): T0(LOW) or T2(HIGH) [1 bit per column] 
  reg    [03:00] last;         // select (BRAM address bit): Tn or T'n [1 bit per column] 
  reg    [03:00] tshift;       // select mux: Tn(LOW) or Tn+1(HIGH) [1 bit per column]
  reg    [02:00] zero_nbram;   // select mux: 0's(HIGH) or BRAM-shift(LOW) [for columns 1-3]
  reg            ptext_nbram;  // select mux: plaintext(HIGH) or BRAM(LOW)
 
  wire   [31:00] aes_din;
  wire   [31:00] aes_dout;

  // prevent output of intermediate round data
  assign DOUT = DONE ? aes_dout : 32'd0;
  
  // feedback controler
  aes32_dsp_8p_fb_con fbc_0 (.CLK  (CLK        ),  
                             .CTRL (aes_mux_sel),  // 2
                             .DIN  (aes_dout   ),  // 32
                 
                             .DOUT (aes_din    )); // 32
  
  // AES main function
  aes32_dsp_8p_func_dec f_0 (.CLK   (CLK              ),
                         .RST   (RST              ),
                         .KEY   (KEY          ),  // 32
                         .DIN   (aes_din          ),  // 32
			 .PTX   (DIN         ),  // 32
                         .BCT   ({bram_ctrl, last}),  // 8
                         .TSH   (tshift           ),  // 4
			 .POB   (ptext_nbram      ),
                         .RXR   (zero_nbram       ),  // 3
                   
                         .DOUT  (aes_dout         )); // 32

  // Note that some of the control logic is verbose, and can be *written* more compactly 
  // (like "aes_mux_sel", for example). I have written it the way it is below for clarity; 
  // it should not affect performance since the synthesizer will optimize it.
  always @(posedge CLK) begin
    if (RST) begin
      count_rnd    <= 1'b0;
	  count_ptext  <= 0;
      sm_state     <= S0;
	  ptext_nbram  <= 1'b1;
      aes_mux_sel  <= 2'b00;
      bram_ctrl    <= 4'b0101;
      tshift       <= 4'b0101;
      last         <= 4'b0000;
      zero_nbram   <= 3'b111;
      DONE         <= 1'b0;
    end else begin
      last[2:0]       <= last[3:1];       // select last round 
      zero_nbram[1:0] <= zero_nbram[2:1]; // select 0's for XOR input
    
      case (sm_state)
        S0  :  begin
                 aes_mux_sel    <= 2'b00;
                 tshift         <= 4'b0101;
                 bram_ctrl      <= 4'b0000;
				 ptext_nbram    <= 1'b1;

                 if (START) sm_state     <= S1;
                 else           sm_state     <= S0;
               end

        S1  :  begin
		 // wait to align plaintext input after it has gone through DSPs
		 if (count_ptext == 4'd4) sm_state    <= S2;
		 else   		  count_ptext <= count_ptext + 1;
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
		 ptext_nbram    <= 1'b0;  // stop plaintext input
                 aes_mux_sel    <= aes_mux_sel + 1;
		 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b1111;
                 sm_state       <= S5;
               end

        S5  :  begin
                 zero_nbram[2]  <= 1'b0;  // allow BRAM output to be XOR'd	
       		 aes_mux_sel    <= aes_mux_sel + 1;
		 bram_ctrl      <= 4'b0101;
                 tshift         <= 4'b0000;
                 sm_state       <= S6;
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
                 count_rnd      <= count_rnd + 1; // increment round count_rnder

                 if (count_rnd == 4'd8)  last[3] <= 1'b1; // last round control
                 if (count_rnd == 4'd9)  DONE <= 1;       // DONE high for 8 cycles of output
                 else  			 DONE <= 0;

                 sm_state       <= S2;
               end

        default : begin
                    sm_state <= S0;
                  end
      endcase
    end
  end

endmodule
