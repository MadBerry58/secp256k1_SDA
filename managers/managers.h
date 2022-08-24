#ifndef SECP251K1_SANDBOX_MANAGERS_H
#define SECP251K1_SANDBOX_MANAGERS_H

#include "FileManager/FileManager.h"
#include "IterationManager/IterationManager.h"
#include "MemoryManager/MemoryManager.h"
#include "NetworkManager/NetworkManager.h"
#include "UIManager/UIManager.h"

unsigned int init_Managers(InitDataStruct initData);

#endif