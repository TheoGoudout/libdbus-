# libdbus++
A DBus library using C++11 features

## What is it?
It is a DBus library that is simple to use.
Using c++11 custom attributes feature and a GCC plugin, this library makes the usage of Dbus transparent.

## How to use it?
In order to compile a file, one needs to add the gcc argument:
```
-fplugin=/plugin/install/path/libdbusplugin.so
```

In the code, each client and server should share a header file with one of the following attributes:
`[[dbus::signal()]]` or `[[dbus::method()]]` or `[[dbus::error()]]`.
