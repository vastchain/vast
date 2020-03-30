/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

#include <string>
#include <vast/chain/types.hpp>

namespace vast { namespace chain {

class controller;
struct action;

namespace contracts {

class lua_engine {
public:
    lua_engine();

public:
    bool invoke_filter(const controller& control, const action& act, const script_name& script);

};

}}}  // namespac vast::chain::contracts
