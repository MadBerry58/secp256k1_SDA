set(runnable_files
    headers/thread_runnable.h
    thread_runnable.cpp
    
    headers/threadManager_runnable.h
    threadManager_runnable.cpp
    
)
add_library(runnableLib ${runnable_files})
# add_library(runnableLib SHARED ${runnable_files})