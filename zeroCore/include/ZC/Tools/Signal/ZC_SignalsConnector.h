#pragma once

#include "ZC_Signal.h"

#include <map>
#include <vector>
#include <set>

template<typename T>
concept ZC_cLessCompare = requires(const T& t1, const T& t2)
{
    {t1 < t2} -> std::same_as<bool>;
};

template<ZC_cLessCompare TCondition, typename TFunction>
class ZC_SignalsConnector;

//  Collection of the Signals sorted by some condition type. Condition type must realize operator less than. 
template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
class ZC_SignalsConnector<TCondition, TReturn(TParams...)>
{
public:
    /*
    Connects ZC_Function with ZC_Signal according to the corresponding condition.

    Params:
    cond - condition (uses copy constructor).
    func - ZC_Function for connection.

    Return:
    ZC_SignalConnection pointer.
    */
    ZC_SignalConnection* Connect(const TCondition& cond, ZC_Function<TReturn(TParams...)>&& func) noexcept;

    /*
    Connects ZC_Function with ZC_Signal according to the corresponding condition.

    Params:
    cond - condition (uses move constructor).
    func - ZC_Function for connection.

    Return:
    ZC_SignalConnection pointer.
    */
    ZC_SignalConnection* Connect(TCondition&& cond, ZC_Function<TReturn(TParams...)>&& func) noexcept;

    /*
    Connects ZC_Function to ZC_Signal according to the corresponding condition, using shared pointer as the connection lifecycle.
    (when all pointers are destroyed on the client side, the connected function will be terminated).

    Params:
    func - ZC_Function for connection (uses copy constructor).
    pShared - shared pointer on some thing.

    Return:
    ZC_SignalConnection pointer.
    */
    template<typename TShared>
    ZC_SignalConnection* Connect(const TCondition& cond, ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept;
    
    /*
    Connects ZC_Function to ZC_Signal according to the corresponding condition, using shared pointer as the connection lifecycle.
    (when all pointers are destroyed on the client side, the connected function will be terminated).

    Params:
    func - ZC_Function for connection (uses move constructor).
    pShared - shared pointer on some thing.

    Return:
    ZC_SignalConnection pointer.
    */
    template<typename TShared>
    ZC_SignalConnection* Connect(TCondition&& cond, ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept;

protected:
    std::map<TCondition, ZC_Signal<TReturn(TParams...)>> signals;
    std::mutex signalsMutex;

    ZC_SignalsConnector() = default;
    virtual ~ZC_SignalsConnector() = default;

    template<typename TCond>
    ZC_Signal<TReturn(TParams...)>& GetSignal(TCond&& cond) noexcept;
};

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_SignalConnection* ZC_SignalsConnector<TCondition, TReturn(TParams...)>::Connect(const TCondition& cond, ZC_Function<TReturn(TParams...)>&& func) noexcept
{
    return GetSignal(cond).Connect(std::move(func));
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_SignalConnection* ZC_SignalsConnector<TCondition, TReturn(TParams...)>::Connect(TCondition&& cond, ZC_Function<TReturn(TParams...)>&& func) noexcept
{
    return GetSignal(std::move(cond)).Connect(std::move(func));
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_SignalsConnector<TCondition, TReturn(TParams...)>::Connect(const TCondition& cond, ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept
{
    return GetSignal(cond).Connect(std::move(func), pShared);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_SignalsConnector<TCondition, TReturn(TParams...)>::Connect(TCondition&& cond, ZC_Function<TReturn(TParams...)>&& func, const ZC_sptr<TShared>& pShared) noexcept
{
    return GetSignal(std::move(cond)).Connect(std::move(func), pShared);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
template<typename TCond>
ZC_Signal<TReturn(TParams...)>& ZC_SignalsConnector<TCondition, TReturn(TParams...)>::GetSignal(TCond&& cond) noexcept
{
    std::lock_guard<std::mutex> lock(signalsMutex);
    auto signalsIter = signals.find(cond);
    if (signalsIter == signals.end()) return signals.emplace(std::forward<TCond>(cond), ZC_Signal<TReturn(TParams...)>()).first->second;
    return signalsIter->second;
}