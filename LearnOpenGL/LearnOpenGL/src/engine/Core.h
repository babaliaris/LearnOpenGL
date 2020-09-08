#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H
#include "Logger.h"

#define ASSERT_FORMAT(x, formatter, ...)\
{\
    if (!(x))\
    {\
        std::stringstream ss;\
        ss << "Assertion Failed: {0}\n\t\t\t\t\t   In File: {1}\n\t\t\t\t\t   At Line: {2}\n\t\t\t\t\t   Message: " << #formatter;\
        LOG_ERROR(ss.str(), #x, __FILE__, __LINE__, __VA_ARGS__);\
        abort();\
    }\
}


#define ASSERT(x, msg)\
{\
    if (!(x))\
    {\
        std::stringstream ss;\
        ss << "Assertion Failed: {0}\n\t\t\t\t\t   In File: {1}\n\t\t\t\t\t   At Line: {2}\n\t\t\t\t\t   Message: {3}";\
        LOG_ERROR(ss.str(), #x, __FILE__, __LINE__, msg);\
        abort();\
    }\
}




//Visual Studio.
#ifdef _MSC_BUILD
    #define RUNTIME_DIR "LearnOpenGL/LearnOpenGL/"

//Other Environments.
#else
    #define RUNTIME_DIR "LearnOpenGL/LearnOpenGL/"

#endif


#endif