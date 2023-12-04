#pragma once

#include "ZC_VecArithmetic.h"

#include <concepts>

template<typename T>
concept ZC_cVecTypes = std::same_as<T, float> ||std::same_as<T, double>;

template<ZC_cVecTypes TValue = float>
struct ZC_Vec3
{
    constexpr ZC_Vec3(TValue x = 0, TValue y = 0, TValue z = 0) noexcept;

    constexpr TValue& operator [] (int index);
    constexpr const TValue& operator [] (int index) const;

    ZC_Vec3<TValue>& operator += (TValue addable) noexcept;
    constexpr ZC_Vec3<TValue> operator + (TValue addable) const noexcept;
    ZC_Vec3<TValue>& operator += (const ZC_Vec3<TValue>& addable) noexcept;
    constexpr ZC_Vec3<TValue> operator + (const ZC_Vec3<TValue>& addable) const noexcept;

    ZC_Vec3<TValue>& operator -= (TValue subtrahend) noexcept;
    constexpr ZC_Vec3<TValue> operator - (TValue subtrahend) const noexcept;
    ZC_Vec3<TValue>& operator -= (const ZC_Vec3<TValue>& subtrahend) noexcept;
    constexpr ZC_Vec3<TValue> operator - (const ZC_Vec3<TValue>& subtrahend) const noexcept;

    ZC_Vec3<TValue>& operator *= (TValue factor) noexcept;
    constexpr ZC_Vec3<TValue> operator * (TValue factor) const noexcept;

private:
    TValue values[3];
};

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue>::ZC_Vec3(TValue x, TValue y, TValue z) noexcept
    :values{x, y ,z}
{}

template<ZC_cVecTypes TValue>
constexpr TValue& ZC_Vec3<TValue>::operator [] (int index)
{
    return values[index];
}

template<ZC_cVecTypes TValue>
constexpr const TValue& ZC_Vec3<TValue>::operator [] (int index) const
{
    return const_cast<TValue&>(values[index]);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator += (TValue addable) noexcept
{
    for (short i = 0; i < 3; ++i) values[i] += addable;
    return *this;
}

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue> ZC_Vec3<TValue>::operator + (TValue addable) const noexcept
{
    return ZC_Vec3(values[0] + addable, values[1] + addable, values[2] + addable);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator += (const ZC_Vec3<TValue>& addable) noexcept
{
    for (short i = 0; i < 3; ++i) values[i] += addable.values[i];
    return *this;
}

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue> ZC_Vec3<TValue>::operator + (const ZC_Vec3<TValue>& addable) const noexcept
{
    return ZC_Vec3(values[0] + addable.values[0], values[1] + addable.values[1], values[2] + addable.values[2]);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator -= (TValue subtrahend) noexcept
{
    for (short i = 0; i < 3; ++i) values[i] -= subtrahend;
    return *this;
}

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue> ZC_Vec3<TValue>::operator - (TValue subtrahend) const noexcept
{
    return ZC_Vec3(values[0] - subtrahend, values[1] - subtrahend, values[2] - subtrahend);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator -= (const ZC_Vec3<TValue>& subtrahend) noexcept
{
    for (short i = 0; i < 3; ++i) values[i] -= subtrahend.values[i];
    return *this;
}

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue> ZC_Vec3<TValue>::operator - (const ZC_Vec3<TValue>& subtrahend) const noexcept
{
    return ZC_Vec3(values[0] - subtrahend.values[0], values[1] - subtrahend.values[1], values[2] - subtrahend.values[2]);
}

template<ZC_cVecTypes TValue>
ZC_Vec3<TValue>& ZC_Vec3<TValue>::operator *= (TValue factor) noexcept
{
    for (short i = 0; i < 3; ++i) values[i] *= factor;
    return *this;
}

template<ZC_cVecTypes TValue>
constexpr ZC_Vec3<TValue> ZC_Vec3<TValue>::operator * (TValue factor) const noexcept
{
    return ZC_Vec3(values[0] * factor, values[1] * factor, values[2] * factor);
}