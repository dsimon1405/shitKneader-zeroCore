#include <ZC_main.h>
#include <ZC_EL.h>
#include <ZC/Renderer/ZC_Shader.h>
#include <ZC/Renderer/ZC_VAO.h>
#include <ZC/Renderer/ZC_VBO.h>

// #include <SDL3/SDL.h>

// #include <fstream>

// const char *vertexShaderSource =
//        "#version 330 core\n"
//         // "#version 320 es\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
// const char *fragmentShaderSource =
//        "#version 330 core\n"
//         // "#version 320 es\n"
//         "precision mediump float;\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\0";
//     void SDLCALL MyAudioCallback(void *userdata, SDL_AudioStream *stream, int approx_amount);


// struct WAVHEADER
// {
//     // WAV-формат начинается с RIFF-заголовка:

//     // Содержит символы "RIFF" в ASCII кодировке
//     // (0x52494646 в big-endian представлении)
//     char chunkId[4];

//     // 36 + subchunk2Size, или более точно:
//     // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
//     // Это оставшийся размер цепочки, начиная с этой позиции.
//     // Иначе говоря, это размер файла - 8, то есть,
//     // исключены поля chunkId и chunkSize.
//     int chunkSize;

//     // Содержит символы "WAVE"
//     // (0x57415645 в big-endian представлении)
//     char format[4];

//     // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
//     // Подцепочка "fmt " описывает формат звуковых данных:

//     // Содержит символы "fmt "
//     // (0x666d7420 в big-endian представлении)
//     char subchunk1Id[4];

//     // 16 для формата PCM.
//     // Это оставшийся размер подцепочки, начиная с этой позиции.
//     int subchunk1Size;

//     // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
//     // Для PCM = 1 (то есть, Линейное квантование).
//     // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
//     short audioFormat;

//     // Количество каналов. Моно = 1, Стерео = 2 и т.д.
//     short numChannels;

//     // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
//     int sampleRate;

//     // sampleRate * numChannels * bitsPerSample/8
//     int byteRate;

//     // numChannels * bitsPerSample/8
//     // Количество байт для одного сэмпла, включая все каналы.
//     short blockAlign;

//     // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
//     short bitsPerSample;

//     //  может быть перед data
//     char info[4];

//     //  размер info
//     int infoSize;

//     // Подцепочка "data" содержит аудио-данные и их размер.

//     // Содержит символы "data"
//     // (0x64617461 в big-endian представлении)
//     char subchunk2Id[4];

//     // numSamples * numChannels * bitsPerSample/8
//     // Количество байт в области данных.
//     int subchunk2Size;

//     // Далее следуют непосредственно Wav данные.
// };


//     short* fbuffer;
//     int fsize;
//     short* sbuffer;
//     int ssize;
//     short* thbuffer;
//     int thsize;
//     short* fobuffer;
//     int fosize;


// void LoadFile(const char* path, short*& buffer, int& buffSize)
// {
//     std::ifstream fstr(path, std::ios::binary);
//     if (!fstr.is_open())
//     {
//         ZC_Err("open fail " + std::string(path));
//     }
//     WAVHEADER header;
//     fstr.read(header.chunkId, sizeof(header.chunkId));
//     fstr.read((char*)&header.chunkSize, sizeof(header.chunkSize));
//     fstr.read(header.format, sizeof(header.format));
//     fstr.read(header.subchunk1Id, sizeof(header.subchunk1Id));
//     fstr.read((char*)&header.subchunk1Size, sizeof(header.subchunk1Size));
//     fstr.read((char*)&header.audioFormat, sizeof(header.audioFormat));
//     fstr.read((char*)&header.numChannels, sizeof(header.numChannels));
//     fstr.read((char*)&header.sampleRate, sizeof(header.sampleRate));
//     fstr.read((char*)&header.byteRate, sizeof(header.byteRate));
//     fstr.read((char*)&header.blockAlign, sizeof(header.blockAlign));
//     fstr.read((char*)&header.bitsPerSample, sizeof(header.bitsPerSample));

//     fstr.read(header.info, sizeof(header.info));
//     fstr.read((char*)&header.infoSize, sizeof(header.infoSize));
//     char info[header.infoSize];
//     fstr.read(info, sizeof(info));

//     fstr.read(header.subchunk2Id, sizeof(header.subchunk2Id));
//     fstr.read((char*)&header.subchunk2Size, sizeof(header.subchunk2Size));

//     buffer = new short[header.subchunk2Size / 2];
//     fstr.read((char*)buffer, header.subchunk2Size);
//     fstr.close();
//     buffSize = header.subchunk2Size / 2;
// }

#include <condition_variable>
class ThreadSafety : public ZC_Noncopyable
{
public:
    // ZC_SignalConnector<bool(void)> connector;

    ThreadSafety() = default;
    ~ThreadSafety() = default;

    void Start()
    {
        lock = std::unique_lock<std::mutex>(mutex);
        cv.wait(lock, [&]
            {
                return unlocked;
            });
        unlocked = false;
    }

    // void StartWithCallBack()
    // {
    //     lock = std::unique_lock<std::mutex>(mutex);
    //     cv.wait(lock, [&]
    //         {
    //             std::vector<bool> vec;
    //             signal(vec);
    //             if (vec.size() == 0)
    //             {
    //                 return unlocked;
    //             }
    //             bool callbackValue = true;
    //             for (bool b : vec)
    //             {
    //                 if (!b)
    //                 {
    //                     callbackValue = false;
    //                     break;
    //                 }
    //             }
    //             return unlocked && callbackValue;
    //         });
    //     unlocked = false;
    // }

    void End()
    {
        unlocked = true;
        lock.unlock();
        cv.notify_all();
    }

protected:
    std::mutex mutex;
    std::condition_variable cv;
    bool unlocked = true;
    std::unique_lock<std::mutex> lock;
    // ZC_Signal<bool(void)> signal;
};

#include <list>
#include <vector>
#include <thread>

template <typename TUnused>
class ZC_IFunction;
template <typename TReturn, typename... TParams>
class ZC_IFunction <TReturn(TParams...)> : public ZC_Noncopyable
{
public:
    ZC_IFunction() = default;
    virtual ~ZC_IFunction() = default;
    virtual TReturn operator()(TParams... params) const noexcept = 0;
};

template <typename TClass, typename TReturn, typename... TParams>
class ZC_Function : public ZC_IFunction<TReturn(TParams...)>
{
public:
    ZC_Function(TClass* _pClass, TReturn(TClass::*_pFunc)(TParams...))
        : pClass(_pClass),
        pFunc(_pFunc)
    {}

    virtual ~ZC_Function() override = default;
    
    virtual TReturn operator()(TParams... params) const noexcept override
    {
        return (pClass->*pFunc)(params...);
    }

private:
    TClass* pClass;
    TReturn(TClass::*pFunc)(TParams...);
};

template <typename TReturn, typename... TParams>
class ZC_Function<void, TReturn, TParams...> : public ZC_IFunction<TReturn(TParams...)>
{
public:
    ZC_Function(TReturn(*_pFunc)(TParams...))
        : pFunc(_pFunc)
    {}

    virtual ~ZC_Function() override = default;
    
    virtual TReturn operator()(TParams... params) const noexcept override
    {
        return (*pFunc)(params...);
    }

private:
    TReturn(*pFunc)(TParams...);
};

class ZC_SignalConnectoin : public ZC_Noncopyable
{
public:
    enum State
    {
        Connected,
        Disconnected,
        Terminated
    };
    ZC_SignalConnectoin() = default;
    ~ZC_SignalConnectoin() = default;

    void Disconnect() noexcept
    {
        if (state == State::Connected)
        {
            state = State::Disconnected;
        }
    }

    void Connect() noexcept
    {
        if (state == State::Disconnected)
        {
            state = State::Connected;
        }
    }

    void Terminate() noexcept
    {
        state = State::Terminated;
    }

    virtual ZC_SignalConnectoin::State GetState() noexcept
    {
        return state;
    }

private:
    State state = State::Connected;
};

template <typename TShared>
class ZC_SignalConnectionShared : public ZC_SignalConnectoin
{
public:
    ZC_SignalConnectionShared(std::shared_ptr<TShared> _pShared)
        : pShared(_pShared)
        {}
    
    virtual ZC_SignalConnectoin::State GetState() noexcept
    {
        ActualizeState();
        return ZC_SignalConnectoin::GetState();
    }

private:
    std::shared_ptr<TShared> pShared;

    void ActualizeState()
    {
        if (pShared.use_count() == 1)
        {
            ZC_SignalConnectoin::Terminate();
        }
    }
};

#include <concepts>
template <typename TFirst, typename TSecond>
concept SameTypes = std::same_as<TFirst, TSecond>;

template <typename TUnused>
class ZC_SignalConnector;

class ThreadSafety;

template <typename TUnused>
class ZC_Signal;
template <typename TReturn, typename... TParams>
class ZC_Signal <TReturn(TParams...)>
{
public:
    ZC_Signal()
        : threadSafty(new ThreadSafety())
    {
        // std::thread th([&]
        // {

        // });
        // th.detach();
    }

    ~ZC_Signal()
    {
        for (auto& list : functions)
        {
            for (auto iter = list.begin(); iter != list.end(); ++iter)
            {
                (*iter).first->Terminate();
                delete (*iter).second;
                (*iter).second = nullptr;
            }
        }
    }

    ZC_SignalConnectoin* Connect(TReturn(*pFunc)(TParams...), unsigned int callNumber = 0) noexcept
    {
        ZC_IFunction<TReturn(TParams...)>* pF = dynamic_cast<ZC_IFunction<TReturn(TParams...)>*>(new ZC_Function<void, TReturn, TParams...>(pFunc));
        ZC_SignalConnectoin* pConnector = new ZC_SignalConnectoin();
        AddFunction(pConnector, pF, callNumber);
        return pConnector;
    }

    template <typename TShared>
    ZC_SignalConnectoin* Connect(TReturn(*pFunc)(TParams...), std::shared_ptr<TShared> pShared, unsigned int callNumber = 0) noexcept
    {
        ZC_IFunction<TReturn(TParams...)>* pF = dynamic_cast<ZC_IFunction<TReturn(TParams...)>*>(new ZC_Function<void, TReturn, TParams...>(pFunc));
        ZC_SignalConnectoin* pConnector = dynamic_cast<ZC_SignalConnectoin*>(new ZC_SignalConnectionShared(pShared));
        AddFunction(pConnector, pF, callNumber);
        return pConnector;
    }

    template <class TClass>
    ZC_SignalConnectoin* Connect(TReturn(TClass::*pFunc)(TParams...), TClass* pClass, unsigned int callNumber = 0) noexcept
    {
        ZC_IFunction<TReturn(TParams...)>* pF = dynamic_cast<ZC_IFunction<TReturn(TParams...)>*>(new ZC_Function<TClass, TReturn, TParams...>(pClass, pFunc));
        ZC_SignalConnectoin* pConnector = new ZC_SignalConnectoin();
        AddFunction(pConnector, pF, callNumber);
        return pConnector;
    }

    template <typename TClass, typename TShared>
    ZC_SignalConnectoin* Connect(TReturn(TClass::*pFunc)(TParams...), TClass* pClass, std::shared_ptr<TShared> pShared, unsigned int callNumber = 0) noexcept
    {
        ZC_IFunction<TReturn(TParams...)>* pF = dynamic_cast<ZC_IFunction<TReturn(TParams...)>*>(new ZC_Function<TClass, TReturn, TParams...>(pClass, pFunc));
        ZC_SignalConnectoin* pConnector = dynamic_cast<ZC_SignalConnectoin*>(new ZC_SignalConnectionShared(pShared));
        AddFunction(pConnector, pF, callNumber);
        return pConnector;
    }

    void operator()(const TParams&... params)
    {
        threadSafty->Start();
        for (auto& list : functions)
        {
            for (auto iter = list.begin(); iter != list.end(); ++iter)
            {
                switch ((*((*iter).first)).GetState())
                {
                    case ZC_SignalConnectoin::State::Connected:
                        (*((*iter).second))(params...);
                        break;
                    case ZC_SignalConnectoin::State::Terminated:
                        delete (*iter).second;
                        (*iter).second = nullptr;
                        break;
                    case ZC_SignalConnectoin::State::Disconnected:
                        break;
                }
            }
        }
        threadSafty->End();
    }

    template <typename TRet> requires SameTypes<TReturn, TRet>
    void operator()(std::vector<TRet>& vec, const TParams&... params)
    {
        int vecSize = 0;
        for (auto& list : functions)
        {
            vecSize += list.size();
        }
        vec.reserve(vecSize);

        threadSafty->Start();
        for (auto& list : functions)
        {
            for (auto iter = list.begin(); iter != list.end(); ++iter)
            {
                switch ((*((*iter).first)).GetState())
                {
                    case ZC_SignalConnectoin::State::Connected:
                        vec.emplace_back((*((*iter).second))(params...));
                        break;
                    case ZC_SignalConnectoin::State::Terminated:
                        delete (*iter).second;
                        (*iter).second = nullptr;
                        break;
                    case ZC_SignalConnectoin::State::Disconnected:
                        break;
                }
            }
        }
        threadSafty->End();
    }

    ZC_SignalConnector<TReturn(TParams...)> GetSafeConnector()
    {
        return ZC_SignalConnector<TReturn(TParams...)>(this);
    }

private:
    std::vector<std::list<std::pair<ZC_SignalConnectoin*, ZC_IFunction<TReturn(TParams...)>*>>> functions;
    ThreadSafety* threadSafty;

    void AddFunction(ZC_SignalConnectoin* pConnector, ZC_IFunction<TReturn(TParams...)>* pFunction, unsigned int callNumber) noexcept
    {
        threadSafty->Start();
        GetCallNumberList(callNumber).emplace_back(std::pair<ZC_SignalConnectoin*, ZC_IFunction<TReturn(TParams...)>*>(pConnector, pFunction));
        threadSafty->End();
    }

    std::list<std::pair<ZC_SignalConnectoin*, ZC_IFunction<TReturn(TParams...)>*>>& GetCallNumberList(unsigned int callNumber) noexcept
    {
        ++callNumber;
        int funcSize = functions.size();
        if (funcSize < callNumber)
        {
            int funcExtention = callNumber - funcSize;
            while (funcExtention-- > 0)
            {
                functions.emplace_back(std::list<std::pair<ZC_SignalConnectoin*, ZC_IFunction<TReturn(TParams...)>*>>());
            }
        }
        return functions[--callNumber];
    }
};

template <typename TReturn, typename... TParams>
class ZC_SignalConnector <TReturn(TParams...)>
{
public:
    ZC_SignalConnector() = default;
    ZC_SignalConnector(ZC_Signal<TReturn(TParams...)>* _signal)
        : signal(_signal)
        {}

    ~ZC_SignalConnector() = default;

    ZC_SignalConnectoin* Connect(TReturn(*pFunc)(TParams...), unsigned int callNumber = 0) noexcept
    {
        return signal->Connect(pFunc, callNumber);
    }

    template <typename TShared>
    ZC_SignalConnectoin* Connect(TReturn(*pFunc)(TParams...), std::shared_ptr<TShared> pShared, unsigned int callNumber = 0) noexcept
    {
        return signal->Connect(pFunc, pShared, callNumber);
    }

    template <class TClass>
    ZC_SignalConnectoin* Connect(TReturn(TClass::*pFunc)(TParams...), TClass* pClass, unsigned int callNumber = 0) noexcept
    {
        return signal->Connect(pFunc, pClass, callNumber);
    }

    template <typename TClass, typename TShared>
    ZC_SignalConnectoin* Connect(TReturn(TClass::*pFunc)(TParams...), TClass* pClass, std::shared_ptr<TShared> pShared, unsigned int callNumber = 0) noexcept
    {
        return signal->Connect(pFunc, pClass, pShared, callNumber);
    }

private:
    ZC_Signal<TReturn(TParams...)>* signal;
};

// class ThreadSafetyWithSignal : public ThreadSafety
// {
// public:
//     ZC_SignalConnector<bool(void)> connector;

//     ThreadSafetyWithSignal()
//         : connector(signal.GetSafeConnector())
//     {}

//     ~ThreadSafetyWithSignal() = default;

//     virtual void Start() override
//     {
//         lock = std::unique_lock<std::mutex>(mutex);
//         cv.wait(lock, [&]
//             {
//                 std::vector<bool> vec;
//                 signal(vec);
//                 if (vec.size() == 0)
//                 {
//                     return unlocked;
//                 }
//                 bool callbackValue = true;
//                 for (bool b : vec)
//                 {
//                     if (!b)
//                     {
//                         callbackValue = false;
//                         break;
//                     }
//                 }
//                 return unlocked && callbackValue;
//             });
//         unlocked = false;
//     }

// private:
//     ZC_Signal<bool(void)> signal;
// };

int Foo(int a)
{
    ZC_Err("no name " + std::to_string(a));
    return a;
}

void VFoo()
{
    ZC_Err("no name void");
}

class A
{
public:
    A(std::string a)
    {
        str = a;
    }
    std::string str;
int Foo(int a)
{
    ZC_Err(str + std::to_string(a));
    return a;
}

void VFoo()
{
    ZC_Err(str + " void");
}
};

    void Print(std::vector<int>& vec)
    {
        ZC_Err("\n");
        for (int& i : vec)
        {
            ZC_Err(std::to_string(i));
        }
    }

void ZC_main(ZC_pAPIFactory apiFactory)
{
    // ThreadSafetyWithSignal* safe = new ThreadSafetyWithSignal();
    // auto lam = []()->bool{
    //     return true;
    //     };
    // safe->connector.Connect(lam);
    // ThreadSafety* sa = dynamic_cast<ThreadSafety*>(safe);
    // sa->Start();
    // sa->End();


    ZC_Signal<int(int)> sig;
    ZC_SignalConnector<int(int)> connection = sig.GetSafeConnector();
    ZC_SignalConnectoin* con = connection.Connect(&Foo, 1);
    A a("a ");
    ZC_SignalConnectoin* acon = sig.Connect(&A::Foo, &a, 0);

    auto lambda = [](int a)->int{ZC_Err("lambda " + std::to_string(a)); return a;};
    ZC_SignalConnectoin* lcon = connection.Connect(lambda, 3);

    // std::shared_ptr<A> p = std::make_shared<A>(A("a shared "));
    // ZC_SignalConnector* scon = sig.Connect(&A::Foo, &*p, p);
    std::vector<int> vec;
    {
        std::shared_ptr<A> p = std::make_shared<A>(A("a shared "));
        ZC_SignalConnectoin* scon = connection.Connect(&A::Foo, &*p, p, 2);
        sig(1);
        scon->Disconnect();
        sig(2);
        scon->Connect();
        sig(vec, 3);
    }
    sig(4);

    // ZC_Err("\n");
    // ZC_Signal<void()> vsig;

    // ZC_SignalConnector* vcon = vsig.Connect(&VFoo);
    // A va("a ");
    // ZC_SignalConnector* avcon = vsig.Connect(&A::VFoo, &va);
    // {
    //     std::shared_ptr<A> p = std::make_shared<A>(A("a shared "));
    //     ZC_SignalConnector* svcon = vsig.Connect(&A::VFoo, &*p, p);
    //     vsig();
    // ZC_Err("\n");
    //     svcon->Disconnect();
    //     vsig();
    // ZC_Err("\n");
    //     svcon->Connect();
    //     vsig();
    // ZC_Err("\n");
    // }

    // auto vlambda = [](){ZC_Err("lambda void");};
    // ZC_SignalConnector* lvcon = vsig.Connect(vlambda);
    // vsig();
    // ZC_Err("\n");

    // std::vector<int> vec1;
    // std::thread th1([&] { sig(vec1, 1); });
    // th1.detach();
    // std::vector<int> vec2;
    // std::thread th2([&] { sig(vec1, 2); });
    // th2.detach();
    // std::vector<int> vec3;
    // std::thread th3([&] { sig(vec1, 3); });
    // th3.detach();
    // std::vector<int> vec4;
    // std::thread th4([&] { sig(vec1, 4); });
    // th4.detach();
    // std::vector<int> vec5;
    // std::thread th5([&] { sig(vec1, 5); });
    // th5.detach();

    std::vector<int> vec1;
    std::thread th1([&] { sig.Connect(&Foo); });
    th1.detach();
    std::thread th2([&] { sig.Connect(&A::Foo, &a); });
    th2.detach();
    std::thread th3([&] { sig.Connect(lambda); });
    th3.detach();
    // std::thread th4([&] { sig.Connect(&A::Foo, &*p, p); });
    // th4.detach();
    std::thread th5([&] { sig.Connect(&Foo); });
    th5.detach();
    std::thread th6([&] { sig.Connect(&A::Foo, &a); });
    th6.detach();
    std::thread th7([&] { sig.Connect(lambda); });
    th7.detach();
    // std::thread th8([&] { sig.Connect(&A::Foo, &*p, p); });
    // th8.detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    sig(vec1, 1);
    Print(vec1);
    // Print(vec2);
    // Print(vec3);
    // Print(vec4);
    // Print(vec5);
    

    ZC_pWindow window = apiFactory->MakeWindow("lolka", 640, 480);
//     SDL_AudioSpec spec;
//     spec.channels = 2;
//     spec.freq = 44100;
//     spec.format = SDL_AUDIO_S16;

//     // Uint8* buffer;
//     // Uint32 bufSize;
//     // int res = SDL_LoadWAV("/home/dmitry/Загрузки/Airplanes.wav", &spec, &buffer, &bufSize);
    
//     LoadFile("/home/dmitry/Загрузки/lp.wav", fbuffer, fsize);
//     LoadFile("/home/dmitry/Загрузки/Airplanes.wav", sbuffer, ssize);
//     LoadFile("/home/dmitry/Загрузки/SharpEdges.wav", thbuffer, thsize);
//     LoadFile("/home/dmitry/Загрузки/TalkingtoMyself.wav", fobuffer, fosize);

//     // std::ifstream fstrs("/home/dmitry/Загрузки/Airplanes.wav", std::ios::binary);
//     // if (!fstrs.is_open())
//     // {
//     //     ZC_Err("open Airplanes.wav fail");
//     // }
//     // fstrs.read(header.chunkId, sizeof(header.chunkId));
//     // fstrs.read((char*)&header.chunkSize, sizeof(header.chunkSize));
//     // fstrs.read(header.format, sizeof(header.format));
//     // fstrs.read(header.subchunk1Id, sizeof(header.subchunk1Id));
//     // fstrs.read((char*)&header.subchunk1Size, sizeof(header.subchunk1Size));
//     // fstrs.read((char*)&header.audioFormat, sizeof(header.audioFormat));
//     // fstrs.read((char*)&header.numChannels, sizeof(header.numChannels));
//     // fstrs.read((char*)&header.sampleRate, sizeof(header.sampleRate));
//     // fstrs.read((char*)&header.byteRate, sizeof(header.byteRate));
//     // fstrs.read((char*)&header.blockAlign, sizeof(header.blockAlign));
//     // fstrs.read((char*)&header.bitsPerSample, sizeof(header.bitsPerSample));

//     // fstrs.read(header.info, sizeof(header.info));
//     // fstrs.read((char*)&header.infoSize, sizeof(header.infoSize));
//     // char infos[header.infoSize];
//     // fstrs.read(infos, sizeof(infos));

//     // fstrs.read(header.subchunk2Id, sizeof(header.subchunk2Id));
//     // fstrs.read((char*)&header.subchunk2Size, sizeof(header.subchunk2Size));

//     // sbuffer = new short[header.subchunk2Size / 2];
//     // fstrs.read((char*)sbuffer, header.subchunk2Size);
//     // fstrs.close();
//     // ssize = header.subchunk2Size / 2;
    
//     SDL_AudioStream *stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &spec, MyAudioCallback, nullptr);
//     auto device = SDL_GetAudioStreamDevice(stream);
//     int ress = SDL_ResumeAudioDevice(device);

//     // SDL_PutAudioStreamData(stream, buffer, bufSize);
//     // SDL_PutAudioStreamData(stream, fbuffer, header.subchunk2Size / 2);
// //    ZC_Shader shader(vertexShaderSource, fragmentShaderSource);
// //
// //    float vertices[] = {
// //         0.5f,  0.5f, 0.0f,  // top right
// //         0.5f, -0.5f, 0.0f,  // bottom right
// //        -0.5f, -0.5f, 0.0f,  // bottom left
// //        -0.5f,  0.5f, 0.0f   // top left
// //    };
// //    ZC_VAO vao;
// //    ZC_VBO vbo;
// //
// //    vao.Bind();
// //    vbo.Bind();
// //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// //    glEnableVertexAttribArray(0);
// //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// //    vbo.Unbind();
// //    vao.Unbind();

//     window->SetClearColor(1, 0, 1);
    while (true)
    {
        if (!window->HandleEvents())
        {
            return;
        }
// //        if (window->inited)
// //        {
// //            GLuint id = 0;
// //            glGenBuffers(1, &id);
// //            GLuint shader = glCreateShader(GL_GEOMETRY_SHADER);
// //            while (window->inited)
// //            {
// //                if (!window->HandleEvents())
// //                {
// //                    break;
// //                }
// //                window->Clear();
// //                ZC_Err("lolka");
// //                window->SwapBuffer();
// //            }
// //        }

//         // if (window->inited)
//         {
//             ZC_Shader shader(vertexShaderSource, fragmentShaderSource);

//             float vertices[] = {
//                     0.5f,  0.5f, 0.0f,  // top right
//                     0.5f, -0.5f, 0.0f,  // bottom right
//                     -0.5f, -0.5f, 0.0f,  // bottom left
//                     -0.5f,  0.5f, 0.0f   // top left
//             };
//             ZC_VAO vao;
//             ZC_VBO vbo;

//             vao.Bind();
//             vbo.Bind();
//             glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//             glEnableVertexAttribArray(0);
//             glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//             vbo.Unbind();
//             vao.Unbind();

//             window->Clear();
//             shader.Use();
//             vao.Bind();
//             glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
//             vao.Unbind();
//             window->SwapBuffer();
//         }

    }
}

    // void SDLCALL MyAudioCallback(void *userdata, SDL_AudioStream *stream, int approx_amount)
    // {
    //     static int findex = 0;
    //     static int sindex = 0;
    //     static int thindex = 0;
    //     static int foindex = 0;
    //     short data[approx_amount / 2];
    //     for (size_t i = 0; i < approx_amount / 2; ++i)
    //     {
    //         data[i] = fbuffer[findex++] / 4 + sbuffer[sindex++] / 4 + thbuffer[thindex++] / 4 + fobuffer[foindex++] / 4;
    //         // findex++;
    //         // data[i] = sbuffer[sindex++];
    //         // sindex++;
    //         if (findex >= fsize)
    //         {
    //             findex = 0;
    //         }
    //         if (sindex >= ssize)
    //         {
    //             sindex = 0;
    //         }
    //         if (thindex >= thsize)
    //         {
    //             thindex = 0;
    //         }
    //         if (foindex >= fosize)
    //         {
    //             foindex = 0;
    //         }
    //     }
        
    //     /* calculate a little more audio here, maybe using `userdata`, write it to `stream` */
    //     SDL_PutAudioStreamData(stream, data, approx_amount);
    // }