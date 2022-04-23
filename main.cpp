#include "include/Operators.h"

#include "testFunctionality.cpp"
#include "filemanager.cpp"
#include "filemanager.cpp"
#include "threads.h"


// std::set<unsigned long> LSB_cardinal;

///Search point
mpz_t counter; ///iteration counter
mpz_t search_space; ///maximum distance of the target from a known point
mpz_t negUserY; ///container for deducing negative Y provided by the user
mpz_t container;

//std::string line;
std::string userBuffer;

bool listLoaded;
bool pointLoaded;
char counterOutput[1024];
char user_input = 's';
int jump;

int main() {
    modInit();

    mpz_init_set_d(negUserY,  0);
    mpz_init_set_d(container, 0);
    mpz_set_ui    (counter, 0);
    mpz_init_set_str(counter,      "2044472428167007402249549317371870405449633012157584065567923", 10);
    mpz_init_set_str(search_space, "2044472428167007402249549317371870405449633012157584065567923", 10);

    Point G        (xG, yG, kG);
    Point A        (xG, yG, kG); ///container point
    Point temp     (xG, yG, kG);
    Point runningT (xG, yG); ///target point
    Point runningNT(xG, yG); ///negative target point
    Point T        (xG, yG); ///Target Point
    Point nT       (xG, yG); ///Negative Target Point


    while(user_input != 'x'){
        std::cout << "\n\nPlease select an option: \n(G)enerate cardinal LSB file\n(L)oad cardinal point file\n(N)ew point search\n(R)esume point search\n(I)terate\nE(x)it program\n\n";
        std::cin  >> user_input;

        switch(user_input){
            case 'G':  //////Generate cardinal points
                //TODO: Generate points function
                break;

            case 'L': /////Load cardinal points
                //TODO: Load points function
                break;

            case 'R': /////Resume search
                ///TODO: Resume search/ Load resume file
                break;

            case 'N': ///Prepare new point
                ///TODO: New target select function
                break;

            case 'I':
                ///TODO: Start iteration function
                break;
                
            case 'E': /////Generate explicit cardinal points file
                ///TODO: Generate explicit points
                break;

            case 'K': /////Extract key from a known association
                ///TODO: Extract key from association
                break;
            
            case 'C': /////Connect to a central database server
                /*
                Bypass the known point list dependencies
                Create 
                */
                
            case 'T': /////Activate test mode
                ///TODO: Enter test mode
                break;

            default:
                std::cout << "Unknown option selected\n";
                break;
        }
    }

    return 0;
}