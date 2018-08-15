//=============================================================================
// Name        : function_traits.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 14 aug. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : Provide a type trait to inspect callable types
//=============================================================================

#ifndef MUL_CORE_FUNCTION_TRAITS_HPP_
#define MUL_CORE_FUNCTION_TRAITS_HPP_

#include <tuple>

namespace mul
{

/* Type traits for a large kind of functions, methods and functors
 * After instantiation, the function_trait look like this:
 *     struct function_trait
 *     {
 *         static constexpr std::size_t arity = <argument count>;
 *
 *         using result_type = <function return type>;
 *
 *         using arguments_as_tuple = <tuple packaging all arguments>;
 *
 *         template <std::size_t N>
 *         struct argument
 *         {
 *             static_assert(N < arity, "error: invalid parameter index.");
 *             using type = <generator to get the type of the Nth argument>;
 *         };
 *     };
 *
 * The tuple 'arguments_as_tuple' can be used with std::apply without any modification
 * Therefore, there will be the class type as first argument for methods
 * Since the arity is the size of this tuple, arity will be equal to the arguments
 *     count + 1 for methods
 */

namespace detail
{

template<typename F>
struct function_trait_impl;

template<typename R, typename... Args>
struct function_trait_impl<R(Args...)>
{
    static constexpr std::size_t arity = sizeof...(Args);

    using return_type = R;

    using arguments_as_tuple = std::tuple<Args...>;

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N, arguments_as_tuple>::type;
    };
};

template<bool IsFunctor, typename F>
struct function_trait_dispatcher;

template<typename R, typename... Args>
struct function_trait_dispatcher<false, R(*)(Args...)> :
        public function_trait_impl<R(Args...)> {};

template<typename C, typename R>
struct function_trait_dispatcher<false, R(C::*)> :
        public function_trait_impl<R(C&)> {};

template<typename C, typename R, typename... Args>
struct function_trait_dispatcher<false, R(C::*)(Args...)> :
        public function_trait_impl<R(C&, Args...)> {};

template<typename C, typename R, typename... Args>
struct function_trait_dispatcher<false, R(C::*)(Args...) const> :
        public function_trait_impl<R(C&, Args...)> {};

template<typename C, typename R, typename... Args>
struct function_trait_dispatcher<true, R(C::*)(Args...)> :
        public function_trait_impl<R(Args...)> {};

template<typename C, typename R, typename... Args>
struct function_trait_dispatcher<true, R(C::*)(Args...) const> :
        public function_trait_impl<R(Args...)> {};

}  // namespace detail

// Functor specialization (default)
template<typename F>
struct function_trait :
        public detail::function_trait_dispatcher<true, decltype(&F::operator())> {};

// Free function pointer/static method specialization
template<typename R, typename... Args>
struct function_trait<R(Args...)> :
        public detail::function_trait_impl<R(Args...)> {};

// Free function pointer/static method pointer specialization
template<typename R, typename... Args>
struct function_trait<R(*)(Args...)> :
        public detail::function_trait_dispatcher<false, R(*)(Args...)> {};

// Member object pointer specialization
template<typename C, typename R>
struct function_trait<R(C::*)> :
        public detail::function_trait_dispatcher<false, R(C::*)> {};

// Method specialization
template<typename C, typename R, typename... Args>
struct function_trait<R(C::*)(Args...)> :
        public detail::function_trait_dispatcher<false, R(C::*)(Args...)> {};

// Const method specialization
template<typename C, typename R, typename... Args>
struct function_trait<R(C::*)(Args...) const> :
        public detail::function_trait_dispatcher<false, R(C::*)(Args...) const> {};

// Additional specializations to remove cvr-qualifier
template <typename T>
struct function_trait<T&> : public function_trait<T> {};

template <typename T>
struct function_trait<const T&> : public function_trait<T> {};

template <typename T>
struct function_trait<volatile T&> : public function_trait<T> {};

template <typename T>
struct function_trait<const volatile T&> : public function_trait<T> {};

template <typename T>
struct function_trait<T&&> : public function_trait<T> {};

template <typename T>
struct function_trait<const T&&> : public function_trait<T> {};

template <typename T>
struct function_trait<volatile T&&> : public function_trait<T> {};

template <typename T>
struct function_trait<const volatile T&&> : public function_trait<T> {};

} // namespace mul

#endif // MUL_CORE_FUNCTION_TRAITS_HPP_

