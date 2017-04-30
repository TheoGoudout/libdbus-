#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

namespace org
{
    namespace dbus
    {
        namespace example
        {
            [[dbus::signal()]]
            void signal();
        }
    }
}

#endif /* HEADER_H_INCLUDED */