# Descriptions

This experiment mainly focused on discovering what may happen when system crashes happen during creating the linked list.

In this experiment, we emulate the process of writing the data to the persistent memory, and mannual control the position of system crash happen during the code execution.

The experiment also includes the implementation of queue using libpmemobj C++ API. It runs in persistent memory.

# Execute instructions (Compile)

    mkdir build

    cd build

    cmake -DCMAKE_BUILD_TYPE=release ..

    make -j16

# Execute instructions (Run)
    
    1. Simulate writing linked list to Pmem 
    ./DFW_Workshop/pmem_simulation [1|2|3] [0|1]
    [1|2|3] 
        1:createLinkedlistWithoutBarrier
        2:createLinkedlistWithBarrier
        3:insertLinkedlist
    [1|2]
        0:make it not crash
        1:make it crash
    2. Simulate recovering process
    ./DFW_Workshop/pmem_recovery_simulation
    
    3. Test the Pmem version queue
    ./DFW_Workshop/queue file-name [push [value]|pop|show]




