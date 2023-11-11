#pragma once

#include <ZC/Tools/Tuple/ZC_TupleGetter.h>

template <typename TFunc>
class ZC_IFunctionHolder;
template <typename TReturn, typename... TParams>
class ZC_IFunctionHolder <TReturn(TParams...)>
{
public:
    virtual ~ZC_IFunctionHolder() = default;
    virtual TReturn operator()(TParams&... params) const noexcept = 0;

protected:
    ZC_IFunctionHolder() noexcept = default;
};