#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vregister.h"

#include "utils.h"

#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

void set_defaults(Vregister *dut){
    dut->clk = 0;
    dut->rst_n = 1;
    dut->load_i = 0;
    dut->d_i = 0;
}

int main(int argc, char** argv, char** env) {
    Vregister *dut = new Vregister;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    set_defaults(dut);

    while (sim_time < MAX_SIM_TIME) {
        dut->clk ^= 1;
        dut->eval();
        m_trace->dump(sim_time);
        SIGDUMP(q_o);
        sim_time++;
    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}