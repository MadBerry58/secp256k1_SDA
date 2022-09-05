#include "FileManager.h"
#include "../../Arithmetic/ModularArithmetic/Mod.h"
#include "../Ports.h"
/*
    fileManager.cpp
    Provides the functionality for saving, loading and checking files used by the program
    Further work: Join generator functions into a single instance by implementing function pointers
                  Consider merging integrity checking into the reader functions
*/
#define FILE_PORT_BUFFER_SIZE 5u
FileManagerData fileManagerDataStructure;

extern mpz_t orderHalf;
mpz_t temp;
mpz_t incrementSizeContainer;
mpz_t sliceSizeContainer;
mpz_t sliceRemainderContainer;
Point tempPoint;
Point containerPoint;
Point remainderPoint;
std::ofstream tempOutput;
std::ifstream tempInput;

unsigned int init_FileManager(FileManagerData *fileManagerStruct)
{
    initPort(&(fileManagerDataStructure.fileManagerRxPort), FILE_PORT_BUFFER_SIZE);

    unsigned long errorNo = 0;
    tempPoint.reset();
    remainderPoint.reset();
    containerPoint.reset();
    mpz_init(temp);
    mpz_init(incrementSizeContainer);
    mpz_init(sliceSizeContainer);
    mpz_init(sliceRemainderContainer);

    ///TODO: implement fileManager initialization checking

    tempOutput.open("HashedGeneratedTest.sda", std::ofstream::trunc);
    if (!tempOutput.is_open())
    {
        DEBUG_MSG("Could not create hash test generation file\n");
        return INTEGRITY_E_INIT_COULDNOTOPENFILE;
    }

    mpz_mdiv_ui(sliceSizeContainer, orderHalf, TEST_GENERATED_SLICE_NUMBER);
    mpz_set_str(incrementSizeContainer, TEST_GENERATED_INCREMENTSIZE, PREFFERED_BASE);
    generateHashedPointsFile(tempOutput, containerPoint, TEST_GENERATED_POINT_NUMBER, TEST_GENERATED_SLICE_NUMBER, TEST_GENERATED_POINTS_PER_SLICE, sliceSizeContainer, incrementSizeContainer);
    tempOutput.close();

    DEBUG_MSG("Hash file generated successfully\n");

    tempOutput.open("UncompressedGeneratedTest.sda", std::ofstream::trunc);
    if (!tempOutput.is_open())
    {
        DEBUG_MSG("Could not create uncompressed test generation file\n");
        return INTEGRITY_E_INIT_COULDNOTOPENFILE;
    }

    mpz_mdiv_ui(sliceSizeContainer, orderHalf, TEST_GENERATED_SLICE_NUMBER);
    mpz_set_str(incrementSizeContainer, TEST_GENERATED_INCREMENTSIZE, PREFFERED_BASE);
    generateUncompressedPointsFile(tempOutput, containerPoint, TEST_GENERATED_POINT_NUMBER, TEST_GENERATED_SLICE_NUMBER, TEST_GENERATED_POINTS_PER_SLICE, sliceSizeContainer, incrementSizeContainer);
    tempOutput.close();

    DEBUG_MSG("Uncompressed file generated successfully\n");


    tempOutput.open("CheckpointTest.sda", std::ofstream::trunc);
    if (!tempOutput.is_open())
    {
        DEBUG_MSG("Could not create checkpoint generation file\n");
        return INTEGRITY_E_INIT_COULDNOTOPENFILE;
    }

    mpz_t dummyKey;
    mpz_init(dummyKey);
    generateRandomKey(dummyKey);
    Point dummyTarget(dummyKey);

    srandom(time(NULL));
    unsigned long dummyIterationNumber = random();

    unsigned long dummyNumberOfSlices = random();

    unsigned long dummyPointsPerSlice = random();

    mpz_t dummyIncrementSize;
    mpz_init_set_ui(dummyIncrementSize, random());
    

    mpz_t dummySliceSize;
    mpz_init(dummySliceSize);
    mpz_mdiv_ui(dummySliceSize, orderHalf, dummyNumberOfSlices);
    
    mpz_t dummyCheckoutKey;
    mpz_init_set(dummyCheckoutKey, dummyKey);
    mpz_addmul_ui(dummyCheckoutKey, dummyIncrementSize, dummyIterationNumber);

    DEBUG_MSG("\nDummy checkout key: %Zx\n\n", dummyCheckoutKey);


    Point dummyCheckout(dummyCheckoutKey);

    DEBUG_MSG("\nGenerated dummyTarget K: %s\n", dummyTarget.getK());
    DEBUG_MSG("Generated dummyTarget X: %s\n", dummyTarget.getX());
    DEBUG_MSG("Generated dummyTarget Y: %s\n", dummyTarget.getY());
    DEBUG_MSG("Generated dummyCheckout K: %s\n", dummyCheckout.getK());
    DEBUG_MSG("Generated dummyCheckout X: %s\n", dummyCheckout.getX());
    DEBUG_MSG("Generated dummyCheckout Y: %s\n", dummyCheckout.getY());
    DEBUG_MSG("Generated dummyIterationNumber: %x\n", dummyIterationNumber);
    DEBUG_MSG("Generated dummyNumberOfSlices: %x\n", dummyNumberOfSlices);
    DEBUG_MSG("Generated dummyPointsPerSlice: %x\n", dummyPointsPerSlice);
    DEBUG_MSG("Generated dummySliceSize: %Zx\n", dummySliceSize);
    DEBUG_MSG("Generated dummyIncrementSize: %Zx\n", dummyIncrementSize);
    mpz_mul_ui(temp, dummyIncrementSize, dummyIterationNumber);
    DEBUG_MSG("Generated total iteration size: %Zx\n\n", temp);

    if ((errorNo = generate_file_checkpoint(tempOutput, dummyTarget, dummyCheckout, dummyIterationNumber, dummyNumberOfSlices, dummyPointsPerSlice, dummySliceSize, dummyIncrementSize)) != CHECKPOINT_E_OK)
    {
        DEBUG_MSG("Checkpoint file generation failed with error code %d", errorNo);
    }
    tempOutput.close();
    
    DEBUG_MSG("Checkpoint file generated successfully\n");
    tempInput.open("CheckpointTest.sda");
    if (!tempInput.is_open())
    {
        DEBUG_MSG("Could not open checkpoint file\n");
        return INTEGRITY_E_INIT_COULDNOTOPENFILE;
    }

    Point dummyOutputTarget;
    Point dummyOutputCheckout;
    mpz_t dummyOutputSliceSize;
    mpz_t dummyOutputIncrementSize;
    mpz_init(dummyOutputSliceSize);
    mpz_init(dummyOutputIncrementSize);
    unsigned long dummyOutputIterationNumber;
    unsigned long dummyOutputNumberOfSlices;
    unsigned long dummyOutputPointsPerSlice;

    if ((errorNo = checkIntegrity_file_checkpoint(tempInput, dummyOutputTarget, dummyOutputCheckout, dummyOutputIterationNumber, dummyOutputNumberOfSlices, dummyOutputPointsPerSlice, dummyOutputSliceSize, dummyOutputIncrementSize, true)) != INTEGRITY_E_OK)
    {
        DEBUG_MSG("Checkpoint reading failed with code %d\n", errorNo);
        return INTEGRITY_E_READ_CHECKPOINT;
    }
    tempOutput.close();
    DEBUG_MSG("Checkpoint file read successfully\n");

    ///Implement checking error codes
    if      (!(dummyTarget == dummyOutputTarget))
    {
        DEBUG_MSG("Target not matching\n");
        return INTEGRITY_E_FILE_INIT_MISMATCHED_TARGET;
    }
    if (!(dummyCheckout == dummyOutputCheckout))
    {
        DEBUG_MSG("Checkout %s not matching \n    read %s\n", dummyCheckout.getK(), dummyOutputCheckout.getK() );
        return INTEGRITY_E_FILE_INIT_MISMATCHED_CHECKOUT;
    }
    if (dummyIterationNumber != dummyOutputIterationNumber)
    {
        DEBUG_MSG("Iteration number %lu not matching read %lu\n", dummyIterationNumber, dummyOutputIterationNumber);
        return INTEGRITY_E_FILE_INIT_MISMATCHED_ITERATION;
    }
    if (dummyNumberOfSlices != dummyOutputNumberOfSlices)
    {
        DEBUG_MSG("Number of slices %lu not matching read %lu\n", dummyNumberOfSlices, dummyOutputNumberOfSlices);
        return INTEGRITY_E_FILE_INIT_MISMATCHED_SLICENO;
    }
    if (dummyPointsPerSlice != dummyOutputPointsPerSlice)
    {
        DEBUG_MSG("Points per slice %lu not matching read %lu\n", dummyPointsPerSlice, dummyOutputPointsPerSlice);
        return INTEGRITY_E_FILE_INIT_MISMATCHED_POINTSPERSLICE;
    }
    if (mpz_cmp(dummySliceSize, dummyOutputSliceSize) != 0)
    {
        DEBUG_MSG("Slice size %Zx not matching read %Zx\n", dummySliceSize, dummyOutputSliceSize);
        return INTEGRITY_E_FILE_INIT_MISMATCHED_SLICESIZE;
    }
    if (mpz_cmp(dummyIncrementSize, dummyOutputIncrementSize) != 0)
    {
        DEBUG_MSG("Increment size %Zx not matching read %Zx\n", dummyIncrementSize, dummyOutputIncrementSize);
        return INTEGRITY_E_FILE_INIT_MISMATCHED_INCREMENTSIZE;
    }

    gmp_printf("FileManager OK\n");
    tempOutput.close();
    return INTEGRITY_E_FILE_INIT_OK;
}

int generationSanityCheck(Point &startingPoint, unsigned long numberOfPoints,unsigned long numberOfSlices, unsigned long pointsPerSlice, mpz_t &incrementSize)
{
    ///TODO: check for negative inputs
    mpz_set_d(temp, 0);
    if(startingPoint.isKeyKnown())
    {
        return GENERATION_E_UNKNOWN_POINT_KEY;
    }

    if(numberOfSlices > numberOfPoints)
    {
        return GENERATION_E_TOO_MANY_SLICES;
    }
    else if (numberOfSlices < 1)
    {
        return GENERATION_E_NO_SLICES;
    }

    if ((numberOfSlices == 1) && (pointsPerSlice != numberOfPoints))
    {
        return GENERATION_E_POINT_NUMBER_NOT_MATCHING;
    }
    else if(pointsPerSlice * numberOfSlices > numberOfPoints)
    {
        return GENERATION_E_TOO_MANY_POINTS_PER_SLICE;
    }

    mpz_mul_ui(temp, incrementSize, numberOfPoints);
    if ((mpz_cmp(temp, orderHalf)) > 0)
    {
        DEBUG_MSG("Generated points are outside the required range\n Range: %Zx\n Generated Range: %Zx\n", orderHalf, temp);
        return GENERATION_E_POINTS_OUTSIDE_RANGE;
    }

    return GENERATION_E_OK;
}

int generateHashedPointsFile(std::ofstream &outputFile, Point &startingPoint,unsigned long numberOfPoints, unsigned long numberOfSlices, unsigned long pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
{
    ////TODO: preallocate needed space
    ////TODO: add low entropy bitsets

    if (outputFile.is_open())
    {
        outputFile << HASHED_POINTS_FILE_TAG << "\n"
                   << STARTING_POINT_TAG << "\n"
                   << startingPoint.getK() << "\n"
                   << startingPoint.getX() << "\n"
                   << startingPoint.getY() << "\n"
                   << SLICE_NUMBER_TAG << "\n"
                   << numberOfSlices << "\n"
                   << POINTS_PER_SLICE_TAG << "\n"
                   << pointsPerSlice << "\n"
                   << INCREMENT_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, PREFFERED_BASE, incrementSize) << "\n"
                   << TOTAL_POINT_NUMBER_TAG << "\n"
                   << numberOfPoints << "\n";

        DEBUG_MSG("Sanity check returned with the error code %d\n", generationSanityCheck(startingPoint, numberOfPoints, numberOfSlices, pointsPerSlice, incrementSize));

        mpz_mmod(sliceRemainderContainer, sliceSize, incrementSize);

        DEBUG_MSG("Remainder: %Zx\n", sliceRemainderContainer);

        remainderPoint *= sliceRemainderContainer;
        
        Point incrementPoint;
        DEBUG_MSG("Increment: %Zx\n", incrementSize);
        
        incrementPoint *= incrementSize;

        DEBUG_MSG("IncrementPoint K: %s\n", incrementPoint.getK());
        DEBUG_MSG("IncrementPoint X: %s\n", incrementPoint.getX());
        DEBUG_MSG("IncrementPoint Y: %s\n", incrementPoint.getY());

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
        outputFile << EOF_TAG << "\n"
                   << GENERATED_POINTS_EOF_TAG << "\n"
                   << startingPoint.getLSB() << "\n";
    }
    else
    {
        return FILE_E_NOT_OPEN;
    }
    return GENERATION_E_OK;
}

int generateUncompressedPointsFile(std::ofstream &outputFile, Point &startingPoint, unsigned long numberOfPoints,unsigned long numberOfSlices,unsigned long pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
{
    ////TODO: implement validation before calling the function
    // TODO: preallocate needed space
    // TODO: add low entropy bitsets

    if (outputFile.is_open())
    {
        outputFile << UNCOMPRESSED_POINTS_FILE_TAG << "\n"
                   << STARTING_POINT_TAG << "\n"
                   << startingPoint.getK() << "\n"
                   << startingPoint.getX() << "\n"
                   << startingPoint.getY() << "\n"
                   << SLICE_NUMBER_TAG << "\n"
                   << numberOfSlices << "\n"
                   << SLICE_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, PREFFERED_BASE, incrementSize) << "\n"
                   << POINTS_PER_SLICE_TAG << "\n"
                   << pointsPerSlice << "\n"
                   << TOTAL_POINT_NUMBER_TAG << "\n"
                   << numberOfPoints << "\n"
                   << INCREMENT_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, PREFFERED_BASE, incrementSize) << "\n";

        mpz_mmod(sliceRemainderContainer, sliceSize, incrementSize);

        DEBUG_MSG("Remainder: %Zx\n", sliceRemainderContainer);

        remainderPoint *= sliceRemainderContainer;

        Point incrementPoint;

        DEBUG_MSG("Increment: %Zx\n", incrementSize);

        incrementPoint *= incrementSize;

        DEBUG_MSG("IncrementPoint K: %s\n", incrementPoint.getK());
        DEBUG_MSG("IncrementPoint X: %s\n", incrementPoint.getX());
        DEBUG_MSG("IncrementPoint Y: %s\n", incrementPoint.getY());

        for (unsigned long i = 0; i < numberOfSlices; ++i)
        {
            /// outputFile << SLICE_ << i << "\n";
            outputFile  << startingPoint.getK() << "\n"
                        << startingPoint.getX() << "\n"
                        << startingPoint.getY() << "\n";
            for (unsigned long j = 0; j < pointsPerSlice; ++j)
            {
                startingPoint += incrementPoint;
                outputFile  << startingPoint.getK() << "\n"
                            << startingPoint.getX() << "\n"
                            << startingPoint.getY() << "\n";
            }
            startingPoint += remainderPoint;
        }
        outputFile << EOF_TAG << "\n"
                   << GENERATED_POINTS_EOF_TAG << "\n"
                   << startingPoint.getLSB() << "\n";
    }
    else
    {
        return FILE_E_NOT_OPEN;
    }
    return GENERATION_E_OK;
}

int generate_file_checkpoint(std::ofstream &outputFile, Point &targetPoint, Point &checkOutPoint, unsigned long &iterationNumber, unsigned long &numberOfSlices, unsigned long &pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
{
    if (outputFile.is_open())
    {
        outputFile << CHECKPOINT_FILE_TAG << "\n"

                   << TARGET_POINT_TAG << "\n"
                   << targetPoint.getK() << "\n"
                   << targetPoint.getX() << "\n"
                   << targetPoint.getY() << "\n"

                   << SLICE_NUMBER_TAG << "\n"
                   << numberOfSlices << "\n"

                   << SLICE_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, PREFFERED_BASE, sliceSize) << "\n"

                   << POINTS_PER_SLICE_TAG << "\n"
                   << pointsPerSlice << "\n"

                   << ITERATION_NUMBER_TAG << "\n"
                   << iterationNumber << "\n"

                   << INCREMENT_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, PREFFERED_BASE, incrementSize) << "\n"

                   << CHECKPOINT_EOF_TAG << "\n"

                   << checkOutPoint.getLSB() << "\n";
    }
    else
    {
        return FILE_E_NOT_OPEN;
    }
    return CHECKPOINT_E_OK;
}

int checkIntegrity_file_checkpoint(std::ifstream &inputFile, Point &output_targetPoint, Point &output_checkOutPoint, unsigned long &output_iterationNumber,
                                   unsigned long &output_numberOfSlices, unsigned long &output_pointsPerSlice, mpz_t &output_sliceSize, mpz_t &output_incrementSize, 
                                   bool writeToParameters)
{
    int integrityError = INTEGRITY_E_OK;
    std::string line;
   unsigned long fileType = FILETYPE_UNKNOWN;
    unsigned long long sliceNumber = 0, pointsPerSlice = 0, totalIterations = 0;
    if (!inputFile.is_open())
    {
        return FILE_E_NOT_OPEN;
    }
    getline(inputFile, line);
    if ( (line == UNCOMPRESSED_POINTS_FILE_TAG) || (line == COMPRESSED_POINTS_FILE_TAG) || (line == HASHED_POINTS_FILE_TAG) )
    {
        return INTEGRITY_E_FILETYPE_MISMATCH;
    }
    else if (line == CHECKPOINT_FILE_TAG)
    {
        fileType = FILETYPE_CHECKPOINT;
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_FILETYPE;
    }

    getline(inputFile, line);
    containerPoint.reset();
    if (line == TARGET_POINT_TAG)
    {
        getline(inputFile, line);
        containerPoint.setK(line.c_str(), PREFFERED_BASE, false);

        getline(inputFile, line);
        containerPoint.setX(line.c_str(), PREFFERED_BASE);

        getline(inputFile, line);
        containerPoint.setY(line.c_str(), PREFFERED_BASE);

        if (containerPoint.checkY() == false)
        {
            return INTEGRITY_E_INVALID_TARGET_POINT;
        }
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_TARGET_POINT;
    }

    getline(inputFile, line);
    if (line == SLICE_NUMBER_TAG)
    {
        getline(inputFile, line);
        sliceNumber = std::stoull(line, 0, LSB_READ_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_SLICE_NUMBER;
    }

    getline(inputFile, line);
    if (line == SLICE_SIZE_TAG)
    {
        getline(inputFile, line);
        mpz_set_str(sliceSizeContainer, line.c_str(), PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_SLICE_SIZE;
    }

    getline(inputFile, line);
    if (line == POINTS_PER_SLICE_TAG)
    {
        getline(inputFile, line);
        pointsPerSlice = std::stoull(line, 0, LSB_READ_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_POINTS_PER_SLICE;
    }

    getline(inputFile, line);
    if (line == ITERATION_NUMBER_TAG)
    {
        getline(inputFile, line);
        totalIterations = std::stoull(line, 0, LSB_READ_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_ITERATIONs_NUMBER;
    }

    getline(inputFile, line);
    if (line == INCREMENT_SIZE_TAG)
    {
        getline(inputFile, line);
        mpz_set_str(incrementSizeContainer, line.c_str(), PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_INCREMENT_SIZE;
    }

    mpz_mul_ui(temp, incrementSizeContainer, totalIterations);
    tempPoint = temp;
    tempPoint += containerPoint;

    DEBUG_MSG("\nGenerated dummyOutputTarget K: %s\n", containerPoint.getK());
    DEBUG_MSG("Generated dummyOutputTarget X: %s\n", containerPoint.getX());
    DEBUG_MSG("Generated dummyOutputTarget Y: %s\n", containerPoint.getY());
    DEBUG_MSG("Generated dummyOutputCheckout K: %s\n", tempPoint.getK());
    DEBUG_MSG("Generated dummyOutputCheckout X: %s\n", tempPoint.getX());
    DEBUG_MSG("Generated dummyOutputCheckout Y: %s\n", tempPoint.getY());
    DEBUG_MSG("Generated dummyOutputIterationNumber: %x\n", totalIterations);
    DEBUG_MSG("Generated dummyOutputNumberOfSlices: %x\n", sliceNumber);
    DEBUG_MSG("Generated dummyOutputPointsPerSlice: %x\n", pointsPerSlice);
    DEBUG_MSG("Generated dummyOutputSliceSize: %Zx\n", sliceSizeContainer);
    DEBUG_MSG("Generated dummyOutputIncrementSize: %Zx\n", incrementSizeContainer);
    DEBUG_MSG("Generated total iteration size: %Zx\n\n", temp);

    getline(inputFile, line);
    if(line == CHECKPOINT_EOF_TAG)
    {
        getline(inputFile, line);
        LSB_HASH_TYPE container = std::stoull(line, NULL, LSB_READ_BASE);
        if ((tempPoint.getLSB()) != container)
        {
            // DEBUG_MSG("File EOF: %x\nPoint EOF: %x\n", container, tempPoint.getLSB());
            return INTEGRITY_E_INVALID_EOF_TOKEN;
        }
        DEBUG_MSG("Read output       EOF: %lu\n", container);
        DEBUG_MSG("nGenerated output EOF: %lu\n", tempPoint.getLSB());
    }
    else
    {
        return INTEGRITY_E_READ_CHECKPOINT;
    }

    if (writeToParameters)
    {   ///TODO: Create active search class/enum
        output_targetPoint = containerPoint;
        output_checkOutPoint = tempPoint;
        output_iterationNumber = totalIterations;
        output_numberOfSlices = sliceNumber;
        output_pointsPerSlice = pointsPerSlice;
        mpz_set(output_incrementSize, incrementSizeContainer);
        mpz_set(output_sliceSize, sliceSizeContainer);
    }

    return INTEGRITY_E_OK;
}

int checkIntegrity_file_generatedPoints(std::ifstream &inputFile)
{
    ///Create dedicated error codes starting with 32
    int integrityError = INTEGRITY_E_OK;
    std::string line;
   unsigned long fileType = FILETYPE_UNKNOWN;
    unsigned long long sliceNumber = 0, pointsPerSlice = 0, totalPoints = 0;
    if(!inputFile.is_open())
    {
        return FILE_E_NOT_OPEN;
    }
    getline(inputFile, line);
    if(line == UNCOMPRESSED_POINTS_FILE_TAG)
    {
        fileType = FILETYPE_UNCOMPRESSED_POINTS;
    }
    else if(line == COMPRESSED_POINTS_FILE_TAG)
    {
        fileType = FILETYPE_COMPRESSED_POINTS;
    }
    else if(line == HASHED_POINTS_FILE_TAG)
    {
        fileType = FILETYPE_HASHED_POINTS;
    }
    else if(line == CHECKPOINT_FILE_TAG)
    {
        return INTEGRITY_E_FILETYPE_MISMATCH;
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_FILETYPE;
    }

    getline(inputFile, line);
    if(line == STARTING_POINT_TAG)
    {
        getline(inputFile, line);
        tempPoint.setK(line.c_str(), PREFFERED_BASE, (fileType != FILETYPE_CHECKPOINT));

        getline(inputFile, line);
        tempPoint.setX(line.c_str(), PREFFERED_BASE);
        
        getline(inputFile, line);
        tempPoint.setY(line.c_str(), PREFFERED_BASE);
        
        if(tempPoint.checkY() == false)
        {
            return INTEGRITY_E_INVALID_INITIAL_POINT;
        }
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_INITIAL_POINT;
    }

    getline(inputFile, line);
    if (line == SLICE_NUMBER_TAG)
    {
        getline(inputFile, line);
        sliceNumber = std::stoll(line, 0, PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_SLICE_NUMBER;
    }

    getline(inputFile, line);
    if (line == SLICE_SIZE_TAG)
    {
        getline(inputFile, line);
        mpz_set_str(sliceSizeContainer, line.c_str(), PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_SLICE_SIZE;
    }

    getline(inputFile, line);
    if (line == POINTS_PER_SLICE_TAG)
    {
        getline(inputFile, line);
        pointsPerSlice = std::stoll(line, 0, PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_POINTS_PER_SLICE;
    }

    getline(inputFile, line);
    if (line == TOTAL_POINT_NUMBER_TAG)
    {
        getline(inputFile, line);
        totalPoints = std::stoll(line, 0, PREFFERED_BASE);
        if (((sliceNumber == 1) && (totalPoints != pointsPerSlice)) || ((sliceNumber > 1) && (totalPoints != (sliceNumber * pointsPerSlice))))
        {
            return INTEGRITY_E_POINT_NUMBERS_NOT_MATCHING;
        }
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_TOTAL_POINT_NUMBER;
    }

    getline(inputFile, line);
    if (line == INCREMENT_SIZE_TAG)
    {
        getline(inputFile, line);
        mpz_set_str(incrementSizeContainer, line.c_str(), PREFFERED_BASE);
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_INCREMENT_SIZE;
    }

    if(sliceNumber > 1)
    {
        mpz_mul_ui(temp, sliceSizeContainer, sliceNumber);
        if(mpz_cmp(temp, orderHalf))
        {
            return INTEGRITY_E_SLICE_SIZE_TOO_BIG;
        }
    }

    mpz_mul_ui(temp, incrementSizeContainer, pointsPerSlice);
    if(mpz_cmp(temp, sliceSizeContainer)) /// in the case of one slice , the slice size is equal to orderHalf; in the case of multiple slices, total increments inside the slice must be smaller or equal than the slice size
    {
        return INTEGRITY_E_INCREMENT_SIZE_TOO_BIG;
    }

    while(line != EOF_TAG)
    {
        getline(inputFile, line);
    }

    getline(inputFile, line);
    
    if (line == GENERATED_POINTS_EOF_TAG)
    {
        mpz_set_ui(temp, 0);
        mpz_mul_ui(temp, sliceSizeContainer, totalPoints / pointsPerSlice);
        mpz_addmul_ui(temp, incrementSizeContainer, totalPoints % pointsPerSlice);
        tempPoint *= temp;

        getline(inputFile, line);
    
        if (std::stol(line, NULL, PREFFERED_BASE) != tempPoint.getLSB())
        {
            return INTEGRITY_E_INVALID_EOF_TOKEN;
        }
    }
    else
    {
        return INTEGRITY_E_UNKNOWN_EOF_TOKEN;
    }

    return INTEGRITY_E_OK;
}

int resumeGeneration();
int expandGeneratedList();

int createNewTargetFile(Point T, Point runningT, Point runningNT, Point temp, mpz_t &search_space)
{
    int jump;
    mpz_t counter;
    std::string userBuffer;
    bool* pointLoaded;
    std::cout << "Insert target's X coordinate (base PREFFERED_BASE)\n";
    std::cin >> userBuffer;
    T.setX(userBuffer.c_str(), PREFFERED_BASE);
    runningT.setX(userBuffer.c_str(), PREFFERED_BASE);
    runningNT.setX(userBuffer.c_str(), PREFFERED_BASE);

    std::cout << "Insert target's Y coordinate (base PREFFERED_BASE)\n";
    std::cin >> userBuffer;
    T.setY(userBuffer.c_str(), PREFFERED_BASE);
    runningT.setY(userBuffer.c_str(), PREFFERED_BASE);
    runningNT.setY(userBuffer.c_str(), PREFFERED_BASE);
    runningNT.negate(); /// prepare point -T

    if (T.checkY())
    {
        std::cout << "Point valid\n";
        *pointLoaded = true;
    }
    else
    {
        std::cout << "Point not valid\n";
        *pointLoaded = false;
    }

    std::cout << "Insert iteration counter (base 10)\n";
    std::cin >> userBuffer;
    mpz_set_str(counter, userBuffer.c_str(), 10);
    mpz_init_set_str(search_space, "20444724287007402249549317371870405449633012157584065567923", 10);

    if (mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1))
    {
        DEBUG_MSG("Counter set to %Zd\n", counter);
    }
    else
    {
        DEBUG_MSG("Counter not inside search space\n");
    }

    if (mpz_cmp_ui(counter, 0))
    {
        temp.multiplyByFactor(temp, counter);
        runningT.addPoint(runningT, temp);
        runningNT.addPoint(runningNT, temp);
    }

    DEBUG_MSG("Iteration ready at point %Zd\n", counter);
    std::cout << "Positive point: \n xT: " << runningT.getX() << "\n yT: " << runningT.getY() << "\n";
    std::cout << "Negative point: \nxNT: " << runningNT.getX() << "\nyNT: " << runningNT.getY();
    *pointLoaded = true;
    jump = 0;
    return 0;
}