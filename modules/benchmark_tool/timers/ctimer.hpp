//=============================================================================
// Name        : ctimer.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 26 apr. 2018
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a bench timer using std::time
//=============================================================================

#include <ctime>

namespace mul
{

struct ctimer
{
    int get_time() const { return std::time(nullptr); }
    
    static constexpr char* unit_str = (char*)"seconds";
};
    
} // namespace mul

