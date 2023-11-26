#pragma once

#include "ZC_Vec4.h"
#include "ZC_MatArithmetic.h"

/*
Matrix 4x4 for working with vectors. Order of operations: Scale->Rotate->Translate
(methods must be called in the reverse order to correctly compile the matrix).

in method
{
    Translate (to the world positon)

    Translate (to the starting position)
    Rotate
    Translate (sentralize object)

    Scale
}
*/
template<ZC_cVecTypes TValue = float>
struct ZC_Mat4
{

    ZC_Mat4(TValue value = 0) noexcept;

    ZC_Vec4<TValue>& operator [] (int index);
    const ZC_Vec4<TValue>& operator [] (int index) const;

    ZC_Mat4<TValue>& operator *= (TValue value) noexcept;
    ZC_Mat4<TValue> operator * (TValue value) const noexcept;
    ZC_Vec4<TValue> operator * (const ZC_Vec4<TValue>& vec) const noexcept;
    ZC_Mat4<TValue>& operator *= (const ZC_Mat4& mat) noexcept;
    ZC_Mat4<TValue> operator * (const ZC_Mat4& mat) const noexcept;

    /*
    Converts a matrix for vector axis scaling.

    Params:
    scale - a vector with scaling values ​​along the axes.

    Return:
    Scaling matrix. 
    */
    ZC_Mat4<TValue>& Scale(const ZC_Vec3<TValue>& scale) noexcept;

    /*
    Converts a matrix for rotation along vector axes.

    Params:
    angle - the angle of rotation in degrees.
    axiss - vector with axes of rotation фтв degree of rotation for each.

    Return:
    Rotation matrix.
    */
    ZC_Mat4<TValue>& Rotate(TValue angle, const ZC_Vec3<TValue>& axiss) noexcept;

    /*
    Transform the matrix for vector translation.

    Params:
    trans - a vector with translate values for each axis.

    Return:
    Translation matrix.
    */
    ZC_Mat4<TValue>& Translate(const ZC_Vec3<TValue>& trans) noexcept;

    /*
    Returns a pointer to the first element of the matrix.
    */
    const TValue* Begin() const noexcept;

private:
    ZC_Vec4<TValue> columns[4];
};

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>::ZC_Mat4(TValue value) noexcept
    :columns
    {
        {static_cast<TValue>(value)},
        {0, static_cast<TValue>(value)},
        {0, 0, static_cast<TValue>(value)},
        {0, 0, 0, static_cast<TValue>(value)}
    }
{}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue>& ZC_Mat4<TValue>::operator [] (int index)
{
    return columns[index];
}

template<ZC_cVecTypes TValue>
const ZC_Vec4<TValue>& ZC_Mat4<TValue>::operator [] (int index) const
{
    return const_cast<const ZC_Vec4<TValue>&>(columns[index]);
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>& ZC_Mat4<TValue>::operator *= (TValue value) noexcept
{
    ZC_MatArithmetic::MultiplyValue(*this, 4, value);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue> ZC_Mat4<TValue>::operator * (TValue value) const noexcept
{
    ZC_Mat4 result = *this;
    return result *= value;
}

template<ZC_cVecTypes TValue>
ZC_Vec4<TValue> ZC_Mat4<TValue>::operator * (const ZC_Vec4<TValue>& vec) const noexcept
{
    ZC_Vec4<TValue> result;
    ZC_MatArithmetic::MultiplyVec(*this, 4, vec, result);
    return result;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>& ZC_Mat4<TValue>::operator *= (const ZC_Mat4<TValue>& mat) noexcept
{
    ZC_MatArithmetic::MultiplyMat(*this, 4, mat);
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue> ZC_Mat4<TValue>::operator * (const ZC_Mat4<TValue>& mat) const noexcept
{
    ZC_Mat4 result = *this;
    return result *= mat;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>& ZC_Mat4<TValue>::Scale(const ZC_Vec3<TValue>& scale) noexcept
{
    columns[0] *= scale[0];
    columns[1] *= scale[1];
    columns[2] *= scale[2];
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>& ZC_Mat4<TValue>::Rotate(TValue angle, const ZC_Vec3<TValue>& axiss) noexcept
{
    const TValue radAngle = ZC_Vec::Radians(angle);
    const TValue c = cos(radAngle);
    const TValue s = sin(radAngle);

    ZC_Vec3<TValue> axis(ZC_Vec::Normalize(axiss));
    ZC_Vec3<TValue> temp(axis * (static_cast<TValue>(1) - c));

    ZC_Vec3<TValue> rotateX;
    rotateX[0] = c + temp[0] * axis[0];
    rotateX[1] = temp[0] * axis[1] + s * axis[2];
    rotateX[2] = temp[0] * axis[2] - s * axis[1];
    ZC_Vec4<TValue> columnX = columns[0] * rotateX[0] + columns[1] * rotateX[1] + columns[2] * rotateX[2];

    ZC_Vec3<TValue> rotateY;
    rotateY[0] = temp[1] * axis[0] - s * axis[2];
    rotateY[1] = c + temp[1] * axis[1];
    rotateY[2] = temp[1] * axis[2] + s * axis[0];
    ZC_Vec4<TValue> columnY = columns[0] * rotateY[0] + columns[1] * rotateY[1] + columns[2] * rotateY[2];

    ZC_Vec3<TValue> rotateZ;
    rotateZ[0] = temp[2] * axis[0] + s * axis[1];
    rotateZ[1] = temp[2] * axis[1] - s * axis[0];
    rotateZ[2] = c + temp[2] * axis[2];
    ZC_Vec4<TValue> columnZ = columns[0] * rotateZ[0] + columns[1] * rotateZ[1] + columns[2] * rotateZ[2];

    columns[0] = columnX;
    columns[1] = columnY;
    columns[2] = columnZ;
    return *this;
}

template<ZC_cVecTypes TValue>
ZC_Mat4<TValue>& ZC_Mat4<TValue>::Translate(const ZC_Vec3<TValue>& trans) noexcept
{
    columns[3] = (columns[0] * trans[0]) + (columns[1] * trans[1]) + (columns[2] * trans[2]) + columns[3];
    return *this;
}

template<ZC_cVecTypes TValue>
const TValue* ZC_Mat4<TValue>::Begin() const noexcept
{
    return &columns[0][0];
}