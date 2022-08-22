#include "CoordinatorSM.h"
#include "../../../../Arithmetic/Arithmetic.h"

unsigned int init_CoordinatorSM(CoordinatorSMStruct *data)
{   
    void         **initArgs   = nullptr;
    unsigned int   initArgs_no = 0u;

    //initialize coordinatorSM
        //establish connection to memory manager - initialize buffers for result storage
        //establish connection to network manager - associate a clientSM for data output
        //establish connection to file manager - create a file stream buffer for saving constant data and checkpoint
    
    /*To be moved to IterationManager*/
    switch(data->chosenAlgorithm)
    {
        case ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS:
            init_continuousSteps();
            break;

        case ITERATOR_SM_ALGORITHM_SLICED_STEPS:
            init_slicedSteps();
            break;

        case ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY:
            init_continuousMultiply();
            break;

        case ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING:
            init_continuousDoubling();
            break;

        case ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION:
            init_bTreeSubdivision(initArgs, initArgs_no);
            break;

        default:
            return THREAD_MGR_E_UNKNOWN_ALGORITHM;
    }
    /*To be moved to IterationManager*/

    switch (data->distribution)
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

    return 0;
}

unsigned int CoordinatorSM(CoordinatorSMStruct *data)
{
    return 0;
}