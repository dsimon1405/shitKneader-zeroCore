#pragma once

#include "ZC_VecArithmetic.h"

#include <concepts>

template<typename T>
concept ZC_cVecTypes = std::same_as<T, float> ||std::same_as<T, double>;

template<ZC_cVecTypes TValue = float>
struct ZC_Vec3
{
    ZC_Vec3(TValue x = 0, TValue y = 0, TValue z = 0) noexcept;

    TValue& operator [] (int index);
    const TValue& operator [] (int index) const;

    ZC_Vec3<TValue>& operator += (TValue addable) noexcept;
    ZC_Vec3<TValue> operator + (TValue addable) const noexcept;
    ZC_Vec3<TValue>& operator += (const ZC_Vec3<TValue>& addable) noexcept;
    ZC_Vec3<TValue> operator + (const ZC_Vec3<TValue>& addable) const noexcept;

    ZC_Vec3<TValue>& operator -= (TValue subtrahend) noexcept;
    ZC_Vec3<TValue> operator - (TValue subtrahend) const noexcept;
    ZC_Vec3<TValue>& operator -= (const ZC_Vec3<TValue>& subtrahend) noexcept;
    ZC_Vec3<TValue> operator - (const ZC_Vec3<TValue>& subtrahend) const noexcept;

    ZC_Vec3<TValue>& operator *= (TValue factor) noexcept;
    ZC_Vec3<TValue> operator * (TValue factor) const noexcept;

private:
    TValue values[3];
};

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>::ZC_Vec3(TValue x, TValue y, TValue z) noexcept
    :values{x, y ,z}
{}

template<ZC_cVecTypes TValue>
TValue& ZC_Vec3<TValue>::operator [] (int index)
{
    return values[index];
}

template<ZC_cVecTypes TValue>
const TValue& ZC_Vec3<TValue>::operator [] (int index) const
{
    return const_cast<TValue&>(values[index]);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator += (TValue addable) noexcept
{
    ZC_VecArithmetic::PlusValue(*this, 3, addable);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue> ZC_Vec3<TValue>::operator + (TValue addable) const noexcept
{
    ZC_Vec3<TValue> result = *this;
    ZC_VecArithmetic::PlusValue(result, 3, addable);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator += (const ZC_Vec3<TValue>& addable) noexcept
{
    ZC_VecArithmetic::PlusVec(*this, 3, addable);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue> ZC_Vec3<TValue>::operator + (const ZC_Vec3<TValue>& addable) const noexcept
{
    ZC_Vec3<TValue> result = *this;
    ZC_VecArithmetic::PlusVec(result, 3, addable);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator -= (TValue subtrahend) noexcept
{
    ZC_VecArithmetic::MinusValue(*this, 3, subtrahend);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue> ZC_Vec3<TValue>::operator - (TValue subtrahend) const noexcept
{
    ZC_Vec3<TValue> result = *this;
    ZC_VecArithmetic::MinusValue(result, 3, subtrahend);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator -= (const ZC_Vec3<TValue>& subtrahend) noexcept
{
    ZC_VecArithmetic::MinusVec(*this, 3, subtrahend);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue> ZC_Vec3<TValue>::operator - (const ZC_Vec3<TValue>& subtrahend) const noexcept
{
    ZC_Vec3<TValue> result = *this;
    ZC_VecArithmetic::MinusVec(result, 3, subtrahend);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator *= (TValue factor) noexcept
{
    ZC_VecArithmetic::MultiplyValue(*this, 3, factor);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue> ZC_Vec3<TValue>::operator * (TValue factor) const noexcept
{
    ZC_Vec3<TValue> result = *this;
    ZC_VecArithmetic::MultiplyValue(result, 3, factor);
    return result;
}