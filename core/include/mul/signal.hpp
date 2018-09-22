//=============================================================================
// Name        : signal.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 22 sept. 2018
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : Provide a portable interface to handle signals
//=============================================================================

#ifndef MUL_CORE_SIGNAL_HPP_
#define MUL_CORE_SIGNAL_HPP_

#include <csignal>
#include <functional>
#include <vector>
#include <map>

namespace mul
{

enum class Signal : int
{
    Termination             = SIGTERM,      // termination request, sent to the program
    SegmentationFault       = SIGSEGV,      // invalid memory access (segmentation fault)
    Interrupt               = SIGINT,       // external interrupt, usually initiated by the user
    InvalidProgramImage     = SIGILL,       // invalid program image, such as invalid instruction
    Abort                   = SIGABRT,      // abnormal termination condition, as is e.g. initiated by std::abort()
    ArithmeticError         = SIGFPE        // erroneous arithmetic operation such as divide by zero
};

class SignalHandler
{
public:

    using HandlerType = std::function<void(Signal)>;

    template<typename F>
    static void add(Signal sig, F&& handler)
    {
        // TODO: add function_trait signature checker
        static_assert(true, "handler must have the signature void(mul::Signal)");

        // If this signal was never registered, register it with std::signal
        if(m_handlers.find(sig) == std::end(m_handlers))
            std::signal(static_cast<int>(sig), SignalHandler::handler);
        // Add the user handler to the list
        m_handlers[sig].emplace_back(std::forward<HandlerType>(handler));
    }

private:

    static void handler(int sig);

    using HandlerContainer = std::vector<HandlerType>;

    static std::map<Signal,HandlerContainer> m_handlers;
};

} // namespace mul

#endif // MUL_CORE_SIGNAL_HPP_
