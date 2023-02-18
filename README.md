# Descriptions

This experiment mainly focused on discovering what may happen when system crashes happen during creating the linked list.

In this experiment, we simulate the process of writing the data to the persistent memory, and mannual control the position of system crash happen during the code execution.


# Execute instructions

    mkdir build

    cd build

    cmake -DCMAKE_BUILD_TYPE=release ..

    make -j16

    ./DFW_Workshop/pmem_simulation




