#pragma once

#define COMCEPT_X_N(name)                                   \
    template<class... Args>                                 \
    struct name                                             \
    {                                                       \
        template<class T>                                   \
        static constexpr bool value = std::name<T,Args...>; \
    }

#define COMCEPT_X_3(name)                               \
    template<class U, class V>                          \
    struct name                                         \
    {                                                   \
        template<class T>                               \
        static constexpr bool value = std::name<T,U,V>; \
    }  

#define COMCEPT_X_2(name)                               \
    template<class U>                                   \
    struct name                                         \
    {                                                   \
        template<class T>                               \
        static constexpr bool value = std::name<T,U>;   \
    }                                                 

#define COMCEPT_X_1(name)                               \
    struct name                                         \
    {                                                   \
        template<class T>                               \
        static constexpr bool value = std::name<T>;     \
    }
