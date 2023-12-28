cmake_minimum_required(VERSION 3.27.0)
project(MY_UTILS LANGUAGES CXX VERSION 1.1.5)

file(GLOB INCLUDES
    include/**/*.hpp
    include/**/*.h
)

file(GLOB SOURCES
    include/**/*.cpp
    include/**/*.c
)

#remove static for XOS
add_library(${PROJECT_NAME} STATIC ${SOURCES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME}) 
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(MY_UTILS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include )
set(MY_UTILS_INCLUDE ${MY_UTILS_INCLUDE} PARENT_SCOPE)
include_directories(${MY_UTILS_INCLUDE})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_UTILS_INCLUDE})
