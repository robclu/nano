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

#include <array>
#include <vector>
#include <type_traits>

namespace nano {
   
    // For 'behind the scenes' or more involved implementations
    namespace detail {
        
        // --------------------------------------------------------------------------------------------------
        /// @struct     array_convert 
        /// @brief      Converts an element to a std type, like nano::int_t to inr or a nano::list into a 
        ///             std::array with N elements
        /// @tparam     Elements    The element(s) to convert to a std type or std::array
        // --------------------------------------------------------------------------------------------------
        template <typename Element>
        struct array_convert
        {
            using type = typename Element::type;
            
            static constexpr type result() { return Element::value; };
        };
        
        // Specialization
        template <typename First, typename... Rest>
        struct array_convert<list<First, Rest...>>
        {
            static constexpr std::size_t size = sizeof...(Rest) + 1;
            
            using type = typename std::array<typename First::type, size>;
            
            static constexpr type result() { 
                return type{ {First::value, Rest::value...} };
            }
        };
        
        // --------------------------------------------------------------------------------------------------
        /// @struct     vector_convert
        /// @brief      Same as convert, but uses vector's instead of arrays, so the performance is worse
        /// @tparam     Element     The element(s) to convert to a std type or std::vector
        // --------------------------------------------------------------------------------------------------
        template <typename Element>
        struct vector_convert
        {
            using type = typename Element::type;
            
            static constexpr type result() { return Element::value; };
        };
        
        // Specialization for lists
        template <typename First, typename... Rest>
        struct vector_convert<list<First, Rest...>>
        {
            using type = typename std::vector<typename First::type>;
            
            static constexpr type result() {
                return type{ {First::value, Rest::value...} };
            }
        };
    }
    
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
        // Number of elements in the external array - for readability of below function
        static constexpr std::size_t num_elements = sizeof...(Tail) + 1;
        
        using array_internal_type   = typename detail::array_convert<Head>::type;
        using array_type            = typename std::array<array_internal_type, num_elements>;       
        
        // --------------------------------------------------------------------------------------------------
        /// @brief      Converts a nano::list to a std::array, if the nano::list just contains elements. If
        ///             the nano::list contains nano::lists, then a std::array of std::array's is created
        /// @return     A std::array of elements, where the element type depends on the elements of the
        ///             nano::list from which it is created.
        // --------------------------------------------------------------------------------------------------
        static constexpr array_type to_array() {
            return array_type{ {detail::array_convert<Head>::result(), 
                                detail::array_convert<Tail>::result()...} };
        }
        
        using vector_internal_type  = typename detail::vector_convert<Head>::type;
        using vector_type           = typename std::vector<vector_internal_type>;
        
        // --------------------------------------------------------------------------------------------------
        /// @brief      Converts a nano::list to a std::vector, if the nano::list just contains elements. If
        ///             the nano::list contains nano::lists, then a std::vector of std::vector's is created.
        /// @return     A std::vector of elements, where the element type depends on the elements of the
        ///             nano::list from which it is created.
        // --------------------------------------------------------------------------------------------------
        static constexpr vector_type to_vector() {
            return vector_type{ {detail::vector_convert<Head>::result(),
                                 detail::vector_convert<Tail>::result()...} };
        }
    };
    
}           // End namespace nano

#endif      // NANO_RUNTIME_VECTOR_HPP

