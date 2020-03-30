/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <type_traits>
#include <boost/any.hpp>
#include <vast/chain/types.hpp>
#include <vast/chain/exceptions.hpp>

namespace vast { namespace chain {

class apply_context;
class authority_checker;
class charge_manager;

struct action {
public:
    action_name name;
    domain_name domain;
    domain_key  key;
    bytes       data;

public:
    action() : index_(-1) {}

    // don't copy cache_ when in copy ctor.
    action(const action& lhs)
        : name(lhs.name)
        , domain(lhs.domain)
        , key(lhs.key)
        , data(lhs.data)
        , index_(lhs.index_)
        , cache_() {}

    action(action&& lhs) noexcept = default;

    action& operator=(const action& lhs) {
        if(this != &lhs) { // self-assignment check expected
            name   = lhs.name;
            domain = lhs.domain;
            key    = lhs.key;
            data   = lhs.data;
            index_ = lhs.index_;
        }
        return *this;
    }

    action& operator=(action&& lhs) noexcept {
        if(this != &lhs) { // self-assignment check expected
            name   = lhs.name;
            domain = lhs.domain;
            key    = lhs.key;
            data   = lhs.data;
            index_ = lhs.index_;
            cache_ = std::move(lhs.cache_);
        }
        return *this;
    }

public:
    template<typename T>
    action(const domain_name& domain, const domain_key& key, const T& value)
        : name(T::get_action_name())
        , domain(domain)
        , key(key)
        , data(fc::raw::pack(value))
        , index_(-1)
        , cache_(value) {}

    action(const action_name name, const domain_name& domain, const domain_key& key, const bytes& data)
        : name(name)
        , domain(domain)
        , key(key)
        , data(data)
        , index_(-1) {}

    template<typename T>
    void
    set_data(const T& value) {
        data   = fc::raw::pack(value);
        cache_ = value;
    }

    void
    set_index(int index) const {
        index_ = index;
    }

    // if T is a reference, will return the reference to the internal cache value
    // Otherwise if T is a value type, will return new copy. 
    template <typename T>
    T
    data_as() const {
        if(cache_.empty()) {
            using raw_type = std::remove_const_t<std::remove_reference_t<T>>;
            VAST_ASSERT(name == raw_type::get_action_name(), action_type_exception, "action name is not consistent with action struct");
            cache_ = fc::raw::unpack<raw_type>(data);
        }
        // no need to check name here, `any_cast` will throws exception if types don't match
        return boost::any_cast<T>(cache_);
    }

private:
    mutable int        index_;
    mutable boost::any cache_;

private:
    friend class apply_context;
    friend class authority_checker;
    friend class charge_manager;
};

}}  // namespace vast::chain

FC_REFLECT(vast::chain::action, (name)(domain)(key)(data));
