//=============================================================================
// Name        : cpptimer.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 26 apr. 2018
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a bench timer using std::chrono
//=============================================================================

#include <chrono>
#include <cstdint>

#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif

namespace mul
{

template<typename TDuration = std::chrono::milliseconds, typename TClock = std::chrono::steady_clock>
struct cpptimer
{
    auto get_time() const -> decltype(std::declval<TDuration>().count())
    { 
        auto now = TClock::now();
        return std::chrono::duration_cast<TDuration>(now.time_since_epoch()).count();
    }
 
#if __cplusplus < 201703L
    // 'if constexpr' not available prior to C++17, so cannot initialize this static variable in-class
    // initialize it in a source file would be too painfull since it is a static template variable
    static constexpr char* unit_str = (char*)"<unknown unit>";

#else
    static constexpr char* unit_str = 
    [&]()
    {
        if      constexpr(std::is_same<TDuration, std::chrono::nanoseconds>::value)
            return (char*)"nanoseconds";
        else if constexpr(std::is_same<TDuration, std::chrono::microseconds>::value)
            return (char*)"microseconds";
        else if constexpr(std::is_same<TDuration, std::chrono::milliseconds>::value)
            return (char*)"milliseconds";
        else if constexpr(std::is_same<TDuration, std::chrono::seconds>::value)
            return (char*)"seconds";
        else if constexpr(std::is_same<TDuration, std::chrono::hours>::value)
            return (char*)"hours";
#if __cplusplus > 201703L
        else if constexpr(std::is_same<TDuration, std::chrono::days>::value)
            return (char*)"days";
        else if constexpr(std::is_same<TDuration, std::chrono::weeks>::value)
            return (char*)"weeks";
        else if constexpr(std::is_same<TDuration, std::chrono::months>::value)
            return (char*)"months";
        else if constexpr(std::is_same<TDuration, std::chrono::years>::value)
            return (char*)"years";
#endif
        else
            return (char*)"<unknown unit>";
    }();
#endif
    
};
    
} // namespace mul

