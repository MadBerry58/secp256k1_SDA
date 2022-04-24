#include "include/Operators.h"

#ifndef SECP251K1_SANDBOX_FILEMANAGER_H
#define SECP251K1_SANDBOX_FILEMANAGER_H

extern mpz_t orderHalf;
mpz_t temp;
mpz_t incrementSizeContainer;
mpz_t sliceSizeContainer;
mpz_t sliceRemainderContainer;
Point tempPoint;
Point remainderPoint;

int fileManager_Init()
{
    tempPoint.reset();
    remainderPoint.reset();
    mpz_init(temp);
    mpz_init(incrementSizeContainer);
    mpz_init(sliceSizeContainer);
    mpz_init(sliceRemainderContainer);
}

int generationSanityCheck(Point startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &incrementSize)
{
    ///TODO: check for negative inputs
    mpz_set_d(temp, 0);
    if(startingPoint.getK())
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
    if(mpz_cmp(temp, orderHalf))
    {
        return GENERATION_E_POINTS_OUTSIDE_RANGE;
    }

    return GENERATION_E_OK;
}

int generateHashedPointsFile(std::ofstream outputFile, Point startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
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
                   << mpz_get_str(NULL, 16, incrementSize) << "\n"
                   << TOTAL_POINT_NUMBER_TAG << "\n"
                   << numberOfPoints << "\n";

        mpz_mod(sliceRemainderContainer, sliceSize, incrementSize);
        remainderPoint *= sliceRemainderContainer;

        Point incrementPoint;
        incrementPoint *= incrementSize;

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
}

int generateUncompressedPointsFile(std::ofstream outputFile, Point startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
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
                   << mpz_get_str(NULL, 16, incrementSize) << "\n"
                   << POINTS_PER_SLICE_TAG << "\n"
                   << pointsPerSlice << "\n"
                   << TOTAL_POINT_NUMBER_TAG << "\n"
                   << numberOfPoints << "\n"
                   << INCREMENT_SIZE_TAG << "\n"
                   << mpz_get_str(NULL, 16, incrementSize) << "\n";

        Point remainderPoint;
        mpz_mod(sliceRemainderContainer, sliceSize, incrementSize);
        remainderPoint *= sliceRemainderContainer;

        Point incrementPoint;
        incrementPoint *= incrementSize;

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
}

int generateCheckpointFile(std::ofstream outputFile, Point targetPoint, unsigned int iterationNumber, )

int checkFileIntegrity(std::ifstream inputFile)
{
    int integrityError = INTEGRITY_E_OK;
    std::string line;
    unsigned int fileType = FILETYPE_UNKNOWN;
    unsigned long long sliceNumber = 0, pointsPerSlice = 0, totalPoints = 0;
    if(inputFile.is_open())
    {
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
            fileType = FILETYPE_CHECKPOINT;
        }
        else
        {
            return INTEGRITY_E_UNKNOWN_FILETYPE;
        }

        getline(inputFile, line);
        if( (line == STARTING_POINT_TAG) || (line == TARGET_POINT_TAG) )
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
        }
        else
        {
            return INTEGRITY_E_UNKNOWN_TOTAL_POINT_NUMBER;
        }

        if ( ( (sliceNumber == 1) && (totalPoints != pointsPerSlice) ) || ((sliceNumber >  1) && (totalPoints != (sliceNumber * pointsPerSlice)) ) )
        {
            return INTEGRITY_E_POINT_NUMBERS_NOT_MATCHING;
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
        if( (line == GENERATED_POINTS_EOF_TAG)
        {
            if(sliceNumber > 1)
            {
                mpz_mul_ui(temp, sliceSizeContainer, sliceNumber);
            }
            else
            {
                mpz_mul_ui(temp, incrementSizeContainer, totalPoints);
            }
            tempPoint.reset();
            tempPoint *= temp;
            getline(inputFile, line);
            if (std::stol(NULL, line, PREFFERED_BASE) != tempPoint.getLSB())
            {
                return INTEGRITY_E_INVALID_EOF_TOKEN;
            }
        }
    }
    else
    {
        return FILE_E_NOT_OPEN;
    }
    return INTEGRITY_E_OK;
}

 
int resumeCheckpoint(std::ifstream checkPoint_read, Point T, Point runningT,Point runningNT, int* jump, bool* pointLoaded)
{
    std::string line;
    mpz_t counter;
    checkPoint_read.open("checkpoint");
    if (checkPoint_read.is_open())
    {
        getline(checkPoint_read, line);
        if ("Target" == line)
        {
            getline(checkPoint_read, line);
            T.setX(line.c_str(), PREFFERED_BASE);
            getline(checkPoint_read, line);
            T.setY(line.c_str(), PREFFERED_BASE);
            std::cout << "Target:\nX: " << T.getX() << "\nY: " << T.getY() << "\n";
            if (!T.checkY())
            {
                std::cout << "Target not valid\n";
            }
        }
        else
        {
            std::cout << "Target not found\n";
        }
        getline(checkPoint_read, line);
        if ("Iteration" == line)
        {
            getline(checkPoint_read, line);
            mpz_set_str(counter, line.c_str(), 10);
        }
        else
        {
            std::cout << "Iteration count not found\n";
        }
        getline(checkPoint_read, line);
        if ("Jump" == line)
        {
            getline(checkPoint_read, line);
            *jump = std::stoi(line);
            std::cout << "Jump:\n"
                      << jump << "\n";
        }
        else
        {
            std::cout << "Jump not found\n";
        }
        getline(checkPoint_read, line);
        if ("Running pTarget" == line)
        {
            getline(checkPoint_read, line);
            runningT.setX(line.c_str(), PREFFERED_BASE);
            getline(checkPoint_read, line);
            runningT.setY(line.c_str(), PREFFERED_BASE);
            std::cout << "Running pTarget:\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n";
        }
        else
        {
            std::cout << "pTarget not found\n";
        }
        getline(checkPoint_read, line);
        if ("Running nTarget" == line)
        {
            getline(checkPoint_read, line);
            runningNT.setX(line.c_str(), PREFFERED_BASE);
            getline(checkPoint_read, line);
            runningNT.setY(line.c_str(), PREFFERED_BASE);
            std::cout << "Running nTarget:\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
        }
        else
        {
            std::cout << "nTarget not found\n";
        }
        // TODO: compare  (Target + temp) to pTarget
        // TODO: compare (-Target + temp) to nTarget
    }
    checkPoint_read.close();
    std::cout << "Checkpoint Restored\n";
    *pointLoaded = true;
    return 0;
}

int loadPoints(std::ifstream cardinalLSB_read, bool* listLoaded){
    std::string line;
    std::set<unsigned long> LSB_cardinal;
    cardinalLSB_read.open("cardinalLSB");
    if (cardinalLSB_read.is_open())
    {
        std::cout << "Loading cardinal LSB file\n";
        while (getline(cardinalLSB_read, line))
        {
            LSB_cardinal.insert(std::stoul(line));
        }
        cardinalLSB_read.close();
    }
    else
    {
        std::cout << "Could not open cardinalLSB file\n";
    }
    std::cout << "Cardinal LSB list loaded\n"
              << "Elements in set: " << LSB_cardinal.size() << "\n";
    *listLoaded = true;
    return 0;
}

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
    mpz_init_set_str(search_space, "2044472428PREFFERED_BASE7007402249549317371870405449633012157584065567923", 10);

    if (mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1))
    {
        gmp_printf("Counter set to %Zd\n", counter);
    }
    else
    {
        gmp_printf("Counter not inside search space\n");
    }

    if (mpz_cmp_ui(counter, 0))
    {
        temp.multiplyByFactor(temp, counter);
        runningT.addPoint(runningT, temp);
        runningNT.addPoint(runningNT, temp);
    }

    gmp_printf("Iteration ready at point %Zd\n", counter);
    std::cout << "Positive point: \n xT: " << runningT.getX() << "\n yT: " << runningT.getY() << "\n";
    std::cout << "Negative point: \nxNT: " << runningNT.getX() << "\nyNT: " << runningNT.getY();
    *pointLoaded = true;
    jump = 0;
    return 0;
}

#endif // SECP251K1_SANDBOX_FILEMANAGER_H