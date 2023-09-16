#ifndef __UTILS_H__
#define __UTILS_H__

#define SIGDUMP(SIGNAME) std::cout << "[LOG] " #SIGNAME "=" << dut->SIGNAME << " @ T=" << sim_time << std::endl

#define SETCLK(VAL) do {\
        dut->clk = VAL; \
        dut->eval(); \
        m_trace->dump(sim_time); \
        sim_time++;} while(0)


#endif