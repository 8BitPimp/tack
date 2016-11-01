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

#pragma once
#include <cstring>
#include <string>
#include <tack/float4.h>
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
bool equals(const float& a, const float& b, float tolerance = 0.001f);
bool equals(const tack::float4& a, const tack::float4& b, float tolerance = 0.001f);

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
