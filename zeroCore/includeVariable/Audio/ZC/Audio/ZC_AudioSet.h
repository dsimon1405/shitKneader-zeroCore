#pragma once

#include <ZC_string.h>

//  Struct - set of audio parameters for an audio stream.
struct ZC_AudioSet
{
    enum Channels
    {
        //  One channel.
        Mono = 1,
        //  Two channels.
        Stereo = 2
    };
    enum BitsPerSample
    {
        S16 = 16,
        S32 = 32,
        // F32 = 0
    };

    //  Number of channels in the audio recording for the audio stream.
    Channels channels;
    //  The number of bytes that should be played per second.
    int frequency = 0;
    //  The number of bytes in one audio sample for an audio stream.
    BitsPerSample bitsPerSample;

    //  Create default audio set.
    ZC_AudioSet() = default;

    /*
    Create audio set.

    Params:
    _channels - number of channels in the audio recording for the audio stream.
    _frequency - the number of bytes that should be played per second in the audio recording for an audio stream.
    _bytePerSample - the number of bytes in one audio sample for an audio stream.
    */
    ZC_AudioSet(const Channels& _channels, const int& _frequency, const BitsPerSample& _bitsPerSample) noexcept;

    operator bool () const noexcept;

    /*
    Compares the ZC_AudioSet pair.

    Params:
    audioSet - set for comparing.

    Return:
    If equal true, else false.
    */
    bool operator == (const ZC_AudioSet& audioSet) const noexcept;

    /*
    Helps get the string representation of ZC_AudioSet.

    Return:
    Strign representation of ZC_AudioSet.
    */
    std::string ToString() const noexcept;
};
