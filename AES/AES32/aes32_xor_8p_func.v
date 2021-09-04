`timescale 1 ps / 1 ps

module aes32_xor_8p_func (
  input  wire         CLK,  
  input  wire         RST,
  input  wire [31:00] DIN,
  input  wire [31:00] PTX,  
  input  wire [31:00] KEY,
  input  wire [03:00] TSH, // T-table shift control (shifts the output of the BRAMs)
  input  wire [07:00] BCT, // BRAM control; [7:4] choose between T0 and T2; [3:0] chooses last round's T-tables 
  input  wire         POB, // select: plaintext(HIGH) or BRAM(LOW)
  input  wire [02:00] RXR, // reset input to DSP (so data it unchanged as it passes through)
  
  output wire [31:00] DOUT
);

  reg    [31:00] bram0a_data_p, bram0b_data_p, bram1a_data_p, bram1b_data_p;
  reg    [31:00] bram0a_data_pp, bram0b_data_pp, bram1a_data_pp, bram1b_data_pp;
  reg    [31:00] xor0a_pdata, xor0b_pdata, xor1a_pdata ,xor1b_pdata;
  
  reg    [31:00] key_p;
  
  wire   [31:00] xor0a_din;
  wire   [31:00] bram0a_data, bram0b_data, bram1a_data, bram1b_data;
  wire   [15:00] bram0a_addr, bram0b_addr, bram1a_addr, bram1b_addr;

  assign DOUT = xor1b_pdata[31:00];  

  // address busses for the BRAMs {0,T0/T2,LAST,DATA,00000}
  assign bram0a_addr = {1'b0, BCT[7], BCT[3], DIN[31:24], 5'd0};
  assign bram0b_addr = {1'b0, BCT[6], BCT[2], DIN[23:16], 5'd0};
  assign bram1a_addr = {1'b0, BCT[5], BCT[1], DIN[15:08], 5'd0};
  assign bram1b_addr = {1'b0, BCT[4], BCT[0], DIN[07:00], 5'd0};
  
  // for simulation
  initial begin
    bram0a_data_p = 0; bram0b_data_p = 0; bram1a_data_p = 0; bram1b_data_p = 0;
  end  

  RAMB36 #(
    .DOA_REG            (1              ), // Optional output registers on A port (0 or 1)
    .DOB_REG            (1              ), // Optional output registers on B port (0 or 1)
    .INIT_A             (36'h000000000  ), // Initial values on A output port
    .INIT_B             (36'h000000000  ), // Initial values on B output port
    .RAM_EXTENSION_A    ("NONE"         ), // "UPPER", "LOWER" or "NONE" when cascaded
    .RAM_EXTENSION_B    ("NONE"         ), // "UPPER", "LOWER" or "NONE" when cascaded
    .READ_WIDTH_A       (36             ), // Valid values are 1, 2, 4, 9, 18, or 36
    .READ_WIDTH_B       (36             ), // Valid values are 1, 2, 4, 9, 18, or 36
    .SIM_COLLISION_CHECK("NONE"         ), // Collision check enable "ALL", "WARNING_ONLY", "GENERATE_X_ONLY" or "NONE"
    .SRVAL_A            (36'h000000000  ), // Set/Reset value for A port output
    .SRVAL_B            (36'h000000000  ), // Set/Reset value for B port output
    .WRITE_MODE_A       ("READ_FIRST"   ), // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE"
    .WRITE_MODE_B       ("READ_FIRST"   ), // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE"
    .WRITE_WIDTH_A      (36             ), // Valid values are 1, 2, 4, 9, 18, or 36
    .WRITE_WIDTH_B      (36             ), // Valid values are 1, 2, 4, 9, 18, or 36
   // TABLE T0 (t_fn)
   .INIT_00(256'h91C5C554DE6F6FB1D66B6BBDFFF2F20DF67B7B8DEE777799F87C7C84C66363A5),
   .INIT_01(256'hEC76769A4DABABE6B5D7D762E7FEFE19562B2B7DCE6767A90201010360303050),
   .INIT_02(256'hFBF0F00B8E4747C9B25959EBEFFAFA15FA7D7D8789C9C9401F82829D8FCACA45),
   .INIT_03(256'h9BC0C05BE472729653A4A4F7239C9CBF45AFAFEA5FA2A2FDB3D4D46741ADADEC),
   .INIT_04(256'h83CCCC4FF5F7F7027E3F3F416C36365A4C26266A3D9393AEE1FDFD1C75B7B7C2),
   .INIT_05(256'h2A15153F62313153ABD8D873E2717193F9F1F108D1E5E53451A5A5F46834345C),
   .INIT_06(256'h2F9A9AB50A05050F379696A1301818289DC3C35E4623236595C7C7520804040C),
   .INIT_07(256'hEA75759F7FB2B2CD4E272769CDEBEB26DFE2E23D1B80809B241212360E070709),
   .INIT_08(256'h5BA0A0FBB45A5AEEDC6E6EB2361B1B2D341A1A2E582C2C741D83839E1209091B),
   .INIT_09(256'h138484975E2F2F71DDE3E33E5229297B7DB3B3CEB7D6D661763B3B4DA45252F6),
   .INIT_0A(256'hB65B5BED79B1B1C8E3FCFC1F40202060C1EDED2C00000000B9D1D168A65353F5),
   .INIT_0B(256'h85CFCF4AB05858E8984C4CD4944A4ADE7239394B67BEBED98DCBCB46D46A6ABE),
   .INIT_0C(256'h11858594663333559A4D4DD7864343C5EDFBFB164FAAAAE5C5EFEF2ABBD0D06B),
   .INIT_0D(256'h4BA8A8E3259F9FBA783C3C44A05050F0FE7F7F8104020206E9F9F9108A4545CF),
   .INIT_0E(256'hF1F5F50470383848219D9DBC3F9292AD058F8F8A804040C05DA3A3FEA25151F3),
   .INIT_0F(256'hBFD2D26DFDF3F30EE5FFFF1A2010103042212163AFDADA7577B6B6C163BCBCDF),
   .INIT_10(256'h2E171739884444CC359797A2BE5F5FE1C3ECEC2F26131335180C0C1481CDCD4C),
   .INIT_11(256'hE67373953219192BBA5D5DE7C86464AC7A3D3D47FC7E7E8255A7A7F293C4C457),
   .INIT_12(256'h0B8888833B9090AB542A2A7E44222266A3DCDC7F9E4F4FD119818198C06060A0),
   .INIT_13(256'hADDBDB76160B0B1DBC5E5EE2A7DEDE792814143C6BB8B8D3C7EEEE298C4646CA),
   .INIT_14(256'hB85C5CE44824246C0C06060A924949DB140A0A1E743A3A4E64323256DBE0E03B),
   .INIT_15(256'hF279798BD3E4E437319595A4399191A8C46262A643ACACEFBDD3D36E9FC2C25D),
   .INIT_16(256'h49A9A9E09C4E4ED2B1D5D564018D8D8CDA6D6DB76E3737598BC8C843D5E7E732),
   .INIT_17(256'h1008081847AEAEE9F47A7A8ECA6565AFCFEAEA25F3F4F407AC5656FAD86C6CB4),
   .INIT_18(256'h97C6C65173B4B4C757A6A6F1381C1C245C2E2E724A25256FF07878886FBABAD5),
   .INIT_19(256'h0F8A8A850D8B8B8661BDBDDC964B4BDD3E1F1F21E874749CA1DDDD7CCBE8E823),
   .INIT_1A(256'h1C0E0E12F7F6F60106030305904848D8CC6666AA71B5B5C47C3E3E42E0707090),
   .INIT_1B(256'h279E9EB93A1D1D2799C1C1581786869169B9B9D0AE5757F96A35355FC26161A3),
   .INIT_1C(256'h339494A7078E8E89A9D9D970D26969BB221111332B9898B3EBF8F813D9E1E138),
   .INIT_1D(256'hA5DFDF7A50282878AA5555FF87CECE49C9E9E920158787923C1E1E222D9B9BB6),
   .INIT_1E(256'hD06868B8844242C6D7E6E63165BFBFDA1A0D0D170989898059A1A1F8038C8C8F),
   .INIT_1F(256'h2C16163A6DBBBBD6A85454FC7BB0B0CB1E0F0F115A2D2D77299999B0824141C3),
   // TABLE T0 (t_fl)
   .INIT_20(256'hC50000006F0000006B000000F20000007B000000770000007C00000063000000),
   .INIT_21(256'h76000000AB000000D7000000FE0000002B000000670000000100000030000000),
   .INIT_22(256'hF00000004700000059000000FA0000007D000000C900000082000000CA000000),
   .INIT_23(256'hC000000072000000A40000009C000000AF000000A2000000D4000000AD000000),
   .INIT_24(256'hCC000000F70000003F000000360000002600000093000000FD000000B7000000),
   .INIT_25(256'h1500000031000000D800000071000000F1000000E5000000A500000034000000),
   .INIT_26(256'h9A000000050000009600000018000000C300000023000000C700000004000000),
   .INIT_27(256'h75000000B200000027000000EB000000E2000000800000001200000007000000),
   .INIT_28(256'hA00000005A0000006E0000001B0000001A0000002C0000008300000009000000),
   .INIT_29(256'h840000002F000000E300000029000000B3000000D60000003B00000052000000),
   .INIT_2A(256'h5B000000B1000000FC00000020000000ED00000000000000D100000053000000),
   .INIT_2B(256'hCF000000580000004C0000004A00000039000000BE000000CB0000006A000000),
   .INIT_2C(256'h85000000330000004D00000043000000FB000000AA000000EF000000D0000000),
   .INIT_2D(256'hA80000009F0000003C000000500000007F00000002000000F900000045000000),
   .INIT_2E(256'hF5000000380000009D000000920000008F00000040000000A300000051000000),
   .INIT_2F(256'hD2000000F3000000FF0000001000000021000000DA000000B6000000BC000000),
   .INIT_30(256'h1700000044000000970000005F000000EC000000130000000C000000CD000000),
   .INIT_31(256'h73000000190000005D000000640000003D0000007E000000A7000000C4000000),
   .INIT_32(256'h88000000900000002A00000022000000DC0000004F0000008100000060000000),
   .INIT_33(256'hDB0000000B0000005E000000DE00000014000000B8000000EE00000046000000),
   .INIT_34(256'h5C0000002400000006000000490000000A0000003A00000032000000E0000000),
   .INIT_35(256'h79000000E4000000950000009100000062000000AC000000D3000000C2000000),
   .INIT_36(256'hA90000004E000000D50000008D0000006D00000037000000C8000000E7000000),
   .INIT_37(256'h08000000AE0000007A00000065000000EA000000F4000000560000006C000000),
   .INIT_38(256'hC6000000B4000000A60000001C0000002E0000002500000078000000BA000000),
   .INIT_39(256'h8A0000008B000000BD0000004B0000001F00000074000000DD000000E8000000),
   .INIT_3A(256'h0E000000F6000000030000004800000066000000B50000003E00000070000000),
   .INIT_3B(256'h9E0000001D000000C100000086000000B9000000570000003500000061000000),
   .INIT_3C(256'h940000008E000000D9000000690000001100000098000000F8000000E1000000),
   .INIT_3D(256'hDF0000002800000055000000CE000000E9000000870000001E0000009B000000),
   .INIT_3E(256'h6800000042000000E6000000BF0000000D00000089000000A10000008C000000),
   .INIT_3F(256'h16000000BB00000054000000B00000000F0000002D0000009900000041000000),
   // TABLE T2 (t_fn)
   .INIT_40(256'hC55491C56FB1DE6F6BBDD66BF20DFFF27B8DF67B7799EE777C84F87C63A5C663),
   .INIT_41(256'h769AEC76ABE64DABD762B5D7FE19E7FE2B7D562B67A9CE670103020130506030),
   .INIT_42(256'hF00BFBF047C98E4759EBB259FA15EFFA7D87FA7DC94089C9829D1F82CA458FCA),
   .INIT_43(256'hC05B9BC07296E472A4F753A49CBF239CAFEA45AFA2FD5FA2D467B3D4ADEC41AD),
   .INIT_44(256'hCC4F83CCF702F5F73F417E3F365A6C36266A4C2693AE3D93FD1CE1FDB7C275B7),
   .INIT_45(256'h153F2A1531536231D873ABD87193E271F108F9F1E534D1E5A5F451A5345C6834),
   .INIT_46(256'h9AB52F9A050F0A0596A1379618283018C35E9DC323654623C75295C7040C0804),
   .INIT_47(256'h759FEA75B2CD7FB227694E27EB26CDEBE23DDFE2809B1B801236241207090E07),
   .INIT_48(256'hA0FB5BA05AEEB45A6EB2DC6E1B2D361B1A2E341A2C74582C839E1D83091B1209),
   .INIT_49(256'h849713842F715E2FE33EDDE3297B5229B3CE7DB3D661B7D63B4D763B52F6A452),
   .INIT_4A(256'h5BEDB65BB1C879B1FC1FE3FC20604020ED2CC1ED00000000D168B9D153F5A653),
   .INIT_4B(256'hCF4A85CF58E8B0584CD4984C4ADE944A394B7239BED967BECB468DCB6ABED46A),
   .INIT_4C(256'h85941185335566334DD79A4D43C58643FB16EDFBAAE54FAAEF2AC5EFD06BBBD0),
   .INIT_4D(256'hA8E34BA89FBA259F3C44783C50F0A0507F81FE7F02060402F910E9F945CF8A45),
   .INIT_4E(256'hF504F1F5384870389DBC219D92AD3F928F8A058F40C08040A3FE5DA351F3A251),
   .INIT_4F(256'hD26DBFD2F30EFDF3FF1AE5FF1030201021634221DA75AFDAB6C177B6BCDF63BC),
   .INIT_50(256'h17392E1744CC884497A235975FE1BE5FEC2FC3EC133526130C14180CCD4C81CD),
   .INIT_51(256'h7395E673192B32195DE7BA5D64ACC8643D477A3D7E82FC7EA7F255A7C45793C4),
   .INIT_52(256'h88830B8890AB3B902A7E542A22664422DC7FA3DC4FD19E4F8198198160A0C060),
   .INIT_53(256'hDB76ADDB0B1D160B5EE2BC5EDE79A7DE143C2814B8D36BB8EE29C7EE46CA8C46),
   .INIT_54(256'h5CE4B85C246C4824060A0C0649DB92490A1E140A3A4E743A32566432E03BDBE0),
   .INIT_55(256'h798BF279E437D3E495A4319591A8399162A6C462ACEF43ACD36EBDD3C25D9FC2),
   .INIT_56(256'hA9E049A94ED29C4ED564B1D58D8C018D6DB7DA6D37596E37C8438BC8E732D5E7),
   .INIT_57(256'h08181008AEE947AE7A8EF47A65AFCA65EA25CFEAF407F3F456FAAC566CB4D86C),
   .INIT_58(256'hC65197C6B4C773B4A6F157A61C24381C2E725C2E256F4A257888F078BAD56FBA),
   .INIT_59(256'h8A850F8A8B860D8BBDDC61BD4BDD964B1F213E1F749CE874DD7CA1DDE823CBE8),
   .INIT_5A(256'h0E121C0EF601F7F60305060348D8904866AACC66B5C471B53E427C3E7090E070),
   .INIT_5B(256'h9EB9279E1D273A1DC15899C186911786B9D069B957F9AE57355F6A3561A3C261),
   .INIT_5C(256'h94A733948E89078ED970A9D969BBD2691133221198B32B98F813EBF8E138D9E1),
   .INIT_5D(256'hDF7AA5DF2878502855FFAA55CE4987CEE920C9E9879215871E223C1E9BB62D9B),
   .INIT_5E(256'h68B8D06842C68442E631D7E6BFDA65BF0D171A0D89800989A1F859A18C8F038C),
   .INIT_5F(256'h163A2C16BBD66DBB54FCA854B0CB7BB00F111E0F2D775A2D99B0299941C38241),
   // TABLE T2 (t_fl)
   .INIT_60(256'h0000C50000006F0000006B000000F20000007B000000770000007C0000006300),
   .INIT_61(256'h000076000000AB000000D7000000FE0000002B00000067000000010000003000),
   .INIT_62(256'h0000F00000004700000059000000FA0000007D000000C900000082000000CA00),
   .INIT_63(256'h0000C000000072000000A40000009C000000AF000000A2000000D4000000AD00),
   .INIT_64(256'h0000CC000000F70000003F000000360000002600000093000000FD000000B700),
   .INIT_65(256'h00001500000031000000D800000071000000F1000000E5000000A50000003400),
   .INIT_66(256'h00009A000000050000009600000018000000C300000023000000C70000000400),
   .INIT_67(256'h000075000000B200000027000000EB000000E200000080000000120000000700),
   .INIT_68(256'h0000A00000005A0000006E0000001B0000001A0000002C000000830000000900),
   .INIT_69(256'h0000840000002F000000E300000029000000B3000000D60000003B0000005200),
   .INIT_6A(256'h00005B000000B1000000FC00000020000000ED00000000000000D10000005300),
   .INIT_6B(256'h0000CF000000580000004C0000004A00000039000000BE000000CB0000006A00),
   .INIT_6C(256'h000085000000330000004D00000043000000FB000000AA000000EF000000D000),
   .INIT_6D(256'h0000A80000009F0000003C000000500000007F00000002000000F90000004500),
   .INIT_6E(256'h0000F5000000380000009D000000920000008F00000040000000A30000005100),
   .INIT_6F(256'h0000D2000000F3000000FF0000001000000021000000DA000000B6000000BC00),
   .INIT_70(256'h00001700000044000000970000005F000000EC000000130000000C000000CD00),
   .INIT_71(256'h000073000000190000005D000000640000003D0000007E000000A7000000C400),
   .INIT_72(256'h000088000000900000002A00000022000000DC0000004F000000810000006000),
   .INIT_73(256'h0000DB0000000B0000005E000000DE00000014000000B8000000EE0000004600),
   .INIT_74(256'h00005C0000002400000006000000490000000A0000003A00000032000000E000),
   .INIT_75(256'h000079000000E4000000950000009100000062000000AC000000D3000000C200),
   .INIT_76(256'h0000A90000004E000000D50000008D0000006D00000037000000C8000000E700),
   .INIT_77(256'h000008000000AE0000007A00000065000000EA000000F4000000560000006C00),
   .INIT_78(256'h0000C6000000B4000000A60000001C0000002E0000002500000078000000BA00),
   .INIT_79(256'h00008A0000008B000000BD0000004B0000001F00000074000000DD000000E800),
   .INIT_7A(256'h00000E000000F6000000030000004800000066000000B50000003E0000007000),
   .INIT_7B(256'h00009E0000001D000000C100000086000000B900000057000000350000006100),
   .INIT_7C(256'h0000940000008E000000D9000000690000001100000098000000F8000000E100),
   .INIT_7D(256'h0000DF0000002800000055000000CE000000E9000000870000001E0000009B00),
   .INIT_7E(256'h00006800000042000000E6000000BF0000000D00000089000000A10000008C00),
   .INIT_7F(256'h000016000000BB00000054000000B00000000F0000002D000000990000004100),
    // The next set of INITP_xx are f6743000000000000000or the parity bits
    .INITP_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0F(256'h0000000000000000000000000000000000000000000000000000000000000000)) 
  RAMB36_0 (
    .CASCADEOUTLATA(             ), // 1-bit cascade A latch output
    .CASCADEOUTLATB(             ), // 1-bit cascade B latch output
    .CASCADEOUTREGA(             ), // 1-bit cascade A register output
    .CASCADEOUTREGB(             ), // 1-bit cascade B register output
    .DOA           (bram0a_data  ), // 32-bit A port data output
    .DOB           (bram0b_data  ), // 32-bit B port data output
    .DOPA          (             ), // 4-bit A port parity data output
    .DOPB          (             ), // 4-bit B port parity data output
    .ADDRA         (bram0a_addr  ), // 16-bit A port address input
    .ADDRB         (bram0b_addr  ), // 16-bit B port address input
    .CASCADEINLATA (1'b0         ), // 1-bit cascade A latch input
    .CASCADEINLATB (1'b0         ), // 1-bit cascade B latch input
    .CASCADEINREGA (1'b0         ), // 1-bit cascade A register input
    .CASCADEINREGB (1'b0         ), // 1-bit cascade B register input
    .CLKA          (CLK          ), // 1-bit A port clock input
    .CLKB          (CLK          ), // 1-bit B port clock input
    .DIA           (32'd0        ), // 32-bit A port data input
    .DIB           (32'd0        ), // 32-bit B port data input
    .DIPA          (4'd0         ), // 4-bit A port parity data input
    .DIPB          (4'd0         ), // 4-bit B port parity data input
    .ENA           (1'b1         ), // 1-bit A port enable input
    .ENB           (1'b1         ), // 1-bit B port enable input
    .REGCEA        (1'b1         ), // 1-bit A port register enable input
    .REGCEB        (1'b1         ), // 1-bit B port register enable input
    .SSRA          (1'b0         ), // 1-bit A port set/reset input
    .SSRB          (1'b0         ), // 1-bit B port set/reset input
    .WEA           (4'd0         ), // 4-bit A port write enable input
    .WEB           (4'd0         )  // 4-bit B port write enable input
  );

  always @(posedge CLK) begin
    if (TSH[3]) bram0a_data_p <= {bram0a_data[07:00], bram0a_data[31:08]};
    else        bram0a_data_p <= bram0a_data;
    if (TSH[2]) bram0b_data_p <= {bram0b_data[07:00], bram0b_data[31:08]};
    else        bram0b_data_p <= bram0b_data;
  
    // another pipeline stage
    if (POB)    bram0a_data_pp <= PTX;
    else	    bram0a_data_pp <= bram0a_data_p;
    if (RXR[2]) bram0b_data_pp <= 0;
    else        bram0b_data_pp <= bram0b_data_p;
    
    key_p <= KEY;
	
    xor0a_pdata <= (bram0a_data_pp ^ key_p);
    xor0b_pdata <= (bram0b_data_pp ^ xor0a_pdata);
  end
 
  RAMB36 #(
    .DOA_REG            (1            ), // Optional output registers on A port (0 or 1)
    .DOB_REG            (1            ), // Optional output registers on B port (0 or 1)
    .INIT_A             (36'h000000000), // Initial values on A output port
    .INIT_B             (36'h000000000), // Initial values on B output port
    .RAM_EXTENSION_A    ("NONE"       ), // "UPPER", "LOWER" or "NONE" when cascaded
    .RAM_EXTENSION_B    ("NONE"       ), // "UPPER", "LOWER" or "NONE" when cascaded
    .READ_WIDTH_A       (36           ), // Valid values are 1, 2, 4, 9, 18, or 36
    .READ_WIDTH_B       (36           ), // Valid values are 1, 2, 4, 9, 18, or 36
    .SIM_COLLISION_CHECK("NONE"       ), // Collision check enable "ALL", "WARNING_ONLY", "GENERATE_X_ONLY" or "NONE"
    .SRVAL_A            (36'h000000000), // Set/Reset value for A port output
    .SRVAL_B            (36'h000000000), // Set/Reset value for B port output
    .WRITE_MODE_A       ("READ_FIRST" ), // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE"
    .WRITE_MODE_B       ("READ_FIRST" ), // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE"
    .WRITE_WIDTH_A      (36           ), // Valid values are 1, 2, 4, 9, 18, or 36
    .WRITE_WIDTH_B      (36           ), // Valid values are 1, 2, 4, 9, 18, or 36
   // TABLE T0 (t_fn)
   .INIT_00(256'h91C5C554DE6F6FB1D66B6BBDFFF2F20DF67B7B8DEE777799F87C7C84C66363A5),
   .INIT_01(256'hEC76769A4DABABE6B5D7D762E7FEFE19562B2B7DCE6767A90201010360303050),
   .INIT_02(256'hFBF0F00B8E4747C9B25959EBEFFAFA15FA7D7D8789C9C9401F82829D8FCACA45),
   .INIT_03(256'h9BC0C05BE472729653A4A4F7239C9CBF45AFAFEA5FA2A2FDB3D4D46741ADADEC),
   .INIT_04(256'h83CCCC4FF5F7F7027E3F3F416C36365A4C26266A3D9393AEE1FDFD1C75B7B7C2),
   .INIT_05(256'h2A15153F62313153ABD8D873E2717193F9F1F108D1E5E53451A5A5F46834345C),
   .INIT_06(256'h2F9A9AB50A05050F379696A1301818289DC3C35E4623236595C7C7520804040C),
   .INIT_07(256'hEA75759F7FB2B2CD4E272769CDEBEB26DFE2E23D1B80809B241212360E070709),
   .INIT_08(256'h5BA0A0FBB45A5AEEDC6E6EB2361B1B2D341A1A2E582C2C741D83839E1209091B),
   .INIT_09(256'h138484975E2F2F71DDE3E33E5229297B7DB3B3CEB7D6D661763B3B4DA45252F6),
   .INIT_0A(256'hB65B5BED79B1B1C8E3FCFC1F40202060C1EDED2C00000000B9D1D168A65353F5),
   .INIT_0B(256'h85CFCF4AB05858E8984C4CD4944A4ADE7239394B67BEBED98DCBCB46D46A6ABE),
   .INIT_0C(256'h11858594663333559A4D4DD7864343C5EDFBFB164FAAAAE5C5EFEF2ABBD0D06B),
   .INIT_0D(256'h4BA8A8E3259F9FBA783C3C44A05050F0FE7F7F8104020206E9F9F9108A4545CF),
   .INIT_0E(256'hF1F5F50470383848219D9DBC3F9292AD058F8F8A804040C05DA3A3FEA25151F3),
   .INIT_0F(256'hBFD2D26DFDF3F30EE5FFFF1A2010103042212163AFDADA7577B6B6C163BCBCDF),
   .INIT_10(256'h2E171739884444CC359797A2BE5F5FE1C3ECEC2F26131335180C0C1481CDCD4C),
   .INIT_11(256'hE67373953219192BBA5D5DE7C86464AC7A3D3D47FC7E7E8255A7A7F293C4C457),
   .INIT_12(256'h0B8888833B9090AB542A2A7E44222266A3DCDC7F9E4F4FD119818198C06060A0),
   .INIT_13(256'hADDBDB76160B0B1DBC5E5EE2A7DEDE792814143C6BB8B8D3C7EEEE298C4646CA),
   .INIT_14(256'hB85C5CE44824246C0C06060A924949DB140A0A1E743A3A4E64323256DBE0E03B),
   .INIT_15(256'hF279798BD3E4E437319595A4399191A8C46262A643ACACEFBDD3D36E9FC2C25D),
   .INIT_16(256'h49A9A9E09C4E4ED2B1D5D564018D8D8CDA6D6DB76E3737598BC8C843D5E7E732),
   .INIT_17(256'h1008081847AEAEE9F47A7A8ECA6565AFCFEAEA25F3F4F407AC5656FAD86C6CB4),
   .INIT_18(256'h97C6C65173B4B4C757A6A6F1381C1C245C2E2E724A25256FF07878886FBABAD5),
   .INIT_19(256'h0F8A8A850D8B8B8661BDBDDC964B4BDD3E1F1F21E874749CA1DDDD7CCBE8E823),
   .INIT_1A(256'h1C0E0E12F7F6F60106030305904848D8CC6666AA71B5B5C47C3E3E42E0707090),
   .INIT_1B(256'h279E9EB93A1D1D2799C1C1581786869169B9B9D0AE5757F96A35355FC26161A3),
   .INIT_1C(256'h339494A7078E8E89A9D9D970D26969BB221111332B9898B3EBF8F813D9E1E138),
   .INIT_1D(256'hA5DFDF7A50282878AA5555FF87CECE49C9E9E920158787923C1E1E222D9B9BB6),
   .INIT_1E(256'hD06868B8844242C6D7E6E63165BFBFDA1A0D0D170989898059A1A1F8038C8C8F),
   .INIT_1F(256'h2C16163A6DBBBBD6A85454FC7BB0B0CB1E0F0F115A2D2D77299999B0824141C3),
   // TABLE T0 (t_fl)
   .INIT_20(256'hC50000006F0000006B000000F20000007B000000770000007C00000063000000),
   .INIT_21(256'h76000000AB000000D7000000FE0000002B000000670000000100000030000000),
   .INIT_22(256'hF00000004700000059000000FA0000007D000000C900000082000000CA000000),
   .INIT_23(256'hC000000072000000A40000009C000000AF000000A2000000D4000000AD000000),
   .INIT_24(256'hCC000000F70000003F000000360000002600000093000000FD000000B7000000),
   .INIT_25(256'h1500000031000000D800000071000000F1000000E5000000A500000034000000),
   .INIT_26(256'h9A000000050000009600000018000000C300000023000000C700000004000000),
   .INIT_27(256'h75000000B200000027000000EB000000E2000000800000001200000007000000),
   .INIT_28(256'hA00000005A0000006E0000001B0000001A0000002C0000008300000009000000),
   .INIT_29(256'h840000002F000000E300000029000000B3000000D60000003B00000052000000),
   .INIT_2A(256'h5B000000B1000000FC00000020000000ED00000000000000D100000053000000),
   .INIT_2B(256'hCF000000580000004C0000004A00000039000000BE000000CB0000006A000000),
   .INIT_2C(256'h85000000330000004D00000043000000FB000000AA000000EF000000D0000000),
   .INIT_2D(256'hA80000009F0000003C000000500000007F00000002000000F900000045000000),
   .INIT_2E(256'hF5000000380000009D000000920000008F00000040000000A300000051000000),
   .INIT_2F(256'hD2000000F3000000FF0000001000000021000000DA000000B6000000BC000000),
   .INIT_30(256'h1700000044000000970000005F000000EC000000130000000C000000CD000000),
   .INIT_31(256'h73000000190000005D000000640000003D0000007E000000A7000000C4000000),
   .INIT_32(256'h88000000900000002A00000022000000DC0000004F0000008100000060000000),
   .INIT_33(256'hDB0000000B0000005E000000DE00000014000000B8000000EE00000046000000),
   .INIT_34(256'h5C0000002400000006000000490000000A0000003A00000032000000E0000000),
   .INIT_35(256'h79000000E4000000950000009100000062000000AC000000D3000000C2000000),
   .INIT_36(256'hA90000004E000000D50000008D0000006D00000037000000C8000000E7000000),
   .INIT_37(256'h08000000AE0000007A00000065000000EA000000F4000000560000006C000000),
   .INIT_38(256'hC6000000B4000000A60000001C0000002E0000002500000078000000BA000000),
   .INIT_39(256'h8A0000008B000000BD0000004B0000001F00000074000000DD000000E8000000),
   .INIT_3A(256'h0E000000F6000000030000004800000066000000B50000003E00000070000000),
   .INIT_3B(256'h9E0000001D000000C100000086000000B9000000570000003500000061000000),
   .INIT_3C(256'h940000008E000000D9000000690000001100000098000000F8000000E1000000),
   .INIT_3D(256'hDF0000002800000055000000CE000000E9000000870000001E0000009B000000),
   .INIT_3E(256'h6800000042000000E6000000BF0000000D00000089000000A10000008C000000),
   .INIT_3F(256'h16000000BB00000054000000B00000000F0000002D0000009900000041000000),
   // TABLE T2 (t_fn)
   .INIT_40(256'hC55491C56FB1DE6F6BBDD66BF20DFFF27B8DF67B7799EE777C84F87C63A5C663),
   .INIT_41(256'h769AEC76ABE64DABD762B5D7FE19E7FE2B7D562B67A9CE670103020130506030),
   .INIT_42(256'hF00BFBF047C98E4759EBB259FA15EFFA7D87FA7DC94089C9829D1F82CA458FCA),
   .INIT_43(256'hC05B9BC07296E472A4F753A49CBF239CAFEA45AFA2FD5FA2D467B3D4ADEC41AD),
   .INIT_44(256'hCC4F83CCF702F5F73F417E3F365A6C36266A4C2693AE3D93FD1CE1FDB7C275B7),
   .INIT_45(256'h153F2A1531536231D873ABD87193E271F108F9F1E534D1E5A5F451A5345C6834),
   .INIT_46(256'h9AB52F9A050F0A0596A1379618283018C35E9DC323654623C75295C7040C0804),
   .INIT_47(256'h759FEA75B2CD7FB227694E27EB26CDEBE23DDFE2809B1B801236241207090E07),
   .INIT_48(256'hA0FB5BA05AEEB45A6EB2DC6E1B2D361B1A2E341A2C74582C839E1D83091B1209),
   .INIT_49(256'h849713842F715E2FE33EDDE3297B5229B3CE7DB3D661B7D63B4D763B52F6A452),
   .INIT_4A(256'h5BEDB65BB1C879B1FC1FE3FC20604020ED2CC1ED00000000D168B9D153F5A653),
   .INIT_4B(256'hCF4A85CF58E8B0584CD4984C4ADE944A394B7239BED967BECB468DCB6ABED46A),
   .INIT_4C(256'h85941185335566334DD79A4D43C58643FB16EDFBAAE54FAAEF2AC5EFD06BBBD0),
   .INIT_4D(256'hA8E34BA89FBA259F3C44783C50F0A0507F81FE7F02060402F910E9F945CF8A45),
   .INIT_4E(256'hF504F1F5384870389DBC219D92AD3F928F8A058F40C08040A3FE5DA351F3A251),
   .INIT_4F(256'hD26DBFD2F30EFDF3FF1AE5FF1030201021634221DA75AFDAB6C177B6BCDF63BC),
   .INIT_50(256'h17392E1744CC884497A235975FE1BE5FEC2FC3EC133526130C14180CCD4C81CD),
   .INIT_51(256'h7395E673192B32195DE7BA5D64ACC8643D477A3D7E82FC7EA7F255A7C45793C4),
   .INIT_52(256'h88830B8890AB3B902A7E542A22664422DC7FA3DC4FD19E4F8198198160A0C060),
   .INIT_53(256'hDB76ADDB0B1D160B5EE2BC5EDE79A7DE143C2814B8D36BB8EE29C7EE46CA8C46),
   .INIT_54(256'h5CE4B85C246C4824060A0C0649DB92490A1E140A3A4E743A32566432E03BDBE0),
   .INIT_55(256'h798BF279E437D3E495A4319591A8399162A6C462ACEF43ACD36EBDD3C25D9FC2),
   .INIT_56(256'hA9E049A94ED29C4ED564B1D58D8C018D6DB7DA6D37596E37C8438BC8E732D5E7),
   .INIT_57(256'h08181008AEE947AE7A8EF47A65AFCA65EA25CFEAF407F3F456FAAC566CB4D86C),
   .INIT_58(256'hC65197C6B4C773B4A6F157A61C24381C2E725C2E256F4A257888F078BAD56FBA),
   .INIT_59(256'h8A850F8A8B860D8BBDDC61BD4BDD964B1F213E1F749CE874DD7CA1DDE823CBE8),
   .INIT_5A(256'h0E121C0EF601F7F60305060348D8904866AACC66B5C471B53E427C3E7090E070),
   .INIT_5B(256'h9EB9279E1D273A1DC15899C186911786B9D069B957F9AE57355F6A3561A3C261),
   .INIT_5C(256'h94A733948E89078ED970A9D969BBD2691133221198B32B98F813EBF8E138D9E1),
   .INIT_5D(256'hDF7AA5DF2878502855FFAA55CE4987CEE920C9E9879215871E223C1E9BB62D9B),
   .INIT_5E(256'h68B8D06842C68442E631D7E6BFDA65BF0D171A0D89800989A1F859A18C8F038C),
   .INIT_5F(256'h163A2C16BBD66DBB54FCA854B0CB7BB00F111E0F2D775A2D99B0299941C38241),
   // TABLE T2 (t_fl)
   .INIT_60(256'h0000C50000006F0000006B000000F20000007B000000770000007C0000006300),
   .INIT_61(256'h000076000000AB000000D7000000FE0000002B00000067000000010000003000),
   .INIT_62(256'h0000F00000004700000059000000FA0000007D000000C900000082000000CA00),
   .INIT_63(256'h0000C000000072000000A40000009C000000AF000000A2000000D4000000AD00),
   .INIT_64(256'h0000CC000000F70000003F000000360000002600000093000000FD000000B700),
   .INIT_65(256'h00001500000031000000D800000071000000F1000000E5000000A50000003400),
   .INIT_66(256'h00009A000000050000009600000018000000C300000023000000C70000000400),
   .INIT_67(256'h000075000000B200000027000000EB000000E200000080000000120000000700),
   .INIT_68(256'h0000A00000005A0000006E0000001B0000001A0000002C000000830000000900),
   .INIT_69(256'h0000840000002F000000E300000029000000B3000000D60000003B0000005200),
   .INIT_6A(256'h00005B000000B1000000FC00000020000000ED00000000000000D10000005300),
   .INIT_6B(256'h0000CF000000580000004C0000004A00000039000000BE000000CB0000006A00),
   .INIT_6C(256'h000085000000330000004D00000043000000FB000000AA000000EF000000D000),
   .INIT_6D(256'h0000A80000009F0000003C000000500000007F00000002000000F90000004500),
   .INIT_6E(256'h0000F5000000380000009D000000920000008F00000040000000A30000005100),
   .INIT_6F(256'h0000D2000000F3000000FF0000001000000021000000DA000000B6000000BC00),
   .INIT_70(256'h00001700000044000000970000005F000000EC000000130000000C000000CD00),
   .INIT_71(256'h000073000000190000005D000000640000003D0000007E000000A7000000C400),
   .INIT_72(256'h000088000000900000002A00000022000000DC0000004F000000810000006000),
   .INIT_73(256'h0000DB0000000B0000005E000000DE00000014000000B8000000EE0000004600),
   .INIT_74(256'h00005C0000002400000006000000490000000A0000003A00000032000000E000),
   .INIT_75(256'h000079000000E4000000950000009100000062000000AC000000D3000000C200),
   .INIT_76(256'h0000A90000004E000000D50000008D0000006D00000037000000C8000000E700),
   .INIT_77(256'h000008000000AE0000007A00000065000000EA000000F4000000560000006C00),
   .INIT_78(256'h0000C6000000B4000000A60000001C0000002E0000002500000078000000BA00),
   .INIT_79(256'h00008A0000008B000000BD0000004B0000001F00000074000000DD000000E800),
   .INIT_7A(256'h00000E000000F6000000030000004800000066000000B50000003E0000007000),
   .INIT_7B(256'h00009E0000001D000000C100000086000000B900000057000000350000006100),
   .INIT_7C(256'h0000940000008E000000D9000000690000001100000098000000F8000000E100),
   .INIT_7D(256'h0000DF0000002800000055000000CE000000E9000000870000001E0000009B00),
   .INIT_7E(256'h00006800000042000000E6000000BF0000000D00000089000000A10000008C00),
   .INIT_7F(256'h000016000000BB00000054000000B00000000F0000002D000000990000004100),
    // The next set of INITP_xx are for the parity bits
    .INITP_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0F(256'h0000000000000000000000000000000000000000000000000000000000000000)) 
  RAMB36_1 (
    .CASCADEOUTLATA(             ), // 1-bit cascade A latch output
    .CASCADEOUTLATB(             ), // 1-bit cascade B latch output
    .CASCADEOUTREGA(             ), // 1-bit cascade A register output
    .CASCADEOUTREGB(             ), // 1-bit cascade B register output
    .DOA           (bram1a_data  ), // 32-bit A port data output
    .DOB           (bram1b_data  ), // 32-bit B port data output
    .DOPA          (             ), // 4-bit A port parity data output
    .DOPB          (             ), // 4-bit B port parity data output
    .ADDRA         (bram1a_addr  ), // 16-bit A port address input
    .ADDRB         (bram1b_addr  ), // 16-bit B port address input
    .CASCADEINLATA (             ), // 1-bit cascade A latch input
    .CASCADEINLATB (             ), // 1-bit cascade B latch input
    .CASCADEINREGA (             ), // 1-bit cascade A register input
    .CASCADEINREGB (             ), // 1-bit cascade B register input
    .CLKA          (CLK          ), // 1-bit A port clock input
    .CLKB          (CLK          ), // 1-bit B port clock input
    .DIA           (             ), // 32-bit A port data input
    .DIB           (             ), // 32-bit B port data input
    .DIPA          (             ), // 4-bit A port parity data input
    .DIPB          (             ), // 4-bit B port parity data input
    .ENA           (~RST         ), // 1-bit A port enable input
    .ENB           (~RST         ), // 1-bit B port enable input
    .REGCEA        (1'b1         ), // 1-bit A port register enable input
    .REGCEB        (1'b1         ), // 1-bit B port register enable input
    .SSRA          (1'b0         ), // 1-bit A port set/reset input
    .SSRB          (1'b0         ), // 1-bit B port set/reset input
    .WEA           (4'd0         ), // 4-bit A port write enable input
    .WEB           (4'd0         )  // 4-bit B port write enable input
  );

  // shift control for column 2 and 3  
  always @(posedge CLK) begin
    if (TSH[1]) bram1a_data_p <= {bram1a_data[07:00], bram1a_data[31:08]};
    else        bram1a_data_p <= bram1a_data;
    if (TSH[0]) bram1b_data_p <= {bram1b_data[07:00], bram1b_data[31:08]};
    else        bram1b_data_p <= bram1b_data;
  
    // another pipeline stage
    if (RXR[1]) bram1a_data_pp <= 0;
    else        bram1a_data_pp <= bram1a_data_p;
    if (RXR[0]) bram1b_data_pp <= 0;
    else        bram1b_data_pp <= bram1b_data_p;
    
    xor1a_pdata <= (bram1a_data_pp ^ xor0b_pdata);
    xor1b_pdata <= (bram1b_data_pp ^ xor1a_pdata);   
  end
 
endmodule
            