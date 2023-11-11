#include <ZC/Audio/ZC_SoundData.h>

ZC_SoundData::ZC_SoundData(char* _data, const unsigned int& _size, const ZC_AudioSet& _audioSet) noexcept
  : data(_data),
  dataSize(_size),
  audioSet(_audioSet)
{}

ZC_SoundData::ZC_SoundData(ZC_SoundData&& soundData) noexcept
  : ZC_SoundData(soundData.data, soundData.dataSize, soundData.audioSet)
{
  soundData.data = nullptr;
  soundData.dataSize = 0;
  soundData.audioSet.frequency = 0;
}

ZC_SoundData& ZC_SoundData::operator = (ZC_SoundData&& soundData) noexcept
{
  data = soundData.data;
  dataSize = soundData.dataSize;
  audioSet = soundData.audioSet;

  soundData.data = nullptr;
  soundData.dataSize = 0;
  soundData.audioSet.frequency = 0;
  return *this;
}

ZC_SoundData::~ZC_SoundData() noexcept
{
  delete[] data;
}

ZC_AudioSet ZC_SoundData::GetAudioSet() const noexcept
{
  return audioSet;
}