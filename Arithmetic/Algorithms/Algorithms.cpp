#include "Algorithms.h"

#define BTREE_BITMASKED // allows for tweaking and testing the functionality of the BTree iterator
#ifdef  BTREE_BITMASKED
//  #define BTREE_BITMASKED_STANDARD
 #define BTREE_BITMASKED_EXPERIMENTAL
#endif

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

#define LEFT  0
#define RIGHT 1
#define EVEN  0
#define ODD   1
/**
 * @brief Checks the validity of the provided iteration parameters
 * 
 * @details The function performs 
 * 
 * @param algorithmType Specifies the algorithm type required by the user 
 * @return int 
 */
unsigned int checkAlgorithmParams(IteratorSM_struct iteratorData)
{
    switch (iteratorData.algorithm)
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

unsigned int init_continuousSteps()
{
    DEBUG_MSG("Accessed the continuousSteps initializer\n");
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


unsigned int init_slicedSteps()
{
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

unsigned int init_continuousMultiply()
{
    DEBUG_MSG("Accessed the continuousMultiply initializer\n");
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

unsigned int init_continuousDoubling()
{
    DEBUG_MSG("Accessed the continuousDoubling initializer\n");
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

unsigned int init_bTreeSubdivision(void **args, unsigned int arg_no)
{
    DEBUG_MSG("Accessed the algorithm\n");
    static bool constDataInitialized;
    
    unsigned int databaseSize = *(unsigned int*)(args[0]);
    unsigned int depthMin     = *(unsigned int*)(args[1]);
    unsigned int depthMax     = *(unsigned int*)(args[2]);
    bool         evenNodesAbsent;                                           /* Flag indicating the presence of even nodes inside the search gap */
    int          depth               = 0;                                   /* variable used for indicating the current tree depth during the iteration*/
    int          bandWidth;
    int          outOfBand_JumpDepth;
    mpz_t        parityBitset;
    mpz_t        fullMask;
    mpz_t        segmentSize;
    mpz_t        branchBitset;
    mpz_t        minDepthMask;
    mpz_t        searchBandMask;
    mpz_t        maskContainer1;
    mpz_t        maskContainer2;
    mpz_t        addNodesBitset;
    mpz_t        comParityBitset;
    mpz_t        outOfBandMasks    [depthMin];                              /* generate masks for the bit distance between the minDepth and the current highest node*/ 
    Point        one               (xG0_String, yG0_String, kG0_String);    /* point G0 is generated for later use */
    Point        two               (xG1_String, yG1_String, kG1_String);    /* point G1 is generated for later use */
    Point        gappedSegments    [(depthMin + 2)];                        /* an extra container slot is added for holding (segment) */
    mpz_set_str( branchBitset,     (const char*)(args[3]), PREFFERED_BASE);

    /* Generate constant iteration data */
    /* All the operations in this area will be done only once*/
    /* Extract data and generate order specific iteration structures*/
    bandWidth = (depthMax - depthMin);                      /* the number of levels for which the points will be computed */
    mpz_init_set_str(parityBitset, order_String, PREFFERED_BASE); /*parity bitset is equivalent to the number bit representation*/
    mpz_init(comParityBitset); mpz_com(comParityBitset, parityBitset); /* complementary parity bitset is reversed for later use */
    mpz_init_set_str(segmentSize, orderMinusOneDivTwo_String, PREFFERED_BASE);
    mpz_init(fullMask);                         /* Bitmask covering the full search depth*/
    
    /* Generate the necessary bitmasks */
    mpz_setbit(fullMask, depthMax);                                     /* Set fullMask to 2^depthMax */
    mpz_sub_ui(fullMask, fullMask, 1ul);                                /* Set fullMask to 2^depthMax - 1 */
    mpz_init(minDepthMask);                     /* Bitmask covering the bits from 0 to minDepth*/
    mpz_div_2exp(minDepthMask, fullMask, bandWidth); /*right shift the full mask with bandWidh places*/
    mpz_init(searchBandMask);                   /* Bitmask covering the bits from minDepth to maxDepth*/
    mpz_xor(searchBandMask, fullMask, minDepthMask); /*xor the full mask and the minDepthMask to get the new mask*/
    mpz_init_set(outOfBandMasks[depth], fullMask);                      /* if iteration is on node 0, all the nodes from minDepth to 0 are considered */
    for(; depth < depthMin; ++depth)                    
    {
        mpz_init_set(outOfBandMasks[depth], outOfBandMasks[depth + 1]); /* initiate the next mask with the value of the current one */
        mpz_clrbit(outOfBandMasks[depth + 1], depth);                   /* reset the bit representing the current position from the next mask */
    }/* Final mask of depthMin should be an empty bitmask */
    mpz_init(maskContainer1);                    /* temporary container */
    mpz_init(maskContainer2);                    /* temporary container - variables are initialized with 0*/
    mpz_init(addNodesBitset);                    /* container variable representing the nodes that should be considered when outside the search band */
    mpz_xor(maskContainer1, searchBandMask, comParityBitset);           /* check if any even nodes are inside the search gap */
    evenNodesAbsent = (0ul == (mpz_cmp_ui(maskContainer1, 0lu)));       /* if no even nodes are found, set the flag as TRUE*/
    /* Determine the depth at which the first point computation will occur after reentering the search band */
    /* If no even nodes are present, the next jump depth is going to be depthMin. Otherwise, the next jump depth will be the first even node after depthMin */

    outOfBand_JumpDepth = ( (evenNodesAbsent * depthMax) + (!evenNodesAbsent * (depthMin + mpz_scan0(parityBitset, depthMin))) );
    mpz_div_2exp(segmentSize,parityBitset, depthMin);                   /* Right shift the order to get the necessary segment */
    gappedSegments[depthMin + evenNodesAbsent] = segmentSize;           /* Generate the last points to be used on the terminal nodes */
    gappedSegments[0] = one;                                            /* Save the unaltered segment size in the last element of the array */
    gappedSegments[0].addPoint(gappedSegments[1], gappedSegments[depthMin + evenNodesAbsent]);
    if(evenNodesAbsent)
    {
        gappedSegments[1] += gappedSegments[depthMin + evenNodesAbsent];
    }

    for(depth = 1; depth < depthMin; ++depth)
    {
        gappedSegments[depth - 1].addPoint(gappedSegments[depth], one);
    }
    return 0;
}

/**
 * @brief This algorithm checks points by continuously dividing the search subspace in half
 * @param databaseSize  
 * @param depthMin      
 * @param depthMax      
 * @param depth         
 * @param position      
 * @param runFlag       
 * 
 * @return int*         
 * 
 * @note Algorithm design courtesy of Schitcu Mihai
 * @note Although the initial implementation was designed with recursive operation in mind, in order to preserve CPU resources, 
 * as well as allow custom operability.
 * The implementation was redesigned to use loop states and pre-generated variables where possible, in order to
 * decouple part of the computational complexity from the user's given parameters, in order to mitigate some of the effects of exponential growth. 
 */
unsigned int bTreeSubdivision(void **args, unsigned int arg_no)
{
    mpz_t          maskContainer1;  
    mpz_t          maskContainer2;  
    mpz_t          addNodesBitset;  
    mpz_t          branchBitset;
    Point          R;
    unsigned int   databaseSize        = *(unsigned int*)(args[0] );
    unsigned int   depthMin            = *(unsigned int*)(args[1] );
    unsigned int   depthMax            = *(unsigned int*)(args[2] );
    bool          *runFlag             =  (bool*)        (args[3] );
    int            depth               = *(int*)         (args[4] ); /* variable used for indicating the current tree depth during the iteration*/
    int            gap_size            = *(int*)         (args[5] ); /* the gap size left by computing points on the layers above the current depth */
    mpz_t         *comParityBitset     =  (mpz_t*)       (args[6] );
    mpz_t        **outOfBandMasks      =  (mpz_t**)      (args[7] ); /* generate masks for the bit distance between the minDepth and the current highest node*/ 
    Point         *one                 =  (Point*)       (args[10]);
    Point        **gappedSegments      =  (Point**)      (args[11]); /* an extra container slot is added for holding (segment) */
    int            outOfBand_JumpDepth = *(int*)         (args[12]);
    mpz_set_str   (branchBitset,          (const char*)  (args[13]), PREFFERED_BASE);


    // Standard BTree bitmasked iterator
    #ifdef BTREE_BITMASKED_STANDARD
    while(depth > -1) /* as long as the end of the iteration has not been reached*/
    ////TODO: replace with a precalculated number of steps, and/or make loop dependent on outside control
    ////OBS:  if no stopping mechanism is provided, the algorithm could in theory loop around the search bamd and start the calculations again, with an offset 
    {
        if(depth == depthMax) /* node is terminal*/
        {/*to optimize the number of operations (namely the reassignment of gap_size), terminal nodes will also do a point computation, by calculating the jumps and landing on the node after the first addition */
            mpz_com(maskContainer1, branchBitset);                  /* reverse bitset to remove leading bits */
            depth = mpz_sizeinbase(maskContainer1, 2);              /* determine the most significant bit (former most significant 0 bit, lowest unvisited branch) */
            mpz_com(maskContainer1, branchBitset);                  /* reverse bitset to restore initial data while leaving out the initial leading bits */
            mpz_setbit(branchBitset, depth);                        /* set current node as visited */
            mpz_ior(addNodesBitset, comParityBitset, branchBitset); /* regenerate the addNodesBitset */
            gap_size = 1u;
            if(depth < depthMin) /* next unvisited branch is outside search band*/
            {
                mpz_and(maskContainer1, outOfBandMasks[depth], addNodesBitset); /* isolate the bits representing nodes that need to be added from the current depth to min depth */
                gap_size += mpz_popcount(maskContainer1); /* count the number of gaps that have to be added to the jump (accounting for the reentry node as well)*/
                depth = outOfBand_JumpDepth; /*set depth on the search band reentry depth*/
            }
            R += gappedSegments[depth];
        }
        else if(mpz_tstbit(addNodesBitset,depth)) /* node is not terminal*/
        {
            R += one;  /* compute point addition*/
            ////TODO: encapsulate the point computation call to allow for registration of the point without increasing the code volume
        }
        depth++; /* step down*/
    }
    #endif //BTREE_BITMASKED_STANDARD

    // Experimental BTree bitmasked iterator
    #ifdef BTREE_BITMASKED_EXPERIMENTAL
    if(depthMax < depth)
    {
        DEBUG_MSG("depth is not in a valid range");
    }

    while(depth > -1) /* as long as the end of the iteration has not been reached */
    ////TODO: replace with a precalculated number of steps, and/or make loop dependent on outside control
    ////OBS:  if no stopping mechanism is provided, the algorithm could in theory loop around the search bamd and start the calculations again, with an offset 
    {
      if(depth == depthMax) /* node is terminal*/
      {/* to optimize the number of operations (namely the reassignment of gap_size), terminal nodes will also do a point computation, by calculating the jumps and landing on the node after the first addition */
        mpz_com(maskContainer1, branchBitset);                  /* reverse bitset to remove leading bits */
        depth = mpz_sizeinbase(maskContainer1, 2);              /* determine the most significant bit (former most significant 0 bit, lowest unvisited branch) */
        mpz_com(maskContainer1, branchBitset);                  /* reverse bitset to restore initial data while leaving out the initial leading bits */
        mpz_setbit(branchBitset, depth);                        /* set current node as visited */
        mpz_ior(addNodesBitset, *comParityBitset, branchBitset);/* regenerate the addNodesBitset */
        gap_size = 1u;                                          /* at least one gap is needed */
        if(depth < depthMin)                                    /* next unvisited branch is outside search band*/
        {
            mpz_and(maskContainer1, *outOfBandMasks[depth], addNodesBitset); /* isolate the bits representing nodes that need to be added from the current depth to min depth */
            gap_size += mpz_popcount(maskContainer1); /* count the number of gaps that have to be added to the jump (accounting for the reentry node as well)*/
            depth = outOfBand_JumpDepth; /*set depth on the search band reentry depth*/
        }
        R += *gappedSegments[depth];
      }
      else if(mpz_tstbit(addNodesBitset,depth)) /* node is not terminal*/
      {
        R += *one;  /* compute point addition*/
        ////TODO: encapsulate the point computation call to allow for registration of the point without increasing the code volume
      }
      depth++; /* step down*/
    }
    #endif //BTREE_BITMASKED_EXPERIMENTAL


    // BTree implemented using pre generated 'for' loops
    #ifdef BTREE_FORLOOPED

    #endif //BTREE_FORLOOPED


    // BTree implemented using recursive implementation
    #ifdef BTREE_RECURSIVE

    #endif //BTREE_RECURSIVE

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