//
// Created by blackberry on 10.01.2021.
//

#ifndef SECP251K1_SANDBOX_POINT_H
#define SECP251K1_SANDBOX_POINT_H
#include "Mod.h"
class Point{
private:
    mpz_t x;
    mpz_t y;
    mpz_t k;
    mpz_t t1;
    mpz_t t2;
    mpz_t m;
    mpz_t n;
    bool keyKnown = false;
    char outputString[100];

public:
    Point(const char *xString, const char *yString);
    Point(const char *xString, const char *yString,const char *kString);
    ~Point();
    void negate();
    void addPoint(Point &result, Point &B);
    void multiplyBy2(Point &result);
    void multiplyByFactor(Point &result, mpz_t &factor);
    void printDec();
    void printHex();
    char *getX();
    char *getY();
    char *getK();
    void printPointInfo(char *pointName);
    char *generateY();
    void setX(const char *x, int base);
    void setY(const char *y, int base);
    void setK(const char *k, int base);
    unsigned long getLSB();
    bool checkY();
    bool checkIteration(Point &target, mpz_t addedKey, long hash);
};

class JPoint{
public:
    JPoint(char *x, char *y, char *z);
    void addPoint(Point &result, Point &B);
    void printDec();
    void printHex();
    char *getX();
    char *getY();
    char *getK();
    unsigned long long int getLSB();
private:
    mpz_t x;
    mpz_t y;
    mpz_t z;
};
#endif //SECP251K1_SANDBOX_POINT_H
