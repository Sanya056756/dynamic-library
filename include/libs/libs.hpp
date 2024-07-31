#ifndef PLUGINS_LIBS_H
#define PLUGINS_LIBS_H

#include <type_traits>

#ifdef _WIN32
#   include <windows.h>
#   define LIBS_OS_WIN
#elif defined(__linux__) || defined(__APPLE__)
#   include <dlfcn.h>
#   define LIBS_OS_UNIX
#endif

class DynamicLibrary
{
public:
    DynamicLibrary() = default;

    ~DynamicLibrary()
    {
        #ifdef LIBS_OS_WIN
        FreeLibrary(m_library);
        #else
        dlclose(m_library);
        #endif
    }

    bool LoadDynamicLibrary(const char* path)
    {
        #ifdef LIBS_OS_WIN
        m_library = LoadLibrary(path);
        #else
        m_library = dlopen(path, RTLD_LAZY);
        #endif
        m_initialized = m_library != nullptr;
        return m_initialized;
    }

    template<typename O, typename... Args>
    bool ExecuteFunction(const char* function, Args... args, O* output)
    {
        if (!m_initialized)
            return false;

        #ifdef LIBS_OS_WIN
        typedef O(__cdecl *proc)(Args...);
        auto func = (proc) GetProcAddress(m_library, function);
        #else
        O(*proc)(Args...);
        void* func = dlsym(m_library, function);
        proc = reinterpret_cast<decltype(proc)>(func);
        #endif

        if (func == nullptr)
            return false;

        bool isVoid = std::is_void<O>::value;

        #ifdef LIBS_OS_WIN
        if (isVoid) func(args...);
        else *output = func(args...);
        #else
        if (isVoid) (*proc)(args...);
        else *output = (*proc)(args...);
        #endif

        return true;
    }

private:
#   ifdef LIBS_OS_WIN
    HMODULE m_library;
#   else
    void* m_library;
#   endif
    bool m_initialized;
};

#endif //PLUGINS_LIBS_H