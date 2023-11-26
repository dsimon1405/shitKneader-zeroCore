#pragma once

#include "ZC_Vec3.h"

#include <math.h>

namespace ZC_Vec
{
    /*
    Normalize the vector - make its length = 1, preserving the direction.

    Params:
    vec - vector for normalization.

    Return:
    Normalized vector;
    */
    template<ZC_cVecTypes TValue>
    ZC_Vec3<TValue> Normalize(const ZC_Vec3<TValue>& vec) noexcept
    {
        TValue squareLegSum = 0;
        for (short i = 0; i < 3; ++i)
        {
            squareLegSum += (vec[i] * vec[i]);
        }
        TValue lengthInversion = static_cast<TValue>(1) / sqrt(squareLegSum);

        ZC_Vec3<TValue> result
        (
            vec[0] * lengthInversion,
            vec[1] * lengthInversion,
            vec[2] * lengthInversion
        );
        return result;
    }

    /*
    Creates a vector orthogonal (90 degrees) to two others.

    Params:
    vec1 - first vector for creation orthogonal vector.
    vec2 - second vector for creation orthogonal vector.

    Return:
    Orthogonal vector.
    */
    template<ZC_cVecTypes TValue>
    ZC_Vec3<TValue> Cross(const ZC_Vec3<TValue>& vec1, const ZC_Vec3<TValue>& vec2) noexcept
    {
        ZC_Vec3<TValue> result
        (
            (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]),
            (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]),
            (vec1[0] * vec2[1]) - (vec1[1] * vec2[0])
        );
        return result;
    }

    /*
    Convert degrees to radians.

    Params:
    angle - angle in degrees.

    Return:
    Angle in radians.
    */
    template<ZC_cVecTypes TValue>
    TValue Radians(TValue angle) noexcept
    {
        static const TValue radiansCoef = static_cast<TValue>(M_PI / 180.0);
        return angle * radiansCoef;
    }

    /*
    Scalar product of two vectors (cosine of the angle between them).
    If 1 then the vectors are aligned (cos0 = 1).
    If 0 then the vectors are orthogonal (cos90 = 0).
    If -1 then they are opposite (cos180 = -1).
    Then cos270 = 0 and return to cos360 = 1 = cos0.

    Params:
    vec1 - first vector.
    vec2 - second vector.

    Return:
    Cosine of the angle between vec1 and vec2.
    */
    template<ZC_cVecTypes TValue>
    TValue Dot(const ZC_Vec3<TValue>& vec1, const ZC_Vec3<TValue>& vec2) noexcept
    {
        return (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) +(vec1[2] * vec2[2]);
    }
}