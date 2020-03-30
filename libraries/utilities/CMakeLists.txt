#list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libraries/fc/GitVersionGen" )
#include( GetGitRevisionDescription )
#get_git_head_revision(GIT_REFSPEC VAST_GIT_REVISION_SHA)
#get_git_unix_timestamp(VAST_GIT_REVISION_UNIX_TIMESTAMP)
#git_describe(VAST_GIT_REVISION_DESCRIPTION --tags)
if(NOT VAST_GIT_REVISION_DESCRIPTION)
    set(VAST_GIT_REVISION_DESCRIPTION "unknown")
endif(NOT VAST_GIT_REVISION_DESCRIPTION)

set(sources
    key_conversion.cpp
    string_escape.cpp
    tempdir.cpp
    words.cpp
)

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/git_revision.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp" @ONLY)
#list(APPEND sources "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp")

add_library(vast_utilities
    ${sources}
)
target_link_libraries(vast_utilities fc)
target_include_directories(vast_utilities PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
if (USE_PCH)
    set_target_properties(vast_utilities PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    cotire(vast_utilities)
endif(USE_PCH)
