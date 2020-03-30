/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

namespace vast { namespace chain {
class token_database;
struct genesis_state;
}}  // namespace vast::chain

namespace vast { namespace chain { namespace contracts {

void initialize_vast_org(token_database& token_db, const genesis_state& genesis);
void update_vast_org(token_database& token_db, const genesis_state& genesis);

}}}  // namespace vast::chain::contracts
