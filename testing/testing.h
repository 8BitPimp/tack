#pragma once
#include <string>

struct test_t {

    test_t(const char* name)
        : pass_(true)
        , name_(name)
    {
    }

    virtual void run() = 0;

    const char* name() const
    {
        return name_;
    }

    bool passed() const
    {
        return pass_;
    }

    bool failed() const
    {
        return !pass_;
    }

    const char* message() const
    {
        return message_.c_str();
    }

    bool has_message() const
    {
        return !message_.empty();
    }

protected:
    bool pass_;
    const char* name_;
    std::string message_;
};

void register_test(test_t* instance);

#define TEST(GROUP, NAME)                           \
    namespace {                                     \
        struct GROUP##_##NAME##_t : public test_t { \
            GROUP##_##NAME##_t()                    \
                : test_t(#GROUP "." #NAME)          \
            {                                       \
                register_test(this);                \
            }                                       \
            virtual void run();                     \
        } GROUP##_##NAME;                           \
    }                                               \
    void GROUP##_##NAME##_t::run()

#define ASSERT(CONDITION)        \
    {                            \
        if (!(CONDITION)) {      \
            this->pass_ = false; \
        } else {                 \
            return;              \
        }                        \
    }

#define EXPECT(CONDITION)        \
    {                            \
        if (!(CONDITION)) {      \
            this->pass_ = false; \
        }                        \
    }
