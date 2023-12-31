#pragma once

namespace ZC_MatArithmetic
{
    template<typename TMat, typename TValue>
    void MultiplyValue(TMat& mat, short size, TValue factor) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            mat[i] *= factor;
        }
    }

    template<typename TMat, typename TVec>
    void MultiplyVec(const TMat& mat, short size, const TVec& factor, TVec& result) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            for (short j = 0; j < size; ++j)
            {
                result[i] += (mat[j][i] * factor[j]);
            }
        }
    }

    template<typename TMat>
    void MultiplyMat(TMat& mat, short size, const TMat& factor) noexcept
    {
        TMat temp;
        for (short i = 0; i < size; ++i)
        {
            for (short j = 0; j < size; ++j)
            {
                temp[i] += (mat[j] * factor[i][j]);
            }
        }
        mat = temp;
    }
}