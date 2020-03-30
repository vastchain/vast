add_library(libvast SHARED
    vast.cpp
    vast_ecc.cpp
    vast_abi.cpp
    vast_address.cpp
    vast_vastlink.cpp
)
set_target_properties(libvast PROPERTIES OUTPUT_NAME vast)

target_link_libraries(libvast PUBLIC
    vast_chain_lite fc_lite ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS}
)

target_include_directories(libvast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

install(
    TARGETS libvast
    RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

if(ENABLE_TESTING)
    add_subdirectory(test)
endif()
