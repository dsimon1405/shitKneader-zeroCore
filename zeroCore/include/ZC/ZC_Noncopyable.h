#pragma once

class ZC_Noncopyable
{
public:
    ZC_Noncopyable(const ZC_Noncopyable&) = delete;
    ZC_Noncopyable& operator=(ZC_Noncopyable&) = delete;

protected:
    ZC_Noncopyable() = default;
};