#pragma once

#include "ZC_SignalConnection.h"

#include <memory>

template<typename TShared>
class ZC_SignalConnectionShared : public ZC_SignalConnection
{
public:
    ZC_SignalConnectionShared() = delete;
    ZC_SignalConnectionShared(const std::shared_ptr<TShared>& _pShared) noexcept;

    ZC_SignalConnectionShared(ZC_SignalConnectionShared&& con) noexcept;
    ZC_SignalConnectionShared& operator = (ZC_SignalConnectionShared&& con) noexcept;

    ~ZC_SignalConnectionShared() override = default;
    
    typename ZC_SignalConnection::State GetState() noexcept override;

private:
    std::shared_ptr<TShared> pShared;

    void ActualizeState();
};

template<typename TShared>
ZC_SignalConnectionShared<TShared>::ZC_SignalConnectionShared(const std::shared_ptr<TShared>& _pShared) noexcept
    : pShared(_pShared)
{}

template<typename TShared>
ZC_SignalConnectionShared<TShared>::ZC_SignalConnectionShared(ZC_SignalConnectionShared&& con) noexcept
    : ZC_SignalConnection(dynamic_cast<ZC_SignalConnection&&>(con)),
    pShared(std::move(con.pShared))
{}

template<typename TShared>
ZC_SignalConnectionShared<TShared>& ZC_SignalConnectionShared<TShared>::operator = (ZC_SignalConnectionShared&& con) noexcept
{
    dynamic_cast<ZC_SignalConnection&>(*this) = dynamic_cast<ZC_SignalConnection&&>(con);
    pShared = std::move(con.pShared);
}

template<typename TShared>
ZC_SignalConnection::State ZC_SignalConnectionShared<TShared>::GetState() noexcept
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