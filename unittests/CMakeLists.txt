add_executable(vast_unittests
    main.cpp
    abi_tests.cpp
    types_tests.cpp
    crypto_tests.cpp

    tokendb/basic_tests.cpp
    tokendb/runtime_tests.cpp
    tokendb/persist_tests.cpp
    tokendb/cache_tests.cpp
    
    snapshot_tests.cpp
    luajit_tests.cpp
    
    contracts/nft_tests.cpp
    contracts/group_tests.cpp
    contracts/ft_tests.cpp
    contracts/suspend_tests.cpp
    contracts/lock_tests.cpp
    contracts/bonus_tests.cpp
    contracts/utils_tests.cpp
    contracts/vastlink_tests.cpp
    contracts/staking_tests.cpp
    contracts/multi_actions_tests.cpp
    )
set_target_properties(vast_unittests PROPERTIES ENABLE_EXPORTS TRUE)

find_package(Jemalloc QUIET)
if(JEMALLOC_FOUND)
    message(STATUS "Found jemalloc; compiling vast_unittests with jemalloc")
    list(APPEND PLATFORM_SPECIFIC_LIBS jemalloc)
endif()

if(UNIX)
    if(APPLE)
        set_target_properties(vast_unittests PROPERTIES LINK_FLAGS "${LUAJIT_LINK_FLAGS}")
    endif()
endif()

target_link_libraries(vast_unittests PRIVATE
    appbase vast_chain vast_testing fc catch ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} ${Intl_LIBRARIES})

add_test(NAME vast_unittests
         COMMAND unittests/vast_unittests
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
