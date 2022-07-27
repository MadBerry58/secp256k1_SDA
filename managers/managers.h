#ifndef SECP251K1_SANDBOX_MANAGERS_H
#define SECP251K1_SANDBOX_MANAGERS_H

#include "../src/headers/Algorithms.h"
#include "FileManager/FileManager.h"
#include "IterationManager/IterationManager.h"
#include "MemoryManager/MemoryManager.h"
#include "NetworkManager/NetworkManager.h"
#include "UIManager/UIManager.h"

unsigned int init_FileManager();
unsigned int init_IterationManager();
unsigned int init_MemoryManager();
unsigned int init_NetworkManager();
unsigned int init_UIManager();

#endif