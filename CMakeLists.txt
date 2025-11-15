cmake_minimum_required(VERSION 3.5)

project(UTS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UTS
    unts.h
    unts.cpp
    Test.cpp)

include(GNUInstallDirs)
install(TARGETS UTS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
