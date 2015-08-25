// ----------------------------------------------------------------------------------------------------------
/// @file   runtime_converter.hpp
/// @brief  Header file for the runtime_converter metaclass which can return runtime containers (like
///         std::vector) from nano containers (mainly lists)
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * runtime_converter header file for nano library.
 * Copyright (C) 2015 Rob Clucas
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ----------------------------------------------------------------------------------------------------------
 */

#ifndef NANO_RUNTIME_CONVERTER_HPP
#define NANO_RUNTIME_CONVERTER_HPP

#include <nano/list.hpp>

#include <vector>

namespace nano {
   
    // -------------------------------------------------------------------------------------------------------
    /// @struct      runtime_converter
    /// @brief       Wrapper class to provide the conversion functions for converting to runtime containers
    /// @tparam      List    The nano::list from which to create the runtime container
    // -------------------------------------------------------------------------------------------------------
    template <typename List>
    struct runtime_converter;
    
    // Specialization for list inputs
    template <typename Head, typename... Tail>
    struct runtime_converter<list<Head, Tail...>>
    {
        // Define type of the list elements (i.e int, float etc ...) 
        // The types are assumed to be the same for a vector
        using element_type = typename Head::type;
        
        // --------------------------------------------------------------------------------------------------
        /// @brief      Converts a nano list into a std vector 
        /// @return     A std::vector with elements from the nano::list
        // --------------------------------------------------------------------------------------------------
        static constexpr std::vector<element_type> to_vector() 
        {
            return std::vector<element_type>({Head::value, Tail::value...});
        }
    };
    
}           // End namespace nano

#endif      // NANO_RUNTIME_VECTOR_HPP

