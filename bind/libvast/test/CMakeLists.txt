add_executable( libvast_tests libvast_tests.cpp  )
target_link_libraries( libvast_tests libvast vast_chain_lite )
target_include_directories(libvast_tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libraries/catch/include
        )

add_test(NAME libvast_tests
         COMMAND bind/libvast/test/libvast_tests
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
