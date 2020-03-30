/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */

#include <vast/utilities/tempdir.hpp>

#include <cstdlib>

namespace vast { namespace utilities {

fc::path temp_directory_path()
{
   const char* eos_tempdir = getenv("VAST_TEMPDIR");
   if( eos_tempdir != nullptr )
      return fc::path( eos_tempdir );
   return fc::temp_directory_path() / "eos-tmp";
}

} } // vast::utilities
