#pragma once

/*
Class for managing connection to the ZC_Signal.
*/
class ZC_SignalConnection
{
public:
    enum State
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
    
    ZC_SignalConnection(ZC_SignalConnection&& con) noexcept;
    ZC_SignalConnection& operator=(ZC_SignalConnection&& con) noexcept;

    virtual ~ZC_SignalConnection() = default;

    /*
    Help to get current connection state.

    Return:
    ZC_SignalConnection::State.
    */
    virtual typename ZC_SignalConnection::State GetState() noexcept;

    /*
    Disconnects from the signal if connected to it.

    Return:
    If the connection was disconnected - true, if it was already terminated - false.
    */
    bool Disconnect() noexcept;

    /*
    Connects to the signal if disconnected from it.

    Return:
    If the connection was connected - true, if it was already terminated - false.
    */
    bool Connect() noexcept;

    /*
    Terminates connection to a signal, whether connected or disconnected. Doesn't do anything if already terminated.
    */
    void Terminate() noexcept;

private:
    State state = State::Connected;
};