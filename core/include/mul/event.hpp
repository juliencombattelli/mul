//=============================================================================
// Name        : event.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 26 apr. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides an observer implementation to handling events
//=============================================================================

#ifndef MUL_CORE_EVENT_HPP_
#define MUL_CORE_EVENT_HPP_

#if __cplusplus < 201402L
#error This library needs at least a C++14 compliant compiler
#endif

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <functional>

namespace mul
{

class receiver;

struct event
{
    virtual ~event() = default;
};

enum class notify_action
{
    done,
    unregistered
};

class sender
{
public:
    void add_receiver(receiver& observer);
    void pop_receiver(receiver& observer);
    void raise(const event& ev);

private:
    std::vector<receiver*> m_receivers;
};

class receiver
{
public:
    virtual ~receiver() = default;
    
    virtual notify_action on_notify(sender& s, const event& ev);


    template<typename TEvent, typename TMethod, typename TObject>
    void add_event_handler(TMethod&& method, TObject&& obj)
    {
        static_assert(std::is_base_of<event, TEvent>::value, "TEvent must be inherit from mul::event.");
        handlers[typeid(TEvent)] = std::bind(method, obj, std::placeholders::_1, std::placeholders::_2);
    }

    template<typename TEvent, typename TFunctor>
    void add_event_handler(TFunctor&& functor)
    {
        static_assert(std::is_base_of<event, TEvent>::value, "TEvent must be inherit from mul::event.");
        handlers[typeid(TEvent)] = functor;
    }

private:
    std::unordered_map<std::type_index,std::function<void(sender&, const event&)>> handlers;
};

} // namespace mul

#endif // MUL_CORE_EVENT_HPP_
