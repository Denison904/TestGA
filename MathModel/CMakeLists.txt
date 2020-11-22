cmake_minimum_required(VERSION 3.13)

set( MATHMODEL_HPPS Header/Game.hpp Header/Snake.hpp)
set(MATHMODEL_CPPS Source/Game.cpp Source/Snake.cpp)

add_library(MathModel STATIC ${MATHMODEL_HPPS} ${MATHMODEL_CPPS})