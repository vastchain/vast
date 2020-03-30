/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

#include <boost/noncopyable.hpp>
#include <vast/chain/exceptions.hpp>
#include <vast/chain/types.hpp>
#include <vast/chain/contracts/types.hpp>

namespace vast { namespace chain {

struct action_ver {
    name   act;
    int    ver;
};
using shared_action_vers = shared_vector<action_ver>;

struct action_ver_type {
    name   act;
    int    ver;
    string type;
};

class execution_context : boost::noncopyable {
public:
    virtual void initialize() = 0;
    virtual ~execution_context() {}

    virtual int index_of(name act) const = 0;
    virtual std::string get_acttype_name(name act) const = 0;
    virtual int set_version(name act, int ver) = 0;
    virtual int set_version_unsafe(name act, int ver) = 0;
    virtual int get_current_version(name act) const = 0;
    virtual int get_max_version(name act) const = 0;
    virtual std::vector<action_ver_type> get_current_actions() const = 0;
};

// helper method to add const lvalue reference to type object
template<typename T>
using add_clr_t = typename std::add_const<typename std::add_lvalue_reference<T>::type>::type;

}}  // namespace vast::chain

FC_REFLECT(vast::chain::action_ver, (act)(ver));
FC_REFLECT(vast::chain::action_ver_type, (act)(ver)(type));
