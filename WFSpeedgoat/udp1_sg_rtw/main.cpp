/* Main generated for Simulink Real-Time model udp1 */
#include <ModelInfo.hpp>
#include <utilities.hpp>
#include "rte_udp1_parameters.h"
#include "udp1.h"

/* Task wrapper function definitions */
void udp1_Task1(void)
{ 
    udp1_step0();
} 
void udp1_Task2(void)
{ 
    udp1_step1();
} 
/* Task descriptors */
slrealtime::TaskInfo task_1( 0u, std::bind(udp1_Task1), slrealtime::TaskInfo::PERIODIC, 0.1, 0, 40);
slrealtime::TaskInfo task_2( 1u, std::bind(udp1_Task2), slrealtime::TaskInfo::PERIODIC, 0.5, 0, 39);

/* Executable base address for XCP */
#ifdef __linux__
extern char __executable_start;
static uintptr_t const base_address = reinterpret_cast<uintptr_t>(&__executable_start);
#else
/* Set 0 as placeholder, to be parsed later from /proc filesystem */
static uintptr_t const base_address = 0;
#endif

/* Model descriptor */
slrealtime::ModelInfo udp1_Info =
{
    "udp1",
    udp1_initialize,
    udp1_terminate,
    []()->char const*& { return udp1_M->errorStatus; },
    []()->unsigned char& { return udp1_M->Timing.stopRequestedFlag; },
    { task_1, task_2 },
    slrealtime::getSegmentVector()
};

int main(int argc, char *argv[]) {
    slrealtime::BaseAddress::set(base_address);
    return slrealtime::runModel(argc, argv, udp1_Info);
}
