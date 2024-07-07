#ifndef __UTILS_H__
#define __UTILS_H__

#define SIGDUMP(SIGNAME) std::cout << "[LOG] " #SIGNAME "=" << dut->SIGNAME << " @ T=" << sim_time << std::endl
#define SETCLK(VAL) do {\
        dut->clk = VAL; \
        dut->eval(); \
        m_trace->dump(sim_time); \
        sim_time++;} while(0)

#define REQUIRE_EQ(ARG1, ARG2) do {      \
        if(ARG1 == ARG2){               \
                std::cout << "\x1b[1;32m[PASSED]\x1b[0m ASSERT(" #ARG1 " == " #ARG2 ") :: (" << ARG1 << " == " << ARG2 << ") [" << __FILE__ << "," << __LINE__ << "]" << std::endl; \
        } else {                \
                std::cout << "\x1b[1;31m[FAILED]\x1b[0m ASSERT(" #ARG1 " == " #ARG2 ") :: (" << ARG1 << " != " << ARG2 << ") [" << __FILE__ << "," << __LINE__ << "]" << std::endl; \
                goto fail_ending;       \
        }                       \
        } while(0)

#define REQUIRE_NEQ(ARG1, ARG2) do {    \
        if(ARG1 != ARG2){               \
                std::cout << "\x1b[1;32m[PASSED]\x1b[0m ASSERT(" #ARG1 " != " #ARG2 ") :: (" << ARG1 << " != " << ARG2 << ")" << std::endl; \
        } else {                        \
                std::cout << "\x1b[1;31m[FAILED]\x1b[0m ASSERT(" #ARG1 " != " #ARG2 ") :: (" << ARG1 << " == " << ARG2 << ")" << std::endl; \
                goto fail_ending;      \
        }                               \
        } while(0)

#endif