#pragma once

#include "ZC_FunctionHolder.h"
#include <ZC/Tools/Exception/ZC_Exception.h>

#include <memory>

/*
Function(method) pointer wrapper.
*/
template<typename TFunc>
class ZC_Function;
template<typename TReturn, typename... TParams>
class ZC_Function<TReturn(TParams...)>
{
public:
    ZC_Function() noexcept = delete;
    
    /*
    Create function wrapper.

    Params:
    pFunc - function pointer.
    */
    ZC_Function(TReturn(*pFunc)(TParams...)) noexcept;
    
    /*
    Create method wrapper.

    Params:
    pFunc - function pointer.
    pClass - class pointer.
    */
    template <typename TClass>
    ZC_Function(TReturn(TClass::*pFunc)(TParams...), TClass* pClass) noexcept;
    
    /*
    Create method wrapper.

    Params:
    pFunc - function pointer.
    pClass - class pointer.
    */
    template <typename TClass>
    ZC_Function(TReturn(TClass::*pFunc)(TParams...) const, TClass* pClass) noexcept;
    
    /*
    Create method wrapper.

    Params:
    pFunc - function pointer.
    pClass - class pointer.
    */
    template <typename TClass>
    ZC_Function(TReturn(TClass::*pFunc)(TParams...) const, const TClass* pClass) noexcept;

    ZC_Function(const ZC_Function<TReturn(TParams...)>&) = delete;
    ZC_Function<TReturn(TParams...)>& operator=(const ZC_Function<TReturn(TParams...)>&) = delete;

    ZC_Function(ZC_Function<TReturn(TParams...)>&& pFunc) noexcept;
    ZC_Function<TReturn(TParams...)>& operator = (ZC_Function<TReturn(TParams...)>&& func) noexcept;

    ~ZC_Function() noexcept;

    /*
    Call function(method). If function is nullptr throw exception.

    Params:
    params... - parameters of the function(method).

    Return:
    TReturn type object.
    */
    TReturn operator () (TParams... params) const;

private:
    ZC_IFunctionHolder<TReturn(TParams...)>* pFuncHolder = nullptr;
};

template <typename TReturn, typename... TParams>
ZC_Function<TReturn(TParams...)>::ZC_Function(TReturn(*pFunc)(TParams...)) noexcept
{
    pFuncHolder = dynamic_cast<ZC_IFunctionHolder<TReturn(TParams...)>*>(new ZC_FunctionHolder<TReturn(TParams...)>(pFunc));
}

template <typename TReturn, typename... TParams>
template <typename TClass>
ZC_Function<TReturn(TParams...)>::ZC_Function(TReturn(TClass::*pFunc)(TParams...), TClass* pClass) noexcept
{
    pFuncHolder = dynamic_cast<ZC_IFunctionHolder<TReturn(TParams...)>*>(new ZC_FunctionHolder<TReturn(TParams...), TClass>(pFunc, pClass));
}

template <typename TReturn, typename... TParams>
template <typename TClass>
ZC_Function<TReturn(TParams...)>::ZC_Function(TReturn(TClass::*pFunc)(TParams...) const, TClass* pClass) noexcept
{
    pFuncHolder = dynamic_cast<ZC_IFunctionHolder<TReturn(TParams...)>*>(new ZC_FunctionHolder<TReturn(TParams...), TClass>(pFunc, pClass));
}

template <typename TReturn, typename... TParams>
template <typename TClass>
ZC_Function<TReturn(TParams...)>::ZC_Function(TReturn(TClass::*pFunc)(TParams...) const, const TClass* pClass) noexcept
{
    pFuncHolder = dynamic_cast<ZC_IFunctionHolder<TReturn(TParams...)>*>(new ZC_FunctionHolder<TReturn(TParams...), TClass>(pFunc, pClass));
}

template <typename TReturn, typename... TParams>
ZC_Function<TReturn(TParams...)>::ZC_Function(ZC_Function<TReturn(TParams...)>&& pFunc) noexcept
    : pFuncHolder(pFunc.pFuncHolder)
{
    pFunc.pFuncHolder = nullptr;
}

template <typename TReturn, typename... TParams>
ZC_Function<TReturn(TParams...)>& ZC_Function<TReturn(TParams...)>::operator = (ZC_Function<TReturn(TParams...)>&& func) noexcept
{
    pFuncHolder = func.pFuncHolder;
    func.pFuncHolder = nullptr;
    return *this;
}

template <typename TReturn, typename... TParams>
ZC_Function<TReturn(TParams...)>::~ZC_Function() noexcept
{
    delete pFuncHolder;
    pFuncHolder = nullptr;
}

template <typename TReturn, typename... TParams>
TReturn ZC_Function<TReturn(TParams...)>::operator () (TParams... params) const
{
    if (!pFuncHolder) throw ZC_Exception(ZC_MakeErrorString("Call ZC_Function() with function pointer = nullptr!", __FILE__, __LINE__));
    return (*pFuncHolder)(params...);
}