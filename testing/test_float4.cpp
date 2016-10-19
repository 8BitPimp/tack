#include "testing.h"
#include <tack/float4.h>

struct test_float4_t : public test_t {

    test_float4_t()
        : test_t("test_float4")
    {
        register_test(this);
    }

    void test1()
    {
        using namespace tack;

        float4 a(0.1f);
        float4 b(0.1f, 0.2f, 0.3f, 0.4f);
        for (int i = 0; i < 10; ++i) {
            a += b;
        }
        float4 c = b;
    }

    virtual bool run() override
    {
        test1();
        return passed();
    }
};

namespace {
test_float4_t test_instance;
} // namespace {}
