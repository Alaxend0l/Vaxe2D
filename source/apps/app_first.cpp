#include "apps/app_first.h"

#include <iostream>

namespace vaxe
{
    int vApp_First::Run()
    {
        std::cout << "APP RUNNING!" << std::endl;
        return 0;
    }
}