
`timescale 1 ps / 1 ps

`define T 2000
// this factor accounts for input delays. Set to 0 for behavioral simulation
`define D 0
 
module aes32_dsp_8p_tb;
  reg          CLK;
  reg          RST;
  reg          START;
  reg  [31:00] DIN; 
  reg  [31:00] KEY;
  
  reg          GSR;
  
  reg  [127:00] CT[00:128];
  reg  [127:00] PT;
  reg  [127:00] exp1;
  reg  [127:00] exp2;
  
  wire         DONE;
  wire [31:00] DOUT;

  integer      errors;
  integer      i;
  
  // test vectors from Gladman:  
  // http://gladman.plushost.co.uk/oldsite/cryptography_technology/rijndael/index.php
  
  parameter PTD  = 128'h3925841d02dc09fbdc118597196a0b32;
  parameter KDx  = 128'hD014F9A8C9EE2589E13F0CC8B6630CA6;
  parameter KDx0 = 128'h0C7B5A631319EAFEB0398890664CFBB4;
  parameter KDx1 = 128'hDF7D925A1F62B09DA320626ED6757324;
  parameter KDx2 = 128'h12C07647C01F22C7BC42D2F37555114A;
  parameter KDx3 = 128'h6EFCD876D2DF54807C5DF034C917C3B9;
  parameter KDx4 = 128'h6EA30AFCBC238CF6AE82A4B4B54A338D;
  parameter KDx5 = 128'h90884413D280860A12A128421BC89739;
  parameter KDx6 = 128'h7C1F13F74208C219C021AE480969BF7B;
  parameter KDx7 = 128'hCC7505EB3E17D1EE82296C51C9481133;
  parameter KDx8 = 128'h2B3708A7F262D405BC3EBDBF4B617D62;
  parameter KDx9 = 128'h2B7E151628AED2A6ABF7158809CF4F3C;
  parameter CTD  = 128'h3243f6a8885a308d313198a2e0370734;

  parameter KD   = 128'hB4EF5BCB3E92E21123E951CF6F8F188E;
  parameter KD0  = 128'h5585820DEB1CEB880C01B4B2258D64EE;
  parameter KD1  = 128'h6AB6F2E9BE996985E71D5F3A298CD05C;
  parameter KD2  = 128'hEFEA4A8BD42F9B6C598436BFCE918F66;
  parameter KD3  = 128'h2AE50B873BC5D1E78DABADD39715B9D9;
  parameter KD4  = 128'hB5A91EF01120DA60B66E7C341ABE140A;
  parameter KD5  = 128'hC27D6492A489C490A74EA654ACD0683E;
  parameter KD6  = 128'h6EAD0CAC66F4A00203C762C40B9ECE6A;
  parameter KD7  = 128'h6533C2C60859ACAE6533C2C60859ACAE;
  parameter KD8  = 128'h6D6A6E686D6A6E686D6A6E686D6A6E68;
  parameter KD9  = 128'h00000000000000000000000000000000;

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
    input [127:00] inp1, inp2, exp1, exp2;
  begin
    $display("---------------------------------------------------------------------------------------------------------------"); 
    $display("Input stream 1: %h; Expected output: %h", inp1, exp1);
    $display("Input stream 2: %h; Expected output: %h", inp2, exp2);
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
	  #`T    DIN = data_in[31:00];
	         KEY = key_in[31:00];
	  #`T    DIN = data_in[63:32];
	         KEY = key_in[63:32];
	  #`T    DIN = data_in[95:64];
	         KEY = key_in[95:64];		 
    end
  endtask   

  // global reset between invocations of AES
  task globres;
  begin
    #(10*`T) RST   = 1;
	     START = 0;
    #(50*`T) RST   = 0;
             KEY   = 32'h00000000;
             DIN   = 32'h00000000;
    #(10*`T);   
    end
  endtask

  aes32_dsp_8p uut (.CLK  (CLK  ), 
                    .RST  (RST  ), 
                    .START(START), 
                    .DIN  (DIN  ), 
                    .KEY  (KEY  ), 

  	            .DONE (DONE ),
                    .DOUT (DOUT ));
               
  // global reset
  assign glbl.GSR = GSR;
  initial begin
    GSR = 1;
    #(20*`T) GSR = 0;
  end

  // extected ECB ciphertext 
  initial begin
    CT[0]   = 128'h66e94bd4ef8a2c3b884cfa59ca342b2e;
    CT[1]   = 128'h3ad78e726c1ec02b7ebfe92b23d9ec34;
    CT[2]   = 128'h45bc707d29e8204d88dfba2f0b0cad9b;
    CT[3]   = 128'h161556838018f52805cdbd6202002e3f;
    CT[4]   = 128'hf5569b3ab6a6d11efde1bf0a64c6854a;
    CT[5]   = 128'h64e82b50e501fbd7dd4116921159b83e;
    CT[6]   = 128'hbaac12fb613a7de11450375c74034041;
    CT[7]   = 128'hbcf176a7eaad8085ebacea362462a281;
    CT[8]   = 128'h47711816e91d6ff059bbbf2bf58e0fd3;
    CT[9]   = 128'hb970dfbe40698af1638fe38bd3df3b2f;
    CT[10]  = 128'hf95b59a44f391e14cf20b74bdc32fcff;
    CT[11]  = 128'h720f74ae04a2a435b9a7256e49378f5b;
    CT[12]  = 128'h2a0445f61d36bfa7e277070730cf76da;
    CT[13]  = 128'h8d0536b997aefec1d94011bab6699a03;
    CT[14]  = 128'h674f002e19f6ed47eff319e51fad4498;
    CT[15]  = 128'h292c02c5cb9163c80ac0f6cf1dd8e92d;
    CT[16]  = 128'hfa321cf18ef5fe727dd82a5c1e945141;
    CT[17]  = 128'ha5a7afe1034c39cccebe3c584bc0be05;
    CT[18]  = 128'h4ff5a52e697e77d081205dbdb21cea39;
    CT[19]  = 128'h209e88dc94c9003000ce0769af7b7166;
    CT[20]  = 128'h5dee41af864cb4b650e5f51551824d38;
    CT[21]  = 128'ha79a63fa7e4503ae6d6e09f5f9053030;
    CT[22]  = 128'ha48316749fae7fac7002031a6afd8ba7;
    CT[23]  = 128'hd6eee8a7357a0e1d64262ca9c337ac42;
    CT[24]  = 128'hb013ca8a62a858053e9fb667ed39829e;
    CT[25]  = 128'hdf6ea9e4538a45a52d5c1a43c88f4b55;
    CT[26]  = 128'h7d03ba451371591d3fd5547d9165c73b;
    CT[27]  = 128'h0e0426281a6277e186499d365d5f49ff;
    CT[28]  = 128'hdbc02169dd2059e6cc4c57c1fedf5ab4;
    CT[29]  = 128'h826590e05d167da6f00dcc75e22788eb;
    CT[30]  = 128'h34a73f21a04421d9786335faab49423a;
    CT[31]  = 128'hed347d0e0128ee1a7392a1d36ab78aa9;
    CT[32]  = 128'hee944b2fe6e9fc888042608da9615f75;
    CT[33]  = 128'h9e7c85a909ef7218ba7947cfb4718f46;
    CT[34]  = 128'h811ae07a0b2b1f816587fa73699ae77d;
    CT[35]  = 128'h68466fbf43c2fe13d4b18f7ec5ea745f;
    CT[36]  = 128'hd20b015c7191b219780956e6101f9354;
    CT[37]  = 128'h5939d5c1bbf54ee1b3e326d757bdde25;
    CT[38]  = 128'hb1fdafe9a0240e8ffea19ce94b5105d3;
    CT[39]  = 128'hd62962ece02cdd68c06bdfefb2f9495b;
    CT[40]  = 128'hb3bb2de6f3c26587ba8bac4f7ad9499a;
    CT[41]  = 128'he0b1072d6d9ff703d6fbef77852b0a6b;
    CT[42]  = 128'hd8dd51c907f478de0228e83e61fd1758;
    CT[43]  = 128'ha42dffe6e7c1671c06a25236fdd10017;
    CT[44]  = 128'h25acf141550bfab9ef451b6c6a5b2163;
    CT[45]  = 128'h4da7fca3949b16e821dbc84f19581018;
    CT[46]  = 128'h7d49b6347cbcc8919c7fa96a37a7a215;
    CT[47]  = 128'h900024b29a08c6721b95ba3b753ddb4d;
    CT[48]  = 128'h6d2182fb283b6934d90ba7848cab5e66;
    CT[49]  = 128'hf73ef01b448d23a4d90de8b2f9666e7a;
    CT[50]  = 128'h4ad9cda2418643e9a3d926af5e6b0412;
    CT[51]  = 128'h7caec8e7e5953997d545b033201c8c5b;
    CT[52]  = 128'h3c43ca1f6b6864503e27b48d88230cf5;
    CT[53]  = 128'h44f779b93108fe9feec880d79ba74488;
    CT[54]  = 128'h9e50e8d9cfd3a682a78e527c9072a1cf;
    CT[55]  = 128'h68d000cbc838bbe3c505d6f814c01f28;
    CT[56]  = 128'h2cb2a9fec1acd1d9b0fa05205e304f57;
    CT[57]  = 128'h01eb2806606e46444520a5cc6180cd4b;
    CT[58]  = 128'hdaa9b25168cc702326f217f1a0c0b162;
    CT[59]  = 128'h3e07e648975d9578d03555b1755807ed;
    CT[60]  = 128'h0b45f52e802c8b8de09579425b80b711;
    CT[61]  = 128'h659595da0b68f6df0dd6ca77202986e1;
    CT[62]  = 128'h05ff42873893536e58c8fa98a45c73c4;
    CT[63]  = 128'hb5b03421de8bbffc4eadec767339a9bd;
    CT[64]  = 128'h788bcd111ecf73d4e78d2e21bef55460;
    CT[65]  = 128'h909cd9ec6790359f982dc6f2393d5315;
    CT[66]  = 128'h332950f361535ff24efac8c76293f12c;
    CT[67]  = 128'ha68ccd4e330ffda9d576da436db53d75;
    CT[68]  = 128'h27c8a1ccfdb0b015d1ed5b3e77143791;
    CT[69]  = 128'hd76a4b95887a77df610dd3e1d3b20325;
    CT[70]  = 128'hc068ab0de71c66dae83c361ef4b2d989;
    CT[71]  = 128'hc2120bcd49eda9a288b3b4be79ac8158;
    CT[72]  = 128'h0c546f62bf2773cd0f564fceca7ba688;
    CT[73]  = 128'h18f3462bede4920213ccb66dab1640aa;
    CT[74]  = 128'hfe42f245edd0e24b216aebd8b392d690;
    CT[75]  = 128'h3d3eebc8d3d1558a194c2d00c337ff2b;
    CT[76]  = 128'h29aaedf043e785db42836f79be6cba28;
    CT[77]  = 128'h215f90c6744e2944358e78619159a611;
    CT[78]  = 128'h8606b1aa9e1d548e5442b06551e2c6dc;
    CT[79]  = 128'h987bb4b8740ec0ede7fea97df033b5b1;
    CT[80]  = 128'hc0a3500da5b0ae07d2f450930beedf1b;
    CT[81]  = 128'h525fdf8312fe8f32c781481a8daaae37;
    CT[82]  = 128'hbfd2c56ae5fb9c9de33a6944572a6487;
    CT[83]  = 128'h7975a57a425cdf5aa1fa929101f650b0;
    CT[84]  = 128'hbf174bc49609a8709b2cd8366daa79fe;
    CT[85]  = 128'h06c50c43222f56c874b1704e9f44bf7d;
    CT[86]  = 128'h0cec48cd34043ea29ca3b8ed5278721e;
    CT[87]  = 128'h9548ea34a1560197b304d0acb8a1698d;
    CT[88]  = 128'h22f9e9b1bd73b6b5b7d3062c986272f3;
    CT[89]  = 128'hfee8e934bd0873295059002230e298d4;
    CT[90]  = 128'h1b08e2e3eb820d139cb4abbdbe81d00d;
    CT[91]  = 128'h0021177681e4d90ceaf69dced0145125;
    CT[92]  = 128'h4a8e314452ca8a8a3619fc54bc423643;
    CT[93]  = 128'h65047474f7222c94c6965425ff1bfd0a;
    CT[94]  = 128'he123f551a9c4a8489622b16f961a9aa4;
    CT[95]  = 128'hef05530948b80915028bb2b6fe429380;
    CT[96]  = 128'h72535b7fe0f0f777cedcd55cd77e2ddf;
    CT[97]  = 128'h3423d8efc31fa2f4c365c77d8f3b5c63;
    CT[98]  = 128'hde0e51c264663f3c5dbc59580a98d8e4;
    CT[99]  = 128'hb2d9391166680947ab09264156719679;
    CT[100] = 128'h10db79f23b06d263835c424af749adb7;
    CT[101] = 128'hddf72d27e6b01ec107ea3e005b59563b;
    CT[102] = 128'h8266b57485a5954a4236751de07f6694;
    CT[103] = 128'h669a501e1f1ade6e5523de01d6dbc987;
    CT[104] = 128'hc20c48f2989725d461d1db589dc0896e;
    CT[105] = 128'hde35158e7810ed1191825d2aa98fa97d;
    CT[106] = 128'h4fe294f2c0f34d0671b693a237ebddc8;
    CT[107] = 128'h087ae74b10ccbfdf6739feb9559c01a4;
    CT[108] = 128'h5dc278970b7def77a5536c77ab59c207;
    CT[109] = 128'h7607f078c77085184eaa9b060c1fbfff;
    CT[110] = 128'h9db841531bcbe7998dad19993fb3cc00;
    CT[111] = 128'hd6a089b654854a94560bae13298835b8;
    CT[112] = 128'he1e223c4cf90cc5d195b370d65114622;
    CT[113] = 128'h1cbed73c50d053bdad372ceee54836a1;
    CT[114] = 128'hd309e69376d257adf2bfda152b26555f;
    CT[115] = 128'h740f7649117f0dee6eaa7789a9994c36;
    CT[116] = 128'h76ae64417c297184d668c5fd908b3ce5;
    CT[117] = 128'h6095fea4aa8035591f1787a819c48787;
    CT[118] = 128'hd1ff4e7acd1c79967febab0f7465d450;
    CT[119] = 128'h5f5ad3c42b9489557bb63bf49ecf5f8a;
    CT[120] = 128'hfb56cc09b680b1d07c5a52149e29f07c;
    CT[121] = 128'hff49b8df4a97cbe03833e66197620dad;
    CT[122] = 128'h5e070ade533d2e090ed0f5be13bc0983;
    CT[123] = 128'h3ab4fb1d2b7ba376590a2c241d1f508d;
    CT[124] = 128'h58b2431bc0bede02550f40238969ec78;
    CT[125] = 128'h0253786e126504f0dab90c48a30321de;
    CT[126] = 128'h200211214e7394da2089b6acd093abe0;
    CT[127] = 128'h0388dace60b6a392f328c2b971b2fe78;
    CT[128] = 128'h58e2fccefa7e3061367f1d57a4e7455a;
  end
      
  // clock
  initial begin
    CLK = 0;
    forever #(`T/2) CLK = ~CLK;
  end
 
  initial begin
    errors = 0;
    RST    = 1;
    DIN    = 0;
    KEY    = 0;
    START  = 0;
    PT     = 128'h80000000000000000000000000000000;
    i      = 1;
    exp1   = 0;
    exp2   = 0;
  end

  initial begin
 
    #`T      globres();
    #`T      exp1 = CTD;
	     exp2 = CTD;
             dispinout(PTD,PTD,exp1,exp2);
    #(`T-`D) START = 1;
             datain(KDx,PTD);
             datain(KDx,PTD);
	     datain(KDx0,128'd0);
	     datain(KDx0,128'd0);
             datain(KDx1,128'd0);
	     datain(KDx1,128'd0);
	     datain(KDx2,128'd0);
	     datain(KDx2,128'd0);
	     datain(KDx3,128'd0);
	     datain(KDx3,128'd0);
	     datain(KDx4,128'd0);
	     datain(KDx4,128'd0);
	     datain(KDx5,128'd0);
	     datain(KDx5,128'd0);
	     datain(KDx6,128'd0);
	     datain(KDx6,128'd0);
	     datain(KDx7,128'd0);
	     datain(KDx7,128'd0);
	     datain(KDx8,128'd0);
	     datain(KDx8,128'd0);
	     datain(KDx9,128'd0);
	     datain(KDx9,128'd0);

    #`T      globres();
    #`T      exp1 = 128'd0;
	     exp2 = 128'd0;
             dispinout(CT[0],CT[0],exp1,exp2);
    #`T      START = 1;
             datain(KD,CT[0]);
             datain(KD,CT[0]);
	     datain(KD0,128'd0);
	     datain(KD0,128'd0);
             datain(KD1,128'd0);
	     datain(KD1,128'd0);
	     datain(KD2,128'd0);
	     datain(KD2,128'd0);
	     datain(KD3,128'd0);
	     datain(KD3,128'd0);
	     datain(KD4,128'd0);
	     datain(KD4,128'd0);
	     datain(KD5,128'd0);
	     datain(KD5,128'd0);
	     datain(KD6,128'd0);
	     datain(KD6,128'd0);
	     datain(KD7,128'd0);
	     datain(KD7,128'd0);
	     datain(KD8,128'd0);
	     datain(KD8,128'd0);
	     datain(KD9,128'd0);
	     datain(KD9,128'd0);
			 
    #`T      globres();	
	
    repeat (128) begin
      #`T      exp1 = PT;
               exp2 = PT;
	
      #`T      START = 1;
               datain(KD,CT[i]);
               datain(KD,CT[i]);
               dispinout(CT[i],CT[i],exp1,exp2);
	       datain(KD0,128'd0);
	       datain(KD0,128'd0);
               datain(KD1,128'd0);
  	       datain(KD1,128'd0);
	       datain(KD2,128'd0);
	       datain(KD2,128'd0);
	       datain(KD3,128'd0);
	       datain(KD3,128'd0);
	       datain(KD4,128'd0);
	       datain(KD4,128'd0);
	       datain(KD5,128'd0);
	       datain(KD5,128'd0);
	       datain(KD6,128'd0);
	       datain(KD6,128'd0);
	       datain(KD7,128'd0);
	       datain(KD7,128'd0);
	       datain(KD8,128'd0);
	       datain(KD8,128'd0);
	       datain(KD9,128'd0);
	       datain(KD9,128'd0);	

      #`T      PT = PT >> 1; // shift input by 1
      #`T      globres();
	       i = i + 1;	
    end
  #`T  $display ("\nERRORS: %d", errors);  // display number of errors
end  
  
  // output is valid when DONE is high; these calls check if it is as expected. 
  initial begin
    forever begin
      @(posedge DONE) begin
	#(`T/2)  simcheck(DOUT, exp1[127:96]);
	#`T      simcheck(DOUT, exp1[31:00]);	         
	#`T      simcheck(DOUT, exp1[63:32]);
        #`T      simcheck(DOUT, exp1[95:64]);
	#`T      simcheck(DOUT, exp2[127:96]);
	#`T      simcheck(DOUT, exp2[31:00]);	         
	#`T      simcheck(DOUT, exp2[63:32]);
        #`T      simcheck(DOUT, exp2[95:64]);
	#(`T/2);
      end	
    end	  
  end

endmodule


