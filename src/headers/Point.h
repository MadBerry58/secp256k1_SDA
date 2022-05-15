//
// Created by blackberry on 10.01.2021.
//

#ifndef SECP251K1_SANDBOX_POINT_H
#define SECP251K1_SANDBOX_POINT_H
#include "Mod.h"


int generatorConstantsInit();
unsigned int pointInit();

class Point
{
private:
    mpz_t           k;
    mpz_t           x;
    mpz_t           y;
    mpz_t           t1;
    mpz_t           t2;
    mpz_t           m;
    mpz_t           n;
    bool            keyKnown = false;
    char            outputString[100];

public: 
    ///Initializer functions    
                    Point                   ();
                    Point                   (mpz_t &key);
                    Point                   (Point &source);
                    Point                   (const char *xString, const char *yString);
                    Point                   (const char *xString, const char *yString,const char *kString);
                    ~Point                  ();

    ///Overloaded operators 
    void            operator=               (Point &source);
    void            operator=               (mpz_t &key);
    void            operator=               (char  *keyString);
    void            operator-=              (Point &source);
    void            operator+=              (Point &source);
    void            operator*=              (mpz_t &factor);
    bool            operator==              (Point &source);
    bool            operator!=              (Point &source);

    ///Arithmetic functions 
    void            negate                  ();
    void            addPoint                (Point &result, Point &B);
    void            multiplyBy2             (Point &result);
    void            multiplyByFactor        (Point &result, mpz_t &factor);

    ///Getters  
    char*           getX                    ();
    char*           getY                    ();
    char*           getK                    ();
    LSB_HASH_TYPE   getLSB                  ();

    ///Setters  
    void            setK                    (const char *k, int base, bool known);
    void            setX                    (const char *x, int base);
    void            setY                    (const char *y, int base);
    void            reset                   ();
    void            setFromK                (const char *kValue, int base); 

    ///Printout functions   
    void            printPointInfo          ();
    void            printDec                ();
    void            printHex                ();

    ///Utility functions    
    bool            checkY                  ();
    char*           generateY               ();
    bool            isKeyKnown              ();

    ///Testing functions
    void            toggleKeyKnowledgeState ();
};


class JPoint{
public:
                    JPoint              (char *x, char *y, char *z);
    void            addPoint            (Point &result, Point &B);
    void            printDec            ();
    void            printHex            ();
    char*           getX                ();
    char*           getY                ();
    char*           getK                ();
    unsigned long long int getLSB();
private:
    mpz_t           x;
    mpz_t           y;
    mpz_t           z;
};

#endif //SECP251K1_SANDBOX_POINT_H
