//=============================================================================
// Name        : type_traits.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : Sep 5, 2016
// Version     : 1.1.0
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

namespace mul 
{

#if __cplusplus < 201703L
// if C++17 is not available, reimplement the missing type_traits within namespace mul
    
// bool_constant implementation from cppreference.com
template<bool B>
using bool_constant = std::integral_constant<bool, B>;
	
// conjunction implementation from cppreference.com
template<class...> struct conjunction : std::true_type { };
template<class B1> struct conjunction<B1> : B1 { };
template<class B1, class... Bn>
struct conjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

// disjunction implementation from cppreference.com
template<class...> struct disjunction : std::false_type { };
template<class B1> struct disjunction<B1> : B1 { };
template<class B1, class... Bn>
struct disjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>  { };

// negation implementation from cppreference.com
template<class B>
struct negation : mul::bool_constant<!bool(B::value)> { };

#else
// if C++17 is available, just import standard version into mul namespace

using std::bool_constant;
using std::conjunction;
using std::disjunction;
using std::negation;

#endif
    
template<typename T, typename... Ts>
struct is_one_of
{
    static constexpr bool value = mul::disjunction<std::is_same<T, Ts>...>::value;
};

template<typename T, typename... Ts>
struct is_one_of<T, std::tuple<Ts...>> : is_one_of<T, Ts...> {}; 
  
} // namespace mul 

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
