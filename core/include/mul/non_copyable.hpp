//=============================================================================
// Name        : non-copyable.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date		   : 27 jun. 2016
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a C++11 non copyable base class
//=============================================================================

#ifndef MUL_CORE_NON_COPYABLE_HPP_
#define MUL_CORE_NON_COPYABLE_HPP_

#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif

namespace mul
{

class non_copyable 
{
protected:
	non_copyable() = default;
	~non_copyable() = default;

	non_copyable(const non_copyable&) = delete;
	non_copyable& operator=(const non_copyable&) = delete;
};

}  // namespace mul

#endif // MUL_CORE_NON_COPYABLE_HPP_
