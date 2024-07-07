
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo.h"

#include "utils.h"

#define MAX_SIM_TIME 20 // @TODO: Update Sim Time
vluint64_t sim_time = 0;

void init_signals(Vfifo *dut){
    dut->clk = 0;
    dut->rst_n = 1;
    dut->enqueue = 0;
    dut->dequeue = 0;
    dut->data_in = 0;
}

void do_reset(Vfifo *dut, VerilatedVcdC *m_trace){
    dut->rst_n = 0;
    SETCLK(0);
    SETCLK(1);
    dut->rst_n = 1;
}

int main(int argc, char** argv, char** env) {
    Vfifo *dut = new Vfifo;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    init_signals(dut);
    do_reset(dut, m_trace);

    while (sim_time < MAX_SIM_TIME) {
        dut->clk ^= 1;
        dut->eval();
        // m_trace->dump(sim_time);

        dut->clk ^= 1;
        dut->eval();
        m_trace->dump(sim_time);

        // @TODO: Stimulate DUT Here

        sim_time++;
    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}