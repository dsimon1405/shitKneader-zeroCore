#pragma once

template<typename TArray>
struct ZC_DynamicArray
{
    TArray* array = nullptr;
    unsigned long size = 0;

    ZC_DynamicArray() = default;
    ZC_DynamicArray(const unsigned long& _size) noexcept
      : size(_size),
      array(new TArray[_size])
    {}

    ZC_DynamicArray(const ZC_DynamicArray&) = delete;
    ZC_DynamicArray& operator = (const ZC_DynamicArray&) = delete;

    ZC_DynamicArray(ZC_DynamicArray&& charArray) noexcept
        : array(charArray.array),
        size(charArray.size)
    {
        charArray.array = nullptr;
    }
    
    ZC_DynamicArray& operator = (ZC_DynamicArray&& charArray) noexcept
    {
        array = charArray.array;
        size = charArray.size;

        charArray.array = nullptr;
        return *this;
    }

    ~ZC_DynamicArray() noexcept
    {
        delete[] array;
        array = nullptr;
    }
};