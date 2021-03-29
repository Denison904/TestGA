cmake_minimum_required(VERSION 3.13)

set(RNN_HPPS Chromosome_RNN.hpp GA_RNN.hpp Layer.hpp RNN_simple.hpp Matrix.hpp)
set(RNN_CPPS Chromosome_RNN.cpp GA_RNN.cpp Layer.cpp RNN_simple.cpp Matrix.cpp)

add_library(RNN STATIC ${RNN_HPPS} ${RNN_CPPS})