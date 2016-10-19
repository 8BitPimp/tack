#include "testing.h"
#include <tack/float4.h>
#include <array>

struct test_float4_abs_t : public test_t {

    test_float4_abs_t()
            : test_t("test_float4_abs")
    {
        register_test(this);
    }

    virtual bool run() override
    {
        using namespace tack;
        const float4 a(-1, 2, -3, 4);
        const float4 b = abs(a);
        std::array<float, 4> out;
        b.store(out.data());
        pass_ &= out[0]==1.f && out[1]==2.f && out[2]==3.f && out[3]==4.f;
        return passed();
    }
};

namespace {
test_float4_abs_t test_1;
} // namespace {}
