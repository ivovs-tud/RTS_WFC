/* Main generated for Simulink Real-Time model wturbines */
#include <ModelInfo.hpp>
#include <utilities.hpp>
#include "rte_wturbines_parameters.h"
#include "wturbines.h"

/* Task wrapper function definitions */
void wturbines_Task1(void)
{ 
    wturbines_step0();
} 
void wturbines_Task2(void)
{ 
    wturbines_step2();
} 
void wturbines_Task3(void)
{ 
    wturbines_step3();
} 
void wturbines_Task4(void)
{ 
    wturbines_step4();
} 
/* Task descriptors */
slrealtime::TaskInfo task_1( 0u, std::bind(wturbines_Task1), slrealtime::TaskInfo::PERIODIC, 0.01, 0, 40);
slrealtime::TaskInfo task_2( 1u, std::bind(wturbines_Task2), slrealtime::TaskInfo::PERIODIC, 0.1, 0, 39);
slrealtime::TaskInfo task_3( 2u, std::bind(wturbines_Task3), slrealtime::TaskInfo::PERIODIC, 0.25, 0, 38);
slrealtime::TaskInfo task_4( 3u, std::bind(wturbines_Task4), slrealtime::TaskInfo::PERIODIC, 0.5, 0, 37);

/* Executable base address for XCP */
#ifdef __linux__
extern char __executable_start;
static uintptr_t const base_address = reinterpret_cast<uintptr_t>(&__executable_start);
#else
/* Set 0 as placeholder, to be parsed later from /proc filesystem */
static uintptr_t const base_address = 0;
#endif

/* Model descriptor */
slrealtime::ModelInfo wturbines_Info =
{
    "wturbines",
    wturbines_initialize,
    wturbines_terminate,
    []()->char const*& { return wturbines_M->errorStatus; },
    []()->unsigned char& { return wturbines_M->Timing.stopRequestedFlag; },
    { task_1, task_2, task_3, task_4 },
    slrealtime::getSegmentVector()
};

int main(int argc, char *argv[]) {
    slrealtime::BaseAddress::set(base_address);
    return slrealtime::runModel(argc, argv, wturbines_Info);
}
