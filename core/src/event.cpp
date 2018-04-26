//=============================================================================
// Name        : event.cpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date		   : 26 apr. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides an observer implementation to handling events
//=============================================================================

#include <mul/event.hpp>

#include <algorithm>
#include <stdexcept>

namespace mul
{

void sender::add_receiver(receiver& observer)
{
    if(std::find(std::begin(m_receivers), std::end(m_receivers), &observer) != std::end(m_receivers))
    {
        throw std::runtime_error("mul::sender::add_receiver(): receiver already registered");
    }
    m_receivers.push_back(&observer);
}

void sender::pop_receiver(receiver& observer)
{
    m_receivers.erase(std::remove(std::begin(m_receivers), std::end(m_receivers),&observer), std::end(m_receivers));
}

void sender::raise(const event& ev)
{
    std::vector<receiver*> dead_receivers;
    for(receiver* receiver : m_receivers)
    {
        if(receiver->on_notify(*this, ev) == notify_action::unregistered)
        {
            dead_receivers.push_back(receiver);
        }
    }

    auto new_end = std::end(m_receivers);
    for(receiver* dead : dead_receivers)
    {
        new_end = std::remove(std::begin(m_receivers), new_end, dead);
    }
    m_receivers.erase(new_end, std::end(m_receivers));
}

notify_action receiver::on_notify(sender& s, const event& ev)
{
    auto find = handlers.find(typeid(ev));

    if(find != handlers.end())
    {
        find->second(s, ev);
        return notify_action::done;
    }
    else
    {
        return notify_action::unregistered;
    }
}

} // namespace mul
