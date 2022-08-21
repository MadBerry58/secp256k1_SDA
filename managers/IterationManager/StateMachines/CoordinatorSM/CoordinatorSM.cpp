#include "CoordinatorSM.h"

unsigned int CoordinatorSM()
{   
    //initialize coordinatorSM
        //establish connection to memory manager - initialize buffers for result storage
        //establish connection to network manager - associate a clientSM for data output
        //establish connection to file manager - create a file stream buffer for saving constant data and checkpoint
    unsigned int workerNumber;
    unsigned int iterationAlgorithm; 
    unsigned int workloadDistribution;
    unsigned int workerBufferSize;

    // workerParameters workerParams[workerNumber]; 

    Point workerBuffers[workerNumber][workerBufferSize];

    unsigned int (*usedAlgorithm)();

    
    switch(iterationAlgorithm)
    {
        case ITERATION_ALGORITHM_CONTINUOUS_STEPS:
            usedAlgorithm = &continuousSteps;
            break;

        case ITERATION_ALGORITHM_SLICED_STEPS:
            usedAlgorithm = &slicedSteps;
            break;

        case ITERATION_ALGORITHM_CONTINUOUS_MULTIPLY:
            usedAlgorithm = &continuousMultiply;
            break;

        case ITERATION_ALGORITHM_CONTINUOUS_DOUBLING:
            usedAlgorithm = &continuousDoubling;
            break;

        default:
            return THREAD_MGR_E_UNKNOWN_ALGORITHM;

    switch (workloadDistribution)
    {
        case WORKLOAD_DISTRIBUTION_SYNCED:
            /* Each worker thread starts at startingPoint + (step * index) */
            break;

        case WORKLOAD_DISTRIBUTION_SLICED:
            /* Each worker thread starts at startingPoint + (sliceNo * sliceSize) */
            break;

        case WORKLOAD_DISTRIBUTION_SCATTERED:
            /* Each worker thread starts at startingPoint + preffered offset */
            break;
        
        default:
            return THREAD_MGR_E_UNKNOWN_MEM_DISTRIBUTION;
    }


    }
    for(unsigned int i = 0; i < workerNumber; ++i)
    {
        // workerParams[i].buffer = workerBuffers[i]; ///assign the buffer pointer to the worker parameter object
    }
    return 0;
}