#pragma once

#include "ZC_Clock.h"

#include <thread>

struct ZC_FPS
{
    short fps = 1000000 / 60;
    ZC_Clock clock;

    void Actualize() noexcept;
    void SetFPS(float _fps) noexcept;
};

void ZC_FPS::Actualize() noexcept
{
    std::this_thread::sleep_for(ZC_Nanoseconds(clock.Stop<ZC_Nanoseconds>() - fps));
    clock.Start();
}

void ZC_FPS::SetFPS(float _fps) noexcept
{
    //  наносекунды 1 / 1 000 000
    fps = 1000000 / fps;
}