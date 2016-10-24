#ifndef TACK_FLOAT4_H_INCLUDED
#define TACK_FLOAT4_H_INCLUDED

#include <cassert>
#include <cstdint>
#include <x86intrin.h>

#include "common.h"

namespace tack {
template <typename in_t, typename out_t>
inline out_t bitcast(const in_t & x)
{
    return *reinterpret_cast<const out_t*>(&x);
}

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

    template <bool aligned = false>
    void load(const float* in)
    {
        alignment_check<aligned>(in);
        m = aligned ? _mm_load_ps(in) : _mm_loadu_ps(in);
    }

    template <bool aligned = false>
    void store(float* out) const
    {
        alignment_check<aligned>(out);
        aligned ? _mm_store_ps(out, m) : _mm_storeu_ps(out, m);
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

    float4& operator^=(const float4& a)
    {
        m = _mm_xor_ps(m, a);
        return *this;
    }

    template <swizzle_t mask>
    float4 swizzle() const
    {
        return _mm_shuffle_ps(m, m, mask);
    }

    float x() const
    {
        return bitcast<int32_t, float>(_mm_extract_ps(m, 0));
    }

    float y() const
    {
        return bitcast<int32_t, float>(_mm_extract_ps(m, 1));
    }

    float z() const
    {
        return bitcast<int32_t, float>(_mm_extract_ps(m, 2));
    }

    float w() const
    {
        return bitcast<int32_t, float>(_mm_extract_ps(m, 3));
    }

private:
    template <bool aligned>
    void alignment_check(const float* in) const
    {
        if (aligned) {
            assert(0 == (size_t(in) & (alignof(__m128) - 1)));
        }
    }

    __m128 m;
};

// TODO: inline float4 operator+(const float4 &a) const

inline float4 operator-(const float4& a)
{
    return _mm_xor_ps(a, _mm_set1_ps(-0.f));
}

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
    return _mm_xor_ps(a, b);
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

inline float4 abs(const float4& a)
{
    static const float4 sign_mask(-0.f);
    return _mm_andnot_ps(sign_mask, a);
}

template <uint8_t x, uint8_t y, uint8_t z, uint8_t w>
inline float4 shuffle(const float4& a, const float4& b)
{
    return _mm_shuffle_ps(a, b, _MM_SHUFFLE(w, z, y, x));
}

template <blend_t mask>
inline float4 blend(const float4& a, const float4& b)
{
    return _mm_blend_ps(a, b, mask);
}
} // tack

#endif // TACK_FLOAT4_H_INCLUDED
