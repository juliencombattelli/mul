//=============================================================================
// Name        : memory.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@gmail.com
// Date        : 25 apr. 2018
// Version     : 2.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : Provide some tools to efficiently manipulate memory
//=============================================================================

#ifndef MUL_CORE_MEMORY_HPP_
#define MUL_CORE_MEMORY_HPP_

#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif

#include <cstdint>

namespace mul
{

inline std::uint32_t to_u32(const std::uint8_t bytes[4])
{
    return std::uint32_t(bytes[0]) << 24 | std::uint32_t(bytes[1]) << 16
         | std::uint32_t(bytes[2]) <<  8 | std::uint32_t(bytes[3]);
}

inline std::uint64_t to_u64(const std::uint8_t bytes[8])
{
    std::uint32_t lbytes = to_u32(&bytes[0]);
    std::uint32_t hbytes = to_u32(&bytes[4]);
    return std::uint64_t(lbytes) << 32 | std::uint64_t(hbytes);
}

inline void to_bytes(std::uint32_t u32, std::uint8_t bytes[4])
{
    std::uint8_t* u8v = (std::uint8_t*)&u32;
    std::uint32_t& bytes_as_u32 = *(std::uint32_t*)bytes;
    bytes_as_u32 = to_u32(u8v);
}

inline void to_bytes(std::uint64_t u64, std::uint8_t bytes[8])
{
    std::uint8_t* u8v = (std::uint8_t*)&u64;
    std::uint64_t& bytes_as_u64 = *(std::uint64_t*)bytes;
    bytes_as_u64 = to_u64(u8v);
}

} // namespace mul

#endif // MUL_CORE_MEMORY_HPP_
