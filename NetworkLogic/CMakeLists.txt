set(network_files
    ProtocolData/ProtocolData.h

    ClientLogic/Client/Client_Types.h
    ClientLogic/Client/Client.h
    ClientLogic/Client/Client.cpp

    ClientLogic/Client/ClientSM/ClientSM.h
    ClientLogic/Client/ClientSM/ClientSM.cpp

    ClientLogic/ClientHandler/ClientHandler_Types.h
    ClientLogic/ClientHandler/ClientHandler.h
    ClientLogic/ClientHandler/ClientHandler.cpp

    ClientLogic/ClientHandler/ClientHandlerSM/ClientHandlerSM.h
    ClientLogic/ClientHandler/ClientHandlerSM/ClientHandlerSM.cpp
    
    SatelliteLogic/Satellite/Satellite_Types.h
    SatelliteLogic/Satellite/Satellite.h
    SatelliteLogic/Satellite/Satellite.cpp

    SatelliteLogic/Satellite/SatelliteSM/SatelliteSM.h
    SatelliteLogic/Satellite/SatelliteSM/SatelliteSM.cpp

    SatelliteLogic/SatelliteHandler/SatelliteHandler_Types.h
    SatelliteLogic/SatelliteHandler/SatelliteHandler.h
    SatelliteLogic/SatelliteHandler/SatelliteHandler.cpp

    SatelliteLogic/SatelliteHandler/SatelliteHandlerSM/SatelliteHandlerSM.h
    SatelliteLogic/SatelliteHandler/SatelliteHandlerSM/SatelliteHandlerSM.cpp

    ServerLogic/Server/Server_Types.h
    ServerLogic/Server/Server.h
    ServerLogic/Server/Server.cpp

    ServerLogic/Server/ServerSM/ServerSM.h
    ServerLogic/Server/ServerSM/ServerSM.cpp

    ServerLogic/Frontend/Frontend_Types.h
    ServerLogic/Frontend/Frontend.h
    ServerLogic/Frontend/Frontend.cpp

    ServerLogic/Frontend/FrontendSM/FrontendSM.h
    ServerLogic/Frontend/FrontendSM/FrontendSM.cpp

    NetworkManager.h
    NetworkManager.cpp
)
add_library(networkLib ${network_files})