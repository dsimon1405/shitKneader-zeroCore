#pragma once

//  Wrapper for dynamic array with open data.
template<typename T>
struct ZC_DynamicArray
{
    T* pArray = nullptr;
    unsigned long size = 0;

    ZC_DynamicArray(T* _pArray = nullptr, unsigned long _size = 0) noexcept;
    ZC_DynamicArray(unsigned long _size) noexcept;

    ZC_DynamicArray(const ZC_DynamicArray&) = delete;
    ZC_DynamicArray& operator = (const ZC_DynamicArray&) = delete;

    ZC_DynamicArray(ZC_DynamicArray&& charArray) noexcept;;
    ZC_DynamicArray& operator = (ZC_DynamicArray&& charArray) noexcept;

    ~ZC_DynamicArray() noexcept;

    T& operator [] (unsigned long index);
    const T& operator [] (unsigned long index) const;

    operator bool () const noexcept;

    const T* Begin() const noexcept;
};

template<typename T>
ZC_DynamicArray<T>::ZC_DynamicArray(T* _pArray, unsigned long _size) noexcept
    : pArray(_pArray),
    size(_size)
{}

template<typename T>
ZC_DynamicArray<T>::ZC_DynamicArray(unsigned long _size) noexcept
        : pArray(new T[_size]),
        size(_size)
{}

template<typename T>
ZC_DynamicArray<T>::ZC_DynamicArray(ZC_DynamicArray&& charArray) noexcept
        : pArray(charArray.pArray),
          size(charArray.size)
{
    charArray.pArray = nullptr;
}

template<typename T>
ZC_DynamicArray<T>& ZC_DynamicArray<T>::operator = (ZC_DynamicArray&& charArray) noexcept
{
    delete[] pArray;
    pArray = charArray.pArray;
    size = charArray.size;

    charArray.pArray = nullptr;
    charArray.size = 0;
    return *this;
}

template<typename T>
ZC_DynamicArray<T>::~ZC_DynamicArray() noexcept
{
    delete[] pArray;
    pArray = nullptr;
}

template<typename T>
T& ZC_DynamicArray<T>::operator [] (unsigned long index)
{
    return pArray[index];
}

template<typename T>
const T& ZC_DynamicArray<T>::operator [] (unsigned long index) const
{
    return const_cast<T&>(pArray[index]);
}

template<typename T>
const T* ZC_DynamicArray<T>::Begin() const noexcept
{
    return pArray;
}

template<typename T>
ZC_DynamicArray<T>::operator bool () const noexcept
{
    return pArray;
}