#pragma once

#include "ZC_IFunctionHolder.h"

#include <utility>

template<typename TFunc, typename TClass = void>
class ZC_FunctionHolder;

template<typename TReturn, typename... TParams>
class ZC_FunctionHolder<TReturn(TParams...)> : public ZC_IFunctionHolder<TReturn(TParams...)>
{
public:
    ZC_FunctionHolder() = delete;
    ZC_FunctionHolder(TReturn(* const& _pFunc)(TParams...)) noexcept;
    
    ~ZC_FunctionHolder() override = default;
    
    TReturn operator()(TParams&... params) const noexcept override;

private:
    TReturn(*pFunc)(TParams...);
};

template <typename TReturn, typename... TParams, typename TClass>
class ZC_FunctionHolder<TReturn(TParams...), TClass> : public ZC_IFunctionHolder<TReturn(TParams...)>
{
public:
    ZC_FunctionHolder() = delete;
    ZC_FunctionHolder(TReturn(TClass::* const& _pFunc)(TParams...), TClass* const& _pClass) noexcept;
    ZC_FunctionHolder(TReturn(TClass::* const& _pFunc)(TParams...) const, TClass* const& _pClass) noexcept;
    ZC_FunctionHolder(TReturn(TClass::* const& _pFunc)(TParams...) const, const TClass* const& _pClass) noexcept;

    ~ZC_FunctionHolder() override = default;
    
    TReturn operator()(TParams&... params) const noexcept override;

private:
    TClass* pClass;
    TReturn(TClass::*pFunc)(TParams...);
};

//  start  template <typename TReturn, typename... TParams> ZC_FunctionHolder<TReturn(TParams...)>
template<typename TReturn, typename... TParams>
ZC_FunctionHolder<TReturn(TParams...)>::ZC_FunctionHolder(TReturn(* const& _pFunc)(TParams...)) noexcept
    : pFunc(_pFunc)
{}

template<typename TReturn, typename... TParams>
TReturn ZC_FunctionHolder<TReturn(TParams...)>::operator()(TParams&... params) const noexcept
{
    return (*pFunc)(std::forward<TParams>(params)...);
}
//  end  template <typename TReturn, typename... TParams> ZC_FunctionHolder<TReturn(TParams...)>

//  start   template<typename TReturn, typename... TParams, typename TClass> class ZC_FunctionHolder<TReturn(TParams...), TClass>
template<typename TReturn, typename... TParams, typename TClass>
ZC_FunctionHolder<TReturn(TParams...), TClass>::ZC_FunctionHolder(TReturn(TClass::* const& _pFunc)(TParams...), TClass* const& _pClass) noexcept
    : pClass(_pClass),
    pFunc(_pFunc)
{}

template<typename TReturn, typename... TParams, typename TClass>
ZC_FunctionHolder<TReturn(TParams...), TClass>::ZC_FunctionHolder(TReturn(TClass::* const&_pFunc)(TParams...) const, TClass* const& _pClass) noexcept
    : pClass(_pClass),
    pFunc((TReturn(TClass::*)(TParams...))(_pFunc))
{}

template<typename TReturn, typename... TParams, typename TClass>
ZC_FunctionHolder<TReturn(TParams...), TClass>::ZC_FunctionHolder(TReturn(TClass::* const& _pFunc)(TParams...) const, const TClass* const& _pClass) noexcept
    : pClass(const_cast<TClass*>(_pClass)),
    pFunc((TReturn(TClass::*)(TParams...))(_pFunc))
{}

template<typename TReturn, typename... TParams, typename TClass>
TReturn ZC_FunctionHolder<TReturn(TParams...), TClass>::operator()(TParams&... params) const noexcept
{
    return (pClass->*pFunc)(std::forward<TParams>(params)...);
}
//  end   template<typename TReturn, typename... TParams, typename TClass> class ZC_FunctionHolder<TReturn(TParams...), TClass>