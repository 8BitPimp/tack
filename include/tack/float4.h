#ifndef TACK_FLOAT4_H_INCLUDED
#define TACK_FLOAT4_H_INCLUDED

#include <cassert>
#include <cstdint>
#include <x86intrin.h>

namespace tack {
struct float4 {
    float4()
        : m(_mm_setzero_ps())
    {
    }

    explicit float4(float x, float y, float z, float w)
        : m(_mm_set_ps(w, z, y, x))
    {
    }

    explicit float4(float v)
        : m(_mm_set_ps1(v))
    {
    }

    float4(const float4& in)
        : m(in)
    {
    }

    float4(const __m128& in)
        : m(in)
    {
    }

    operator const __m128&() const
    {
        return m;
    }

    float4& operator=(const float4& in)
    {
        m = in.m;
        return *this;
    }

    void load(const float* in)
    {
        m = is_aligned(in) ? _mm_load_ps(in) : _mm_loadu_ps(in);
    }

    void store(float* out) const
    {
        is_aligned(out) ? _mm_store_ps(out, m) : _mm_storeu_ps(out, m);
    }

    float4& operator+=(const float4& a)
    {
        m = _mm_add_ps(m, a);
        return *this;
    }

    float4& operator-=(const float4& a)
    {
        m = _mm_sub_ps(m, a);
        return *this;
    }

    float4& operator*=(const float4& a)
    {
        m = _mm_mul_ps(m, a);
        return *this;
    }

    float4& operator/=(const float4& a)
    {
        m = _mm_div_ps(m, a);
        return *this;
    }

    // TODO: float4& operator%=(const float4& a)

    float4& operator&=(const float4& a)
    {
        m = _mm_and_ps(m, a);
        return *this;
    }

    float4& operator|=(const float4& a)
    {
        m = _mm_or_ps(m, a);
        return *this;
    }

    float4& operator^=(const float4& a) {
        m = _mm_andnot_ps(m, a);
        return *this;
    }

    template <uint8_t x, uint8_t y, uint8_t z, uint8_t w>
    float4 shuffle()
    {
        return _mm_shuffle_ps(m, m, _MM_SHUFFLE(w, z, y, x));
    }

private:
    bool is_aligned(const float* in) const
    {
        return 0 == (size_t(in) & ((1 << alignof(__m128)) - 1));
    }

    __m128 m;
};

// TODO: inline float4 operator+(const float4 &a) const

// TODO: inline float4 operator-(const float4 &a) const

inline float4 operator+(const float4& a, const float4& b)
{
    return _mm_add_ps(a, b);
}

inline float4 operator-(const float4& a, const float4& b)
{
    return _mm_sub_ps(a, b);
}

inline float4 operator*(const float4& a, const float4& b)
{
    return _mm_mul_ps(a, b);
}

inline float4 operator/(const float4& a, const float4& b)
{
    return _mm_div_ps(a, b);
}

// TODO: inline float4 operator%(const float4& a, const float4& b)

inline float4 operator&(const float4& a, const float4& b)
{
    return _mm_and_ps(a, b);
}

inline float4 operator|(const float4& a, const float4& b)
{
    return _mm_or_ps(a, b);
}

inline float4 operator^(const float4& a, const float4& b)
{
    return _mm_andnot_ps(a, b);
}

inline float4 operator==(const float4& a, const float4& b)
{
    return _mm_cmpeq_ps(a, b);
}

inline float4 operator<(const float4& a, const float4& b)
{
    return _mm_cmplt_ps(a, b);
}

inline float4 operator<=(const float4& a, const float4& b)
{
    return _mm_cmple_ps(a, b);
}

inline float4 operator>(const float4& a, const float4& b)
{
    return _mm_cmpgt_ps(a, b);
}

inline float4 operator>=(const float4& a, const float4& b)
{
    return _mm_cmpge_ps(a, b);
}

inline float4 operator!=(const float4& a, const float4& b)
{
    return _mm_cmpneq_ps(a, b);
}

inline float4 sqrt(const float4& a)
{
    return _mm_sqrt_ps(a);
}

inline float4 rsqrt(const float4& a)
{
    return _mm_rsqrt_ps(a);
}

inline float4 max(const float4& a, const float4& b)
{
    return _mm_max_ps(a, b);
}

inline float4 min(const float4& a, const float4& b)
{
    return _mm_min_ps(a, b);
}

template <uint8_t x, uint8_t y, uint8_t z, uint8_t w>
inline float4 shuffle(const float4& a, const float4& b)
{
    return _mm_shuffle_ps(a, b, _MM_SHUFFLE(w, z, y, x));
}
} // tack

#endif // TACK_FLOAT4_H_INCLUDED
