cmake_minimum_required(VERSION 3.5)
project(a_start_test CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} test_a_star.cc)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

add_test(
        NAME ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMAND ${PROJECT_NAME}
)