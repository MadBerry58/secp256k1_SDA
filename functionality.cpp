#ifndef OPERATORS
#define OPERATORS
#include "include/Operators.h"
#endif

int startIteration(bool &listLoaded, bool &pointLoaded, std::set<unsigned int> LSBset, Point runningT, Point runningNT, mpz_t &counter, std::ofstream matches_write,
                   int &jump, int subJumps, int jumps, std::ofstream checkPoint_write, Point sJ, Point G, Point T, Point J2)
{
    mpz_t search_space;
    mpz_init_set_str(search_space, "2044472428167007402249549317371870405449633012157584065567923", 10);
    std::string userBuffer;
    char counterOutput[1024];
    
    if (listLoaded && pointLoaded)
    {
        gmp_printf("Iteration starting at %Zd\n", counter);

        /// Check if coordinates are already in the list
        if (LSBset.find(runningT.getLSB()) != LSBset.end())
        {
            std::cout << "Target hash inside cardinal list\n";
            mpz_get_str(counterOutput, 10, counter);
            userBuffer = "pMatch";
            userBuffer.append(counterOutput);
            matches_write.open(userBuffer);
            matches_write << "(Q + " << counterOutput << ")\n";
            matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
            matches_write.close();
        }

        if (LSBset.find(runningNT.getLSB()) != LSBset.end())
        {
            std::cout << "Target hash inside cardinal list\n";
            mpz_get_str(counterOutput, 10, counter);
            userBuffer = "nMatch";
            userBuffer.append(counterOutput);
            matches_write.open(userBuffer);
            matches_write << "(Q + " << counterOutput << ")\n";
            matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
            matches_write.close();
        }

        unsigned int i = jump;
        // TODO: segment loop to avoid if every iteration

        while (mpz_cmp(search_space, counter))
        { /// while counter < search space
            for (; i < jumps; ++i)
            { /// jumps inside subInterval
                if ((i & 255) == 0)
                {
                    mpz_get_str(counterOutput, 10, counter);
                    std::cout << "Checkpoint iteration: " << counterOutput << " jump " << i << "\n";

                    checkPoint_write.open("checkpoint");
                    checkPoint_write << "Target\n"
                                     << T.getX() << "\n"
                                     << T.getY() << "\n";
                    checkPoint_write << "Iteration\n"
                                     << counterOutput << "\n";
                    checkPoint_write << "Jump\n"
                                     << i << "\n";
                    checkPoint_write << "Running pTarget"
                                     << "\n"
                                     << runningT.getX() << "\n"
                                     << runningT.getY() << "\n";
                    checkPoint_write << "Running nTarget"
                                     << "\n"
                                     << runningNT.getX() << "\n"
                                     << runningNT.getY() << "\n";
                    checkPoint_write.close();
                }
                for (auto j = 0; j < subJumps; ++j)
                { /// subJumps inside Jump

                    runningT.addPoint(runningT, sJ);
                    runningNT.addPoint(runningNT, sJ);
                    if (LSBset.find(runningT.getLSB()) != LSBset.end())
                    {
                        mpz_get_str(counterOutput, 10, counter);
                        userBuffer = "pMatch";
                        userBuffer.append(counterOutput);
                        matches_write.open(userBuffer);
                        matches_write << "(Q + " << counterOutput << ") + (J * " << i << ") + (sJ * " << j + 1 << ")\n";
                        // TODO: register key instead of J/SJ
                        matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                        matches_write.close();
                    }
                    if (LSBset.find(runningNT.getLSB()) != LSBset.end())
                    {
                        mpz_get_str(counterOutput, 10, counter);
                        userBuffer = "nMatch";
                        userBuffer.append(counterOutput);
                        matches_write.open(userBuffer);
                        matches_write << "(-Q + " << counterOutput << ") + (J * " << i << ") + (sJ * " << j + 1 << ")\n";
                        matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                        matches_write.close();
                    }
                }

                runningT.addPoint(runningT, G);
                runningNT.addPoint(runningNT, G);

                if (LSBset.find(runningT.getLSB()) != LSBset.end())
                {
                    mpz_get_str(counterOutput, 10, counter);
                    userBuffer = "pMatch";
                    userBuffer.append(counterOutput);
                    matches_write.open(userBuffer);
                    matches_write << "(Q + " << counterOutput << ") + (J * " << i + 1 << ")\n";
                    matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                    matches_write.close();
                }
                if (LSBset.find(runningNT.getLSB()) != LSBset.end())
                {
                    mpz_get_str(counterOutput, 10, counter);
                    userBuffer = "nMatch";
                    userBuffer.append(counterOutput);
                    matches_write.open(userBuffer);
                    matches_write << "(-Q + " << counterOutput << ") + (J * " << i + 1 << ")\n";
                    matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                    matches_write.close();
                }
            }

            i = 0;

            runningT.addPoint(runningT, J2);
            runningNT.addPoint(runningNT, J2);
            mpz_add_ui(counter, counter, 1);

            if (LSBset.find(runningT.getLSB()) != LSBset.end())
            {
                mpz_get_str(counterOutput, 10, counter);
                userBuffer = "matches/pMatch";
                userBuffer.append(counterOutput);
                matches_write.open(userBuffer);
                matches_write << "(Q + " << counterOutput << ")\n";
                matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                matches_write.close();
            }
            if (LSBset.find(runningNT.getLSB()) != LSBset.end())
            {
                mpz_get_str(counterOutput, 10, counter);
                userBuffer = "matches/nMatch";
                userBuffer.append(counterOutput);
                matches_write.open(userBuffer);
                matches_write << "(-Q + " << counterOutput << ")\n";
                matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                matches_write.close();
            }
        }
    }
    else
    {
        std::cout << "Point or Cardinal List not loaded\n";
    }
    return 0;
}

int generateExplicitList(Point A, Point G, Point I, Point sI, Point J, Point sJ, int intervals, int subIntervals, std::ofstream cardinalPoints){
    char user_input = 's';
    std::cout << "The list needs 20GB of disk space. Are you sure?(Y/n)\n";
    // TODO: preallocate needed space
    std::cin >> user_input;
    if (user_input == 'Y')
    {
        std::cout << "Generating explicit cardinal points file";
        cardinalPoints.open("cardinalPoints");
        cardinalPoints << "G:\n"
                       << G.getK() << "\n"
                       << G.getX() << "\n"; /// Generator - Interval * 0 + 1 (0 is the point at infinity)
        cardinalPoints << "I:\n"
                       << I.getK() << "\n"
                       << I.getX() << "\n"; /// Interval
        cardinalPoints << "sI:\n"
                       << sI.getK() << "\n"
                       << sI.getX() << "\n"; /// SubInterval - sI * n + G = I
        cardinalPoints << "J:\n"
                       << J.getK() << "\n"
                       << J.getX() << "\n";
        cardinalPoints << "sJ:\n"
                       << sJ.getK() << "\n"
                       << sJ.getX() << "\n";

        for (int i = 0; i < intervals / 2; ++i)
        {
            for (int j = 0; j < subIntervals; ++j)
            {
                A.addPoint(A, sI);
                cardinalPoints << "Interval: " << i << " Subinterval: " << j + 1 << "\n"
                               << A.getK() << "\n"
                               << A.getX() << "\n";
            }
            A.addPoint(A, G);
            cardinalPoints << "Interval: " << i + 1 << "\n"
                           << A.getK() << "\n"
                           << A.getX() << "\n";
        }
        cardinalPoints.close();
        std::cout << "Explicit cardinal points file generated\n";
    }
    else
    {
        std::cout << "Exiting\n";
        
    }
    return 0;
}