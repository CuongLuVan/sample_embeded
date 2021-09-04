vlib work
vlog +acc  "aes32_dsp_cmac.v"
vlog +acc  "aes32_dsp_cmac_tb.v"
vlog +acc  "C:/Xilinx/10.1/ISE/verilog/src/glbl.v"
vsim -t 1ps   -L xilinxcorelib_ver -L unisims_ver -L unimacro_ver -L secureip -lib work aes32_dsp_cmac_tb glbl
run 2500ns
quit