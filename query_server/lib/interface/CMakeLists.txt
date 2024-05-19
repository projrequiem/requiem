px4_add_library(interface_LIB
    Interface.cpp
)

add_dependencies(interface_LIB prebuild_targets)
target_link_libraries(interface_LIB PRIVATE geo world_magnetic_model ecl_EKF)
target_compile_options(interface_LIB PRIVATE -fno-associative-math)