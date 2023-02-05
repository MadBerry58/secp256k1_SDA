#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include "MemoryUtility_Types.h"
// unsigned int init_MemoryManager(MemoryManagerData *memoryManagerStruct);

// Point ***init_PointBuffers(unsigned int bufferLength, unsigned int bufferNumber);
// unsigned int delete_PointBuffer(Point **buffer, unsigned int bufferSize);

// mpz_t ***init_mpzBuffers(unsigned int bufferLength, unsigned int bufferNumber);
// unsigned int delete_mpzBuffer(mpz_t **buffer, unsigned int bufferSize);

// unsigned int read_file_checkpoint(std::ifstream &inputFile, Point &targetPoint, Point &checkOutPoint, unsigned int iterationNumber, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);

// unsigned int loadPoints(std::ifstream cardinalLSB_read, bool *listLoaded);

#endif // SECP251K1_SANDBOX_MEMORYMANAGER_H

////TODO: add a mpz buffer manager to allow compile time memory allocation and reuse

/**
 * @brief In order to allow for the reduction of the space complexity, some will be used:
 * 
 *  Discreete Logarithm dispersion:
 *      As any public key representation of a point P manifests the discreete logarithm property withing a prime field of P of 256 bits,
 *      the coordinates themselves can be threated as 256 bits hashes. As such, using the low collision property of hashes,
 *      smaller subsections of the entire X coordinate can saved (around 32 bits), while maintaining rellevand differences.
 *      The viability of this approach is determined by the ratio of stored hashes to the hash length:
 *          a.i: a 32 bit subsection can allow for 4294967296 distinct entries (occupying around 18GB of memory)
 *               a RAM capacity of around 30GB would allow for 7500000000 distinct entries, giving a collision ratio of 1.7462298274
 *               as the optimal case would require a ratio below one, increasing the subsection size is the easiest solution
 *               a 33 bit subsection allows for 8589934592 distinct entries, lowering the ratio to 0,873114914
 *               the issue with this approach is that 33 bits do not fit in a standard data type, forcing the data alignment 
 *               to double the required memory allocation size
 *   
 *  RIPE160 hashing:
 *       The data alignment issues will persist regardless of the available size (with next proper alignment happening at 64bits - 
 *       requiring over 150*10^12 GB of memory).
 *       //Deprecated 
 *       A way to take advantage of this issue is by stuffing the remaining registry space with
 *       other relevant data.
 *       The relevant data in question is another secp256l1 particularity, the RIPE160 hash associated with every public key.
 *       As this hash is the only information available about some of the potential target keys, having it as part of the generated
 *       data allows for attacking wallets previously immune to a purely elliptical key approach
 *       //Deprecated
 *       In order to reduce the checking complexity with the same memory requirements, the RIPE160 of both Q and -Q will be used in the
 *       generation process, with 32 bits of each stuffed inside a 64 bit registry. This will increase computational complexity for
 *       the client (Lord Farquaad voice: "but that's a sacrifice I'm willing to make").
 *       
 *  Entry structure:
 *  
 *  /                      64 bit registry                         \
 * 
 *  1010001010000111011011010101101111101001110011010100110101101101
 *  ^                              ^^                              ^
 *  |   RIPE160(Q) & 2^32          ||   RIPE160(-Q) & 2^32         |  
 * 
 * Elliptical symmetry: 
 *      As the public key representations of (Q) and (-Q) are symmetrical on the X axis, the Y coordinate can be
 *      disregarded, as it is trivial to compute from the X coordinate of a known point K = (Q + I) where K and I are known.
 *      In practice, this means that for any target with a known public key, the matching can also be done on the X coordinate,
 *      allowing for a database-independent and low cost checking mechanism on the client's side, by comparing -Q == (Q + I).
 *      if k(I) > (Order)/2 then Q is either in the 1st or 3th quadrant.
 *          if k(I) is even, then Q is in the 1st quadran
 *              k(Q) = (Order - k(I) - 1) / 2
 *          else 
 *          if k(I) is odd,  then Q is in the 3rs quadran
 *              k(Q) = ()
 *      else
 *      if k(I) < (Order)/2 then Q is in the 2nd or 4th quadrant. 
 *          if k(I) is even, then Q is in the 2nd quadran
 *          else
 *          if k(I) is odd,  then Q is in the 4th quadran
 * 
 */