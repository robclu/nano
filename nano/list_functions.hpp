// ----------------------------------------------------------------------------------------------------------
/// @file   list_funcitons.hpp
/// @brief  Header file for the list functions. Some list functions need higher order functions, but some
///         hof's use lists so we can't put those in the same file, so all list functions that need hof's are
///         here.
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * list header file for nano library.
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

#ifndef NANO_LIST_FUNCTIONS_HPP
#define NANO_LIST_FUNCTIONS_HPP

#include <nano/higher_order_functions.hpp>

#include <type_traits>

namespace nano {
   
namespace detail {
    
    // ------------------------------------------------------------------------------------------------------
    /// @struct     search_lists
    /// @brief      For each element in the first list, the index of the element in the second list is
    ///             searched for, if found it's added to a new list, otherwise -1 is added
    /// @tparam     List1       The list to iterate over
    /// @tparam     List2       The list to look through for each element in List1
    // ------------------------------------------------------------------------------------------------------
    template <typename List1, typename List2>
    struct search_lists;
    
    // ------------------------------------------------------------------------------------------------------
    /// @tparam     Head1       The front element in the first list
    /// @tparam     Tail1       The rest of the elements in the first list 
    /// @tparam     Head2       THe front element in the second list 
    /// @tparam     Tail2       The rest of the elements in the second list 
    // ------------------------------------------------------------------------------------------------------
    template <typename Head1, typename... Tail1, typename Head2, typename... Tail2>
    struct search_lists<list<Head1, Tail1...>, list<Head2, Tail2...>>
    {
        // For all elements in list one, search for the element's index in list2
        using result =  list<
                            nano::int_t<find_type<Head1, list<Head2, Tail2...>>::result>,    // Head of List1
                            nano::int_t<find_type<Tail1, list<Head2, Tail2...>>::result>...  // Rest of List1
                            >;
    };
}   // End namespace detail

// ----------------------------------------------------------------------------------------------------------
/// @struct     find_common
/// @brief      Finds all common elements in 2 lists and returns a zipped list of the result, where each
///             zipped element is a index of the common element in the lists. The zips are sorted by the
///             index of the element in the first list. For example, if there are 2 lists:                 \n\n
///             [ 0, 4, 2, 1 ] and [ 12, 1, 4, 2 ]                                                         \n\n
///             the returned list will be:                                                                 \n\n
///             [ [1, 2], [2 ,3], [1, 2] ]
/// @tparam     List1       The first list to search through
/// @tparam     List2       The second list to search through
// ----------------------------------------------------------------------------------------------------------
template <typename List1, typename List2>
struct find_common;

// Specialization
template <typename Head1, typename... Tail1, typename Head2, typename... Tail2>
struct find_common<list<Head1, Tail1...>, list<Head2, Tail2...>>
{
    // Create indices to zip
    using indices = typename range<0, sizeof...(Tail1), 1>::result;
    
    // Create a list of the indices of elements from list 2 in list1
    using searched_lists = typename 
        detail::search_lists<list<Head1, Tail1...>, list<Head2, Tail2...>>::result;
    
    // Essentially filter by zipping only elements in searched_lists which were found 
    using result = typename zip<is_found, indices, searched_lists, empty_list>::result;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     find_uncommon
/// @brief      Finds all elements of the first list which are not present in the second list, and returns a 
///             new list without the common elements. For example, if there are 2 lists:                   \n\n
///             [ 2, 3, 1, 4 ] and [ 4, 5, 2 ]                                                             \n\n
///             the returned list will be:                                                                 \n\n
///             [ 3, 1 ]
/// @tparam     List1       The first list to search through
/// @tparam     List2       The second list to search through
// ----------------------------------------------------------------------------------------------------------
template <typename List1, typename List2>
struct find_uncommon;

// Specialization
template <typename Head1, typename... Tail1, typename Head2, typename... Tail2>
struct find_uncommon<list<Head1, Tail1...>, list<Head2, Tail2...>>
{
   // Filter out all the elements which were found 
   using result = typename 
       filter<type_not_present, list<Head1, Tail1...>, list<Head2, Tail2...>, empty_list>::result;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     find_uncommon_indices
/// @brief      Finds the indices of the elements in the first list which are not present in the second list
///             and returns a list of the index values. For example, if there are 2 lists:                 \n\n
///             [ 2, 3, 1, 4 ] and [ 4, 5, 2 ]                                                             \n\n
///             the returned list will be:                                                                 \n\n
///             [ 1, 3 ] 
/// @tparam     List1       The list to get the indices of
/// @tparam     List2       The list to check for elements against
// ----------------------------------------------------------------------------------------------------------
template <typename List1, typename List2>
struct find_uncommon_indices;

// Specialization
template <typename Head1, typename... Tail1, typename Head2, typename... Tail2>
struct find_uncommon_indices<list<Head1, Tail1...>, list<Head2, Tail2...>>
{
    // Create a list of indices
    using indices = typename range<0, sizeof...(Tail1), 1>::result;
    
    // Create a list of results for if an element in list 1 
    // is found in list 2
    using search_results = typename 
        detail::search_lists<list<Head1, Tail1...>, list<Head2, Tail2...>>::result;
    
    // Now create the list of indices of the elements in list one 
    // which were found in list 2 by filtering the indices list 
    // using the search results
    using result = typename 
        filter<first_not_present, indices, search_results, empty_list>::result;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     multiplies
/// @brief      Same as std::multiplies, but for a nano:list which can be computed at compile time - computes
///             the product of the list elelents from the starting value.
/// @tparam     List        The list to compute the product of
/// @tparam     Current     The current value of the multiplication (for the first case, this is the start
///                         value and is default to 1)
// ----------------------------------------------------------------------------------------------------------
template <typename List, typename Current = nano::int_t<1>>
struct multiplies;

// Specialization for list
template <typename Head, typename... Tail, typename Current>
struct multiplies<list<Head, Tail...>, Current>
{
    // Multiply head of list and the current value to update the total product sum
    using updated_value = typename std::conditional<
                                    std::is_same<typename Current::type, int>::value,
                                    nano::int_t< Head::value * Current::value>,
                                    nano::size_t<Head::value * Current::value>
                                        >::type;
        
    // Now use the updaed value and multiply with the next list element on the next level of recursion
    static constexpr typename Current::type result = multiplies<list<Tail...>, updated_value>::result;
};

// Terminating case
template <typename Current>
struct multiplies<empty_list, Current>
{
    static constexpr typename Current::type result = Current::value;
};

}           // End namespace nano

#endif      // LIST_FUNCTIONS_HPP
