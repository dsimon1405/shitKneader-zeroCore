#include <ZC_main.h>
#include <ZC_EL.h>

void ZC_main(ZC_pAPIFactory apiFactory)
{
    ZC_pWindow window = apiFactory->MakeWindow("lolka", 640, 480);
    window->SetClearColor(1, 0, 1);
    while (true)
    {
        if (!window->HandleEvents())
        {
            return;
        }
        window->Clear();


        window->SwapBuffer();
    }
}