#pragma once

#include "ZC_SignalConnection.h"
#include <ZC/Tools/ZC_sptr.h>

template<typename TShared>
class ZC_SignalConnectionShared : public ZC_SignalConnection
{
public:
    ZC_SignalConnectionShared(const ZC_sptr<TShared>& _pShared) noexcept;

    ~ZC_SignalConnectionShared() override = default;
    
    typename ZC_SignalConnection::State GetState() noexcept override;

private:
    ZC_sptr<TShared> pShared;
};

template<typename TShared>
ZC_SignalConnectionShared<TShared>::ZC_SignalConnectionShared(const ZC_sptr<TShared>& _pShared) noexcept
    : pShared(_pShared)
{}

template<typename TShared>
typename ZC_SignalConnection::State ZC_SignalConnectionShared<TShared>::GetState() noexcept
{
    if (pShared.UseCount() == 1) Terminate();
    return ZC_SignalConnection::GetState();
}