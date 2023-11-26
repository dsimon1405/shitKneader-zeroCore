#pragma once

#include "ZC/Tools/Function/ZC_Function.h"
#include "ZC_SignalConnectionShared.h"
#include <ZC/Tools/ZC_uptr.h>
#include <ZC/Tools/ZC_sptr.h>

#include <list>
#include <concepts>
#include <mutex>

template<typename T>
concept ZC_cNotRValueRef = !std::is_rvalue_reference<T>::value;

template<typename TFunction>
class ZC_SignalConnector;
/*
Class for connecting any number of ZC_Functions with the same signature. It is not possible to create a connector for a function/method that accepts
rvalue reference type parameters.
*/
template<typename TReturn, ZC_cNotRValueRef... TParams>
class ZC_SignalConnector<TReturn(TParams...)>
{
public:
    /*
    Connects ZC_Function.

    Params:
    func - ZC_Function for connection.

    Return:
    ZC_SignalConnection pointer.
    */
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)>&& func) noexcept;
    
    /*
    Connects ZC_Function using shared pointer as the connection lifecycle.
    (when all pointers are destroyed on the client side, the connected function will be terminated).

    Params:
    func - ZC_Function for connection.
    pShared - shared pointer on some thing.

    Return:
    ZC_SignalConnection pointer.
    */
    template<typename TShared>
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept;
    
    //  Return the number of all added functions with states(connected/disconnected).
    size_t Size() noexcept;

protected:
    std::list<std::pair<ZC_uptr<ZC_SignalConnection>, ZC_Function<TReturn(TParams...)>>> functions;
    std::mutex functionsMutex;
    
    ZC_SignalConnector() = default;
    virtual ~ZC_SignalConnector() = default;
};

template<typename TReturn, ZC_cNotRValueRef... TParams>
ZC_SignalConnection* ZC_SignalConnector<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)>&& func) noexcept
{
    ZC_uptr<ZC_SignalConnection> pConnection = ZC_uptrMake<ZC_SignalConnection>();
    return functions.emplace_back(std::make_pair(std::move(pConnection), std::move(func))).first.Get();
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_SignalConnector<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept
{
    ZC_uptr<ZC_SignalConnection> pConnection = ZC_uptrMakeFromChild<ZC_SignalConnection, ZC_SignalConnectionShared<TShared>>(pShared); 
    return functions.emplace_back(std::make_pair(std::move(pConnection), std::move(func))).first.Get();
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
size_t ZC_SignalConnector<TReturn(TParams...)>::Size() noexcept
{
    std::lock_guard<std::mutex> lock(functionsMutex);
    for (auto functionsIter = functions.begin(); functionsIter != functions.end();)
    {
        functionsIter = functionsIter->first->GetState() == ZC_SignalConnection::State::Terminated ?
            functions.erase(functionsIter) : ++functionsIter;
    }
    return functions.size();
}