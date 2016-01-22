cmake_minimum_required(VERSION 3.3)
project(paa_exam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SATInstance.cpp SATInstance.h SATClause.cpp SATClause.h SATEvaluation.cpp SATEvaluation.h)
add_executable(paa_exam ${SOURCE_FILES})