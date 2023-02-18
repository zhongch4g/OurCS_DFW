# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.

add_executable (pmem_simulation pmem_simulation.cpp)
target_link_libraries (pmem_simulation LINK_PUBLIC)

