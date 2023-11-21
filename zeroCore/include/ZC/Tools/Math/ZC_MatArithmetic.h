#pragma once

namespace ZC_MatArithmetic
{
    template<typename TMat, typename TValue>
    void MultiplyValue(TMat& mat, const short& size, const TValue& factor)
    {
        for (short i = 0; i < size; ++i)
        {
            mat[i] *= factor;
        }
    }

    template<typename TMat, typename TVec>
    void MultiplyVec(const TMat& mat, const short& size, const TVec& factor, TVec& result)
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
    void MultiplyMat(TMat& mat, const short& size, const TMat& factor)
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