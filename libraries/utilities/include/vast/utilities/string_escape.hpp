/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

#include <string>

namespace vast { namespace utilities {

  std::string escape_string_for_c_source_code(const std::string& input);

} } // end namespace vast::utilities
