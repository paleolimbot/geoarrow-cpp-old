
cmake_minimum_required(VERSION 3.11)
message(STATUS "Building using CMake version: ${CMAKE_VERSION}")

project(GeoArrow)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_EXAMPLES "Build geoarrow-cpp examples" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include_directories(src ${OPENSSL_INCLUDE_DIR})
include_directories(src ${ABSL_INCLUDE_DIR})
add_library(geoarrow src/geoarrow/geoarrow.cpp)

set_target_properties(geoarrow PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

if(BUILD_EXAMPLES)
  # add_executable(example-simple examples/example-simple/example-simple.cc)
  # arget_link_libraries(example-simple PUBLIC s2geography s2)
endif()

install(TARGETS geoarrow DESTINATION lib)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")

if(BUILD_EXAMPLES)
  # install(TARGETS example-simple DESTINATION examples)
endif()
