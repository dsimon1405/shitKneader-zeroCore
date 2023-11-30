#pragma once

#include "ZC_SignalConnector.h"

#include <vector>

template<typename TFunction>
class ZC_Signal;
/*
Class for calling any number of ZC_Functions with the same signature. It is not possible to create a signal for a function/method that accepts rvalue
reference type parameters.
*/
template<typename TReturn, ZC_cNotRValueRef... TParams>
class ZC_Signal<TReturn(TParams...)> : public ZC_SignalConnector<TReturn(TParams...)>
{
public:
    //  Creates a ZC_Signal with the function signature <TReturn(TParams...)>.
    ZC_Signal() = default;

    ZC_Signal(const ZC_Signal<TReturn(TParams...)>&) = delete;
    ZC_Signal<TReturn(TParams...)>& operator = (const ZC_Signal<TReturn(TParams...)>&) = delete;

    ZC_Signal(ZC_Signal<TReturn(TParams...)>&& sig) noexcept;
    ZC_Signal<TReturn(TParams...)>& operator = (ZC_Signal<TReturn(TParams...)>&& sig) noexcept;

    ~ZC_Signal() override = default;
    
    /*
    Calls all connected ZC_Function.

    Params:
    params - parameters of the functions.
    */
    void operator()(TParams... params) noexcept;
    
    /*
    Calls all connected ZC_Function.

    Params:
    vec - a reference to a vector that will be filled with the function's return values.
    params - parameters of the functions.
    */
    void operator()(std::vector<TReturn>& container, TParams... params, bool needReserve = true) noexcept;
    
    //  Create Connector to the signal. Usefull for hide signal in private zone.
    ZC_SignalConnector<TReturn(TParams...)>* GetConnector() noexcept;
};

template<typename TReturn, ZC_cNotRValueRef... TParams>
ZC_Signal<TReturn(TParams...)>::ZC_Signal(ZC_Signal<TReturn(TParams...)>&& sig) noexcept
{
    this->functions = std::move(sig.functions);
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
ZC_Signal<TReturn(TParams...)>& ZC_Signal<TReturn(TParams...)>::operator = (ZC_Signal<TReturn(TParams...)>&& sig) noexcept
{
    this->functions = std::move(sig.functions);
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
void ZC_Signal<TReturn(TParams...)>::operator () (TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(this->functionsMutex);
    for (auto functionsIter = this->functions.begin(); functionsIter != this->functions.end();)
    {
        switch (functionsIter->first->GetState())
        {
            case ZC_SignalConnection::State::Connected:
                functionsIter->second(params...);
                ++functionsIter;
                break;
            case ZC_SignalConnection::State::Disconnected:
                ++functionsIter;
                break;
            case ZC_SignalConnection::State::Terminated:
                functionsIter = this->functions.erase(functionsIter);
                break;
        }
    }
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
void ZC_Signal<TReturn(TParams...)>::operator () (std::vector<TReturn>& container, TParams... params, bool needReserve) noexcept
{
    if (needReserve) container.reserve(this->Size());
    std::lock_guard<std::mutex> lock(this->functionsMutex);
    for (auto functionsIter = this->functions.begin(); functionsIter != this->functions.end();)
    {
        switch (functionsIter->first->GetState())
        {
            case ZC_SignalConnection::State::Connected:
                container.emplace_back(functionsIter->second(params...));
                ++functionsIter;
                break;
            case ZC_SignalConnection::State::Disconnected:
                ++functionsIter;
                break;
            case ZC_SignalConnection::State::Terminated:
                functionsIter = this->functions.erase(functionsIter);
                break;
        }
    }
}

template<typename TReturn, ZC_cNotRValueRef... TParams>
ZC_SignalConnector<TReturn(TParams...)>* ZC_Signal<TReturn(TParams...)>::GetConnector() noexcept
{
    return dynamic_cast<ZC_SignalConnector<TReturn(TParams...)>*>(this);
}