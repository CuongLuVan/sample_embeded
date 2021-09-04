
`timescale 1 ps / 1 ps

`define T 2000
// this factor accounts for input delays. Set to 0 for behavioral simulation
`define D 0

module aes32_dsp_cmac_tb;
  reg           CLK;
  reg           RST;
  reg           START;
  reg  [31:00]  DIN; 
  reg  [31:00]  KEY;
  reg  [15:00]  MSG;
  
  reg           GSR;
  reg  [127:00] SK[00:11];
  
  reg  [127:00] exp1;
  reg  [127:00] exp2;
  
  wire          DONE;
  wire [31:00]  DOUT;

  integer       errors;
  integer       i;  
  
  // test vectors taken from NIST Special Publication 800-38B
  // http://csrc.nist.gov/publications/nistpubs/800-38B/SP_800-38B.pdf
  
  // inputs
  parameter PT0    = 128'h6BC1BEE2_2E409F96_E93D7E11_7393172A; 
  parameter PT1    = 128'hAE2D8A57_1E03AC9C_9EB76FAC_45AF8E51;
  parameter PT2    = 128'h30C81C46_A35CE411_e5fbc119_1a0a52ef;
  parameter PT2i   = 128'h30C81C46_A35CE411_80000000_00000000; // partial block, padded with 80...
  parameter PT3    = 128'hf69f2445_df4f9b17_ad2b417b_e66c3710;
      
  // CMAC K1  (complete M) and K2 (partial M)  derived from main key
  parameter K1     = 128'hfbeed618_35713366_7c85e08f_7236a8de;
  parameter K2     = 128'hf7ddac30_6ae266cc_f90bc11e_e46d513b;

  // extected ciphertexts
  parameter CT_EMP = 128'h80000000_00000000_00000000_00000000;
  parameter CT_0   = 128'hBB1D6929_E9593728_7FA37D12_9B756746;
  parameter CT_128 = 128'h070A16B4_6B4D4144_F79BDD9D_D04A287C;
  parameter CT_320 = 128'hDFA66747_DE9AE630_30CA3261_1497C827;
  parameter CT_512 = 128'h51F0BEBF_7E3B9D92_FC497417_79363CFE;

  // check simulated vs expected value and display result
  task simcheck;
    input [31:00] sim, exp;
  begin
    if (sim !== exp) begin
      errors = errors + 1;
      $display("FAIL: Simulated value = %h, expected value = %h, errors = %d, at time %d", sim, exp, errors, $time);
    end else
      $display("Pass: Simulated value = %h, expected value = %h, errors = %d, at time %d", sim, exp, errors, $time);	
  end
  endtask

  // display input vector and expected output
  task dispinout;
    input [127:00] inp1, inp2, exp1, exp2, MSG;
  begin
    $display("---------------------------------------------------------------------------------------------------------------"); 
    $display("Input stream 1: %h; Expected output: %h; MSG = %3d", inp1, exp1, MSG);
    $display("Input stream 2: %h; Expected output: %h; MSG = %3d", inp2, exp2, MSG);
    $display("---------------------------------------------------------------------------------------------------------------");
  end
  endtask

  // input data in 4 32 bit words
  task datain;
    input [127:00] key_in;
    input [127:00] data_in;
	begin
	  #`T    DIN = data_in[127:96]; 
	         KEY = key_in[127:96]; 
	  #`T    DIN = data_in[95:64];
	         KEY = key_in[95:64];
	  #`T    DIN = data_in[63:32];
	         KEY = key_in[63:32];
	  #`T    DIN = data_in[31:00];
	         KEY = key_in[31:00];
    end
  endtask 

  // global reset between invocations of AES
  task globres;
  begin
    #(10*`T) RST = 1;
	     START = 0;
    #(50*`T) RST  = 0;
             KEY = 32'h00000000;
             DIN = 32'h00000000;
    #(10*`T);   
  end
  endtask

  aes32_dsp_cmac uut (.CLK  (CLK  ), 
                      .RST  (RST  ), 
                      .START(START), 
                      .DIN  (DIN  ), 
                      .KEY  (KEY  ),
                      .MSG  (MSG  ),					  

                      .DOUT (DOUT ),
  		      .DONE (DONE ));
               
  // global reset
  assign glbl.GSR = GSR;
  initial 
  begin
    GSR = 1;
    #(5*`T) GSR = 0;
  end

  // generate clock
  initial begin
    CLK = 1;
    forever #(`T/2) CLK = ~CLK;
  end
 
  // initial state for inputs
  initial begin
    RST    = 1;
    DIN    = 0;
    KEY    = 0;
    MSG    = 16'd0;
    START  = 0;
    errors = 0;
    i      = 0;
  end

  initial begin
    SK[0]  = 128'h2B7E1516_28AED2A6_ABF71588_09CF4F3C;
    SK[1]  = 128'hA0FAFE17_88542CB1_23A33939_2A6C7605;    
    SK[2]  = 128'hF2C295F2_7A96B943_5935807A_7359F67F;
    SK[3]  = 128'h3D80477D_4716FE3E_1E237E44_6D7A883B;   
    SK[4]  = 128'hEF44A541_A8525B7F_B671253B_DB0BAD00;  
    SK[5]  = 128'hD4D1C6F8_7C839D87_CAF2B8BC_11F915BC;
    SK[6]  = 128'h6D88A37A_110B3EFD_DBF98641_CA0093FD;  
    SK[7]  = 128'h4E54F70E_5F5FC9F3_84A64FB2_4EA6DC4F;
    SK[8]  = 128'hEAD27321_B58DBAD2_312BF560_7F8D292F;      
    SK[9]  = 128'hAC7766F3_19FADC21_28D12941_575C006E;      
    SK[10] = 128'hD014F9A8_C9EE2589_E13F0CC8_B6630CA6;  
  end


  initial begin
     // test  0 (empty string)
    #`T      globres();
    #`T      MSG   = 16'd1;
    #`T      exp1  = CT_0;
	     exp2  = CT_0;
    dispinout(CT_EMP, CT_EMP, exp1, exp2, MSG);
    #(`T-`D) START = 1;
    #`T      datain(K2,CT_EMP);
             datain(K2,CT_EMP);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end

     // test  128
    #`T      globres(); i = 0;
    #`T      MSG  = 16'd1;
    #`T      exp1 = CT_128;
	     exp2 = CT_128;
             dispinout(PT0, PT0, exp1, exp2, MSG);
    #`T      START = 1;
    #`T      datain(K1,PT0);
             datain(K1,PT0);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end 

    // test 320 (incomplete M)
    #`T      globres(); i = 1;
    #`T      MSG   = 16'd3;
    #`T      exp1 = CT_320;
             exp2 = CT_320;
    $display("---------------------------------------------------------------------------------------------------------------"); 
    $display("Message 1:\n%h\n%h\n%h\nExpected output: %h; MSG = %3d", PT0, PT1, PT2i, exp1, MSG);
    $display("Message 2:\n%h\n%h\n%h\nExpected output: %h; MSG = %3d", PT0, PT1, PT2i, exp1, MSG);
    $display("---------------------------------------------------------------------------------------------------------------");
    #`T      START = 1;
    #`T      datain(SK[0],PT0);
             datain(SK[0],PT0);
             repeat (10) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
             i = 0;
             datain(128'd0,PT1);
             datain(128'd0,PT1);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
             i = 0;
             datain(128'd0,PT2i);
             datain(128'd0,PT2i);
             datain(K2,128'd0);
             datain(K2,128'd0);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end

    // test 512
    #`T      globres(); i = 1;
    #`T      MSG   = 16'd4;
    #`T      exp1 = CT_512;
	     exp2 = CT_512;
    $display("---------------------------------------------------------------------------------------------------------------"); 
    $display("Message 1:\n%h\n%h\n%h\n%h\nExpected output: %h; MSG = %3d", PT0, PT1, PT2, PT3, exp1, MSG);
    $display("Message 2:\n%h\n%h\n%h\n%h\nExpected output: %h; MSG = %3d", PT0, PT1, PT2, PT3, exp1, MSG);
    $display("---------------------------------------------------------------------------------------------------------------");
    #`T      START = 1;
    #`T      datain(SK[0],PT0);
             datain(SK[0],PT0);
             repeat (10) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
             i = 0;
             datain(128'd0,PT1);
             datain(128'd0,PT1);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
             i = 0;
             datain(128'd0,PT2);
             datain(128'd0,PT2);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
             i = 0;
	     datain(128'd0,PT3);
             datain(128'd0,PT3);
             datain(K1,128'd0);
             datain(K1,128'd0);
             repeat (11) begin
               datain(SK[i],128'd0);
	       datain(SK[i],128'd0);
               i = i + 1;
             end
    #`T      globres();
  $display ("\nERRORS: %d", errors);  // display total number of errors 
  end

  // output is valid when DONE is high; these calls check if it is as expected. 
  initial begin
    forever begin
      @(posedge DONE) begin
        #`T      simcheck(DOUT, exp1[127:96]);
	#`T      simcheck(DOUT, exp1[95:64]);	         
	#`T      simcheck(DOUT, exp1[63:32]);
        #`T      simcheck(DOUT, exp1[31:00]);
	#`T      simcheck(DOUT, exp2[127:96]);
	#`T      simcheck(DOUT, exp2[95:64]);	         
        #`T      simcheck(DOUT, exp2[63:32]);
        #`T      simcheck(DOUT, exp2[31:00]);
      end	
    end
  end	

endmodule			 





