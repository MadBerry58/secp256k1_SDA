#include "include/Operators.h"
#include "threads.h"

auto intervals= 18051648; //0x1137240
char I_k[] = "EDED35E2DD180B3069CABD39C376B4D874708B552E18F3861D0FBB5F5D";
char I_x[] = "4d5ccdf43771c81a609bae495080886c7fe130c075982e9ea249f3930e619cc2";
char I_y[] = "54da63392c132035d1530469a449f4b383016c5846266e9d7ff7e67e42efe7e7";

auto subIntervals= 12; //0xC
char sI_k[] = "13D3C47D926CAB995E263A6F7AF48F1209B40B9C6E82144B2D16A4F29D";
char nsI_k[] = "FFFFFFEC2C3B826D935466A1D9C59083C61FCADCFB3D03CD3DBE135FB9914EA4";
char sI_x[] = "ae4252d8c002f5ad3f49254a8031809ebfea77efe98573263a2272aac2c9eda7";
char sI_y[] = "9268c32d7351167ad4e9c30d89579b21668c96044418974ec812660dfa90d985";
char nsI_y[] = "6d973cd28caee9852b163cf276a864de997369fbbbe768b137ed99f1056f22aa";

auto jumps= 7058; //7058 = 0x1B92 , 2* 7058 = 0x3724
char kJ[] =  "5C0D2392F0EC680CBBD9E31E72D8033A92767425B1D6705A306EEF";
char nkJ[] = "FFFFFFFFFFA3F2DC6D0F1397F344261B9C3C04E374B629C79A20881C7605D252";
char xJ[] =  "7a3e3a50b0b8a8167fb8e271f6d7636b6d328fcd9a19dd4f3dc7935b10e44e2d";
char yJ[] =  "17ec64bd587820ff7f2b830a3403a061c58f89f1a7d07f64ea9274db8b8a72ff";
char nyJ[] = "e8139b42a787df0080d47cf5cbfc5f9e3a70760e582f809b156d8b2374758930";

char kJ2[] = "FFFFFFF6161DC136C9AA3350ECE2C841406753E1D542D2047EC838F644E3C7F4";
char nkJ2[] = "9E9E23EC93655CCAF131D37BD7A478904DA05CE37410A25968B52794D";
char xJ2[] = "aea9d03ff30f72eb9efb5b6787e1ffa9970fa76e24f5485a7874ea689ec7cfd4";
char yJ2[] = "b0cfbd70128d1ed877da292de2eaae1033b59dcbee53f586436543354958e9f";
char nyJ2[] = "f4f30428fed72e1278825d6d21d1551efcc4a623411ac0a79bc9abcbab6a6d90";

auto subJumps= 18522; // 0x485A
char ksJ[] = "145B4081CC2E32B538FE828E3D0E59728A42D47EC1F61721CB3";
char xsJ[] = "3f20f070b21dc3d8502c2bc963d072fe3a4f6499983e281a425043f1188fc443";
char ysJ[] = "88728e6a46fc44c9a3aaf6f08f7f62626a58ed30de614afb75c903ab15c5a652";



std::set<unsigned long> LSB_cardinal;

///Search point
mpz_t counter; ///iteration counter
mpz_t search_space; ///maximum distance of the target from a known point
mpz_t negUserY; ///container for deducing negative Y provided by the user
mpz_t container;

std::string line;
std::string userBuffer;

bool listLoaded;
bool pointLoaded;
char counterOutput[1024];
char user_input = 's';
int jump;

int main() {
    modInit();

    std::ofstream checkPoint_write; ///write file handle used for saving checkpoints
    std::ifstream checkPoint_read;  ///read file handle used for loading checkpoints
    std::ifstream cardinalLSB_read; ///read file handle used for loading points
    std::ofstream cardinalLSB_write;///write file handle used for generating points
    std::ofstream cardinalPoints; ///write file handle used for generating the explicit point list
    std::ofstream matches_write;

    mpz_init_set_d(negUserY,  0);
    mpz_init_set_d(container, 0);
    mpz_set_ui(counter, 0);
    mpz_init_set_str(counter,      "2044472428167007402249549317371870405449633012157584065567923", 10);
    mpz_init_set_str(search_space, "2044472428167007402249549317371870405449633012157584065567923", 10);

    Point G        (xG, yG, kG);
    Point A        (xG, yG, kG); ///container point
    Point temp     (xG, yG, kG);
    Point runningT (xG, yG); ///target point
    Point runningNT(xG, yG); ///negative target point
    Point T        (xG, yG); ///Target Point
    Point nT       (xG, yG); ///Negative Target Point
    Point J2       (xJ2, yJ2, kJ2);
    Point nJ2      (xJ2, nyJ2, nkJ2);
    Point I        (I_x, I_y, I_k); ///interval between segments
    Point sI       (sI_x, sI_y, sI_k); ///interval between segments
    Point nsI      (sI_x, nsI_y, nsI_k);
    Point J        (xJ, yJ, kJ);
    Point nJ       (xJ, nyJ, nkJ);
    Point sJ       (xsJ, ysJ, ksJ); ///interval between segments


    while(user_input != 'x'){
        std::cout << "\n\nPlease select an option: \n(G)enerate cardinal LSB file\n(L)oad cardinal point file\n(N)ew point search\n(R)esume point search\n(I)terate\nE(x)it program\n\n";
        std::cin  >> user_input;

        switch(user_input){
            case 'G':  //////Generate cardinal points
                std::cout << "The list needs 2.5GB of disk space and will take a good while. Are you sure?(Y/n)\n";
                //TODO: preallocate needed space
                //TODO: add low entropy bitsets
                std::cin >> user_input;
                if(user_input == 'Y'){
                    std::cout << "Generating new LSB file\n";

                    cardinalLSB_write.open("cardinalLSB");
                    LSB_cardinal.insert(G.getLSB());
                    cardinalLSB_write << G.getLSB() << "\n";
                    LSB_cardinal.insert(I.getLSB());
                    cardinalLSB_write << I.getLSB() << "\n";
                    LSB_cardinal.insert(sI.getLSB());
                    cardinalLSB_write << sI.getLSB() << "\n";
                    LSB_cardinal.insert(J.getLSB());
                    cardinalLSB_write << J.getLSB() << "\n";
                    LSB_cardinal.insert(sJ.getLSB());
                    cardinalLSB_write << sJ.getLSB() << "\n";
                    //TODO: create a filename generator to output multiple files.
                    for(int i = 0; i < intervals / 2; ++i){
                        for(int j = 0; j < subIntervals; ++j){
                            A.addPoint(A, sI);
                            LSB_cardinal.insert(A.getLSB());
                            cardinalLSB_write << A.getLSB() << "\n";
                        }
                        A.addPoint(A, G);
                        LSB_cardinal.insert(A.getLSB());
                        cardinalLSB_write << A.getLSB() << "\n";
                    }
                    cardinalLSB_write.close();

                    std::cout << "Cardinal point file generated\n";
                    std::cout << "Elements in set: "<< LSB_cardinal.size() << "\n";
                    listLoaded = true;
                }else {std::cout << "Exiting to menu\n";break;}
                break;

            case 'L': /////Load cardinal points
                cardinalLSB_read.open("cardinalLSB");
                if(cardinalLSB_read.is_open()){
                    std::cout << "Loading cardinal LSB file\n";
                    while(getline(cardinalLSB_read, line)){
                        LSB_cardinal.insert(std::stoul(line));
                    }
                    cardinalLSB_read.close();
                }else{
                    std::cout << "Could not open cardinalLSB file\n";
                    }
                std::cout << "Cardinal LSB list loaded\n" << "Elements in set: "<< LSB_cardinal.size() << "\n";
                listLoaded = true;
                break;

            case 'R': /////Resume search
                checkPoint_read.open("checkpoint");
                if(checkPoint_read.is_open()){
                    getline(checkPoint_read, line);
                    if ("Target" == line){
                        getline(checkPoint_read, line);
                        T.setX(line.c_str(), 16);
                        getline(checkPoint_read, line);
                        T.setY(line.c_str(), 16);
                        std::cout << "Target:\nX: " << T.getX() << "\nY: "<< T.getY() <<"\n";
                        if(!T.checkY()){std::cout << "Target not valid\n";break;}
                    }else{std::cout << "Target not found\n";}
                    getline(checkPoint_read, line);
                    if ("Iteration" == line) {
                        getline(checkPoint_read, line);
                        mpz_set_str(counter, line.c_str(), 10);
                    } else {std::cout << "Iteration count not found\n";}
                    getline(checkPoint_read, line);
                    if ("Jump" == line) {
                        getline(checkPoint_read, line);
                        jump = std::stoi(line);
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
                pointLoaded = true;
                break;

            case 'N': ///Prepare new point
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
                runningNT.negate(); ///prepare point -T

                if(T.checkY()){
                    std::cout << "Point valid\n";
                    pointLoaded = true;
                }else{
                    std::cout << "Point not valid\n";
                    pointLoaded = false;
                    break;
                }

                std::cout << "Insert iteration counter (base 10)\n";
                std::cin >> userBuffer;
                mpz_set_str(counter, userBuffer.c_str(), 10);

                if(mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1)){
                    gmp_printf("Counter set to %Zd\n", counter);
                }else{gmp_printf("Counter not inside search space\n");}

                if(mpz_cmp_ui(counter, 0)){
                    temp.multiplyByFactor(temp, counter);
                    runningT. addPoint(runningT,  temp);
                    runningNT.addPoint(runningNT, temp);
                }

                gmp_printf("Iteration ready at point %Zd\n", counter);
                std::cout << "Positive point: \n xT: " << runningT.getX() << "\n yT: " << runningT.getY() << "\n";
                std::cout << "Negative point: \nxNT: " << runningNT.getX() << "\nyNT: " << runningNT.getY();
                pointLoaded = true;
                jump = 0;
                break;

            case 'I':
                if(listLoaded && pointLoaded){
                    gmp_printf("Iteration starting at %Zd\n", counter);

                    ///Check if coordinates are already in the list
                    if(LSB_cardinal.find(runningT.getLSB()) != LSB_cardinal.end()){
                        std::cout << "Target hash inside cardinal list\n";
                        mpz_get_str(counterOutput, 10, counter);
                        userBuffer = "pMatch";
                        userBuffer.append(counterOutput);
                        matches_write.open(userBuffer);
                        matches_write << "(Q + " << counterOutput   << ")\n";
                        matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                        matches_write.close();
                    }
                    if(LSB_cardinal.find(runningNT.getLSB()) != LSB_cardinal.end()){
                        std::cout << "Target hash inside cardinal list\n";
                        mpz_get_str(counterOutput, 10, counter);
                        userBuffer = "nMatch";
                        userBuffer.append(counterOutput);
                        matches_write.open(userBuffer);
                        matches_write << "(Q + " << counterOutput   << ")\n";
                        matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                        matches_write.close();
                    }

                    unsigned int i = jump;
                    //TODO: segment loop to avoid if every iteration

                    while (mpz_cmp(search_space, counter)){   ///while counter < search space
                        for(; i < jumps; ++i){   ///jumps inside subInterval
                            if((i & 255) == 0){
                                mpz_get_str(counterOutput, 10, counter);
                                std::cout << "Checkpoint iteration: " << counterOutput << " jump " << i << "\n";

                                checkPoint_write.open("checkpoint");
                                checkPoint_write << "Target\n"        << T.getX()<<"\n"<<T.getY() << "\n";
                                checkPoint_write << "Iteration\n"     << counterOutput            << "\n";
                                checkPoint_write << "Jump\n" << i     << "\n";
                                checkPoint_write << "Running pTarget" << "\n" <<  runningT.getX() << "\n" <<  runningT.getY() << "\n";
                                checkPoint_write << "Running nTarget" << "\n" << runningNT.getX() << "\n" << runningNT.getY() << "\n";
                                checkPoint_write.close();
                            }
                            for(auto j = 0; j < subJumps; ++j){ ///subJumps inside Jump

                                runningT.addPoint( runningT,  sJ);
                                runningNT.addPoint(runningNT, sJ);
                                if(LSB_cardinal.find(runningT. getLSB()) != LSB_cardinal.end()){
                                    mpz_get_str(counterOutput, 10, counter);
                                    userBuffer = "pMatch";
                                    userBuffer.append(counterOutput);
                                    matches_write.open(userBuffer);
                                    matches_write << "(Q + " << counterOutput   <<") + (J * "<< i << ") + (sJ * " << j + 1 << ")\n";
                                    //TODO: register key instead of J/SJ
                                    matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                                    matches_write.close();
                                }
                                if(LSB_cardinal.find(runningNT.getLSB()) != LSB_cardinal.end()){
                                    mpz_get_str(counterOutput, 10, counter);
                                    userBuffer = "nMatch";
                                    userBuffer.append(counterOutput);
                                    matches_write.open(userBuffer);
                                    matches_write << "(-Q + " << counterOutput    << ") + (J * "<< i << ") + (sJ * " << j + 1 << ")\n";
                                    matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                                    matches_write.close();
                                }
                            }

                            runningT. addPoint(runningT,  G);
                            runningNT.addPoint(runningNT, G);

                            if(LSB_cardinal.find(runningT. getLSB()) != LSB_cardinal.end()){
                                mpz_get_str(counterOutput, 10, counter);
                                userBuffer = "pMatch";
                                userBuffer.append(counterOutput);
                                matches_write.open(userBuffer);
                                matches_write << "(Q + " << counterOutput   << ") + (J * " << i + 1         << ")\n";
                                matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                                matches_write.close();
                            }
                            if(LSB_cardinal.find(runningNT.getLSB()) != LSB_cardinal.end()){
                                mpz_get_str(counterOutput, 10, counter);
                                userBuffer = "nMatch";
                                userBuffer.append(counterOutput);
                                matches_write.open(userBuffer);
                                matches_write << "(-Q + " << counterOutput    << ") + (J * "<< i + 1            << ")\n";
                                matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                                matches_write.close();
                            }
                        }

                        i = 0;

                        runningT. addPoint(runningT,  J2);
                        runningNT.addPoint(runningNT, J2);
                        mpz_add_ui(counter, counter, 1);

                        if(LSB_cardinal.find(runningT. getLSB()) != LSB_cardinal.end()){
                            mpz_get_str(counterOutput, 10, counter);
                            userBuffer = "matches/pMatch";
                            userBuffer.append(counterOutput);
                            matches_write.open(userBuffer);
                            matches_write << "(Q + " << counterOutput   << ")\n";
                            matches_write << " Qx: " << runningT.getX() << "\n Qy: " << runningT.getY() << "\n";
                            matches_write.close();
                        }
                        if(LSB_cardinal.find(runningNT.getLSB()) != LSB_cardinal.end()){
                            mpz_get_str(counterOutput, 10, counter);
                            userBuffer = "matches/nMatch";
                            userBuffer.append(counterOutput);
                            matches_write.open(userBuffer);
                            matches_write << "(-Q + " << counterOutput   << ")\n";
                            matches_write << " -Qx: " << runningNT.getX() << "\n -Qy: " << runningNT.getY() << "\n";
                            matches_write.close();
                        }
                    }
                }else{
                    std::cout << "Point or Cardinal List not loaded\n";
                    break;
                }
            case 'E': /////Generate explicit cardinal points file
                std::cout << "The list needs 20GB of disk space. Are you sure?(Y/n)\n";
                //TODO: preallocate needed space
                std::cin >> user_input;
                if(user_input == 'Y'){
                    std::cout << "Generating explicit cardinal points file";
                    cardinalPoints.open("cardinalPoints");
                    cardinalPoints <<"G:\n"  << G.getK()  << "\n" << G.getX()  << "\n"; ///Generator - Interval * 0 + 1 (0 is the point at infinity)
                    cardinalPoints <<"I:\n"  << I.getK()  << "\n" << I.getX()  << "\n"; ///Interval
                    cardinalPoints <<"sI:\n" << sI.getK() << "\n" << sI.getX() << "\n"; ///SubInterval - sI * n + G = I
                    cardinalPoints <<"J:\n"  << J.getK()  << "\n" << J.getX()  << "\n";
                    cardinalPoints <<"sJ:\n" << sJ.getK() << "\n" << sJ.getX() << "\n";

                    for(int i = 0; i < intervals / 2; ++i){
                        for(int j = 0; j < subIntervals; ++j){
                            A.addPoint(A, sI);
                            cardinalPoints << "Interval: " << i << " Subinterval: " << j + 1 <<"\n"<< A.getK() << "\n" << A.getX() << "\n";
                        }
                        A.addPoint(A, G);
                        cardinalPoints << "Interval: " << i + 1 << "\n" << A.getK() << "\n" << A.getX() << "\n";
                    }
                    cardinalPoints.close();
                    std::cout << "Explicit cardinal points file generated\n";
                }else{std::cout << "Exiting\n";break;}
            case 'K': /////Extract key from a known association

                break;

            case 'T': /////Activate test mode
                char testInput;
                std::cout << "Selecte test mode: \n(A)rithmetic, (I)teration, (U)tility\n";
                std::cin >> testInput;
                switch (testInput) {
                    case 'A':
                        std::cout << "Selecte test operation: \n(A)ddition, (S)ubtraction, (D)ouble, (M)ultiplication, (B)ack\n";
                        std::cin >> testInput;
                        switch (testInput) {
                            case 'A':
                                std::cout << "Insert point A X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point A Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setY(userBuffer.c_str(), 16);

                                if(runningT.checkY()){
                                    std::cout << "Point A valid\n";
                                }else{
                                    std::cout << "Point A not valid\n";
                                    break;
                                }

                                std::cout << "Insert point B X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningNT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point B Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningNT.setY(userBuffer.c_str(), 16);

                                if(runningNT.checkY()){
                                    std::cout << "Point B valid\n";
                                }else{
                                    std::cout << "Point B not valid\n";
                                    break;
                                }

                                runningT.addPoint(temp, runningNT);
                                std::cout << "A + B = T\n";
                                std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY()<< "\n";

                                break;

                            case 'S':
                                std::cout << "Insert point A X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point A Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setY(userBuffer.c_str(), 16);

                                if(runningT.checkY()){
                                    std::cout << "Point A valid\n";
                                }else{
                                    std::cout << "Point A not valid\n";
                                    break;
                                }

                                std::cout << "Insert point B X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningNT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point B Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningNT.setY(userBuffer.c_str(), 16);

                                if(runningNT.checkY()){
                                    std::cout << "Point B valid\n";
                                }else{
                                    std::cout << "Point B not valid\n";
                                    break;
                                }

                                runningNT.negate();
                                runningT.addPoint(temp, runningNT);
                                std::cout << "A - B = T\n";
                                std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY()<< "\n";

                                break;

                            case 'D':
                                std::cout << "Insert point A X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point A Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setY(userBuffer.c_str(), 16);

                                if(runningT.checkY()){
                                    std::cout << "Point A valid\n";
                                }else{
                                    std::cout << "Point A not valid\n";
                                    break;
                                }
                                runningT.multiplyBy2(temp);

                                if(temp.checkY()){
                                    std::cout << "A * 2 Valid\n";
                                    std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY()<< "\n";
                                }else{
                                    std::cout << "A * 2 Invalid\n";
                                    std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY()<< "\n";
                                    break;
                                }
                                break;

                            case 'M':
                                std::cout << "Insert point A X coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setX(userBuffer.c_str(), 16);

                                std::cout << "Insert point A Y coordinate (base 16)\n";
                                std::cin >> userBuffer;
                                runningT.setY(userBuffer.c_str(), 16);

                                if(runningT.checkY()){
                                    std::cout << "Point A valid\n";
                                }else{
                                    std::cout << "Point A not valid\n";
                                    break;
                                }

                                std::cout << "Insert factor (base 16)\n";
                                std::cin >> userBuffer;
                                mpz_set_str(container, userBuffer.c_str(), 16);

                                runningT.multiplyByFactor(temp, container);
                                gmp_printf("A * %Zx\n", container);
                                std::cout << "xT: " << temp.getX() << "\nyT: " << temp.getY()<< "\n";
                                break;

                            case 'B':
                                break;
                            default:
                                std::cout << "Unknown option selected\n";
                        }
                        break;

                    case 'I':
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

                        runningNT.negate(); ///prepare point -T

                        if(T.checkY()){ ///if the point is valid, proceed with the iteration
                            std::cout << "Point valid\n";
                        }else{
                            std::cout << "Point invalid\n";
                            break;
                        }

                        std::cout << "Selecte test operation: \n(J)umps, (S)ubJumps, (I)terate Jumps, (F)ull Iteration\n";
                        std::cin >> testInput;
                        switch (testInput) {
                            case 'J':
                                std::cout << "Number of jumps:\n";
                                int testJumps;
                                std::cin >> testJumps;
                                for(auto j = 0; j < testJumps; ++j){
                                    runningT.addPoint( runningT,  J);
                                    runningNT.addPoint(runningNT, J);
                                }
                                std::cout << " Point + " << testJumps << " * J\nX: " << runningT.getX() <<  "\nY: " << runningT.getY()  <<"\n\n";
                                std::cout << "NPoint + " << testJumps << " * J\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() <<"\n";
                                break;
                            case 'S':
                                std::cout << "Number of subJumps:\n";
                                int testSubJumps;
                                std::cin >> testSubJumps;
                                for(auto j = 0; j < testSubJumps; ++j){
                                    runningT. addPoint(runningT,  sJ);
                                    runningNT.addPoint(runningNT, sJ);
                                }
                                std::cout << " Point + " << testSubJumps << " * sJ\nX: " << runningT. getX() << "\nY: " << runningT. getY() <<"\n\n";
                                std::cout << "NPoint + " << testSubJumps << " * sJ\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() <<"\n";
                                break;

                            case 'I':
                                std::cout << "Number of Jumps:\n";
                                int testIteration;
                                std::cin >> testIteration;
                                for(auto  i = 0; i < testIteration; ++i){
                                    for(auto j = 0; j < subJumps; ++j){
                                        runningT.addPoint (runningT,  sJ);
                                        runningNT.addPoint(runningNT, sJ);
                                    }
                                    runningT.addPoint( runningT,  G);
                                    runningNT.addPoint(runningNT, G);
                                }
                                std::cout << " Point + " << testIteration << " * (sj * SJ + 1)\nX: " << runningT. getX() << "\nY: " << runningT. getY() <<"\n\n";
                                std::cout << "NPoint + " << testIteration << " * (sj * SJ + 1)\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() <<"\n";
                                break;

                            case 'F':
                                std::cout << "Number of Iterations:\n";
                                int testIterations;
                                std::cin >> testIterations;
                                for(auto it = 0; it < testIterations; ++it){
                                    for(auto  i = 0; i < jumps; ++i){
                                        for(auto j = 0; j < subJumps; ++j){
                                            runningT. addPoint(runningT,  sJ);
                                            runningNT.addPoint(runningNT, sJ);
                                        }
                                        runningT. addPoint(runningT,  G);
                                        runningNT.addPoint(runningNT, G);
                                    }
                                    runningT. addPoint(runningT,  J2);
                                    runningNT.addPoint(runningNT, J2);
                                }
                                
                                std::cout << " Point + " << testIterations << "\nX: " << runningT. getX() << "\nY: " << runningT. getY() <<"\n\n";
                                std::cout << "NPoint + " << testIterations << "\nX: " << runningNT.getX() << "\nY: " << runningNT.getY() <<"\n";
                                break;
                            default:
                                std::cout << "Unknown option selected\n";
                                break;
                        }
                        break;

                    case 'U':
                        std::cout << "Selecte test operation: \n (L)oad Checkpoint, (S)et size test, (E)xtract Iterator Key\n(F)ind in list, (C)ount numbers in list\n(G)enerate checkpoints\n";
                        std::cin >> testInput;
                        switch (testInput) {
                            case 'L':
                                checkPoint_read.open("checkpoint");
                                if(checkPoint_read.is_open()){
                                    getline(checkPoint_read, line);
                                    if ("Target" == line){
                                        getline(checkPoint_read, line);
                                        T.setX(line.c_str(), 16);
                                        getline(checkPoint_read, line);
                                        T.setY(line.c_str(), 16);
                                        if(!T.checkY()){std::cout << "Target not valid\n";break;}
                                    }else{std::cout << "Target not found\n";}
                                    getline(checkPoint_read, line);
                                    if ("Iteration " == line) {
                                        getline(checkPoint_read, line);
                                        mpz_set_str(counter, line.c_str(), 10);
                                        G.multiplyByFactor(temp, counter);
                                    } else {std::cout << "Iteration count not found\n";}
                                    getline(checkPoint_read, line);
                                    if ("Jump" == line) {
                                        getline(checkPoint_read, line);
                                        jump = atol(line.c_str());
                                        for(int i = 0; i < jump; ++i){
                                            temp.addPoint(temp, J);
                                        }
                                    } else {std::cout << "Jump not found\n";}
                                    getline(checkPoint_read, line);
                                    if ("Running pTarget" == line) {
                                        getline(checkPoint_read, line);
                                        runningT.setX(line.c_str(), 16);
                                        getline(checkPoint_read, line);
                                        runningT.setY(line.c_str(), 16);
                                    }else{std::cout << "pTarget not found\n";}
                                    getline(checkPoint_read, line);
                                    if ("Running nTarget" == line) {
                                        getline(checkPoint_read, line);
                                        runningT.setX(line.c_str(), 16);
                                        getline(checkPoint_read, line);
                                        runningT.setY(line.c_str(), 16);
                                    }else{std::cout << "nTarget not found\n";}
                                    temp.addPoint(temp, T);
                                    if(runningT.getLSB() == temp.getLSB()){

                                    }
                                    //TODO: compare  (Target + temp) to pTarget
                                    //TODO: compare (-Target + temp) to nTarget
                                }
                                checkPoint_read.close();
                                std::cout << "Checkpoint Restored\n";
                                //TODO: separate N branch into New and Iterate branches to accommodate resuming iteration
                                break;
                            case 'S':
                                std::cout << "Max size of LSB: " << LSB_cardinal.max_size() << "\n";
                                std::cout << "Stress test?(Y/n)\n";
                                std::cin >> testInput;
                                if(testInput == 'Y'){
                                    std::set<unsigned int> testSet;
                                    std::pair<std::set<int>::iterator,bool> ret;
                                    for(unsigned int i = 0; i < testSet.max_size(); ++i){
                                        testSet.insert(i);
                                        printf("Elements: %lu",testSet.size());
                                    }
                                }
                                break;
                            case 'E':
                                //TODO: extract key of the added point from j, sj and i;
                                break;
                            case 'F':
                                if(listLoaded){
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

                                    runningNT.negate(); ///prepare point -T

                                    if(T.checkY()){ ///if the point is valid, proceed with the iteration
                                        std::cout << "Point valid\n";
                                    }else{
                                        std::cout << "Point invalid\n";
                                        break;
                                    }
                                    if(LSB_cardinal.find(runningNT.getLSB()) != LSB_cardinal.end()){
                                        std::cout << "Point in list\n";
                                    }else{
                                        std::cout << "Point not in list\n";
                                    }
                                    break;
                                }else{
                                    std::cout << "List not loaded\n";
                                    break;
                                }
                                break;
                            case 'C':
                                std::cout << "Elements in list: " << LSB_cardinal.size() << "\n";
                                break;
                            case 'G':
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
                                runningNT.negate(); ///prepare point -T

                                if(T.checkY()){
                                    std::cout << "Point valid\n";
                                    pointLoaded = true;
                                }else{
                                    std::cout << "Point not valid\n";
                                    pointLoaded = false;
                                    break;
                                }

                                std::cout << "Insert iteration counter (base 10)\n";
                                std::cin >> userBuffer;
                                mpz_set_str(counter, userBuffer.c_str(), 10);

                                if(mpz_cmp(search_space, counter) && (mpz_cmp_ui(counter, 0) > -1)){
                                    gmp_printf("Counter set to %Zd\n", counter);
                                }else{gmp_printf("Counter not inside search space\n");}

                                if(mpz_cmp_ui(counter, 0)){
                                    G.multiplyByFactor(temp, counter);
                                    runningT. addPoint(runningT,  temp);
                                    runningNT.addPoint(runningNT, temp);
                                }

                                mpz_get_str(counterOutput, 10, counter);
                                checkPoint_write.open("checkpoint");
                                checkPoint_write << "Target\n"        << T.getX()<<"\n"<<T.getY() << "\n";
                                checkPoint_write << "Iteration\n"     << counterOutput            << "\n";
                                checkPoint_write << "Jump\n" << 0     << "\n";
                                checkPoint_write << "Running pTarget" << "\n" <<  runningT.getX() << "\n" <<  runningT.getY() << "\n";
                                checkPoint_write << "Running nTarget" << "\n" << runningNT.getX() << "\n" << runningNT.getY() << "\n";
                                checkPoint_write.close();
                                break;
                            default:
                                std::cout << "Unknown option selected\n";
                            break;
                        }
                break;
                }
                break;
            default:
                std::cout << "Unknown option selected\n";
                break;
        }
    }
    return 0;
}