#include <cstdio>
#include <cassert>
#include <vector>
#include "testing.h"

namespace {
std::vector<test_t*> s_tests;
} // namespace {}

void register_test(test_t* test)
{
    s_tests.push_back(test);
}

int main()
{
    size_t passed = 0;
    for (test_t* test : s_tests) {
        assert(test);
        printf("%s: ", test->name());
        test->run();
        if (test->failed()) {
            printf("failed\n");
        }
        else {
            ++passed;
            printf("passed\n");
        }
        if (test->has_message()) {
            printf("  - %s\n", test->message());
        }
    }
    printf("%zu of %zu passed\n", passed, s_tests.size());
    return 0;
}
