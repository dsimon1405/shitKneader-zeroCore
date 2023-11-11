#include <ZC/Audio/ZC_AudioSet.h>

ZC_AudioSet::ZC_AudioSet(const Channels& _channels, const int& _frequency, const BitsPerSample& _bitsPerSample) noexcept
    : channels(_channels),
    frequency(_frequency),
    bitsPerSample(_bitsPerSample)
{}

bool ZC_AudioSet::operator == (const ZC_AudioSet& audioSet) const noexcept
{
    return channels == audioSet.channels &&
        frequency == audioSet.frequency &&
        bitsPerSample == audioSet.bitsPerSample;
}

std::string ZC_AudioSet::ToString() const noexcept
{
    return std::string("channels = " + std::to_string(channels)
    + "\nfrequency = " + std::to_string(channels)
    + "\nbitsPerSample = " + std::to_string(bitsPerSample));
}
