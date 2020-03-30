/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

#include <string>
#include <memory>
#include <fmt/format.h>
#include <vast/postgres_plugin/vast_pg.hpp>

namespace vast {

struct copy_context : boost::noncopyable {
public:
    copy_context(pg& pg) : db_(pg) {}

public:
    void
    commit() {
        db_.commit_copy_context(*this);
    }

private:
    fmt::memory_buffer blocks_copy_;
    fmt::memory_buffer trxs_copy_;
    fmt::memory_buffer actions_copy_;

private:
    pg& db_;

private:
    friend class pg;
};

}  // namespace vast
