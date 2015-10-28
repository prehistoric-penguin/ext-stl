project("ext-stl" CXX C)
cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
find_package(Threads)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -std=c++11")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(BENCHMARK_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/bench)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_SRCS)
foreach(i ${TEST_SRCS})
  get_filename_component(name ${i} NAME_WE)
  set(name "${name}_unittest")
  add_executable(${name} ${i})
  target_link_libraries(${name} ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(${name} pthread)
endforeach()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/benchmark BENCH_SRCS)
foreach(i ${BENCH_SRCS})
  get_filename_component(name ${i} NAME_WE)
  set(name "${name}_bench")
  add_executable(${name} ${i})
endforeach()
