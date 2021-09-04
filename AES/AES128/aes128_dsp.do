vlib work
vlog +acc  "aes128_dsp.v"
vlog +acc  "aes128_dsp_tb.v"
vlog +acc  "C:/Xilinx/10.1/ISE/verilog/src/glbl.v"
vsim -t 1ps   -L xilinxcorelib_ver -L unisims_ver -L unimacro_ver -L secureip -lib work aes128_dsp_tb glbl
run 54400ns
quit
