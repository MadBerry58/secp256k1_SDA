#include "headers/Iterators.h"

int hashGeneratorIterator(std::ofstream &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice)
{
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