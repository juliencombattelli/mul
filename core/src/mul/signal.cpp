//=============================================================================
// Name        : signal.cpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 22 sept. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : Provide a portable interface to handle signals
//=============================================================================

#include <mul/signal.hpp>

namespace mul
{

std::map<Signal,SignalHandler::HandlerContainer> SignalHandler::m_handlers;

void SignalHandler::handler(int sig)
{
    // Get the handler container corresponding to sig
    auto& sigHandlers = m_handlers[static_cast<Signal>(sig)];

    for(auto& handler : sigHandlers)
        // If handler's std::function is valid then execute it
        if(handler)
            handler(static_cast<Signal>(sig));
}

} // namespace mul
