#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_TEST_CASE
#include "minimal/log.h"
#include <doctest/doctest.h>
#include <exception>

int main(int const argc, char const **argv) {
    try {
        doctest::Context context;
        context.setOption("cout", true);  // Forces doctest to flush output
        context.applyCommandLine(argc, argv);

        auto const res(context.run());
        if (context.shouldExit()) {
            return res;
        }

        return res;
    } catch (std::exception const &e) {
        std::stringstream ss;
        ss << "Exception: " << e.what();
        cmgt::Log::error(ss.str());
    } catch (...) {
        cmgt::Log::error("Unkown exception thrown");
    }
}