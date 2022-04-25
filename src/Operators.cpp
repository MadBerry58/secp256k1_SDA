//
// Created by blackberry on 25.01.2021.
//
#include "headers/Operators.h"

void saveMatch(/* jump, iteration, match X, fileName */){
    /* Save iteration
     * Save jump
     * Save match
     * */
}
void generateLeastSignificantBits(/* fileName */){
    /* Generate LSB file*/
}
void loadLeastSignificantBits(char *filename, std::ifstream cardinalLSB_read, std::set<unsigned long int> LSB_cardinal){
    //TODO: test function
    std::string line;
    cardinalLSB_read.open(filename);
    if(cardinalLSB_read.is_open()){
        std::cout << "Loading cardinal LSB file from " << filename <<"\n";
        while(getline(cardinalLSB_read, line)){
            LSB_cardinal.insert(std::stoul(line));
        }
        cardinalLSB_read.close();
    }else{
        std::cout << "Could not open cardinalLSB file\n";
    }
    std::cout << "Cardinal LSB list loaded\n" << "Elements in set: "<< LSB_cardinal.size() << "\n";
}

bool Operator::saveCheckpoint(){
    return false;
}

bool Operator::loadCheckpoint(char *fileName){
    return false;
}

void generateExplicititCardinalList(){
    /*Generate X&K pair file
     * */
}
bool regenerateAddedPoint(){
    /* key = iteration + (k(J)*jumps)
     * AddedPoint = G * key
     * pTarget = Target + AddedPoint
     * nTarget =-Target + AddedPoint
     * if(compare(pTarget, checkpoint_pTarget) || compare(nTarget, checkpoint_nTarget)){
     * return false
     * }else{
     * return true
     * }
     * */
    return false;
}
bool checkForMatches(std::set<unsigned int> LSB_cardinal, Point runningT){
    if(LSB_cardinal.find(runningT.getLSB()) != LSB_cardinal.end()){
        std::cout << "Target hash inside cardinal list\n";
        return true;
    }else{return false;}
}

bool saveMatch(mpz_t key, std::ofstream matches_write, Point runningT){
    char keyOutputString[1024];
    std::string fileName;
    mpz_get_str(keyOutputString, 10, key);
    fileName = "matches/Match";
    fileName.append(keyOutputString);
    matches_write.open(fileName);
    matches_write << "(Q + " << keyOutputString   << ")\n";
    matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
    matches_write.close();
    return true;
}

void extractKeyFromIteration(mpz_t result, mpz_t iteration, int jumps, int subJumps, char ksJ[], char kJ[]){
    mpz_t temp;
    mpz_init_set_str(temp, ksJ, 16);
    mpz_addmul_ui(result, temp, subJumps);
    mpz_set_str(temp, kJ, 16);
    mpz_addmul_ui(result, temp, jumps);
    mpz_add(result, result, iteration);
    gmp_printf("Extracted key: %Zx \n", result);
    ///free temp
}

void Operator::extractKey(mpz_t &output, mpz_t iteration, int jumps, int subJumps){

}

int Operator::iterate(int iterations){
    return 0;
}