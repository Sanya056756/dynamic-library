# Dynamic Library

Dynamic Library is a C++ library for execute function in shared library.

## Installation

Use [CMake](https://cmake.org/) and module [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) to install Dynamic Library.

```cmake
include(FetchContent)

FetchContent_Declare(
    dynamic-library
    GIT_REPOSITORY https://github.com/Sanya056756/dynamic-library
    GIT_TAG master
)

FetchContent_MakeAvailable(dynamic-library)

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
    std::string input = "Hello World!";

    DynamicLibrary library;
    
    if (!library.LoadDynamicLibrary(libraryPath))
        throw std::runtime_error("Failed to load shared library");

    if (!library.ExecuteFunction<void, std::string>(functionName, input, nullptr))
        throw std::runtime_error("Failed to execute function in shared library");
}
```

## Contributing

I'm always open to discussing any suggestions for improving the project.