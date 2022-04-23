#include "include/Operators.h"

int generatePointsFile(std::ofstream cardinalLSB_write, std::set<unsigned long> LSBset, Point G, Point I , Point sI, Point J, Point sJ, Point A,  int intervals, int subIntervals){
    bool* listLoaded;
    cardinalLSB_write.open("cardinalLSB");
    LSBset.insert(G.getLSB());
    cardinalLSB_write << G.getLSB() << "\n";
    LSBset.insert(I.getLSB());
    cardinalLSB_write << I.getLSB() << "\n";
    LSBset.insert(sI.getLSB());
    cardinalLSB_write << sI.getLSB() << "\n";
    LSBset.insert(J.getLSB());
    cardinalLSB_write << J.getLSB() << "\n";
    LSBset.insert(sJ.getLSB());
    cardinalLSB_write << sJ.getLSB() << "\n";
    char user_input = 's';
    // TODO: create a filename generator to output multiple files.

    std::cout << "The list needs 2.5GB of disk space and will take a good while. Are you sure?(Y/n)\n";
    // TODO: preallocate needed space
    // TODO: add low entropy bitsets
    std::cin >> user_input;
    if (user_input == 'Y')
    {
        std::cout << "Generating new LSB file\n";
        /// TODO: Generate cardinal Points function
        std::cout << "Cardinal point file generated\n";
        // std::cout << "Elements in set: "<< LSB_cardinal.size() << "\n";
        *listLoaded = true;
    }
    else
    {
        std::cout << "Exiting to menu\n";
    }
    

    for (int i = 0; i < intervals / 2; ++i)
    {
        for (int j = 0; j < subIntervals; ++j)
        {
            A.addPoint(A, sI);
            LSBset.insert(A.getLSB());
            cardinalLSB_write << A.getLSB() << "\n";
        }
        A.addPoint(A, G);
        LSBset.insert(A.getLSB());
        cardinalLSB_write << A.getLSB() << "\n";
    }
    cardinalLSB_write.close();
    return 0;
}


int restoreCheckpoint(std::ifstream checkPoint_read, Point T , int* jump, Point runningT, Point runningNT, bool* pointLoaded)
{
    std::string line;
    mpz_t counter;
    checkPoint_read.open("checkpoint");
    if(checkPoint_read.is_open()){
        getline(checkPoint_read, line);
        if ("Target" == line){
            getline(checkPoint_read, line);
            T.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            T.setY(line.c_str(), 16);
            std::cout << "Target:\nX: " << T.getX() << "\nY: "<< T.getY() <<"\n";
            if(!T.checkY()){std::cout << "Target not valid\n";
            ///TODO: add error handling
            }
        }
        else
        {
            std::cout << "Target not found\n";
        }
        getline(checkPoint_read, line);
        if ("Iteration" == line) {
            getline(checkPoint_read, line);
            mpz_set_str(counter, line.c_str(), 10);
        } 
        else 
        {
            std::cout << "Iteration count not found\n";
        }
        getline(checkPoint_read, line);
        if ("Jump" == line) {
            getline(checkPoint_read, line);
            *jump = std::stoi(line);
            std::cout << "Jump:\n" << jump <<"\n";
        } else {std::cout << "Jump not found\n";}
        getline(checkPoint_read, line);
        if ("Running pTarget" == line) {
            getline(checkPoint_read, line);
            runningT.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            runningT.setY(line.c_str(), 16);
            std::cout << "Running pTarget:\nX: " << runningT.getX() << "\nY: "<< runningT.getY() <<"\n";
        }else{std::cout << "pTarget not found\n";}
        getline(checkPoint_read, line);
        if ("Running nTarget" == line) {
            getline(checkPoint_read, line);
            runningNT.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            runningNT.setY(line.c_str(), 16);
            std::cout << "Running nTarget:\nX: " << runningNT.getX() << "\nY: "<< runningNT.getY() <<"\n";
        }else{std::cout << "nTarget not found\n";}
        //TODO: compare  (Target + temp) to pTarget
        //TODO: compare (-Target + temp) to nTarget
    }
    checkPoint_read.close();
    std::cout << "Checkpoint Restored\n";
    *pointLoaded = true;
    return 0;
}
    
int resumeCheckpoint(std::ifstream checkPoint_read, Point T, Point runningT,Point runningNT, int* jump, bool* pointLoaded)
{
    std::string line;
    mpz_t counter;
    checkPoint_read.open("checkpoint");
    if (checkPoint_read.is_open())
    {
        getline(checkPoint_read, line);
        if ("Target" == line)
        {
            getline(checkPoint_read, line);
            T.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            T.setY(line.c_str(), 16);
            std::cout << "Target:\nX: " << T.getX() << "\nY: " << T.getY() << "\n";
            if (!T.checkY())
            {
                std::cout << "Target not valid\n";
            }
        }
        else
        {
            std::cout << "Target not found\n";
        }
        getline(checkPoint_read, line);
        if ("Iteration" == line)
        {
            getline(checkPoint_read, line);
            mpz_set_str(counter, line.c_str(), 10);
        }
        else
        {
            std::cout << "Iteration count not found\n";
        }
        getline(checkPoint_read, line);
        if ("Jump" == line)
        {
            getline(checkPoint_read, line);
            *jump = std::stoi(line);
            std::cout << "Jump:\n"
                      << jump << "\n";
        }
        else
        {
            std::cout << "Jump not found\n";
        }
        getline(checkPoint_read, line);
        if ("Running pTarget" == line)
        {
            getline(checkPoint_read, line);
            runningT.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            runningT.setY(line.c_str(), 16);
            std::cout << "Running pTarget:\nX: " << runningT.getX() << "\nY: " << runningT.getY() << "\n";
        }
        else
        {
            std::cout << "pTarget not found\n";
        }
        getline(checkPoint_read, line);
        if ("Running nTarget" == line)
        {
            getline(checkPoint_read, line);
            runningNT.setX(line.c_str(), 16);
            getline(checkPoint_read, line);
            runningNT.setY(line.c_str(), 16);
            std::cout << "Running nTarget:\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() << "\n";
        }
        else
        {
            std::cout << "nTarget not found\n";
        }
        // TODO: compare  (Target + temp) to pTarget
        // TODO: compare (-Target + temp) to nTarget
    }
    checkPoint_read.close();
    std::cout << "Checkpoint Restored\n";
    *pointLoaded = true;
    return 0;
}

int loadPoints(std::ifstream cardinalLSB_read, bool* listLoaded){
    std::string line;
    std::set<unsigned long> LSB_cardinal;
    cardinalLSB_read.open("cardinalLSB");
    if (cardinalLSB_read.is_open())
    {
        std::cout << "Loading cardinal LSB file\n";
        while (getline(cardinalLSB_read, line))
        {
            LSB_cardinal.insert(std::stoul(line));
        }
        cardinalLSB_read.close();
    }
    else
    {
        std::cout << "Could not open cardinalLSB file\n";
    }
    std::cout << "Cardinal LSB list loaded\n"
              << "Elements in set: " << LSB_cardinal.size() << "\n";
    *listLoaded = true;
    return 0;
}

int createNewTargetFile(Point T, Point runningT, Point runningNT, Point temp, mpz_t &search_space)
{
    int jump;
    mpz_t counter;
    std::string userBuffer;
    bool* pointLoaded;
    std::cout << "Insert target's X coordinate (base 16)\n";
    std::cin >> userBuffer;
    T.setX(userBuffer.c_str(), 16);
    runningT.setX(userBuffer.c_str(), 16);
    runningNT.setX(userBuffer.c_str(), 16);

    std::cout << "Insert target's Y coordinate (base 16)\n";
    std::cin >> userBuffer;
    T.setY(userBuffer.c_str(), 16);
    runningT.setY(userBuffer.c_str(), 16);
    runningNT.setY(userBuffer.c_str(), 16);
    runningNT.negate(); /// prepare point -T

    if (T.checkY())
    {
        std::cout << "Point valid\n";
        *pointLoaded = true;
    }
    else
    {
        std::cout << "Point not valid\n";
        *pointLoaded = false;
    }

    std::cout << "Insert iteration counter (base 10)\n";
    std::cin >> userBuffer;
    mpz_set_str(counter, userBuffer.c_str(), 10);
    mpz_init_set_str(search_space, "2044472428167007402249549317371870405449633012157584065567923", 10);

    if (mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1))
    {
        gmp_printf("Counter set to %Zd\n", counter);
    }
    else
    {
        gmp_printf("Counter not inside search space\n");
    }

    if (mpz_cmp_ui(counter, 0))
    {
        temp.multiplyByFactor(temp, counter);
        runningT.addPoint(runningT, temp);
        runningNT.addPoint(runningNT, temp);
    }

    gmp_printf("Iteration ready at point %Zd\n", counter);
    std::cout << "Positive point: \n xT: " << runningT.getX() << "\n yT: " << runningT.getY() << "\n";
    std::cout << "Negative point: \nxNT: " << runningNT.getX() << "\nyNT: " << runningNT.getY();
    *pointLoaded = true;
    jump = 0;
    return 0;
}