#pragma once

#include "ZC_Vec3.h"

template<ZC_cVecTypes TValue>
struct ZC_Vec4
{
    ZC_Vec4(const TValue& x = 0, const TValue& y = 0, const TValue& z = 0, const TValue& w = 0) noexcept;
    ZC_Vec4(const ZC_Vec3<TValue>& vec3, const TValue& w = 0) noexcept;

    TValue& operator [] (const int& index);
    const TValue& operator [] (const int& index) const;

    ZC_Vec4<TValue>& operator += (const TValue& addable) noexcept;
    ZC_Vec4<TValue> operator + (const TValue& addable) const noexcept;
    ZC_Vec4<TValue>& operator += (const ZC_Vec4<TValue>& addable) noexcept;
    ZC_Vec4<TValue> operator + (const ZC_Vec4<TValue>& addable) const noexcept;

    ZC_Vec4<TValue>& operator -= (const TValue& subtrahend) noexcept;
    ZC_Vec4<TValue> operator - (const TValue& subtrahend) const noexcept;
    ZC_Vec4<TValue>& operator -= (const ZC_Vec4<TValue>& subtrahend) noexcept;
    ZC_Vec4<TValue> operator - (const ZC_Vec4<TValue>& subtrahend) const noexcept;

    ZC_Vec4<TValue>& operator *= (const TValue& factor) noexcept;
    ZC_Vec4<TValue> operator * (const TValue& factor) const noexcept;

private:
    TValue values[4];
};

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>::ZC_Vec4(const TValue& x, const TValue& y, const TValue& z, const TValue& w) noexcept
    :values{x, y ,z, w}
{}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>::ZC_Vec4(const ZC_Vec3<TValue>& vec3, const TValue& w) noexcept
    :values{vec3[0], vec3[1], vec3[2], w}
{}

template<ZC_cVecTypes TValue>
TValue& ZC_Vec4<TValue>::operator [] (const int& index)
{
    return values[index];
}

template<ZC_cVecTypes TValue>
const TValue& ZC_Vec4<TValue>::operator [] (const int& index) const
{
    return const_cast<TValue&>(values[index]);
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator += (const TValue& addable) noexcept
{
    ZC_VecArithmetic::PlusValue(*this, 4, addable);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator + (const TValue& addable) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::PlusValue(result, 4, addable);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator += (const ZC_Vec4<TValue>& addable) noexcept
{
    ZC_VecArithmetic::PlusVec(*this, 4, addable);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator + (const ZC_Vec4<TValue>& addable) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::PlusVec(result, 4, addable);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator -= (const TValue& subtrahend) noexcept
{
    ZC_VecArithmetic::MinusValue(*this, 4, subtrahend);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator - (const TValue& subtrahend) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::MinusValue(result, 4, subtrahend);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator -= (const ZC_Vec4<TValue>& subtrahend) noexcept
{
    ZC_VecArithmetic::MinusVec(*this, 4, subtrahend);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator - (const ZC_Vec4<TValue>& subtrahend) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::MinusVec(result, 4, subtrahend);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator *= (const TValue& factor) noexcept
{
    ZC_VecArithmetic::MultiplyValue(*this, 4, factor);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator * (const TValue& factor) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::MultiplyValue(result, 4, factor);
    return result;
}