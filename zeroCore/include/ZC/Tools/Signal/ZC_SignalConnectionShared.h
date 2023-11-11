#pragma once

#include "ZC_SignalConnection.h"

#include <memory>

template<typename TShared>
class ZC_SignalConnectionShared : public ZC_SignalConnection
{
public:
    ZC_SignalConnectionShared() = delete;
    ZC_SignalConnectionShared(std::shared_ptr<TShared> _pShared) noexcept;

    ~ZC_SignalConnectionShared() override = default;
    
    typename ZC_SignalConnection::ConnectionState GetState() noexcept override;

private:
    std::shared_ptr<TShared> pShared;

    void ActualizeState();
};

template<typename TShared>
ZC_SignalConnectionShared<TShared>::ZC_SignalConnectionShared(std::shared_ptr<TShared> _pShared) noexcept
    : pShared(_pShared)
{}

template<typename TShared>
ZC_SignalConnection::ConnectionState ZC_SignalConnectionShared<TShared>::GetState() noexcept
{
    ActualizeState();
    return ZC_SignalConnection::GetState();
}

template<typename TShared>
void ZC_SignalConnectionShared<TShared>::ActualizeState()
{
    if (pShared.use_count() == 1)
    {
        ZC_SignalConnection::Terminate();
    }
}