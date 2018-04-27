//=============================================================================
// Name        : factory.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date		   : 26 apr. 2018
// Version     : 1.1.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : Provide an abstract factory template class
//=============================================================================

#ifndef MUL_CORE_FACTORY_HPP_
#define MUL_CORE_FACTORY_HPP_

#if __cplusplus < 201402L
#error This library needs at least a C++14 compliant compiler
#endif

#include <map>
#include <memory>

namespace mul
{

namespace detail
{
    
/*
 *  Wrapper interface to extend any TBase class providing a create() method
 *      returning a unique_ptr<TBase> 
 */
template<class TBase>
struct instanciator
{
	virtual std::unique_ptr<TBase> create() = 0;
	virtual ~instanciator() = default;
};

/*
 *  Wrapper implementation providing a dynamic allocation creation
 *  The TDerived class must be default constructible
 */
template<class TBase, class TDerived>
struct new_instanciator : instanciator<TBase>
{
    static_assert(std::is_default_constructible<TDerived>::value, "Class managed by mul::factory must be default constructible.");
	std::unique_ptr<TBase> create()
	{
		return std::make_unique<TDerived>();
	}
};

} // namespace detail

template<class TBase, class TKey>
class factory
{
public:
	template<class TDerived>
	void register_class(const TKey& id)
	{
		m_map[id] = std::make_unique<detail::new_instanciator<TBase, TDerived>>();
	}

	std::unique_ptr<TBase> create(const TKey& id)
	{
		return m_map.at(id)->create();
	}

private:
    std::map<TKey, std::unique_ptr<detail::instanciator<TBase>>> m_map;
};

} // namespace mul

#endif // MUL_CORE_FACTORY_HPP_
