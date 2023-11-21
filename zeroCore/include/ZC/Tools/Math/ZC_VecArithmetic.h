#pragma once

namespace ZC_VecArithmetic
{
    template<typename TVec, typename TValue>
    void PlusValue(TVec& vec, const short& size, const TValue& addable) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            vec[i] += addable;
        }
    }

    template<typename TVec>
    void PlusVec(TVec& vec1, const short& size, const TVec& addable) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            vec1[i] += addable[i];
        }
    }

    template<typename TVec, typename TValue>
    void MinusValue(TVec& vec, const short& size, const TValue& subtrahend) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            vec[i] -= subtrahend;
        }
    }

    template<typename TVec>
    void MinusVec(TVec& vec1, const short& size, const TVec& subtrahend) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            vec1[i] -= subtrahend[i];
        }
    }

    template<typename TVec, typename TValue>
    void MultiplyValue(TVec& vec, const short& size, const TValue& factor) noexcept
    {
        for (short i = 0; i < size; ++i)
        {
            vec[i] *= factor;
        }
    }
}