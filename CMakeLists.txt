cmake_minimum_required(VERSION 3.1.0 )

project(TEST)
file(GLOB CPPS "*.cpp")
file(GLOB HPPS "*.hpps")
add_executable(TEST ${HPPS} ${CPPS})

