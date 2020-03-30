#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <fc/filesystem.hpp>
#include <fc/log/logger.hpp>
#include <fc/exception/exception.hpp>

#include <llvm/ADT/StringMap.h>

std::string vast_unittests_dir = "tmp/vast_unittests";

CATCH_TRANSLATE_EXCEPTION(fc::exception& e) {
    return e.to_detail_string();
}

int
main(int argc, char* argv[]) {
    if(fc::exists(vast_unittests_dir)) {
        fc::remove_all(vast_unittests_dir);
    }
    fc::logger::get().set_log_level(fc::log_level(fc::log_level::error));

    auto result = Catch::Session().run(argc, argv);

    fc::remove_all(vast_unittests_dir);
    return result;
}
