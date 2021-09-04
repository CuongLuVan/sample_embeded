vlib work
vlog +acc  "aes128_dsp_u.v"
vlog +acc  "aes128_dsp_u_tb.v"
vlog +acc  "C:/Xilinx/10.1/ISE/verilog/src/glbl.v"
vsim -t 1ps   -L xilinxcorelib_ver -L unisims_ver -L unimacro_ver -L secureip -lib work aes128_dsp_u_tb glbl
run 545ns
quit

