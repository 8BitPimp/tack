#pragma once
#include <string>
#include <vector>

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

    template <class... Args>
    void format_message(Args... args)
    {
        std::vector<char> buffer(snprintf(nullptr, 0, args...) + 1);
        snprintf(buffer.data(), buffer.size(), args...);
        message_ += buffer.data();
    }

    void format_message(const char* format)
    {
        std::vector<char> buffer(strlen(format) + 1);
        snprintf(buffer.data(), buffer.size(), "%s", format);
        message_ += buffer.data();
    }

    const char* message() const
    {
        return message_.data();
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

#define ASSERT(CONDITION)                                        \
    {                                                            \
        if (!(CONDITION)) {                                      \
            this->pass_ = false;                                 \
            this->format_message("%s:%d: ", __FILE__, __LINE__); \
            return;                                              \
        }                                                        \
    }

#define ASSERT_MSG(CONDITION, ...)                               \
    {                                                            \
        if (!(CONDITION)) {                                      \
            this->pass_ = false;                                 \
            this->format_message("%s:%d: ", __FILE__, __LINE__); \
            this->format_message(__VA_ARGS__);                   \
            return;                                              \
        }                                                        \
    }

#define EXPECT(CONDITION)                                        \
    {                                                            \
        if (!(CONDITION)) {                                      \
            this->pass_ = false;                                 \
            this->format_message("%s:%d: ", __FILE__, __LINE__); \
        }                                                        \
    }

#define EXPECT_MSG(CONDITION, ...)                               \
    {                                                            \
        if (!(CONDITION)) {                                      \
            this->pass_ = false;                                 \
            this->format_message("%s:%d: ", __FILE__, __LINE__); \
            this->format_message(__VA_ARGS__);                   \
        }                                                        \
    }
