#ifndef SECP251K1_SANDBOX_MANAGERS_H
#define SECP251K1_SANDBOX_MANAGERS_H

#include "FileManager/FileManager.h"
#include "IterationManager/IterationManager.h"
#include "MemoryManager/MemoryManager.h"
#include "NetworkManager/NetworkManager.h"
#include "UIManager/UIManager.h"

Port *uiManagerPort;
Port *iterationManagerPort;
Port *networkManagerPort;
Port *memoryManagerPort;
Port *fileManagerPort;

unsigned int init_managers(std::string initData);

#endif