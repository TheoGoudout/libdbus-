#include <iostream>

#include "header.h"

namespace org
{
    namespace dbus
    {
        namespace example
        {
            void signal()
            {
                std::cout << "Hello world!" << std::endl;
            }
        }
    }
}

int main (int argc, char** argv)
{
    while (true) ;

    return 0;
}