cmake_minimum_required(VERSION 3.0.0)
project(snake VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_C_STANDARD gnu99)


find_library(LIBRT rt) 
if(LIBRT)
    target_link_libraries(${PROJECT_NAME} ${LIBRT})
endif()
