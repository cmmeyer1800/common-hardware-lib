
MODULE=fifo

MOD_SRC := $(PWD)/rtl/$(MODULE).sv
TB_SRC := $(PWD)/hvl/$(MODULE)_tb.cpp

.PHONY:sim
sim: waveform.vcd

.PHONY:verilate
verilate: .stamp.verilate

.PHONY:build
build: obj_dir/V$(MODULE)

.PHONY:waves
waves: waveform.vcd
	@echo
	@echo "### WAVES ###"
	gtkwave waveform.vcd

waveform.vcd: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)

.stamp.verilate: ./rtl/$(MODULE).sv ./hvl/$(MODULE)_tb.cpp
	@echo
	@echo "### VERILATING ###"
	verilator -Wall --trace -cc ./rtl/$(MODULE).sv --exe ./hvl/$(MODULE)_tb.cpp
	@touch .stamp.verilate

.PHONY:lint
lint: ./rtl/$(MODULE).sv
	verilator --lint-only ./rtl/$(MODULE).sv

.PHONY: clean
clean:
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.vcd