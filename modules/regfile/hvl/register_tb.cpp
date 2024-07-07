#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vregfile.h"

#include "utils.h"

#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

void set_defaults(Vregfile *dut){
    dut->clk = 0;
    dut->rst_n = 1;
    dut->load_i = 0;
    dut->d_i = 0;
}

int main(int argc, char** argv, char** env) {
    Vregfile *dut = new Vregfile;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    set_defaults(dut);

    dut->rst_n = 0;
    SETCLK(1);
    dut->rst_n = 1;
    SETCLK(0);

    for(uint32_t i = 0; i < 1000; i++){
        dut->d_i = i*4096;
        dut->load_i = 1;

        SETCLK(1);
        dut->load_i = 0;

        // SIGDUMP(q_o);
        REQUIRE_EQ(dut->q_o, i*4096);

        SETCLK(0);
    }

    dut->d_i = 123456;
    dut->load_i = 1;
    SETCLK(1);
    dut->load_i = 0;
    dut->rst_n = 0;
    SETCLK(0);

    SETCLK(1);

    dut->rst_n = 1;

    SETCLK(0);

    assert(dut->q_o == 0);

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
