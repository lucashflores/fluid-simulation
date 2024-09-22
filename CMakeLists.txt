cmake_minimum_required(VERSION 3.13)
project(fluid-simulation)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

if(WIN32)
    find_path(SDL2_DIR_BIN SDL2.dll PATHS "C:/SDL2/bin" "C:/Program Files/SDL2/bin" REQUIRED)
    set(SDL2_DIR ${SDL2_DIR_BIN}/..)
    include_directories(include ${SDL2_DIR}/include)
    link_directories(${SDL2_DIR}/lib)
endif()
# if(UNIX)
#     find_package(SDL2 REQUIRED)
#     include_directories(include ${SDL2_LIBRARY_DIR})
# endif()

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "./")

if(WIN32)
    target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2 -mwindows) #-mwindows
    file(COPY ${SDL2_DIR}/bin/SDL2.dll DESTINATION ./)
endif()
# if(UNIX)
#     target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
# endif()

# For Windows Installer
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY ${SDL2_DIR}/bin/ DESTINATION .)

include(InstallRequiredSystemLibraries)

# CPack configuration
set(CPACK_PACKAGE_NAME "FluidSimulation")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "Yuske&Lucker&Edu")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fluid simulation application")
set(CPACK_PACKAGE_EXECUTABLES "fluid-simulation" "Fluid Simulation")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "FluidSimulation")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_SOURCE_INSTALLED_DIRECTORIES "${CMAKE_SOURCE_DIR}/src;${CMAKE_SOURCE_DIR}/include")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/CMakeLists.txt.user;/CMakeCache.txt;/cmake_install.cmake;/CPackConfig.cmake;/CPackSourceConfig.cmake;/Makefile;/CMakeFiles/")

# Include CPack
include(CPack)