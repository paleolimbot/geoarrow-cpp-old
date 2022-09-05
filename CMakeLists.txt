
cmake_minimum_required(VERSION 3.11)
message(STATUS "Building using CMake version: ${CMAKE_VERSION}")

project(GeoArrow)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(GEOARROW_BUILD_EXAMPLES "Build geoarrow-cpp examples" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(GEOARROW_BUILD_TESTS "Build tests for geoarrow" OFF)

include_directories(src)
add_library(geoarrow src/geoarrow/geoarrow.cpp)

set_target_properties(geoarrow PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

if(GEOARROW_BUILD_EXAMPLES)
  add_executable(example-bbox examples/example-bbox/example-bbox.cpp)
  target_link_libraries(example-bbox PUBLIC geoarrow)
endif()

if(GEOARROW_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.11.0.zip
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()

  add_executable(index_math_test src/geoarrow/index_math_test.cc)
  target_link_libraries(index_math_test gtest_main)

  include(GoogleTest)
  gtest_discover_tests(index_math_test)
endif()

install(TARGETS geoarrow DESTINATION lib)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")

if(GEOARROW_BUILD_EXAMPLES)
  install(TARGETS example-bbox DESTINATION examples)
endif()
