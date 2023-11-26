#pragma once

#include "ZC_Vec3.h"

template<ZC_cVecTypes TValue = float>
struct ZC_Vec4
{
    ZC_Vec4(TValue x = 0, TValue y = 0, TValue z = 0, TValue w = 0) noexcept;
    ZC_Vec4(const ZC_Vec3<TValue>& vec3, TValue w = 0) noexcept;

    TValue& operator [] (int index);
    const TValue& operator [] (int index) const;

    ZC_Vec4<TValue>& operator += (TValue addable) noexcept;
    ZC_Vec4<TValue> operator + (TValue addable) const noexcept;
    ZC_Vec4<TValue>& operator += (const ZC_Vec4<TValue>& addable) noexcept;
    ZC_Vec4<TValue> operator + (const ZC_Vec4<TValue>& addable) const noexcept;

    ZC_Vec4<TValue>& operator -= (TValue subtrahend) noexcept;
    ZC_Vec4<TValue> operator - (TValue subtrahend) const noexcept;
    ZC_Vec4<TValue>& operator -= (const ZC_Vec4<TValue>& subtrahend) noexcept;
    ZC_Vec4<TValue> operator - (const ZC_Vec4<TValue>& subtrahend) const noexcept;

    ZC_Vec4<TValue>& operator *= (TValue factor) noexcept;
    ZC_Vec4<TValue> operator * (TValue factor) const noexcept;

private:
    TValue values[4];
};

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>::ZC_Vec4(TValue x, TValue y, TValue z, TValue w) noexcept
    :values{x, y ,z, w}
{}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>::ZC_Vec4(const ZC_Vec3<TValue>& vec3, TValue w) noexcept
    :values{vec3[0], vec3[1], vec3[2], w}
{}

template<ZC_cVecTypes TValue>
TValue& ZC_Vec4<TValue>::operator [] (int index)
{
    return values[index];
}

template<ZC_cVecTypes TValue>
const TValue& ZC_Vec4<TValue>::operator [] (int index) const
{
    return const_cast<TValue&>(values[index]);
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator += (TValue addable) noexcept
{
    ZC_VecArithmetic::PlusValue(*this, 4, addable);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator + (TValue addable) const noexcept
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
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator -= (TValue subtrahend) noexcept
{
    ZC_VecArithmetic::MinusValue(*this, 4, subtrahend);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator - (TValue subtrahend) const noexcept
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
ZC_Vec4<TValue>& ZC_Vec4<TValue>::operator *= (TValue factor) noexcept
{
    ZC_VecArithmetic::MultiplyValue(*this, 4, factor);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Vec4<TValue>::operator * (TValue factor) const noexcept
{
    ZC_Vec4<TValue> result = *this;
    ZC_VecArithmetic::MultiplyValue(result, 4, factor);
    return result;
}