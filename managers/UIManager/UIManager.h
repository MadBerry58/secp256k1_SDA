#ifndef SECP251K1_SANDBOX_UIRUNNABLE_H
#define SECP251K1_SANDBOX_UIRUNNABLE_H

#include "../../TypeDef.h"

#include "TestUI/TestUI.h"
#include "ServerUI/ServerUI.h"
#include "ClientUI/ClientUI.h"
#include "SatelliteUI/SatelliteUI.h"

static char counterOutput[1024];
static char user_input = 's';
static std::string user_long_input = "s";

int UserInterfaceSM_Init(UISMStruct UIdata);
int UserInterfaceSM_Start(UISMStruct UIdata);

#endif // SECP251K1_SANDBOX_UIRUNNABLE_H