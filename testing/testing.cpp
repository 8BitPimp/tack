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
            printf("failed\n  - %s\n", test->message());
        }
        else {
            ++passed;
            printf("passed\n");
        }
    }
    printf("%zu of %zu passed\n", passed, s_tests.size());
    return 0;
}
