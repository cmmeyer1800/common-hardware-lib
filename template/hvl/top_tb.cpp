{# template/hvl/tob_tb.cpp #}
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "V{{ mod_name }}.h"

#include "utils.h"

#define MAX_SIM_TIME 20 // @TODO: Update Sim Time
vluint64_t sim_time = 0;

void init_signals(V{{ mod_name }} *dut){
    // @TODO: SPECIFY DUT INITIAL SIGNAL VALUES HERE
}

int main(int argc, char** argv, char** env) {
    V{{ mod_name }} *dut = new V{{ mod_name }};

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    init_signals(dut);

    while (sim_time < MAX_SIM_TIME) {
        // dut->clk ^= 1;
        dut->eval();
        m_trace->dump(sim_time);

        // @TODO: Stimulate DUT Here

        sim_time++;
    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
