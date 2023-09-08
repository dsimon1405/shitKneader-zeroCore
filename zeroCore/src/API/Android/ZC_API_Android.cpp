#include <ZC/API/Android/ZC_API_Android.h>

#include <ZC/API/Android/ZC_A_Window.h>

ZC_API_Android::ZC_API_Android(std::shared_ptr<ZC_A_Window> win)
    : window(win)
{}

ZC_pWindow ZC_API_Android::MakeWindow(const char* name, const int& width, const int& height)
{
    return std::dynamic_pointer_cast<ZC_Window>(window);
}

ZC_pAPIFactory ZC_API_Android::ZC_GetAPI(std::shared_ptr<ZC_A_Window> win)
{
    return std::dynamic_pointer_cast<ZC_APIFactory>(std::make_shared<ZC_API_Android>(win));
}