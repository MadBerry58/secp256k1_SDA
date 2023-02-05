#ifndef ITERATOR_H
#define ITERATOR_H

#include "Iterator_Types.h"

unsigned int Iterator_create        (IteratorSM_struct &iteratorInstance);
unsigned int Iterator_init          (IteratorSM_struct &iteratorInstance);
unsigned int Iterator_checkForEvents(IteratorSM_struct &iteratorInstance);
unsigned int Iterator_run_Algorithm (IteratorSM_struct &iteratorInstance); ///TODO: decide if number of steps should be an argument or a struct element
unsigned int Iterator_pause         (IteratorSM_struct &iteratorInstance);
unsigned int Iterator_resume        (IteratorSM_struct &iteratorInstance);
unsigned int Iterator_shutdown      (IteratorSM_struct &iteratorInstance);
unsigned int Iterator_reset_sm      (IteratorSM_struct &iteratorInstance);

unsigned int Iterator_notifyHandler (IteratorSM_struct &iteratorInstance, IteratorSM_output);

#endif // ITERATOR_H

/**
 * @note On constant memory initialization
 * 
 * Given that the core functionality of the program is bottlenecked by the modular arithmetic processing bandwith
 * of the processors, there will be a finite return on multiple thread investment, as the same number of modular
 * calculations can be done, regardless of active threads. (testing needed!!!)
 * As such, the memory costs for efficient iteration also becomes finite, with trivial memory requirements (an upper limit of ~200MB)
 * for the worst case scenario.
 * 
 * This allows for performance improvements by statically allocating the required buffers at compile time, drastically reducing overhead time.
 * 
 * To implement this, a macro config file is prefferable, to allow for easy tuning:
 * 
 * Compile static version with default config file and "final" flag off.
 * Run static version, and allow to run for detecting the hangups.
 *  Program generates a new macro config file, with tuned parameters.
 * Recompile program with new macro config file.
 * Repeat the process until the "final" flag is set inside the macro file
 * 
 * A compromise between the two methods is the use of buffer pools. Since most buffer mpz containers are standard in size (256 / limbSize + limb),
 * they could be preallocated at compile time, improving access time by having the adresses inside the CPU registry. 
 * This method still preserves some of the overhead time, as pointers refferences will still require the adress parsing.
 * 
 * A hybrid method would be to have both compile time and runtime implementations inside the code, using the previously mentioned config file
 * to specify the variable initialization type. The main initialization types would be CONSTANT, RUNTIME and POOLED.
 * This approach requires the most amount of work, but alows for the most flexibility.
 * Coupled with a scripting language like python and/or bash, this approach could allow for automatic calibration of the necessary parameters.
 * 
 * @note CUDA: to be analyzed
 */