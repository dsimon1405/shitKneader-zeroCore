#include <ZC/Audio/ZC_Audio.h>

#include <ZC_Config.h>

#if defined(ZC_SDL_AUDIO)
    #include "PC/SDL/ZC_SDL_AudioStream.h"
    bool ZC_Audio::MakeAudioStream(const ZC_AudioSet& audioSet) noexcept
    {
        return CreateAudioStream<ZC_SDL_AudioStream>(audioSet);
    }
#elif defined(ZC_OBOE)
    #include "Android/oboe/ZC_oboe_AudioStream.h"
    bool ZC_Audio::MakeAudioStream(const ZC_AudioSet& audioSet) noexcept
    {
        return CreateAudioStream<ZC_oboe_AudioStream>(audioSet);
    }
#endif