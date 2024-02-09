add_library(polymorphism_ext SHARED polymorphism.cpp)
set_target_properties(polymorphism_ext PROPERTIES PREFIX "")
if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  set_target_properties(polymorphism_ext PROPERTIES SUFFIX ".so")
endif()
# Use bundled boost python sources
target_include_directories(polymorphism_ext
  PRIVATE
    ${BOOSTPY_SOURCE_DIR}/include
)
target_link_libraries(polymorphism_ext
  PRIVATE
    Boost::python
)
