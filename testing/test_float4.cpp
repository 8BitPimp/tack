#include "testing.h"
#include <array>
#include <tack/float4.h>

TEST(float4, construct_value)
{
    tack::float4 a;
    std::array<float, 4> o;
    a.store(o.data());
    for (auto& f : o) {
        ASSERT(equals(0.f, f));
    }
}

TEST(float4, construct_single)
{
    tack::float4 a(42);
    std::array<float, 4> o;
    a.store(o.data());
    for (auto& f : o) {
        ASSERT(equals(42.f, f));
    }
}

TEST(float4, construct_multiple)
{
    tack::float4 a(42, 23, -42, -23);
    std::array<float, 4> o;
    a.store(o.data());
    ASSERT(equals(42.f, o[0]));
    ASSERT(equals(23.f, o[1]));
    ASSERT(equals(-42.f, o[2]));
    ASSERT(equals(-23.f, o[3]));
}

TEST(float4, construct_copy)
{
    tack::float4 a(42, 23, 48, 64);
    tack::float4 b(a);
    ASSERT(equals(a, b));
}

TEST(float4, assign_copy)
{
    tack::float4 a(42);
    tack::float4 b;
    b = a;
    ASSERT(equals(a, b));
}

TEST(float4, load_store)
{
    std::array<float, 4> i = { 42, 23, -42, -23 };
    tack::float4 f;
    f.load(i.data());
    std::array<float, 4> o;
    f.store(o.data());
    for (size_t index = 0; index < 4; index++) {
        ASSERT(equals(i[index], o[index]));
    }
}

TEST(float4, load_store_aligned)
{
    alignas(tack::float4) float i[4] = { 42, 23, -42, -23 };
    tack::float4 f;
    f.load<true>(i);
    alignas(tack::float4) float o[4];
    f.store<true>(o);
    for (size_t index = 0; index < 4; index++) {
        ASSERT(equals(i[index], o[index]));
    }
}

TEST(float4, operator_assign_plus)
{
    tack::float4 a(-23);
    a += tack::float4(42);
    ASSERT(equals(a, tack::float4(-23 + 42)));
}

TEST(float4, operator_assign_minus)
{
    tack::float4 a(42);
    a -= tack::float4(-256);
    ASSERT(equals(a, tack::float4(42 - (-256))));
}

TEST(float4, operator_assign_multiply) {
    tack::float4 a(4);
    a *= tack::float4(19);
    ASSERT(equals(a, tack::float4(4 * 19)));
}

TEST(float4, operator_assign_divide) {
    tack::float4 a(45.5f);
    a /= tack::float4(0.5f);
    ASSERT(equals(a, tack::float4(45.5f / 0.5f)));
}

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
