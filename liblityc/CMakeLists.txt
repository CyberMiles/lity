if (EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS='[\"_solidity_license\",\"_solidity_version\",\"_solidity_compile\"]' -s RESERVED_FUNCTION_POINTERS=20")
	add_executable(soljson liblityc.cpp)
	target_link_libraries(soljson PRIVATE lity)
else()
	add_library(liblityc liblityc.cpp)
	set_target_properties(liblityc PROPERTIES OUTPUT_NAME lityc)
	target_link_libraries(liblityc PRIVATE lity)
endif()
