set(runnable_files
    headers/thread_runnable.h
    thread_runnable.cpp
    
    headers/threadManager_runnable.h
    threadManager_runnable.cpp
    
    headers/UI_runnable.h
    UI_runnable.cpp
)
add_library(runnableLib SHARED ${runnable_files})