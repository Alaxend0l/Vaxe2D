#pragma once

namespace vaxe
{
    class vApplication
    {
    public:
        virtual int Run() {return -1;}
    protected:
        bool quit{false};
    };
}