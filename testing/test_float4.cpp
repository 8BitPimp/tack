#include "testing.h"
#include <tack/float4.h>
#include <array>

TEST(float4, abs)
{
    using namespace tack;
    const float4 a(-1, 2, -3, 4);
    const float4 b = abs(a);
    std::array<float, 4> out;
    b.store(out.data());
    ASSERT(equals(b, float4(1.f, 2.f, 3.f, 4.f)));
}

TEST(float4, equal)
{
    using namespace tack;
    float4 a(42, 23, 48, 64);
    float4 b = a;
    float4 c = a == b;
    std::array<float, 4> out;
    c.store(out.data());
    ASSERT_MSG(out[0] && out[1] && out[2] && out[3],
        "c is not equal to a");
}
