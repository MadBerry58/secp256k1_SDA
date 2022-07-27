#include "MemoryManager.h"

void pointProfile_Init(targetProfile* profile)
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

int read_file_checkpoint(std::ifstream &inputFile, Point &targetPoint, Point &checkOutPoint, unsigned int iterationNumber, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize)
{
    return 0;
}

int loadPoints(std::ifstream cardinalLSB_read, bool *listLoaded)
{
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
