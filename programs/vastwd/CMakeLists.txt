add_executable(vastwd main.cpp)

if(UNIX AND NOT APPLE)
    set(rt_library rt)
endif()

find_package(Jemalloc QUIET)
if(JEMALLOC_FOUND)
    message(STATUS "Found jemalloc; compiling vastwd with jemalloc")
    list(APPEND PLATFORM_SPECIFIC_LIBS jemalloc)
endif()

target_link_libraries(vastwd
    PRIVATE appbase
    PRIVATE wallet_api_plugin wallet_plugin
    PRIVATE http_plugin
    PRIVATE vast_chain fc ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS}
)

install(
    TARGETS vastwd
    RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR} OPTIONAL
)
