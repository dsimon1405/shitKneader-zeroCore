#include <ZC/API/PC/ZC_PC_main.h>

#include <ZC/ZC_APIFactory.h>

int main(int argv, char** args)
{
    ZC_pAPIFactory api = ZC_APIFactory::GetApiFactory();
    ZC_main(api);

    return 0;
}