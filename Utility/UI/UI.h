#ifndef SECP251K1_SANDBOX_UIRUNNABLE_H
#define SECP251K1_SANDBOX_UIRUNNABLE_H

#include <string.h>
#include "TestUI/TestUI.h"
#include "ServerUI/ServerUI.h"
#include "ClientUI/ClientUI.h"
#include "SatelliteUI/SatelliteUI.h"

#define UI_SM_IDLE_WAIT 0.1

unsigned int init_UserInterfaceSM(UI_SM_struct *UIdata);
unsigned int start_UserInterfaceSM(UI_SM_struct *UIdata);

#endif // SECP251K1_SANDBOX_UIRUNNABLE_H