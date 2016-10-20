#include "testing.h"
#include <array>
#include <tack/float4.h>

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
    const float4 a(42, 23, 48, 64);
    const float4 b = a;
    const float4 c = a == b;
    std::array<float, 4> out;
    c.store(out.data());
    ASSERT_MSG(out[0] && out[1] && out[2] && out[3],
        "c is not equal to a");
}

TEST(float4, extract)
{
    using namespace tack;
    const float4 a(1.f, 2.f, 3.f, 4.f);
    ASSERT(a.x() == 1.f);
    ASSERT(a.y() == 2.f);
    ASSERT(a.z() == 3.f);
    ASSERT(a.w() == 4.f);
}

TEST(float4, blend)
{
    using namespace tack;
    const float4 a(1.f);
    const float4 b(2.f);
    const float4 c = blend<e_aabb>(a, b);
    ASSERT(equals(c, float4(1.f, 1.f, 2.f, 2.f)));
}

TEST(float4, swizzle)
{
    using namespace tack;
    std::array<float, 4> out;
    {
        const float4 a(1.f, 2.f, 3.f, 4.f);
        const float4 b = a.swizzle<e_xzyw>();
        b.store(out.data());
        ASSERT((out[0] == 1.f) && (out[1] == 3.f) && (out[2] == 2.f) && (out[3] == 4.f));
    }
    {
        const float4 a(1.f, 2.f, 3.f, 4.f);
        const float4 b = a.swizzle<e_xxyy>();
        b.store(out.data());
        ASSERT((out[0] == 1.f) && (out[1] == 1.f) && (out[2] == 2.f) && (out[3] == 2.f));
    }
}

TEST(float4, unary_minus)
{
    using namespace tack;
    const float4 a(-50.f, 30.f, 80.f, -123.f);
    const float4 b = -a;
    ASSERT(equals(b, float4(50.f, -30.f, -80.f, 123.f)));
}
