struct ClientHandlerSM_struct
{
    unsigned int *SMstate = nullptr;
    // Point **pointBuffer;
    // std::thread *stateMachineHandle;
    // uint64_t *clientConnectionID;
    unsigned int bufferSize = 100u;
};

struct Challange
{
    // char key[CHALLANGE_NUMBER][LSB_STRING_SIZE];
    bool updatedFlag = false;
};

struct Solution
{
    // char solution[CHALLANGE_NUMBER][SOLUTION_STRING_SIZE];
    bool solutionReady = true;
};

struct ProgressPackage
{
    char *serializedProgressData;
    char *dataSize;
    char progressDataHash[32];
};

