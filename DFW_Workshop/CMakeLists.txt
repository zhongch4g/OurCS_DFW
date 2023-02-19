# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.

# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2018-2020, Intel Corporation

cmake_minimum_required(VERSION 3.4)
project(queue CXX)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

include(FindThreads)

if(NOT WIN32)
	find_package(PkgConfig QUIET)
endif()

if(PKG_CONFIG_FOUND)
	pkg_check_modules(LIBPMEMOBJ++ REQUIRED libpmemobj++)
else()
	find_package(LIBPMEMOBJ++ REQUIRED)
endif()

link_directories(${LIBPMEMOBJ++_LIBRARY_DIRS})

add_executable(queue queue.cpp)
target_include_directories(queue PUBLIC ${LIBPMEMOBJ++_INCLUDE_DIRS} . ..)
target_link_libraries(queue ${LIBPMEMOBJ++_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(queue_memory queue_memory.cpp)
target_include_directories(queue_memory PUBLIC ${LIBPMEMOBJ++_INCLUDE_DIRS} . ..)
target_link_libraries(queue_memory ${LIBPMEMOBJ++_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable (pmem_simulation pmem_simulation.cpp)
target_link_libraries (pmem_simulation LINK_PUBLIC)

add_executable (pmem_recovery_simulation pmem_recovery_simulation.cpp)
target_link_libraries (pmem_recovery_simulation LINK_PUBLIC)

