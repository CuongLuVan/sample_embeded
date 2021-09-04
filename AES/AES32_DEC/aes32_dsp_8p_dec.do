vlib work
vlog +acc  "aes32_dsp_8p.v"
vlog +acc  "aes32_dsp_8p_tb.v"
vlog +acc  "C:/Xilinx/10.1/ISE/verilog/src/glbl.v"
vsim -t 1ps   -L xilinxcorelib_ver -L unisims_ver -L unimacro_ver -L secureip -lib work aes32_dsp_8p_tb glbl
run 45000ns
quit

