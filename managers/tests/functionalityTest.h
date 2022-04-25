#ifndef SECP251K1_SANDBOX_ITERATION_TEST_H
#define SECP251K1_SANDBOX_ITERATION_TEST_H
#include "../../src/headers/Point.h"
#include "../../managers/headers/fileManager.h"

#define TESTING_AUTOMATIC       0u
#define TESTING_MANUAL          1u
#define TEST_FAILED             0u
#define TEST_PASSED             1u

int testFunctionality(bool testingType = TESTING_MANUAL)
{
    ///generate points from from 2^0 to 2^256
    std::ofstream Gfile;
    Gfile.open("GFile");
    if(Gfile.is_open())
    {
        mpz_t factor;
        mpz_init_set_ui(factor, 2); //Test mpz functionality
        Point G; ///Test basic point initialiser
        G.printPointInfo();
        for(int i = 0; i < 256; i++)
        {
            Gfile << "#define kG" << i << "_String \"" << G.getK() << "\"\n"
                  << "#define xG" << i << "_String \"" << G.getX() << "\"\n"
                  << "#define yG" << i << "_String \"" << G.getY() << "\"\n\n";
            G *= factor;
        }

    }
    else
    {
        std::cout << "Could not open file" << "\n";
    }
    Gfile.close();
    return TEST_PASSED;
}
// int verboseTestRoutine(Point runningT, Point runningNT, Point temp, Point G, Point T, Point J, Point sJ, Point J2, mpz_t &container,
//                        std::ofstream checkPoint_write, std::ifstream checkPoint_read, std::set<unsigned int> LSBset, mpz_t &counter,
//                        mpz_t &search_space)
// {

//     char testInput;
//     std::string userBuffer;
//     std::string line;
//     bool pointLoaded;
//     bool listLoaded;
//     int subJumps;
//     int jumps;
//     int jump;
//     char counterOutput[1024];

//     std::cout << "Selecte test mode: \n(A)rithmetic, (I)teration, (U)tility\n";
//     std::cin >> testInput;

//     switch (testInput)
//     {
//     case 'A':
//         std::cout << "Selecte test operation: \n(A)ddition, (S)ubtraction, (D)ouble, (M)ultiplication, (B)ack\n";
//         std::cin >> testInput;
//         switch (testInput)
//         {
//         case 'A':
//             std::cout << "Insert point A X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point A Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setY(userBuffer.c_str(), 16);

//             if (runningT.checkY())
//             {
//                 std::cout << "Point A valid\n";
//             }
//             else
//             {
//                 std::cout << "Point A not valid\n";
//                 break;
//             }

//             std::cout << "Insert point B X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningNT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point B Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningNT.setY(userBuffer.c_str(), 16);

//             if (runningNT.checkY())
//             {
//                 std::cout << "Point B valid\n";
//             }
//             else
//             {
//                 std::cout << "Point B not valid\n";
//                 break;
//             }

//             runningT.addPoint(temp, runningNT);
//             std::cout << "A + B = T\n";
//             std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY() << "\n";

//             break;

//         case 'S':
//             std::cout << "Insert point A X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point A Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setY(userBuffer.c_str(), 16);

//             if (runningT.checkY())
//             {
//                 std::cout << "Point A valid\n";
//             }
//             else
//             {
//                 std::cout << "Point A not valid\n";
//                 break;
//             }

//             std::cout << "Insert point B X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningNT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point B Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningNT.setY(userBuffer.c_str(), 16);

//             if (runningNT.checkY())
//             {
//                 std::cout << "Point B valid\n";
//             }
//             else
//             {
//                 std::cout << "Point B not valid\n";
//                 break;
//             }

//             runningNT.negate();
//             runningT.addPoint(temp, runningNT);
//             std::cout << "A - B = T\n";
//             std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY() << "\n";

//             break;

//         case 'D':
//             std::cout << "Insert point A X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point A Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setY(userBuffer.c_str(), 16);

//             if (runningT.checkY())
//             {
//                 std::cout << "Point A valid\n";
//             }
//             else
//             {
//                 std::cout << "Point A not valid\n";
//                 break;
//             }
//             runningT.multiplyBy2(temp);

//             if (temp.checkY())
//             {
//                 std::cout << "A * 2 Valid\n";
//                 std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY() << "\n";
//             }
//             else
//             {
//                 std::cout << "A * 2 Invalid\n";
//                 std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY() << "\n";
//                 break;
//             }
//             break;

//         case 'M':
//             std::cout << "Insert point A X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert point A Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             runningT.setY(userBuffer.c_str(), 16);

//             if (runningT.checkY())
//             {
//                 std::cout << "Point A valid\n";
//             }
//             else
//             {
//                 std::cout << "Point A not valid\n";
//                 break;
//             }

//             std::cout << "Insert factor (base 16)\n";
//             std::cin >> userBuffer;
//             mpz_set_str(container, userBuffer.c_str(), 16);

//             runningT.multiplyByFactor(temp, container);
//             gmp_printf("A * %Zx\n", container);
//             std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY() << "\n";
//             break;

//         case 'B':
//             break;
//         default:
//             std::cout << "Unknown option selected\n";
//         }
//         break;

//     case 'I':
//         std::cout << "Insert target's X coordinate (base 16)\n";
//         std::cin >> userBuffer;
//         T.setX(userBuffer.c_str(), 16);
//         runningT.setX(userBuffer.c_str(), 16);
//         runningNT.setX(userBuffer.c_str(), 16);

//         std::cout << "Insert target's Y coordinate (base 16)\n";
//         std::cin >> userBuffer;
//         T.setY(userBuffer.c_str(), 16);
//         runningT.setY(userBuffer.c_str(), 16);
//         runningNT.setY(userBuffer.c_str(), 16);

//         runningNT.negate(); /// prepare point -T

//         if (T.checkY())
//         { /// if the point is valid, proceed with the iteration
//             std::cout << "Point valid\n";
//         }
//         else
//         {
//             std::cout << "Point invalid\n";
//             break;
//         }

//         std::cout << "Selecte test operation: \n(J)umps, (S)ubJumps, (I)terate Jumps, (F)ull Iteration\n";
//         std::cin >> testInput;
//         switch (testInput)
//         {
//         case 'J':
//             std::cout << "Number of jumps:\n";
//             int testJumps;
//             std::cin >> testJumps;
//             for (auto j = 0; j < testJumps; ++j)
//             {
//                 runningT.addPoint(runningT, J);
//                 runningNT.addPoint(runningNT, J);
//             }
//             std::cout << " Point + " << testJumps << " * J\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n\n";
//             std::cout << "NPoint + " << testJumps << " * J\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
//             break;
//         case 'S':
//             std::cout << "Number of subJumps:\n";
//             int testSubJumps;
//             std::cin >> testSubJumps;
//             for (auto j = 0; j < testSubJumps; ++j)
//             {
//                 runningT.addPoint(runningT, sJ);
//                 runningNT.addPoint(runningNT, sJ);
//             }
//             std::cout << " Point + " << testSubJumps << " * sJ\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n\n";
//             std::cout << "NPoint + " << testSubJumps << " * sJ\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
//             break;

//         case 'I':
//             std::cout << "Number of Jumps:\n";
//             int testIteration;
//             std::cin >> testIteration;
//             for (auto i = 0; i < testIteration; ++i)
//             {
//                 for (auto j = 0; j < subJumps; ++j)
//                 {
//                     runningT.addPoint(runningT, sJ);
//                     runningNT.addPoint(runningNT, sJ);
//                 }
//                 runningT.addPoint(runningT, G);
//                 runningNT.addPoint(runningNT, G);
//             }
//             std::cout << " Point + " << testIteration << " * (sj * SJ + 1)\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n\n";
//             std::cout << "NPoint + " << testIteration << " * (sj * SJ + 1)\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
//             break;

//         case 'F':
//             std::cout << "Number of Iterations:\n";
//             int testIterations;
//             std::cin >> testIterations;
//             for (auto it = 0; it < testIterations; ++it)
//             {
//                 for (auto i = 0; i < jumps; ++i)
//                 {
//                     for (auto j = 0; j < subJumps; ++j)
//                     {
//                         runningT.addPoint(runningT, sJ);
//                         runningNT.addPoint(runningNT, sJ);
//                     }
//                     runningT.addPoint(runningT, G);
//                     runningNT.addPoint(runningNT, G);
//                 }
//                 runningT.addPoint(runningT, J2);
//                 runningNT.addPoint(runningNT, J2);
//             }

//             std::cout << " Point + " << testIterations << "\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n\n";
//             std::cout << "NPoint + " << testIterations << "\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
//             break;
//         default:
//             std::cout << "Unknown option selected\n";
//             break;
//         }
//         break;

//     case 'U':
//         std::cout << "Selecte test operation: \n (L)oad Checkpoint, (S)et size test, (E)xtract Iterator Key\n(F)ind in list, (C)ount numbers in list\n(G)enerate checkpoints\n";
//         std::cin >> testInput;
//         switch (testInput)
//         {
//         case 'L':
//             checkPoint_read.open("checkpoint");
//             if (checkPoint_read.is_open())
//             {
//                 getline(checkPoint_read, line);
//                 if ("Target" == line)
//                 {
//                     getline(checkPoint_read, line);
//                     T.setX(line.c_str(), 16);
//                     getline(checkPoint_read, line);
//                     T.setY(line.c_str(), 16);
//                     if (!T.checkY())
//                     {
//                         std::cout << "Target not valid\n";
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     std::cout << "Target not found\n";
//                 }
//                 getline(checkPoint_read, line);
//                 if ("Iteration " == line)
//                 {
//                     getline(checkPoint_read, line);
//                     mpz_set_str(counter, line.c_str(), 10);
//                     G.multiplyByFactor(temp, counter);
//                 }
//                 else
//                 {
//                     std::cout << "Iteration count not found\n";
//                 }
//                 getline(checkPoint_read, line);
//                 if ("Jump" == line)
//                 {
//                     getline(checkPoint_read, line);
//                     jump = atol(line.c_str());
//                     for (int i = 0; i < jump; ++i)
//                     {
//                         temp.addPoint(temp, J);
//                     }
//                 }
//                 else
//                 {
//                     std::cout << "Jump not found\n";
//                 }
//                 getline(checkPoint_read, line);
//                 if ("Running pTarget" == line)
//                 {
//                     getline(checkPoint_read, line);
//                     runningT.setX(line.c_str(), 16);
//                     getline(checkPoint_read, line);
//                     runningT.setY(line.c_str(), 16);
//                 }
//                 else
//                 {
//                     std::cout << "pTarget not found\n";
//                 }
//                 getline(checkPoint_read, line);
//                 if ("Running nTarget" == line)
//                 {
//                     getline(checkPoint_read, line);
//                     runningT.setX(line.c_str(), 16);
//                     getline(checkPoint_read, line);
//                     runningT.setY(line.c_str(), 16);
//                 }
//                 else
//                 {
//                     std::cout << "nTarget not found\n";
//                 }
//                 temp.addPoint(temp, T);
//                 if (runningT.getLSB() == temp.getLSB())
//                 {
//                 }
//                 // TODO: compare  (Target + temp) to pTarget
//                 // TODO: compare (-Target + temp) to nTarget
//             }
//             checkPoint_read.close();
//             std::cout << "Checkpoint Restored\n";
//             // TODO: separate N branch into New and Iterate branches to accommodate resuming iteration
//             break;
//         case 'S':
//             std::cout << "Max size of LSB: " << LSBset.max_size() << "\n";
//             std::cout << "Stress test?(Y/n)\n";
//             std::cin >> testInput;
//             if (testInput == 'Y')
//             {
//                 std::set<unsigned int> testSet;
//                 std::pair<std::set<int>::iterator, bool> ret;
//                 for (unsigned int i = 0; i < testSet.max_size(); ++i)
//                 {
//                     testSet.insert(i);
//                     printf("Elements: %lu", testSet.size());
//                 }
//             }
//             break;
//         case 'E':
//             // TODO: extract key of the added point from j, sj and i;
//             break;
//         case 'F':
//             if (listLoaded)
//             {
//                 std::cout << "Insert target's X coordinate (base 16)\n";
//                 std::cin >> userBuffer;
//                 T.setX(userBuffer.c_str(), 16);
//                 runningT.setX(userBuffer.c_str(), 16);
//                 runningNT.setX(userBuffer.c_str(), 16);

//                 std::cout << "Insert target's Y coordinate (base 16)\n";
//                 std::cin >> userBuffer;
//                 T.setY(userBuffer.c_str(), 16);
//                 runningT.setY(userBuffer.c_str(), 16);
//                 runningNT.setY(userBuffer.c_str(), 16);

//                 runningNT.negate(); /// prepare point -T

//                 if (T.checkY())
//                 { /// if the point is valid, proceed with the iteration
//                     std::cout << "Point valid\n";
//                 }
//                 else
//                 {
//                     std::cout << "Point invalid\n";
//                     break;
//                 }
//                 if (LSBset.find(runningNT.getLSB()) != LSBset.end())
//                 {
//                     std::cout << "Point in list\n";
//                 }
//                 else
//                 {
//                     std::cout << "Point not in list\n";
//                 }
//                 break;
//             }
//             else
//             {
//                 std::cout << "List not loaded\n";
//                 break;
//             }
//             break;
//         case 'C':
//             std::cout << "Elements in list: " << LSBset.size() << "\n";
//             break;
//         case 'G':
//             std::cout << "Insert target's X coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             T.setX(userBuffer.c_str(), 16);
//             runningT.setX(userBuffer.c_str(), 16);
//             runningNT.setX(userBuffer.c_str(), 16);

//             std::cout << "Insert target's Y coordinate (base 16)\n";
//             std::cin >> userBuffer;
//             T.setY(userBuffer.c_str(), 16);
//             runningT.setY(userBuffer.c_str(), 16);
//             runningNT.setY(userBuffer.c_str(), 16);
//             runningNT.negate(); /// prepare point -T

//             if (T.checkY())
//             {
//                 std::cout << "Point valid\n";
//                 pointLoaded = true;
//             }
//             else
//             {
//                 std::cout << "Point not valid\n";
//                 pointLoaded = false;
//                 break;
//             }

//             std::cout << "Insert iteration counter (base 10)\n";
//             std::cin >> userBuffer;
//             mpz_set_str(counter, userBuffer.c_str(), 10);

//             if (mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1))
//             {
//                 gmp_printf("Counter set to %Zd\n", counter);
//             }
//             else
//             {
//                 gmp_printf("Counter not inside search space\n");
//             }

//             if (mpz_cmp_ui(counter, 0))
//             {
//                 G.multiplyByFactor(temp, counter);
//                 runningT.addPoint(runningT, temp);
//                 runningNT.addPoint(runningNT, temp);
//             }

//             mpz_get_str(counterOutput, 10, counter);
//             checkPoint_write.open("checkpoint");
//             checkPoint_write << "Target\n"
//                              << T.getX() << "\n"
//                              << T.getY() << "\n";
//             checkPoint_write << "Iteration\n"
//                              << counterOutput << "\n";
//             checkPoint_write << "Jump\n"
//                              << 0 << "\n";
//             checkPoint_write << "Running pTarget"
//                              << "\n"
//                              << runningT.getX() << "\n"
//                              << runningT.getY() << "\n";
//             checkPoint_write << "Running nTarget"
//                              << "\n"
//                              << runningNT.getX() << "\n"
//                              << runningNT.getY() << "\n";
//             checkPoint_write.close();
//             break;
//         default:
//             std::cout << "Unknown option selected\n";
//             break;
//         }
//         break;
//     }
//     return 0;
// }

#endif // SECP251K1_SANDBOX_ITERATION_TEST_H