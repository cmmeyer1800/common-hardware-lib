#include <queue>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo.h"

#include "utils.h"

#define RAND_RANGE(size) (rand() % (1 << size))

#define MAX_SIM_TIME 20 // @TODO: Update Sim Time
vluint64_t sim_time = 0;

void dump_fifo(Vfifo *dut){
    std::cout << "FIFO: ";
    for(int i = 0; i < 16; i++){
        std::cout << dut->mem[i] << " ";
    }
    std::cout << std::endl;
}

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
    
    // CPP queue for data validation
    std::queue<int> q;
    uint32_t data;

    init_signals(dut);
    do_reset(dut, m_trace);
    
    // Empty to begin with
    REQUIRE_EQ(dut->empty, 1);
    REQUIRE_EQ(dut->full, 0);

    // Enqueuing 1 element
    data = RAND_RANGE(31);
    dut->enqueue = 1;
    dut->data_in = data;
    SETCLK(0);
    SETCLK(1);
    q.push(data);
    REQUIRE_EQ(dut->empty, 0);
    REQUIRE_EQ(dut->full, 0);

    // Fill the fifo
    for(int i = 0; i < 15; i++){
        data = RAND_RANGE(31);
        dut->enqueue = 1;
        dut->data_in = data;
        SETCLK(0);
        SETCLK(1);
        q.push(data);
    }
    REQUIRE_EQ(dut->empty, 0);
    REQUIRE_EQ(dut->full, 1);

    // Dequeue 1 element
    dut->dequeue = 1;
    dut->enqueue = 0;
    SETCLK(0);
    SETCLK(1);
    REQUIRE_EQ(dut->data_out, q.front());
    q.pop();
    REQUIRE_EQ(dut->empty, 0);
    REQUIRE_EQ(dut->full, 0);

    // Dequeue all elements
    for(int i = 0; i < 15; i++){
        dut->dequeue = 1;
        SETCLK(0);
        SETCLK(1);
        REQUIRE_EQ(dut->data_out, q.front());
        q.pop();
    }
    REQUIRE_EQ(dut->empty, 1);
    REQUIRE_EQ(dut->full, 0);

    // Generate State
    for (int i = 0; i < 8; i++){
        data = RAND_RANGE(31);
        dut->enqueue = 1;
        dut->dequeue = 0;
        dut->data_in = data;
        SETCLK(0);
        SETCLK(1);
        q.push(data);
    }
    REQUIRE_EQ(dut->empty, 0);
    REQUIRE_EQ(dut->full, 0);

    // Simultanous enqueue and dequeue
    for(int i = 0; i < 100; i++){
        data = RAND_RANGE(31);
        dut->enqueue = 1;
        dut->dequeue = 1;
        dut->data_in = data;
        SETCLK(0);
        SETCLK(1);
        q.push(data);
        REQUIRE_EQ(dut->data_out, q.front());
        q.pop();
    }

    // Dequeue all elements
    for(int i = 0; i < 8; i++){
        dut->dequeue = 1;
        dut->enqueue = 0;
        SETCLK(0);
        SETCLK(1);
        REQUIRE_EQ(dut->data_out, q.front());
        q.pop();
    }
    REQUIRE_EQ(dut->empty, 1);
    REQUIRE_EQ(dut->full, 0);

    for(int i=0;i<5;i++) SETCLK(0); SETCLK(1);
    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);

fail_ending:
    for(int i=0;i<5;i++) SETCLK(0); SETCLK(1);
    m_trace->close();
    delete dut;
    exit(EXIT_FAILURE);
}