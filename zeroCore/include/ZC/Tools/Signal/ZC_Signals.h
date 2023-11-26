#pragma once

#include "ZC_SignalsConnector.h"

#include <map>
#include <vector>
#include <set>

template<ZC_cLessCompare TCondition, typename TFunction>
class ZC_Signals;

//  Collection of the Signals sorted by some condition type. Condition type must realize operator less than. 
template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
class ZC_Signals<TCondition, TReturn(TParams...)> : public ZC_SignalsConnector<TCondition, TReturn(TParams...)>
{
public:
    ZC_Signals() = default;

    ZC_Signals(const ZC_Signals<TCondition, TReturn(TParams...)>&) = delete;
    ZC_Signals<TCondition, TReturn(TParams...)>& operator = (const ZC_Signals<TCondition, TReturn(TParams...)>&) = delete;

    ZC_Signals(ZC_Signals<TCondition, TReturn(TParams...)>&& sig) noexcept;
    ZC_Signals<TCondition, TReturn(TParams...)>& operator = (ZC_Signals<TCondition, TReturn(TParams...)>&& sig) noexcept;

    ~ZC_Signals() override = default;
    
    /*
    Calls all connected ZC_Function.

    Params:
    params - parameters of the functions.
    */
    void operator () (TParams... params) noexcept;

    struct Conditions;
    /*
    Calls signals that match the conditions.

    Params:
    conds - conditions.
    params - parameters of the functions.
    */
    void operator () (const typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& conds, TParams... params) noexcept;
    
    struct Container;
    /*
    Calls all signals and fills the vector with the values ​​returned from the called functions.

    Params:
    container - container.
    params - parameters of the functions.
    */
    void operator () (std::vector<TReturn>& container, TParams... params) noexcept;
    
    /*
    Calls signals that match the conditions added to the container and fills the container with the values ​​returned from the called functions.

    Params:
    container - container.
    params - parameters of the functions.
    */
    void operator () (typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& container, TParams... params) noexcept;

    //  Create Connector to the signal. Usefull for hide signal in private zone.
    ZC_SignalsConnector<TCondition, TReturn(TParams...)>* GetConnector() noexcept;

    //  Create Conditions using copy to parameter cond.
    typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions GetConditions(const TCondition& cond) noexcept;
    //  Create Conditions using move to parameter cond.
    typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions GetConditions(TCondition&& cond) noexcept;

    //  Create Container using copy to parameter cond.
    typename ZC_Signals<TCondition, TReturn(TParams...)>::Container GetContainer(const TCondition& cond) noexcept;
    //  Create Container using move to parameter cond.
    typename ZC_Signals<TCondition, TReturn(TParams...)>::Container GetContainer(TCondition&& cond) noexcept;

    //  Wrapper for set of conditions.
    struct Conditions
    {
        std::set<TCondition> conditions;
        
        Conditions(const TCondition& cond) noexcept;
        Conditions(TCondition&& cond) noexcept;

        Conditions(const typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&) = delete;
        Conditions& operator = (const typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&) = delete;

        Conditions(typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&& cont) noexcept;
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& operator = (typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&& cont) noexcept;
        
        /*
        Copy a condition if it doesn't exist, if the condition allready exists, nothing happens.

        Params:
        cond - signals condition.

        Return:
        Pointer to itself.
        */
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& Add(const TCondition& cond) noexcept;

        /*
        Move a condition if it doesn't exist, if the condition allready exists, nothing happens.

        Params:
        cond - signals condition.

        Return:
        Pointer to itself.
        */
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& Add(TCondition&& cond) noexcept;
    };

    // Wrapper for a map of conditions that have vectors with a return values.
    struct Container
    {
        std::map<TCondition, std::vector<TReturn>> datas;

        Container() = default;
        Container(const TCondition& cond) noexcept;
        Container(TCondition&& cond) noexcept;

        Container(const typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&) = delete;
        Container& operator = (const typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&) = delete;

        Container(typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&& cont) noexcept;
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& operator = (typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&& cont) noexcept;
        /*
        Copy a condition if it doesn't exist, if the condition allready exists, nothing happens.

        Params:
        cond - signals condition.

        Return:
        Pointer to itself.
        */
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& Add(const TCondition& cond) noexcept;

        /*
        Move a condition if it doesn't exist, if the condition allready exists, nothing happens.

        Params:
        cond - signals condition.

        Return:
        Pointer to itself.
        */
        typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& Add(TCondition&& cond) noexcept;

        /*
        Return vector of values add in ZC_Signals call.

        Params:
        cond - signals condition.

        Return:
        Vector of values.
        */
        std::vector<TReturn>* GetData(const TCondition& cond) noexcept;
    };
};

//  Signals start

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::ZC_Signals(ZC_Signals<TCondition, TReturn(TParams...)>&& sig) noexcept
{
    this->signals = std::move(sig.signals);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>& ZC_Signals<TCondition, TReturn(TParams...)>::operator = (ZC_Signals<TCondition, TReturn(TParams...)>&& sig) noexcept
{
    this->signals = std::move(sig.signals);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
void ZC_Signals<TCondition, TReturn(TParams...)>::operator () (TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(this->signalsMutex);
    for (auto signalsIter = this->signals.begin(); signalsIter != this->signals.end();)
    {
        signalsIter->second(params...);
        signalsIter = signalsIter->second.Size() == 0 ? this->signals.erase(signalsIter) : ++signalsIter;
    }
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
void ZC_Signals<TCondition, TReturn(TParams...)>::operator () (const typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& conds, TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(this->signalsMutex);
    for (auto& cond : conds.conditions)
    {
        auto signalsIter = this->signals.find(cond);
        if (signalsIter == this->signals.end()) continue;
        signalsIter->second(params...);
        if (signalsIter->second.Size() == 0) this->signals.erase(signalsIter);
    }
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
void ZC_Signals<TCondition, TReturn(TParams...)>::operator () (std::vector<TReturn>& container, TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(this->signalsMutex);
    size_t callsCount = 0;
    for (auto& signal : this->signals)
    {
        callsCount += signal.second.Size();
    }
    container.reserve(callsCount);
    
    for (auto signalsIter = this->signals.begin(); signalsIter != this->signals.end();)
    {
        signalsIter->second(container, params..., false);
        signalsIter = signalsIter->second.Size() == 0 ? this->signals.erase(signalsIter) : ++signalsIter;
    }
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
void ZC_Signals<TCondition, TReturn(TParams...)>::operator () (typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& container, TParams... params) noexcept
{
    std::lock_guard<std::mutex> lock(this->signalsMutex);
    for (auto& containerPair : container.datas)
    {
        auto signalsIter = this->signals.find(containerPair.first);
        if (signalsIter == this->signals.end()) continue;
        signalsIter->second(containerPair.second, params...);
        if (signalsIter->second.Size() == 0) this->signals.erase(signalsIter);
    }
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_SignalsConnector<TCondition, TReturn(TParams...)>* ZC_Signals<TCondition, TReturn(TParams...)>::GetConnector() noexcept
{
    return dynamic_cast<ZC_SignalsConnector<TCondition, TReturn(TParams...)>*>(this);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions ZC_Signals<TCondition, TReturn(TParams...)>::GetConditions(const TCondition& cond) noexcept
{
    return ZC_Signals<TCondition, TReturn(TParams...)>::Conditions(cond);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions ZC_Signals<TCondition, TReturn(TParams...)>::GetConditions(TCondition&& cond) noexcept
{
    return ZC_Signals<TCondition, TReturn(TParams...)>::Conditions(std::move(cond));
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Container ZC_Signals<TCondition, TReturn(TParams...)>::GetContainer(const TCondition& cond) noexcept
{
    return ZC_Signals<TCondition, TReturn(TParams...)>::Container(cond);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Container ZC_Signals<TCondition, TReturn(TParams...)>::GetContainer(TCondition&& cond) noexcept
{
    return ZC_Signals<TCondition, TReturn(TParams...)>::Container(std::move(cond));
}
//  Signals end

//  Conditions start

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::Conditions(const TCondition& cond) noexcept
{
    conditions.emplace(cond);
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::Conditions(TCondition&& cond) noexcept
{
    conditions.emplace(std::move(cond));
}
        
template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::Conditions(typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&& cond) noexcept
    : conditions(std::move(cond.conditions))
{}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::operator = (typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions&& cond) noexcept
{
    conditions = std::move(cond.conditions);
    return *this;
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::Add(const TCondition& cond) noexcept
{
    conditions.emplace(cond);
    return *this;
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Conditions& ZC_Signals<TCondition, TReturn(TParams...)>::Conditions::Add(TCondition&& cond) noexcept
{
    conditions.emplace(std::move(cond));
    return *this;
}
//  Conditions end

//  Container start

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Container::Container(const TCondition& cond) noexcept
{
    datas.emplace(cond, std::vector<TReturn>());
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Container::Container(TCondition&& cond) noexcept
{
    datas.emplace(std::move(cond), std::vector<TReturn>());
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
ZC_Signals<TCondition, TReturn(TParams...)>::Container::Container(typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&& cont) noexcept
    : datas(std::move(cont.datas))
{}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& ZC_Signals<TCondition, TReturn(TParams...)>::Container::operator = (typename ZC_Signals<TCondition, TReturn(TParams...)>::Container&& cont) noexcept
{
    datas = std::move(cont.datas);
    return *this;
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& ZC_Signals<TCondition, TReturn(TParams...)>::Container::Add(const TCondition& cond) noexcept
{
    datas.emplace(cond, std::vector<TReturn>());
    return *this;
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
typename ZC_Signals<TCondition, TReturn(TParams...)>::Container& ZC_Signals<TCondition, TReturn(TParams...)>::Container::Add(TCondition&& cond) noexcept
{
    datas.emplace(std::move(cond), std::vector<TReturn>());
    return *this;
}

template<ZC_cLessCompare TCondition, ZC_cNotRValueRef TReturn, typename... TParams>
std::vector<TReturn>* ZC_Signals<TCondition, TReturn(TParams...)>::Container::GetData(const TCondition& cond) noexcept
{
    auto datasIter = datas.find(cond);
    if (datasIter == datas.end()) return nullptr;
    return &datasIter->second;
}
//  Container end