file(GLOB HEADERS "include/vast/vast_plugin/*.hpp")
add_library( vast_plugin
        vast_plugin.cpp
        ${HEADERS} )

target_link_libraries( vast_plugin chain_plugin vast_chain appbase fc )
target_include_directories( vast_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
