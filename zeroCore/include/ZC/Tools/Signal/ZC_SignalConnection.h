#pragma once

/*
Class for managing connection to the ZC_Signal.
*/
class ZC_SignalConnection
{
public:
    enum ConnectionState
    {
        //  The function will be called.
        Connected,
        //  The function will not be called.
        Disconnected,
        //  Function removed from ZC_Signal.
        Terminated
    };
    
    ZC_SignalConnection() = default;

    ZC_SignalConnection(const ZC_SignalConnection&) = delete;
    ZC_SignalConnection& operator=(const ZC_SignalConnection&) = delete;
    
    ZC_SignalConnection(ZC_SignalConnection&&) = delete;
    ZC_SignalConnection& operator=(ZC_SignalConnection&&) = delete;

    virtual ~ZC_SignalConnection() = default;

    /*
    Help to get current connection state.

    Return:
    ZC_SignalConnection::State.
    */
    virtual typename ZC_SignalConnection::ConnectionState GetState() noexcept;

    /*
    Change state on Disconnected.
    */
    void Disconnect() noexcept;

    /*
    Change state on Connected.
    */
    void Connect() noexcept;

    /*
    Change state on Terminated.
    */
    void Terminate() noexcept;

private:
    ConnectionState connectionState = ConnectionState::Connected;
};