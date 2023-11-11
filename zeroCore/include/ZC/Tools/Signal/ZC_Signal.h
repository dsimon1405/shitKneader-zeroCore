#pragma once

#include "ZC/Tools/Function/ZC_Function.h"
#include "ZC_SignalConnectionShared.h"

#include <map>
#include <vector>
#include <concepts>
#include <condition_variable>
#include <thread>

template<typename TFirst, typename TSecond>
concept ZC_cSameTypes = std::same_as<TFirst, TSecond>;

template<typename TUnused>
class ZC_Signal;
/*
Class for calling any number of ZC_Functions with the same signature.
*/
template<typename TReturn, typename... TParams>
class ZC_Signal<TReturn(TParams...)>
{
public:
    /*
    Class for connecting ZC_Function to ZC_Signal.
    */
    class Connector
    {
    public:
        Connector() = delete;

        /*
        Create Connector to ZC_Signal.

        Params:
        _pSignal - ZC_Signal pointer.
        */
        Connector(ZC_Signal<TReturn(TParams...)>* _pSignal) noexcept;

        ~Connector() noexcept = default;

        /*
        Connect ZC_Function to ZC_Signal.

        Params:
        func - ZC_Function for connection.
        callNumber - call sequence number.

        Return:
        On success ZC_SignalConnection pointer, otherwise nullptr.
        */
        ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber = 0) noexcept;

        /*
        Connect ZC_Function to ZC_Signal.

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
    Create a ZC_Signal with the function signature <TReturn(TParams...)>.
    */
    ZC_Signal() noexcept;

    ZC_Signal(const ZC_Signal<TReturn(TParams...)>&) = delete;
    ZC_Signal<TReturn(TParams...)>& operator=(const ZC_Signal<TReturn(TParams...)>&) = delete;

    ZC_Signal(ZC_Signal<TReturn(TParams...)>&&) = delete;
    ZC_Signal<TReturn(TParams...)>& operator=(ZC_Signal<TReturn(TParams...)>&&) = delete;

    ~ZC_Signal() noexcept;

    /*
    Connect ZC_Function to ZC_Signal.

    Params:
    func - ZC_Function for connection.
    callNumber - call sequence number.

    Return:
    ZC_SignalConnection pointer.
    */
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber = 0) noexcept;
    
    /*
    Connect ZC_Function to ZC_Signal.

    Params:
    func - ZC_Function for connection.
    pShared - shared pointer on some thing (if it's use_cout() = 1 func will be disconnect).
    callNumber - call sequence number.

    Return:
    ZC_SignalConnection pointer.
    */
    template<typename TShared>
    ZC_SignalConnection* Connect(ZC_Function<TReturn(TParams...)> func, std::shared_ptr<TShared> pShared, const unsigned short& callNumber = 0) noexcept;
    
    /*
    Call all connected ZC_Function.

    Params:
    params - parameters of the functions.
    */
    void operator()(TParams... params) noexcept;
    
    /*
    Call all connected ZC_Function.

    Params:
    vec - a reference to a vector that will be filled with the function's return values.
    params - parameters of the functions.
    */
    template<ZC_cSameTypes<TReturn> _TReturn>
    void operator()(std::vector<_TReturn>& vec, TParams... params) noexcept;
    
    /*
    Help to get Connector to the current ZC_Signal.

    Return:
    Connector to the current ZC_Signal.
    */
    typename ZC_Signal<TReturn(TParams...)>::Connector GetConnector() noexcept;

private:
    enum FunctionsState
    {
        Active,
        Terminate,
        Finish
    };

    std::map<unsigned short, std::map<ZC_SignalConnection*, ZC_Function<TReturn(TParams...)>>> functions;
    std::mutex functionsMutex;
    std::condition_variable functionsCV;
    FunctionsState functionState = FunctionsState::Active;

    void AddFunction(ZC_SignalConnection* pConnection, ZC_Function<TReturn(TParams...)>& func, const unsigned short& callNumber) noexcept;
    void FunctionsTerminate() noexcept;
    void FunctionsFinish() noexcept;
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
ZC_Signal<TReturn(TParams...)>::ZC_Signal() noexcept
{
    std::thread functionsTerminateTh([&]
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(functionsMutex);
            functionsCV.wait(lock, [&]
                {
                    return functionState != FunctionsState::Active;
                });
            
            if (functionState == FunctionsState::Finish)
            {
                FunctionsFinish();
                break;
            }
            
            FunctionsTerminate();

            functionState = FunctionsState::Active;
        }
    });

    functionsTerminateTh.detach();
}

template<typename TReturn, typename... TParams>
ZC_Signal<TReturn(TParams...)>::~ZC_Signal() noexcept
{
    std::unique_lock<std::mutex> lock(functionsMutex);
    functionState = FunctionsState::Finish;
    lock.unlock();
    functionsCV.notify_one();
}

template<typename TReturn, typename... TParams>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)> func, const unsigned short& callNumber) noexcept
{
    ZC_SignalConnection* pConnection = new ZC_SignalConnection();
    AddFunction(pConnection, func, callNumber);
    return pConnection;
}

template<typename TReturn, typename... TParams>
template<typename TShared>
ZC_SignalConnection* ZC_Signal<TReturn(TParams...)>::Connect(ZC_Function<TReturn(TParams...)> func, std::shared_ptr<TShared> pShared, const unsigned short& callNumber) noexcept
{
    ZC_SignalConnection* pConnection = dynamic_cast<ZC_SignalConnection*>(new ZC_SignalConnectionShared(pShared));
    AddFunction(pConnection, func, callNumber);
    return pConnection;
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::operator () (TParams... params) noexcept
{
    std::unique_lock<std::mutex> lock(functionsMutex);

    for (std::pair<const unsigned short, std::map<ZC_SignalConnection*, ZC_Function<TReturn(TParams...)>>>& callPair : functions)
    {
        for (std::pair<ZC_SignalConnection*const, ZC_Function<TReturn(TParams...)>>& funcPair : callPair.second)
        {
            switch (funcPair.first->GetState())
            {
                case ZC_SignalConnection::ConnectionState::Connected:
                    funcPair.second(params...);
                    break;
                case ZC_SignalConnection::ConnectionState::Terminated:
                    functionState = FunctionsState::Terminate;
                    break;
                case ZC_SignalConnection::ConnectionState::Disconnected:
                    break;
            }
        }
    }

    if (functionState == FunctionsState::Terminate)
    {
        lock.unlock();
        functionsCV.notify_one();
    }
}

template<typename TReturn, typename... TParams>
template<ZC_cSameTypes<TReturn> TRet>
void ZC_Signal<TReturn(TParams...)>::operator () (std::vector<TRet>& vec, TParams... params) noexcept
{
    std::unique_lock<std::mutex> lock(functionsMutex);

    int vecSize = 0;
    for (auto& callPair : functions)
    {
        vecSize += callPair.second.size();
    }
    vec.reserve(vecSize);

    for (std::pair<const unsigned short, std::map<ZC_SignalConnection*, ZC_Function<TReturn(TParams...)>>>& callPair : functions)
    {
        for (std::pair<ZC_SignalConnection*const, ZC_Function<TReturn(TParams...)>>& funcPair : callPair.second)
        {
            switch (funcPair.first->GetState())
            {
                case ZC_SignalConnection::ConnectionState::Connected:
                    vec.emplace_back(funcPair.second(params...));
                    break;
                case ZC_SignalConnection::ConnectionState::Terminated:
                    functionState = FunctionsState::Terminate;
                    break;
                case ZC_SignalConnection::ConnectionState::Disconnected:
                    break;
            }
        }
    }

    if (functionState == FunctionsState::Terminate)
    {
        lock.unlock();
        functionsCV.notify_one();
    }
}

template<typename TReturn, typename... TParams>
typename ZC_Signal<TReturn(TParams...)>::Connector ZC_Signal<TReturn(TParams...)>::GetConnector() noexcept
{
    return ZC_Signal<TReturn(TParams...)>::Connector(this);
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::AddFunction(ZC_SignalConnection* pConnection, ZC_Function<TReturn(TParams...)>& func, const unsigned short& callNumber) noexcept
{
    std::lock_guard<std::mutex> lock(functionsMutex);
    auto callPairIter = functions.find(callNumber);
    if (callPairIter != functions.end())
    {
        callPairIter->second.emplace(pConnection, std::move(func));
    }
    else
    {
        std::map<ZC_SignalConnection*, ZC_Function<TReturn(TParams...)>> map;
        map.emplace(pConnection, std::move(func));
        functions.emplace(callNumber, std::move(map));
    }
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::FunctionsTerminate() noexcept
{
    for (auto callPairIter = functions.begin(); callPairIter != functions.end();)
    {
        for (auto funcPairIter = callPairIter->second.begin(); funcPairIter != callPairIter->second.end();)
        {
            if (funcPairIter->first->GetState() == ZC_SignalConnection::ConnectionState::Terminated)
            {
                delete funcPairIter->first;
                funcPairIter = callPairIter->second.erase(funcPairIter);
            }
            else
            {
                ++funcPairIter;
            }
        }

        callPairIter = callPairIter->second.size() == 0 ? functions.erase(callPairIter) : ++callPairIter;
    }
}

template<typename TReturn, typename... TParams>
void ZC_Signal<TReturn(TParams...)>::FunctionsFinish() noexcept
{
    for (auto& callPair : functions)
    {
        for (auto& funcPair : callPair.second)
        {
            funcPair.first->Terminate();
            delete funcPair.first;
        }
    }
}
//  end  ZC_Signal<TReturn(TParams...)>