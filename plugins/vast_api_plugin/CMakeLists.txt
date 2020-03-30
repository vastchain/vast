file(GLOB HEADERS "include/vast/vast_api_plugin/*.hpp")
add_library( vast_api_plugin
             vast_api_plugin.cpp
             ${HEADERS} )

target_link_libraries( vast_api_plugin vast_plugin http_plugin appbase )
target_include_directories( vast_api_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
