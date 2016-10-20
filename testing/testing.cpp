#include <cstdio>
#include <cassert>
#include <vector>
#include <array>
#include <cmath>
#include "testing.h"
#include <tack/float4.h>

namespace {
std::vector<test_t*> s_tests;
} // namespace {}

void register_test(test_t* test)
{
    s_tests.push_back(test);
}

bool equals(const tack::float4 &a, const tack::float4 &b, float tolerance) {
    std::array<float, 4> av, bv;
    a.store(av.data());
    b.store(bv.data());
    bool pass = true;
    for (size_t i=0; i<4; ++i)
        pass &= (fabsf(bv[i]-av[i]) < tolerance);
    return pass;
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
    return passed != s_tests.size() ? 1 : 0;
}
