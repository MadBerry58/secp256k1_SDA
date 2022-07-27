#ifndef SECP251K1_SANDBOX_ARITHMETICTEST_C
#define SECP251K1_SANDBOX_ARITHMETICTEST_C

#include "TestUI.h"

unsigned int ArithmeticTestUI(char &user_input, std::string &user_long_input)
{
    mpz_t temp1;
    mpz_t temp2;
    mpz_t temp3;
    mpz_init_set_ui(temp1,0u);
    mpz_init_set_ui(temp2,0u);
    mpz_init_set_ui(temp3,0u);
    Point tempPoint1;
    Point tempPoint2;
    Point tempPoint3;
    unsigned int containerIndex = 0u;
    Point pointContainer[10];

    std::cout << "\n"
                <<  "Select Arithmetic Operation:\n"
                <<  "(@) Point Generation\n"
                <<  "(+) Point Addition\n"
                <<  "(-) Point Subtraction\n"
                <<  "(*) Point Multiplication\n"
                <<  "(/) Point Division\n"
                <<  "(S) Save last result in a new entry"
                <<  "(I) Select result index"
                <<  "(D) Display selected index"
                <<  "(=) Compare Points\n"
                <<  "(T) Back to Top\n"
                <<  "\n";
    while(user_input != 'T')
    {
        std::cin >> user_input;
        switch(user_input)
        {
            case '@':
                std::cout << "Insert point key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;
                tempPoint1.printPointInfo();
                break;

            case '+':
                std::cout << "Insert point A key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;

                std::cout << "Insert point B key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp2, user_long_input.c_str(), 16);
                tempPoint2 = temp2;

                tempPoint1 += tempPoint2;

                tempPoint1.printPointInfo();
                break;

            case '-':
                std::cout << "Insert point A key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;

                std::cout << "Insert point B key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp2, user_long_input.c_str(), 16);
                tempPoint2 = temp2;

                tempPoint1 -= tempPoint2;

                tempPoint1.printPointInfo();
                break;

            case '*':
                std::cout << "Insert point A key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;

                std::cout << "Insert scalar B (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp2, user_long_input.c_str(), 16);

                tempPoint1 *= temp2;

                tempPoint1.printPointInfo();
                break;

            case '/':
                std::cout << "Insert point A key (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;

                std::cout << "Insert scalar B (hex):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp2, user_long_input.c_str(), 16);

                tempPoint1 /= temp2;

                tempPoint1.printPointInfo();
                break;

            case '=':
                std::cout << "Insert point A index (dec):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp1, user_long_input.c_str(), 16);
                tempPoint1 = temp1;
                std::cout << "Point A:\n";
                tempPoint1.printPointInfo();

                std::cout << "Insert point B index (dec):\n";
                std::cin >> user_long_input;
                mpz_set_str(temp2, user_long_input.c_str(), 16);
                tempPoint2 = temp2;
                std::cout << "Point A:\n";
                tempPoint2.printPointInfo();

                if(tempPoint1 == tempPoint2)
                    std::cout << "Points are equal\n";
                else
                    std::cout << "Points are not equal\n";

                tempPoint1.printPointInfo();
                break;
            
            case 'I':
                std::cout << "Select Index:\n";
                std::cin >> containerIndex;
                std::cout << "Selected Index:\n" << containerIndex << "\n";
                break;

            case 'S':
                pointContainer[containerIndex] = tempPoint1;
                std::cout << "Point saved on index " << containerIndex << "\n";
                break;
        }
    }
    return 0;
}

#endif