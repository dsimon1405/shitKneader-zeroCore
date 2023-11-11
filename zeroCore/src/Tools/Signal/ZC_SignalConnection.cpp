#include <ZC/Tools/Signal/ZC_SignalConnection.h>

ZC_SignalConnection::ConnectionState ZC_SignalConnection::GetState() noexcept
{
    return connectionState;
}

void ZC_SignalConnection::Disconnect() noexcept
{
    if (connectionState == ConnectionState::Connected)
    {
        connectionState = ConnectionState::Disconnected;
    }
}

void ZC_SignalConnection::Connect() noexcept
{
    if (connectionState == ConnectionState::Disconnected)
    {
        connectionState = ConnectionState::Connected;
    }
}

void ZC_SignalConnection::Terminate() noexcept
{
    connectionState = ConnectionState::Terminated;
}