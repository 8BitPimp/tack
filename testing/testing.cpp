// Copyright © 2016 Aidan Dodds <aidan.dodds@googlemail.com>
//                  Kenneth Benzie <k.benzie83@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "testing.h"
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <tack/float4.h>
#include <vector>

namespace {
std::vector<test_t*> s_tests;
} // namespace {}

void register_test(test_t* test)
{
    s_tests.push_back(test);
}

bool equals(const float& a, const float& b, float tolerance)
{
    return fabsf(a - b) < tolerance;
}

bool equals(const tack::float4& a, const tack::float4& b, float tolerance)
{
    std::array<float, 4> av, bv;
    a.store(av.data());
    b.store(bv.data());
    bool pass = true;
    for (size_t i = 0; i < 4; ++i)
        pass &= equals(av[i], bv[i], tolerance);
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
        } else {
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
