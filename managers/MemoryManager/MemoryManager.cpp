#include "MemoryManager.h"
#include "../Ports.h"

std::set<LSB_HASH_TYPE> knownPointsMemoryBlock;

#define MEMORYMAN_RXPORT_BUFFER_SIZE 5u
unsigned int init_MemoryManager(MemoryManagerData *memoryManagerStruct)
{
    initPort(&(memoryManagerStruct->memoryManagerRxPort), MEMORYMAN_RXPORT_BUFFER_SIZE);
    return MEMORY_MANAGER_E_OK;
}

/**
 * @brief Initialize a set of Point buffers
 * 
 * @param bufferLength The length of the required buffers
 * @param bufferNumber The number of buffers required
 * @return Point*** An array of pointers refferencing the initialized containers 
 */
Point ***init_PointBuffers(unsigned int bufferLength, unsigned int bufferNumber)
{
    Point ***retPtr = (Point***)malloc(sizeof(Point*) * bufferLength * bufferNumber);
    for(unsigned int i = 0u; i < bufferNumber; ++i)
    {
        for(unsigned int j = 0u; i < bufferLength; ++j)
        {
            retPtr[i][j] = new Point();
        }
    }
    return retPtr;
}
unsigned int delete_PointBuffer(Point **buffer, unsigned int bufferSize)
{
    for(int i = 0u; i < bufferSize; ++i)
    {
        buffer[i]->~Point();
    }
    free(buffer);
    return 0u;
}

/**
 * @brief Initialize a set of mpz_buffers
 * 
 * @param bufferLength The length of the required buffers
 * @param bufferNumber The number of buffers initialized
 * @return mpz_t*** An array of pointers refferencing the initialized containers 
 */
mpz_t ***init_mpzBuffers(unsigned int bufferLength, unsigned int bufferNumber)
{
    mpz_t ***retPtr = (mpz_t***)malloc(sizeof(mpz_t*) * bufferLength * bufferNumber);
        for(unsigned int i = 0u; i < bufferNumber; ++i)
        {
            for(int j; j < bufferLength; ++j)
            {
                mpz_init2(*(retPtr[i][j]), 256u);
            }
        }
        return retPtr;
}
unsigned int delete_mpzBuffer(mpz_t **buffer, unsigned int bufferSize)
{
    for(int i = 0u; i < bufferSize; ++i)
    {
        mpz_clear(*(buffer[i]));
    }
    free(buffer);
    return 0u;
}

void knownPointsProfile_Init(targetProfile* profile)
{
    profile->checkOutPoint.reset();
    profile->targetPoint.reset();
    profile->iterationNumber = 0;
    profile->numberOfSlices = 0;
    profile->pointsPerSlice = 0;
    mpz_init_set_ui(profile->incrementSize, 0u);
    mpz_init_set_si(profile->sliceSize, 0u);
}

void targetProfile_Init(pointsProfile* profile)
{
    profile->finalPoint.reset();
    profile->initialPoint.reset();
    profile->iterationNumber = 0;
    profile->numberOfSlices = 0;
    profile->pointsPerSlice = 0;
    mpz_init_set_ui(profile->incrementSize, 0u);
    mpz_init_set_si(profile->sliceSize, 0u);
    // std::set<LSB_HASH_SIZE> knownSet;
}

unsigned int read_file_checkpoint(std::ifstream &inputFile, Point &targetPoint, Point &checkOutPoint, unsigned int iterationNumber, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
{
    return 0;
}

unsigned int loadKnownPoints(std::ifstream &knownPointSet, bool *listLoaded)
{
    std::string line;
    // cardinalLSB_read.open("cardinalLSB"); //file manager should provide the open ifstream
    if (knownPointSet.is_open())
    {
        std::cout << "Loading cardinal known points file\n";
        while (getline(knownPointSet, line))
        {
            knownPointsMemoryBlock.insert(std::stoul(line));
        }
        // knownPointSet.close(); //file manager should close the ifstream
    }
    else
    {
        std::cout << "Provided file stream is not linked\n";
    }
    *listLoaded = true;
    return MEMORY_MANAGER_E_OK;
}

unsigned int generatePoints()
{
    //if pointProfile file is empty, populate the file ///TODO: create call inside iterationManager for the creation of the points
    return 0;
}