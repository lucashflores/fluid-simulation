cmake_minimum_required(VERSION 3.13)
project(fluid-simulation)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

if(WIN32)
    set(SDL2_DIR "C:/SDL2-2.0.18/i686-w64-mingw32")
    set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include)
    set(SDL2_LIBRARY_DIR ${SDL2_DIR}/lib)
    include_directories(include ${SDL2_INCLUDE_DIR})
endif()
# if(UNIX)
#     find_package(SDL2 REQUIRED)
#     include_directories(include ${SDL2_LIBRARY_DIR})
# endif()

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "./")

if(WIN32)
    target_link_libraries(${PROJECT_NAME} -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a) #-mwindows
    file(COPY ${SDL2_DIR}/bin/SDL2.dll DESTINATION ./)
endif()
# if(UNIX)
#     target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
# endif()