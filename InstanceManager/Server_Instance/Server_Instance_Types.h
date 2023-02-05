#ifndef SERVER_INSTANCE_TYPES_H
#define SERVER_INSTANCE_TYPES_H

struct ServerInstance_struct
{
    // Port networkManagerRxPort;
    // Port *parentPort                     = nullptr;
    // NetworkManager_initType functionMode = NM_MODE_NONE;
    unsigned int maxClients              = 0u;
    // unsigned int initializedMembers      = INITIALIZED_BIT_NETWORKMANAGER_NONE;
};

enum NM_ModuleBitMasks
{
    INITIALIZED_BIT_NETWORKMANAGER_NONE            = 0b00000000,
    INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO     = 0b00000001,
    INITIALIZED_BIT_NETWORKMANAGER_SERVERIP        = 0b00000010,
    INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT      = 0b00000100,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED0    = 0b00001000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED1    = 0b00010000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED2    = 0b00100000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED3    = 0b01000000,
    INITIALIZED_BIT_NETWORKMANAGER_FAULT           = 0b10000000,

    INITIALIZED_BIT_NETWORKMANAGER_CLIENT_READY    = 0b00000110,
    INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY    = 0b00000111,
    INITIALIZED_BIT_NETWORKMANAGER_SATELLITE_READY = 0b00000111
};

enum NetworkManager_initType
{
    NM_MODE_NONE,
    NM_MODE_SERVER,
    NM_MODE_CLIENT,
    NM_MODE_SATELLITE,
    NM_MODE_TEST
};



#endif