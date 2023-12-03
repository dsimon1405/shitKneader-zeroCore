#include <ZC/Audio/ZC_Sound.h>

#include <ZC/Audio/ZC_AudioStream.h>

ZC_Sound::ZC_Sound(const ZC_SoundData* _soundData) noexcept
    : ZC_StreamSound(_soundData)
{
    conGetpZC_StreamSound = ZC_AudioStream::sGetpZC_StreamSound.Connect(ZC_Function<ZC_StreamSound*()>(&ZC_Sound::GetpZC_StreamSound, this));
    conGetpZC_StreamSound->Disconnect();
}

ZC_Sound::~ZC_Sound() noexcept
{
    conGetpZC_StreamSound->Terminate();
}

void ZC_Sound::Play() noexcept
{
    if (ZC_AudioStream::GetState() != ZC_AudioStream::State::Null && soundData->GetAudioSet() == ZC_AudioStream::GetAudioSet())
    {
        std::lock_guard<std::mutex> lock(soundStateMutex);
        if (soundState == ZC_StreamSound::SoundState::Pause || soundState == ZC_StreamSound::SoundState::Stop)
        {
            conGetpZC_StreamSound->Connect();
        }
        soundState = ZC_StreamSound::SoundState::Play;
    }
}

void ZC_Sound::PlayLoop() noexcept
{
    if (ZC_AudioStream::GetState() != ZC_AudioStream::State::Null && soundData->GetAudioSet() == ZC_AudioStream::GetAudioSet())
    {
        std::lock_guard<std::mutex> lock(soundStateMutex);
        if (soundState == ZC_StreamSound::SoundState::Pause || soundState == ZC_StreamSound::SoundState::Stop)
        {
            conGetpZC_StreamSound->Connect();
        }
        soundState = ZC_StreamSound::SoundState::PlayLoop;
    }
}

void ZC_Sound::Pause() noexcept
{
    std::lock_guard<std::mutex> lock(soundStateMutex);
    if (soundState == ZC_StreamSound::SoundState::Play || soundState == ZC_StreamSound::SoundState::PlayLoop)
    {
        conGetpZC_StreamSound->Disconnect();
        soundState = ZC_StreamSound::SoundState::Pause;
    }
}

void ZC_Sound::Stop() noexcept
{
    std::lock_guard<std::mutex> lock(soundStateMutex);
    if (soundState != ZC_StreamSound::SoundState::Stop)
    {
        conGetpZC_StreamSound->Disconnect();
        soundDataIndex = 0;
        soundState = ZC_StreamSound::SoundState::Stop;
    }
}

typename ZC_StreamSound::SoundState ZC_Sound::GetState() noexcept
{
    std::lock_guard<std::mutex> lock(soundStateMutex);
    return soundState;
}

void ZC_Sound::SetVolume(float _volume) noexcept
{
    if (_volume >= 0 && _volume <= 100.f) volume = _volume / 100.f;
}

short ZC_Sound::GetVolume() const noexcept
{
    return volume * 100;
}

ZC_StreamSound* ZC_Sound::GetpZC_StreamSound() noexcept
{
    return dynamic_cast<ZC_StreamSound*>(this);
}

ZC_upSound ZC_Sound::GetSameSound() const noexcept
{
    return ZC_uptrMake<ZC_Sound>(soundData);
}