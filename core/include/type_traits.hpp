//=============================================================================
// Name        : type_traits.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date           : Sep 5, 2016
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : 
//=============================================================================

#ifndef MUL_CORE_TYPE_TRAITS_HPP_
#define MUL_CORE_TYPE_TRAITS_HPP_

#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif

#include <type_traits>

/*
 * Macro declaring a type trait checking if a class has a given method
 * Example :
 *     DECLARE_HAS_METHOD_TRAITS(has_reserve, reserve);
 *     cout << has_reserve<vector<int>, void(int)>::value;
 */
#define MUL_DECLARE_HAS_METHOD_TRAITS(TYPE_TRAIT_NAME, METHOD_NAME)                 \
template<typename CLASS, typename SIGNATURE = void()>                               \
struct TYPE_TRAIT_NAME {};                                                          \
                                                                                    \
template<typename T,typename Ret, typename... Args>                                 \
struct TYPE_TRAIT_NAME<T, Ret(Args...)>                                             \
{                                                                                   \
private:                                                                            \
                                                                                    \
    template<typename U>                                                            \
    static constexpr auto check(U*)                                                 \
        -> typename std::is_same                                                    \
            <                                                                       \
                decltype(std::declval<U>().METHOD_NAME( std::declval<Args>()... )), \
                Ret                                                                 \
            >::type;                                                                \
                                                                                    \
    template<typename>                                                              \
    static constexpr std::false_type check(...);                                    \
                                                                                    \
public:                                                                             \
                                                                                    \
    static constexpr bool value = decltype(check<T>(0))::value;                     \
}

/*
 * Macro declaring a type trait checking if a class has a given method, discarding its return type
 * Example :
 *     MUL_DECLARE_HAS_METHOD_TRAITS_DISCARD_RETURN_TYPE(has_reserve, reserve);
 *     cout << has_reserve<vector<int>, int>::value;
 */
#define MUL_DECLARE_HAS_METHOD_TRAITS_DISCARD_RETURN_TYPE(TYPE_TRAIT_NAME, METHOD_NAME)     \
template<typename CLASS, typename SIGNATURE = void()>                                       \
struct TYPE_TRAIT_NAME {};                                                                  \
                                                                                            \
template<typename T, typename... Args>                                                      \
struct TYPE_TRAIT_NAME<T, Args...>                                                          \
{                                                                                           \
private:                                                                                    \
                                                                                            \
    template<typename U>                                                                    \
    static constexpr auto check(U*)                                                         \
        -> decltype(std::declval<U>().METHOD_NAME( std::declval<Args>()... ),               \
                    std::true_type());                                                      \
                                                                                            \
    template<typename>                                                                      \
    static constexpr std::false_type check(...);                                            \
                                                                                            \
public:                                                                                     \
                                                                                            \
    static constexpr bool value = decltype(check<T>(0))::value;                             \
};                                                                                          \
                                                                                            \
template<typename T, typename Ret, typename... Args>                                        \
struct TYPE_TRAIT_NAME<T, Ret(Args...)>                                                     \
{                                                                                           \
private:                                                                                    \
                                                                                            \
    template<typename U>                                                                    \
    static constexpr auto check(U*)                                                         \
        -> decltype(std::declval<U>().METHOD_NAME( std::declval<Args>()... ),               \
                    std::true_type());                                                      \
                                                                                            \
    template<typename>                                                                      \
    static constexpr std::false_type check(...);                                            \
                                                                                            \
public:                                                                                     \
                                                                                            \
    static constexpr bool value = decltype(check<T>(0))::value;                             \
}

/*
 * Macro declaring a type trait checking if a class contains a given alias
 * Example:
 *     DECLARE_HAS_TYPEDEF_TRAITS(has_value_type_typedef, value_type);
 *     cout << has_value_type_typedef<vector<int>>::value;
 */
#define MUL_DECLARE_HAS_TYPEDEF_TRAITS(TYPE_TRAIT_NAME, HAS_TYPEDEF)    \
template<class CLASS>                                                   \
struct TYPE_TRAIT_NAME                                                  \
{                                                                       \
private:                                                                \
                                                                        \
    template<class C>                                                   \
    static char(&test(typename C::HAS_TYPEDEF *))[2];                   \
                                                                        \
    template<class>                                                     \
    static char(&test(...))[1];                                         \
                                                                        \
public:                                                                 \
                                                                        \
    static constexpr bool value = sizeof(test<CLASS>(0)) > 1;           \
}

#endif // MUL_CORE_TYPE_TRAITS_HPP_
