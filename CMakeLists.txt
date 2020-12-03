cmake_minimum_required(VERSION 3.1.0 )

project(TEST)
file(GLOB CPPS "*.cpp")
file(GLOB HPPS "*.hpps")
add_executable(TEST ${HPPS} ${CPPS})

add_subdirectory(MathModel)
target_link_libraries(TEST MathModel)
install(TARGETS TEST DESTINATION bin)
