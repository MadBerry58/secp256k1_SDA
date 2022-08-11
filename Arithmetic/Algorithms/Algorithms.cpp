#include "Algorithms.h"

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
 * 
 * @note Algorithm design courtesy of Schitcu Mihai
 */
unsigned int bTreeSubdivision(unsigned int databaseSize, mpz_t searchPosition, unsigned int searchDepthLimit_upper, unsigned int searchDepthLimit_lower, bool *runFlag)
{
    DEBUG_MSG("Accessed the bTreeSubdivision algorithm\n");
    mpz_t segment;
    mpz_init_set_str(segment, order_String, PREFFERED_BASE);
    
    mpz_t bTreeDepthMap;
    mpz_init_set_ui(bTreeDepthMap, 0u);

    unsigned int depthMax = mpz_sizeinbase (segment, 2u);
    unsigned int depthMin = depthMax - log2(databaseSize);

    Point one(xG0_String, yG0_String, kG0_String);
    Point two(xG1_String, yG1_String, kG1_String);

    Point segments[depthMin];

    mpz_t segments_size[depthMin];
    // mpz_sub_ui(segment, segment, 1u);
    int depth = 0;
    int depthMax;

    //// Generate segment keys and tree map
    for(;depth < depthMin; ++depth)
    {
        if(mpz_odd_p(segment))
        {
            //segment is odd, divide segment by checking the middle point (segment + 1)/2
            mpz_sub_ui(segments_size[depth], segment, 1u);
            mpz_tdiv_q_2exp (segments_size[depth], segments_size[depth], 1u);
            mpz_setbit (bTreeDepthMap, depth);
        }
        else if (mpz_even_p(segment))
        {
            //segment is even, divide segment by checking the [segment/2] and [segment/2]*2 points
            mpz_sub_ui(segments_size[depth], segment, 2u);
            mpz_tdiv_q_2exp (segments_size[depth], segments_size[depth], 1u);
            // mpz_setbit (bTreeDepthMap, depth);
        }
        else
        {
            return -1; ////TODO: Create mpz error code
        }
    }

    //Generate segment point representation
    //The generation is done in reverse in order to use two additions instead of one addition and a multiplications

    segments[depth] = segments_size[depth];
    --depth;

    for(;depth > 0; --depth)
    {
        if(1u == mpz_tstbit(bTreeDepthMap, depth))
        {
            segments[depth - 1] = segments[depth];
            segments[depth]+=one;
            segments[depth]+=segments[depth - 1];

        }
        else if (0u == mpz_tstbit(bTreeDepthMap, depth))
        {
            segments[depth - 1] = segments[depth];
            segments[depth]+=two;
            segments[depth]+=segments[depth - 1];
        }
        else
        {
            return -1; ////TODO: Create mpz error code
        }
    }

    unsigned int searchDepth = mpz_sizeinbase(searchPosition, 2);

    //Build key
    //Search map: 0 - left, 1 - right
    //

    mpz_t resumeKey;
    mpz_init_set_ui(resumeKey, 0u);

    unsigned int gap_size = 0;
    int runningDepth = depth;

    for(; runningDepth < searchDepth; ++runningDepth)
    {
        if (1u == mpz_tstbit(searchPosition, runningDepth))
        {
            //right branch. add the segment to the resumeKey
            mpz_add_ui(resumeKey, segments_size[runningDepth], mpz_odd_p(segments_size[runningDepth-1]));
        }
        
        else if(0u == mpz_tstbit(searchPosition, runningDepth))
        {
            //left branch, don't add anything to the previous number 
        }

        else
        {
            return -1; ////TODO: Create mpz error code
        }
    }

    #define LEFT  0
    #define RIGHT 1
    #define EVEN  0
    #define ODD   1

    Point           R;
    Point           gappedSegments[2 * depthMax];


    mpz_t           parityBitset;
    mpz_init_set_ui(parityBitset, 1);

    mpz_t           comParityBitset;
    mpz_init_set_ui(comParityBitset, 1);// complementary parity bitset is pre generated to avoid a complement action each step regenerating

    mpz_t           branchBitset;
    mpz_init_set_ui(branchBitset, 1);
    
    
    mpz_t           fullMask;
    mpz_init        (fullMask);
    mpz_setbit      (fullMask, depthMax);
    mpz_sub_ui      (fullMask, fullMask, 1);

    // mpz_t           currentPositionBitset;
    // mpz_init        (currentPositionBitset);


    mpz_t           minDepthMask;
    mpz_init        (minDepthMask);
    mpz_div_2exp    (minDepthMask, fullMask, (depthMax - depthMin));

    mpz_t           outOfBandMasks[depthMin];


    mpz_t           maskContainer1;
    mpz_init_set_ui(maskContainer1, 0);

    mpz_t           maskContainer2;
    mpz_init_set_ui(maskContainer2, 0);

    mpz_t           ascendMasks[depth];
    mpz_t           descendMasks[depth];

    mpz_t           searchBandMask;
    mpz_init        (searchBandMask);
    mpz_mul_2exp    (searchBandMask, fullMask, depthMin);
    mpz_and         (searchBandMask, searchBandMask, minDepthMask);

    mpz_and         (maskContainer1, searchBandMask, parityBitset);
    bool            evenNodesAbsent = mpz_cmp_ui(maskContainer1, 0lu);
    int             outOfBand_JumpDepth = ( (evenNodesAbsent * (depthMax - 1)) + (!evenNodesAbsent * (depthMin + mpz_scan0(parityBitset, depthMin))) );
    int             outOfBand_gap;

    mpz_t           addNodesBitset;
    mpz_init        (addNodesBitset); // Since the branch bitset is not changed until the last step, an intersection of the comParityBitset and branchBitset in the last step can remove the bit checks
    
    while(depth > -1)
        if(depth < depthMax) //node is not terminal
        {
            if(mpz_tstbit(addNodesBitset,depth))
            {
                R += gappedSegments[gap_size];  //compute point addition
                gap_size = 0;                   //reverse gap to G
            }
            depth++;                            //step down
        }
        else //node is terminal
        {
            mpz_com(maskContainer1, branchBitset);      //reverse bitset to remove leading bits
            depth = mpz_sizeinbase(maskContainer1, 2);  //determine the most significant bit (former most significant 0 bit, lowest unvisited branch)
            mpz_com(maskContainer1, branchBitset);      //reverse bitset to restore initial data while leaving out the initial trailing bits
            mpz_setbit(branchBitset, depth);            //set current node as visited
            mpz_ior(addNodesBitset, comParityBitset, branchBitset); //regenerate the addNodesBitset

            if(depth < depthMin)
            {
                mpz_and(maskContainer1, outOfBandMasks[depth], addNodesBitset); // isolate the bits representing nodes that need to be added from the current depth to min depth
                gap_size += mpz_popcount(maskContainer1) + (evenNodesAbsent * depthMax);
                //compute the out of band gap by adding the number of nodes computed previously
                //in case nu even nodes are inside the search gap, add maxDepth (representing segment * 2 + n) to the gap; otherwise, just add 1
                //since odd nodes 
            }


        }
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