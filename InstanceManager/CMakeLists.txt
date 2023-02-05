set(instance_files
    Client_Instance/Client_Instance_Types.h
    Client_Instance/Client_Instance.h
    Client_Instance/Client_Instance.cpp
    
    Satellite_Instance/Satellite_Instance_Types.h
    Satellite_Instance/Satellite_Instance.h
    Satellite_Instance/Satellite_Instance.cpp

    Server_Instance/Server_Instance_Types.h
    Server_Instance/Server_Instance.h
    Server_Instance/Server_Instance.cpp

    InstanceManager.h
    InstanceManager.cpp
)
add_library(instanceLib ${instance_files})