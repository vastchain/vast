file(GLOB HEADERS "include/vast/staking_plugin/*.hpp")

add_library( staking_plugin
             staking_plugin.cpp
             ${HEADERS}
           )

target_link_libraries( staking_plugin chain_plugin http_client_plugin appbase vast_chain vast_utilities )
target_include_directories( staking_plugin
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../chain_interface/include"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../staking_plugin/include"
    )
