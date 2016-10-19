#pragma once
#include <string>

struct test_t {

    test_t(const char* name)
        : pass_(true)
        , name_(name)
    {
    }

    virtual bool run() = 0;

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

extern void register_test(test_t* instance);
