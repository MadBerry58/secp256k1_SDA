//
// Created by blackberry on 10.01.2021.
//

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
Point::Point(const char xString[], const char yString[]) {
    mpz_init_set_str(this->x, xString, 16);
    mpz_init_set_str(this->y, yString, 16);
    mpz_init_set_d(t1, 0);
    mpz_init_set_d(t2, 0);
    mpz_init_set_d(m, 1);
    mpz_init_set_d(n, 1);
    mpz_init_set_d(k, 0);
}
Point::Point(const char *xString, const char *yString,const char *kString) {
    mpz_init_set_str(this->x, xString, 16);
    mpz_init_set_str(this->y, yString, 16);
    mpz_init_set_d(t1, 0);
    mpz_init_set_d(t2, 0);
    mpz_init_set_d(m, 1);
    mpz_init_set_d(n, 1);
    mpz_init_set_str(k, kString, 16);
    keyKnown = true;
}
Point::~Point(){
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(t1);
    mpz_clear(t2);
    mpz_clear(m);
    mpz_clear(n);
    mpz_clear(k);
}

void Point::negate() {
    neg(y, y);
}

void Point::addPoint(Point &result, Point &B){
//     m = div(sub(yP2,yP1) , sub(xP2,xP1));
//     n = sub(yP1 , mul(m,xP1));
//    result.x = sub(sub(mul(m,m) ,(xP1)) , (xP2));
//    result.y = neg(add(mul(m,result.x) , n));
    addKeys(result.k, k, B.k);
    sub(t1, B.y, this->y);         /// t1 = By - Ay mod p
    sub(t2, B.x, this->x);         /// t2 = Bx - Ax mod p
    div(m, t1, t2);            /// m  = t1 / t2 mod p
    mul(t1, m, this->x);           /// t1 = m * Ax mod p
    sub(n, this->y, t1);           /// n = Ax - t1 mod p
    pow(t1, m, two);             /// t1 = m * m
    sub(t2, t1, this->x);          /// t2 = t1 - Ax
    sub(result.x, t2, B.x);    /// Cx = t2 - Bx
    mul(t1, m, result.x);      /// t1 = m * Cx
    add(t2, t1, n);            /// t2 = t1 + n
    neg(result.y, t2);         /// Cy = neg(t2)
}

void Point::multiplyBy2(Point &result){
//	m = (3 * X²) / (2 * sqrt(X²+7))
//	n = Y - m * X;
//	result.x = m² - 2*X
//	result.y = -(m*result.x + n)
// -------------------- //
    pow(m, x, two); //pow(X,TWO)
    mul(t1, three, m); //mul(THREE, pow(X,TWO))
    pow(m, x, three); //pow(X,THREE)
    add(t2, m, seven); //add(pow(X,THREE),SEVEN)
    modSqrt(m, t2); //sqrt(add(pow(X,THREE),SEVEN))
    mul(t2, m, two); //mul(TWO , sqrt(add(pow(X,THREE),SEVEN)))
    mul(t2, y, two); //mul(TWO, y)
    div(m, t1, t2); //m = div(mul(THREE, pow(X,TWO)) , mul(TWO , sqrt(add(pow(X,THREE),SEVEN))));
    mul(t1, m, x); //mul(m,X)
    sub(n, y, t1); //n = sub(Y , mul(m,X));
    mul(t1, x, two); // mul(TWO,X)
    pow(t2, m, two); // pow(m,TWO)
    sub(result.x, t2, t1); // result.x = sub(pow(m,TWO) , mul(TWO,X));
    mul(t1, m, result.x); //mul(m, result.x)
    add(t2, t1, n); //add(mul(m, result.x) , n)
    neg(result.y, t2); //result.y = neg(add(mul(m, result.x) , n));
}

void Point::multiplyByFactor(Point &result, mpz_t &factor){
    Point temp(xG, yG);
    mpz_set(temp.x, this->x);
    mpz_set(temp.y, this->y);
    
    unsigned int i = 0;
    while(mpz_tstbit(factor, i) == 0){
        temp.multiplyBy2(temp);
        ++i;
    }
    mpz_set(result.x, temp.x);
    mpz_set(result.y, temp.y);
    temp.multiplyBy2(temp);
    ++i;
    for(;i < mpz_sizeinbase(factor, 2); ++i){
        if(mpz_tstbit(factor, i)){
            result.addPoint(result, temp);
        }
        temp.multiplyBy2(temp);
    }

}

void Point::printDec(){
    gmp_printf("\n x: %Zd", x);
    gmp_printf("\n y: %Zd", y);
    gmp_printf("\n");
}
void Point::printHex(){
    gmp_printf("\n x: %Zx", x);
    gmp_printf("\n y: %Zx", y);
    if(keyKnown)
        gmp_printf("\n k: %Zx", k);
    else
        gmp_printf("\n k +: %Zx", k);
    gmp_printf("\n");
}
char *Point::getX() {
    return mpz_get_str(outputString, 16, x);
}
char *Point::getY() {
    return mpz_get_str(outputString, 16, y);
}
char *Point::generateY() {
    pow(t1, x, three); //X^3
    add(t2, t1, seven);//X^3 + 7
    modSqrt(t1, t2); //sqrt(X^3 + 7)
    mpz_get_str(outputString, 16, t1); //output Y
    gmp_printf("Y: %Zx\n", t1);
    neg(t2, t1);
    mpz_get_str(outputString, 16, t2); //output -Y
    gmp_printf("-Y: %Zx\n", t2);
    return outputString;
}
char *Point::getK() {
    if(keyKnown){
        return mpz_get_str(outputString, 16, k);
    }else
        mpz_get_str(outputString, 16, k);
    strcat(outputString, "+");
    return outputString;
}
void Point::setX(const char *xCoordinate, int base){
    mpz_set_str(x, xCoordinate, base);
}
void Point::setY(const char *yCoordinate, int base){
    mpz_set_str(y, yCoordinate, base);
}
void Point::setK(const char *kValue, int base){
    mpz_set_str(k, kValue, base);
}

unsigned long Point::getLSB() {
    return x->_mp_d[0];
}

void Point::printPointInfo(char *pointName){
    gmp_printf("Point ", pointName);
    if(keyKnown)gmp_printf("\nK: %Zx", k);
    gmp_printf("\nX: %Zx\n", x);
    gmp_printf("Y: %Zx\n", y);
};

bool Point::checkY() {
    pow(t1, y, two);
    pow(t2, x, three);
    add(t2, t2, seven);
    if(mpz_cmp(t1, t2) == 0){
        return true;
    }else{
        return false;
    }
}

///Jacoby (cartesian) points