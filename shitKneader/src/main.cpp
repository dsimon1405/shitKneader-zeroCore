#include <ZC_main.h>
#include <ZC_EL.h>

void ZC_main(ZC_pAPIFactory apiFactory)
{
    ZC_pWindow window = apiFactory->CreateWindow("lolka", 640, 480);
    while (true)
    {
        if (!window->HandleEvents())
        {
            return;
        }
        window->Clear();

        ZC_Err("lol");
        window->SwapBuffer();
    }
}