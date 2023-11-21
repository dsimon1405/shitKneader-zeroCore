#pragma once

#include "ZC/Tools/Function/ZC_Function.h"
#include "ZC_SignalConnectionShared.h"
#include <ZC/Tools/ZC_uptr.h>

#include <map>
#include <vector>
#include <concepts>
#include <condition_variable>

template<typename TUnused>
class ZC_Signal;
//  Class for calling any number of ZC_Functions with the same signature.
template<typename TReturn, typename... TParams>
class ZC_Signal<TReturn(TParams...)>
{
public:
    //  Class for connecting ZC_Function to ZC_Signal.
    class Connector
    {
    public:
        Connector() = delete;

        /*
        Creates Connector to ZC_Signal.

        Params:
        _pSignal - ZC_Signal pointer.
        */
        Connector(ZC_Signal<TReturn(TParams...)>* _pSignal) noexcept;

        ~Connector() noexcept = default;

        /*
        Connects ZC_Function to ZC_Signal.

        Params:
        func - ZC_Function for connection.
        callNumber - call sequence number.

        Return:
        On success ZC_SignalConnection pointer, otherwise nullptr.
        */
        ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber = 0) noexcept;

        /*
        Connects ZC_Function to ZC_Signal.

        Params:
        func - ZC_Function for connection.
        pShared - shared pointer on some thing (if pShared.use_cout() = 1 func will be disconnect).
        callNumber - call sequence number.

        Return:
        On success ZC_SignalConnection pointer, else nullptr.
        */
        template <typename TShared>
        ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const std::shared_ptr<TShared>& pShared, const unsigned short& callNumber = 0) noexcept;

    private:
        ZC_Signal<TReturn(TParams...)>* pSignal;
    };

    /*
    Creates a ZC_Signal with the function signature <TReturn(TParams...)>.
    */
    ZC_Signal() = default;

    ZC_Signal(const ZC_Signal<TReturn(TParams...)>&) = delete;
    ZC_Signal<TReturn(TParams...)>& operator = (const ZC_Signal<TReturn(TParams...)>&) = delete;

    ZC_Signal(ZC_Signal<TReturn(TParams...)>&& sig) noexcept;
    ZC_Signal<TReturn(TParams...)>& operator = (ZC_Signal<TReturn(TParams...)>&& sig) noexcept;

    ~ZC_Signal() = default;

    /*
    Connects ZC_Function to ZC_Signal.

    Params:
    func - ZC_Function for connection.
    callNumber - call sequence number.

    Return:
    ZC_SignalConnection pointer.
    */
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber = 0) noexcept;
    
    /*
    Connects ZC_Function to ZC_Signal.

    Params:
    func - ZC_Function for connection.
    pShared - shared pointer on some thing (if it's use_cout() = 1 func will be disconnect).
    callNumber - call sequence number.

    Return:
    ZC_SignalConnection pointer.
    */
    template<typename TShared>
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const std::shared_ptr<TShared>& pShared, const unsigned short& callNumber = 0) noexcept;
    
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
    void operator()(std::vector<TReturn>& vec, TParams... params) noexcept;
    
    /*
    Help to get Connector to the current ZC_Signal.

    Return:
    Connector to the current ZC_Signal.
    */
    typename ZC_Signal<TReturn(TParams...)>::Connector GetConnector() noexcept;

private:
    std::map<unsigned short, std::map<ZC_uptr<ZC_SignalConnection>, ZC_Function<TReturn(TParams...)>>> functions;
    std::mutex functionsMutex;

    void AddFunction(ZC_uptr<ZC_SignalConnection>& pConnection, ZC_Function<TReturn(TParams...)>& func, const unsigned short& callNumber) noexcept;
};

//  start  ZC_Signal<TReturn(TParams...)>::Connector

template<typename TReturn, typename... TParams>
ZC_Signal<TReturn(TParams...)>::Connector::Connector(ZC_Signal<TReturn(TParams...)>* _pSignal) noexcept
{
    pSignal = _pSignal;
}

template<typename TReturn, typename... TParams>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connector::Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber) noexcept
{
    return pSignal ? pSignal->Connect(std::move(func), callNumber) : nullptr;
}

template<typename TReturn, typename... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connector::Connect(ZC_Function<TReturn(TParams...)> func, const std::shared_ptr<TShared>& pShared, const unsigned short& callNumber) noexcept
{
    return pSignal ? pSignal->Connect(std::move(func), pShared, callNumber) : nullptr;
}
//  end  ZC_Signal<TReturn(TParams...)>::Connector

//  start  ZC_Signal<TReturn(TParams...)>

template<typename TReturn, typename... TParams>
ZC_Signal<TReturn(TParams...)>::ZC_Signal(ZC_Signal<TReturn(TParams...)>&& sig) noexcept
    : functions(std::move(sig.functions))
{}

template<typename TReturn, typename... TParams>
ZC_Signal<TReturn(TParams...)>& ZC_Signal<TReturn(TParams...)>::operator = (ZC_Signal<TReturn(TParams...)>&& sig) noexcept
{
    functions = std::move(sig.functions);
}

template<typename TReturn, typename... TParams>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber) noexcept
{
    ZC_uptr<ZC_SignalConnection> pConnection = ZC_uptrMake<ZC_SignalConnection>(ZC_SignalConnection());
    ZC_SignalConnection* con = pConnection.Get();
    AddFunction(pConnection, func, callNumber);
    return con;
}

template<typename TReturn, typename... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)> func, const std::shared_ptr<TShared>& pShared, const unsigned short& callNumber) noexcept
{
    ZC_uptr<ZC_SignalConnection> pConnection = ZC_uptrMakeFromChild<ZC_SignalConnection, ZC_SignalConnection>(pShared); 
    ZC_SignalConnection* con = pConnection.Get();
    AddFunction(pConnection, func, callNumber);
    return con;
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::operator () (TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(functionsMutex);
    for (auto callPairIter = functions.begin(); callPairIter != functions.end();)
    {
        for (auto funcPairIter = callPairIter->second.begin(); funcPairIter != callPairIter->second.end();)
        {
            switch (funcPairIter->first->GetState())
            {
                case ZC_SignalConnection::State::Connected:
                    funcPairIter->second(params...);
                    ++funcPairIter;
                    break;
                case ZC_SignalConnection::State::Terminated:
                    funcPairIter = callPairIter->second.erase(funcPairIter);
                    break;
                case ZC_SignalConnection::State::Disconnected:
                    ++funcPairIter;
                    break;
            }
        }

        callPairIter = callPairIter->second.size() == 0 ? functions.erase(callPairIter) : ++callPairIter;
    }
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::operator () (std::vector<TReturn>& vec, TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(functionsMutex);
    int vecSize = 0;
    for (auto& callPair : functions)
    {
        vecSize += callPair.second.size();
    }
    vec.reserve(vecSize);

    for (auto callPairIter = functions.begin(); callPairIter != functions.end();)
    {
        for (auto funcPairIter = callPairIter->second.begin(); funcPairIter != callPairIter->second.end();)
        {
            switch (funcPairIter->first->GetState())
            {
                case ZC_SignalConnection::State::Connected:
                    vec.emplace_back(funcPairIter->second(params...));
                    ++funcPairIter;
                    break;
                case ZC_SignalConnection::State::Terminated:
                    funcPairIter = callPairIter->second.erase(funcPairIter);
                    break;
                case ZC_SignalConnection::State::Disconnected:
                    ++funcPairIter;
                    break;
            }
        }

        callPairIter = callPairIter->second.size() == 0 ? functions.erase(callPairIter) : ++callPairIter;
    }
}

template<typename TReturn, typename... TParams>
typename ZC_Signal<TReturn(TParams...)>::Connector ZC_Signal<TReturn(TParams...)>::GetConnector() noexcept
{
    return ZC_Signal<TReturn(TParams...)>::Connector(this);
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::AddFunction(ZC_uptr<ZC_SignalConnection>& pConnection, ZC_Function<TReturn(TParams...)>& func, const unsigned short& callNumber) noexcept
{
    std::lock_guard<std::mutex> lock(functionsMutex);
    auto callPairIter = functions.find(callNumber);
    if (callPairIter != functions.end())
    {
        callPairIter->second.emplace(std::move(pConnection), std::move(func));
    }
    else
    {
        std::map<ZC_uptr<ZC_SignalConnection>, ZC_Function<TReturn(TParams...)>> map;
        map.emplace(std::move(pConnection), std::move(func));
        functions.emplace(callNumber, std::move(map));
    }
}