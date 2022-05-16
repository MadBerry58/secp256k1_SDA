#include "functionalityTest.h"

int testFunctionality(bool testingType)
{
    /// generate points from from 2^0 to 2^256
    std::ofstream Gfile;
    Gfile.open("GeneratorEnum.h");
    if (Gfile.is_open())
    {
        mpz_t factor;
        mpz_init_set_ui(factor, 2); // Test mpz functionality
        Point G;                    /// Test basic point initialiser
        G.printPointInfo();
        Gfile
            << "int generatorConstantsInit()\n"
            << "{\n"
            << "  std::map<int, std::string> kGs;\n"
            << "  std::map<int, std::string> xGs;\n"
            << "  std::map<int, std::string> yGs;\n\n";

        for (int i = 0; i < 256; i++)
        {
            Gfile << "  kGs.insert(std::pair<int, std::string>(" << i << ", \" " << G.getK() << " \"));"
                  << "\n"
                  << "  xGs.insert(std::pair<int, std::string>(" << i << ", \" " << G.getX() << " \"));"
                  << "\n"
                  << "  yGs.insert(std::pair<int, std::string>(" << i << ", \" " << G.getY() << " \"));"
                  << "\n\n";
            G *= factor;
        }
        Gfile << "  return 0;\n"
              << "}\n";
    }
    else
    {
        std::cout << "Could not open file"
                  << "\n";
    }
    Gfile.close();
    return TEST_PASSED;
}