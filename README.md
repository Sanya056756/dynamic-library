# Dynamic Library

Dynamic Library is a C++ library for execute function in shared library.

## Installation

Use [CMake](https://cmake.org/) and module [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) to install Dynamic Library.

```cmake
include(FetchContent)

FetchContent_Declare(
    openssl-evp
    GIT_REPOSITORY https://github.com/Sanya056756/openssl-evp.git
    GIT_TAG master
)

FetchContent_MakeAvailable(openssl-evp)

...

target_link_libraries(target_name PRIVATE Dynamic::LIBS)
```

## Usage

main.cpp:

```cpp
#include <iostream>

#include <libs/libs.hpp>

int main()
{
    const char* libraryPath = "shared.dll"; // shared.so, shared.dylib ...
    const char* functionName = "hello";

    DynamicLibrary library;
    
    if (!library.LoadDynamicLibrary(libraryPath))
    {
        std::cerr << "Failed to load dynamic library" << std::endl;
        return 1;
    }

    if (!library.ExecuteFunction<void, std::string>(functionName, "Hello World!", nullptr))
    {
        std::cerr << "Failed to execute function in dynamic library" << std::endl;
        return 1;
    }
}
```

## Contributing

I'm always open to discussing any suggestions for improving the project.