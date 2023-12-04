#pragma once

#include "ZC_Clock.h"

#include <thread>

struct ZC_FPS
{
    short fps = 1000000 / 60;
    ZC_Clock clock;

    void Actualize();
    void SetFPS(double _fps);
};

void ZC_FPS::Actualize()
{
    std::this_thread::sleep_for(ZC_Nanoseconds(clock.Restart<ZC_Nanoseconds>() - fps));
    clock.Start();
}

void ZC_FPS::SetFPS(double _fps)
{
    //  наносекунды 1 / 1 000 000
    fps = 1000000.0 / fps;
}