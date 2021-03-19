cmake_minimum_required(VERSION 3.0.0)
project(FVM VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 11)
add_executable(FVMexe main.cpp functions.hpp functions.cpp  solver.hpp solver.cpp gridData.hpp gridData.cpp getMeshData.cpp setInitialCondition.cpp FVM_INSE.cpp setBound.cpp output.cpp calculateTimeStep.cpp viscidFlux.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
