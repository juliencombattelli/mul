//=============================================================================
// Name        : timer.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 26 apr. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a timer class based on C++11 std::chrono
//=============================================================================

#ifndef MUL_CORE_TIMER_HPP_
#define MUL_CORE_TIMER_HPP_

#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif

#include <ratio>
#include <chrono>

namespace mul
{

template<typename TArith, typename TClock = std::chrono::steady_clock>
class time
{
    static_assert(std::is_arithmetic<TArith>::value, "TArith must be an arithmetic type.");
    
public:
    using value_type = TArith;
    using clock_type = TClock;
    using duration_type = typename clock_type::duration;

    using nano      = std::chrono::duration<value_type, std::nano>;
    using micro     = std::chrono::duration<value_type, std::micro>;
    using milli     = std::chrono::duration<value_type, std::milli>;
    using second    = std::chrono::duration<value_type, std::ratio<1>>;
    using minute    = std::chrono::duration<value_type, std::ratio<60>>;
    using hour      = std::chrono::duration<value_type, std::ratio<3600>>;
    using day       = std::chrono::duration<value_type, std::ratio<3600*24>>;
    using week      = std::chrono::duration<value_type, std::ratio<3600*24*7>>;

    explicit time(duration_type d) : m_time(d) {}

    value_type nanos() const { return  nano(m_time).count(); }
    value_type micros() const { return  micro(m_time).count(); }
    value_type millis() const { return  milli(m_time).count(); }
    value_type seconds() const { return  second(m_time).count(); }
    value_type minutes() const { return  minute(m_time).count(); }
    value_type hours() const { return  hour(m_time).count(); }
    value_type days() const { return  day(m_time).count(); }
    value_type weeks() const { return  week(m_time).count(); }

private:
    duration_type m_time;
};

template<typename TArith, typename TClock = std::chrono::steady_clock>
class timer
{
public:
    using value_type = TArith;
    using clock_type = TClock;
    using duration_type = typename clock_type::duration;
    using time_point_type = typename clock_type::time_point;

    explicit timer(bool run = false) { if(run) reset(); }

    void reset() { m_start = clock_type::now(); }

    time<TArith, TClock> elapsed() const { return time<value_type, clock_type>(clock_type::now() - m_start); }

private:
    time_point_type m_start;
};

} // namespace mul

#endif // MUL_CORE_TIMER_HPP_ 
