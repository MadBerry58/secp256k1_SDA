#include "headers/Algorithms.h"

///TODO: Implement iteration algorithms:
/*
// Iteration algorithm types
#define ITERATION_ALGORITHM_INVALID                     0u
#define ITERATION_ALGORITHM_CONTINUOUS_STEPS            1u
#define ITERATION_ALGORITHM_SLICED_STEPS                2u
#define ITERATION_ALGORITHM_CONTINUOUS_MULTIPLY         3u
#define ITERATION_ALGORITHM_CONTINUOUS_DOUBLING         4U
#define ITERATION_ALGORITHM_BTREE_SUBDIVISION           5U
*/

/**
 * @brief Checks the validity of the provided iteration parameters
 * 
 * @details The function performs 
 * 
 * @param algorithmType Specifies the algorithm type required by the user 
 * @return int 
 */
unsigned int checkIterationParams(unsigned int algorithmType, struct algorithmParams)
{
    switch (algorithmType)
    {
        case ITERATION_ALGORITHM_INVALID:
            DEBUG_MSG("Algorithm undefined\n");
            break;

        case ITERATION_ALGORITHM_SLICED_STEPS:
            DEBUG_MSG("slicedSteps algorithm selected\n");
            break;

        case ITERATION_ALGORITHM_CONTINUOUS_STEPS:
            DEBUG_MSG("continuousSteps algorithm selected\n");
            break;

        case ITERATION_ALGORITHM_CONTINUOUS_MULTIPLY:
            DEBUG_MSG("continuousMultiply algorithm selected\n");
            break;

        case ITERATION_ALGORITHM_CONTINUOUS_DOUBLING:
            DEBUG_MSG("continuousDoubling algorithm selected\n");
            break;

        case ITERATION_ALGORITHM_BTREE_SUBDIVISION:
            DEBUG_MSG("bTreeSubdivision algorithm selected\n");
            break;

        default:
            break;
    }
    return 0;
}
/**
 * @brief The function checks points by adding a fixed value each step
 * 
 * @details 
 * 
 * @return int* 
 */

unsigned int continuousSteps()
{
    DEBUG_MSG("Accessed the continuousSteps algorithm\n");
    return 0;
}

/**
 * @brief The algorithm checks points by dividing the search space into arbitrary subsegments
 * 
 * @details 
 * 
 * @return int* 
 */
unsigned int slicedSteps()
{
    DEBUG_MSG("Accessed the slicedSteps algorithm\n");
    return 0;
}

/**
 * @brief This algorithm checks points by continuously adding the target to itself
 * 
 * @return int* 
 */
unsigned int continuousMultiply()
{
    DEBUG_MSG("Accessed the continuousMultiply algorithm\n");
    return 0;
}

/**
 * @brief This algorithm checks points by continuously doubling the target
 * 
 * @return int* 
 */
unsigned int continuousDoubling()
{
    DEBUG_MSG("Accessed the continuousDoubling algorithm\n");
    return 0;
}

/**
 * @brief This algorithm checks points by continuously dividing the search subspace in half
 * 
 * @return int* 
 */
unsigned int bTreeSubdivision()
{
    DEBUG_MSG("Accessed the bTreeSubdivision algorithm\n");
    return 0;
}

/**
 * @brief This algorithm generates known points and saves the least significant bits of the X coordinate as a hash
 * 
 * @param outputFile 
 * @param startingPoint 
 * @param incrementPoint 
 * @param remainderPoint 
 * @param numberOfSlices 
 * @param pointsPerSlice 
 * @return int 
 */
unsigned int hashGeneratorIterator(std::ofstream &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice)
{
    DEBUG_MSG("Accessed the hashGeneratorIterator algorithm\n");

    for (unsigned long i = 0; i < numberOfSlices; ++i)
    {
        /// outputFile << SLICE_ << i << "\n";
        outputFile << startingPoint.getLSB() << "\n";
        for (unsigned long j = 0; j < pointsPerSlice; ++j)
        {
            startingPoint += incrementPoint;
            outputFile << startingPoint.getLSB() << "\n";
        }
        startingPoint += remainderPoint;
    }
    return 0;
}