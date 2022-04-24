/*
    Point.cpp
    Contains point arithmetic functionality using modulo operations over the prime integer field
    Wrapper functions are provided for ease of use
    Overloaded operators are provided as wrappers for ease of use. Do ~NOT~ use for critical functionality
*/

#include <cstring>
#include "../include/Point.h"
extern mpz_t moduloHalb;
extern mpz_t one;
extern mpz_t two;
extern mpz_t three;
extern mpz_t four;
extern mpz_t five;
extern mpz_t six;
extern mpz_t seven;


///Affine (cartesian) points
Point::Point()
{
    mpz_init_set_str(this->x, xG_String, PREFFERED_BASE);
    mpz_init_set_str(this->y, yG_String, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_ui(k, 1);
}

Point::Point(Point &source)
{
    mpz_init_set_str(this->x, source.getX(), PREFFERED_BASE);
    mpz_init_set_str(this->y, source.getY(), PREFFERED_BASE);
    mpz_init_set_str(this->k, source.getK(), PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
}

Point::Point(mpz_t &key)
{
    mpz_init_set_str(this->x, xG_String, PREFFERED_BASE);
    mpz_init_set_str(this->y, yG_String, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_ui(k, 1);
    this->multiplyByFactor(*this, key);
}

Point::Point(const char xString[], const char yString[]) {
    mpz_init_set_str(this->x, xString, PREFFERED_BASE);
    mpz_init_set_str(this->y, yString, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_ui(k, 0);
}

Point::Point(const char *xString, const char *yString, const char *kString) {
    mpz_init_set_str(this->x, xString, PREFFERED_BASE);
    mpz_init_set_str(this->y, yString, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_str(k, kString, PREFFERED_BASE);
    keyKnown = true;
}

Point::~Point()
{
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(t1);
    mpz_clear(t2);
    mpz_clear(m);
    mpz_clear(n);
    mpz_clear(k);
}



void Point::operator=(Point &source)
{
    mpz_set(this->x, source.x);
    mpz_set(this->y, source.y);
    mpz_set(this->k, source.k);
    this->keyKnown = source.keyKnown;
}

void Point::operator=(mpz_t &key)
{
    mpz_set_ui(this->k, 1);
    mpz_set_str(this->x, xG_String, PREFFERED_BASE);
    mpz_set_str(this->y, yG_String, PREFFERED_BASE);
    *this *= key;
}

void Point::operator+=(Point &source)
{
    /// TODO:  test to see if it's consistent with the addPoint function
    addKeys(this->k, this->k, source.k);
    
    sub(t1, source.y, this->y);     /// t1 = By - Ay mod p
    sub(t2, source.x, this->x);     /// t2 = Bx - Ax mod p
    div(m, t1, t2);                 /// m  = t1 / t2 mod p
    mul(t1, m, this->x);            /// t1 = m * Ax mod p
    sub(n, this->y, t1);            /// n = Ax - t1 mod p
    pow(t1, m, two);                /// t1 = m * m
    sub(t2, t1, this->x);           /// t2 = t1 - Ax
    sub(this->x, t2, source.x);     /// Cx = t2 - Bx
    mul(t1, m, this->x);            /// t1 = m * Cx
    add(t2, t1, n);                 /// t2 = t1 + n
    neg(this->y, t2);               /// Cy = neg(t2)
}

void Point::operator*=(mpz_t &factor)
{
    ///TODO: Check if operator matches multiplyByFactor and multiplyBy2 functions
    if(mpz_cmp_ui(factor, 2u))
    {
        this->multiplyByFactor(*this, factor);
    }
    else
    {
        this->multiplyBy2(*this);
    }
}



void Point::negate() 
{
    neg(y, y);
}

void Point::addPoint(Point &result, Point &B)
{
//    m         = div( sub(yP2, yP1) , sub(xP2,xP1) );
//    n         = sub(yP1 , mul(m,xP1));
//    result.x  = sub(sub(mul(m,m) ,(xP1)) , (xP2));
//    result.y  = neg(add(mul(m,result.x) , n));

    addKeys (result.k, this->k, B.k);
    sub     (t1, B.y, this->y);         /// t1  = By - Ay mod p
    sub     (t2, B.x, this->x);         /// t2  = Bx - Ax mod p
    div     (m, t1, t2);                /// m   = t1 / t2 mod p
    mul     (t1, m, this->x);           /// t1  = m * Ax mod p
    sub     (n, this->y, t1);           /// n   = Ax - t1 mod p
    pow     (t1, m, two);               /// t1  = m * m
    sub     (t2, t1, this->x);          /// t2  = t1 - Ax
    sub     (result.x, t2, B.x);        /// Cx  = t2 - Bx
    mul     (t1, m, result.x);          /// t1  = m * Cx
    add     (t2, t1, n);                /// t2  = t1 + n
    neg     (result.y, t2);             /// Cy  = neg(t2)
}

void Point::multiplyBy2(Point &result)
{
//	m = (3 * X²) / (2 * sqrt(X²+7))
//	n = Y - m * X;
//	result.x = m² - 2*X
//	result.y = -(m*result.x + n)
// -------------------- //
    pow     (m, x, two);        // m        = x^2)
    mul     (t1, three, m);     // t1       = 3 * x^2
    pow     (m, x, three);      // m        = x^3
    add     (t2, m, seven);     // t2       = x^3 + 7
    modSqrt (m, t2);            // m        = sqrt(x^3 + 7)
    mul     (t2, m, two);       // t2       = 2 * sqrt(x^3 + 7)
    mul     (t2, y, two);       // t2       = 2 * y
    div     (m, t1, t2);        // m        = (3 * x^2) / (2 * sqrt(x^3 + 7));
    mul     (t1, m, x);         // t1       = x * (3 * x^2) / (2 * sqrt(x^3 + 7))
    sub     (n, y, t1);         // n        = y - (x * (3 * x^2) / (2 * sqrt(x^3 + 7)))
    mul     (t1, x, two);       // t1       = 2 * x
    pow     (t2, m, two);       // t2       = ((3 * x^2) / (2 * sqrt(x^3 + 7))) ^ 2
    sub     (result.x, t2, t1); // result.x = ((3 * x^2) / (2 * sqrt(x^3 + 7))) ^ 2 - 2 * x
    mul     (t1, m, result.x);  // t1       = (3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x
    add     (t2, t1, n);        // t2       = (3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x + n
    neg     (result.y, t2);     // result.y = -((3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x + n)
}

void Point::multiplyByFactor(Point &result, mpz_t &factor)
{
    unsigned int factorSize = mpz_sizeinbase(factor, 2);
    Point temp(xG_String, yG_String);
    mpz_set(temp.x, this->x);
    mpz_set(temp.y, this->y);
    
    unsigned int i = 0;

    while (mpz_tstbit(factor, i) == 0) /// covers the case when factor's LSB is not 0
    {
        temp.multiplyBy2(temp);
        ++i;
    }
    result = temp;

    ++i;
    for (i; i < factorSize; ++i)
    {
        if (mpz_tstbit(factor, i))
        {
            result+=temp;
        }
        temp.multiplyBy2(temp);
    }
}



char *Point::getK() 
{
    if(keyKnown)
    {
        return mpz_get_str(outputString, PREFFERED_BASE, k);
    }
    else
    {
        mpz_get_str(outputString, PREFFERED_BASE, k);
        strcat(outputString, "+");
        return outputString;
    }
}

char *Point::getX()
{
    return mpz_get_str(outputString, PREFFERED_BASE, x);
}

char *Point::getY()
{
    return mpz_get_str(outputString, PREFFERED_BASE, y);
}

unsigned long Point::getLSB()
{
    return x->_mp_d[0];
}



void Point::setK(const char *kValue, int base, bool known)
{
    mpz_set_str(k, kValue, base);
    keyKnown = known;
}

void Point::setX(const char *xCoordinate, int base)
{
    mpz_set_str(x, xCoordinate, base);
}

void Point::setY(const char *yCoordinate, int base)
{
    mpz_set_str(y, yCoordinate, base);
}

void Point::reset()
{
    mpz_set_ui(this->k, 1);
    mpz_set_str(this->x, xG_String, PREFFERED_BASE);
    mpz_set_str(this->y, yG_String, PREFFERED_BASE);
}



void Point::printPointInfo(char *pointName)
{
    gmp_printf("Point ", pointName);
    if(keyKnown)
    {
        gmp_printf("\nK: %Zx", k);
    }
    gmp_printf("\nX: %Zx\n", x);
    gmp_printf("Y: %Zx\n", y);
}

void Point::printDec()
{
    gmp_printf("\n x: %Zd", x);
    gmp_printf("\n y: %Zd", y);
    gmp_printf("\n");
}

void Point::printHex()
{
    gmp_printf("\n x: %Zx", x);
    gmp_printf("\n y: %Zx", y);
    if (keyKnown)
    {
        gmp_printf("\n k: %Zx", k);
    }
    else
    {
        gmp_printf("\n k +: %Zx", k);
    }
    gmp_printf("\n");
}



bool Point::checkY() 
{
    pow(t1, y, two);
    pow(t2, x, three);
    add(t2, t2, seven);
    if(mpz_cmp(t1, t2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char *Point::generateY()
{
    pow(t1, x, three);                 // X^3
    add(t2, t1, seven);                // X^3 + 7
    modSqrt(t1, t2);                   // sqrt(X^3 + 7)
    mpz_get_str(outputString, PREFFERED_BASE, t1); // output Y
    gmp_printf("Y: %Zx\n", t1);
    neg(t2, t1);
    mpz_get_str(outputString, PREFFERED_BASE, t2); // output -Y
    gmp_printf("-Y: %Zx\n", t2);
    return outputString;
}
///Jacoby (cartesian) points

///TODO: Implement Jacoby type operations for accelerated point multiplication