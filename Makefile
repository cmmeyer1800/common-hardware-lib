TOP_SRC := $(PWD)/rtl/register.sv
TB_SRC := $(PWD)/hvl/reg_tb.cpp

all: convert test
	make -C obj_dir -f Vregister.mk Vregister

convert: $(TOP_SRC)
	verilator --cc $(TOP_SRC)

test: $(TOP_SRC) $(TB_SRC)
	verilator -Wall --trace -cc $(TOP_SRC) --exe $(TB_SRC)