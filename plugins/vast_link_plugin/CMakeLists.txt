file(GLOB HEADERS "include/vast/vast_link_plugin/*.hpp")
add_library( vast_link_plugin
             vast_link_plugin.cpp
             ${HEADERS} )

target_link_libraries( vast_link_plugin chain_plugin http_plugin vast_chain appbase )
target_include_directories( vast_link_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
