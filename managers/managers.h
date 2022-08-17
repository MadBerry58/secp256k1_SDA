#ifndef SECP251K1_SANDBOX_MANAGERS_H
#define SECP251K1_SANDBOX_MANAGERS_H

#include "../TypeDef.h"

#include "FileManager/FileManager.h"
#include "IterationManager/IterationManager.h"
#include "MemoryManager/MemoryManager.h"
#include "NetworkManager/NetworkManager.h"
#include "UIManager/UIManager.h"

unsigned int init_managers(std::string initData);
unsigned int sendMessage(auto message, bool *notificationFlag, auto *messageContainer);

#endif