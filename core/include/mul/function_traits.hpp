#ifndef MUL_CORE_FUNCTION_TRAITS_HPP_
#define MUL_CORE_FUNCTION_TRAITS_HPP_

#include <tuple>

namespace mul
{

/* Type traits for a large kind of functions, methods and functors
 * After instantiation, the function_traits look like this:
 *     struct function_traits
 *     {
 *         using result_type = <function return type>;
 *
 *         static constexpr std::size_t arity = <argument count>;
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
 */

template<class F>
struct function_traits;

template<class F>
struct function_traits<F&> : public function_traits<F>
{};

template<class F>
struct function_traits<F&&> : public function_traits<F>
{};

// function pointer
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)>
{};

// member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...)> : public function_traits<R(Args...)>
{};

// const member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...) const> : public function_traits<R(Args...)>
{};

// member object pointer
template<class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C&)>
{};

// implementation for function pointer,
//                    member function pointer,
//                    const member function pointer,
//                    member object pointer
template<class R, class... Args>
struct function_traits<R(Args...)>
{
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(Args);

    using arguments_as_tuple = std::tuple<Args...>;

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
    };
};

// default implementation (mostly for functors and lambdas)
template<class F>
struct function_traits
{
private:
    using call_type = function_traits<decltype(&F::operator())>;
public:
    using return_type = typename call_type::return_type;

    static constexpr std::size_t arity = call_type::arity - 1;

    using arguments_as_tuple = typename call_type::arguments_as_tuple;

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename call_type::template argument<N+1>::type;
    };
};

template <typename _Fn, typename _Tuple, size_t... _Idx>
constexpr decltype(auto) apply_impl(_Fn&& __f, _Tuple&& __t, std::index_sequence<_Idx...>)
{
    return std::invoke(std::forward<_Fn>(__f), std::get<_Idx>(std::forward<_Tuple>(__t))...);
}

template <typename _Fn, typename _Class, typename _Tuple, size_t... _Idx>
constexpr decltype(auto) apply_impl_memfun(_Fn&& __f, _Class&& __obj, _Tuple&& __t, std::index_sequence<_Idx...>)
{
    return std::invoke(std::forward<_Fn>(__f), std::forward<_Class>(__obj), std::get<_Idx>(std::forward<_Tuple>(__t))...);
}

template <typename _Fn, typename _Tuple>
constexpr decltype(auto) apply(_Fn&& __f, _Tuple&& __t)
{
    using _Indices = std::make_index_sequence<std::tuple_size_v<std::decay_t<_Tuple>>>;
    return apply_impl(std::forward<_Fn>(__f), std::forward<_Tuple>(__t), _Indices{});
}

template <typename _MemFun, typename _Class, typename _Tuple>
constexpr decltype(auto) apply(_MemFun&& __f, _Class&& __obj, _Tuple&& __t)
{
    using _Indices = std::make_index_sequence<std::tuple_size_v<std::decay_t<_Tuple>>>;
    return apply_impl_memfun(std::forward<_MemFun>(__f), std::forward<_Class>(__obj), std::forward<_Tuple>(__t), _Indices{});
}

} // namespace mul

#endif // MUL_CORE_FUNCTION_TRAITS_HPP_
