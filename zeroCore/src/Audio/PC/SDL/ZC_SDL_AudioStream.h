#pragma once

#include <ZC/Audio/ZC_AudioStream.h>

#include <SDL3/SDL_audio.h>

class ZC_SDL_AudioStream : public ZC_AudioStream
{
public:
    ZC_SDL_AudioStream(const ZC_AudioSet& _audioSet);
    ~ZC_SDL_AudioStream() noexcept override;

private:
    SDL_AudioStream* stream = nullptr;
    
    static void SDLCALL MyAudioCallback(void *userdata, SDL_AudioStream *stream, int approx_amount);
};