// ----------------------------------------------------------------------------------------------------------
/// @file   higher_order_functions.hpp
/// @brief  Header file for nano higher order functions.                                                     \n
///                                                                                                          \n
/// Higher order functions are functions which satisfy at least one of the following properties:             \n
///                                                                                                          \n
/// \begin{itemize} 
/// \item{ Takes one or more functions as an input }
/// \item{ Outputs a function }
/// \end{itemize}
///                                                                                                          \n
/// So this header find contains all functions which fit that definition.
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

#ifndef NANO_HIGHER_ORDER_FUNCTIONS
#define NANO_HIGHER_ORDER_FUNCTIONS

#include <nano/list.hpp>

namespace nano {
    
// ----------------------------------------------------------------------------------------------------------
/// @struct     filter
/// @brief      Takes a list and an evaluation function, which itself takes the list and a parameter to
///             evaluate if each element of the list must be filtered
/// @tparam     Evaluator       The function that determines if an element is filtered or not
/// @tparam     List1           The list to filter
/// @param      List2           The list to use for filtering (to help Evaluator)
/// @tparam     Passed          The elements that have passed the Evaluator
// ----------------------------------------------------------------------------------------------------------
template <template <typename...> class Evaluator, typename List1, typename List2, typename Passed>
struct filter;

// Specialization for when Args is a list
template <template <typename, typename> class  Evaluator   , 
          typename                      Head1       , 
          typename...                   Tail1       , 
          typename                      Head2       ,
          typename...                   Tail2       ,   
          typename...                   Passed      >
struct filter<Evaluator, list<Head1, Tail1...>, list<Head2, Tail2...>, list<Passed...>>
{
    using passed = typename std::conditional<
                        Evaluator<Head1, list<Head2, Tail2...>>::result     ,
                        list<Passed..., Head1>                              ,
                        list<Passed...>
                            >::type;
    
    // Check if the evaluator uses a constant filter (2nd) list 
    // or if the filter list must drop the head element
    using filter_list = typename std::conditional<
                            Evaluator<Head1, list<Head2, Tail2...>>::constant_list  ,
                            list<Head2, Tail2...>                                   ,
                            list<Tail2...>      
                                >::type;
    
    using result = typename filter<Evaluator, list<Tail1...>, filter_list, passed>::result;
};

// Base case - when all the elements have been evaluated
template <template <typename, typename> class  Evaluator   ,
          typename...                   Tail2       ,
          typename...                   Passed      >
struct filter<Evaluator, empty_list, list<Tail2...>, list<Passed...>>
{
    using result = list<Passed...>;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     zip 
/// @brief      Takes two lists, and zips the corresponding elements into a list of 2 elements if the function
///             to determine if the elements should be zips succeeds, otherwise the elements are not zipped.
/// @tparam     Evaluator       A function which operates on corresponding elements from the 2 lists to
///             determine if the elements should be zipped.
/// @tparam     List1           First list for zipping.
/// @tparam     List2           Second list for zipping.
/// @tparam     Passed          The elements which have 'passed' the functions test and have been added to the
///             zipped list.
// ----------------------------------------------------------------------------------------------------------
template <template <typename...> class  Evaluator   , 
          typename                      List1       , 
          typename                      List2       , 
          typename...                   Passed      >
struct zip;

// Recursize case - when the whole list has not been traversed
template <template <typename...> class  Evaluator   ,
          typename                      Head1       , 
          typename...                   Tail1       ,
          typename                      Head2       ,
          typename...                   Tail2       ,
          typename...                   Passed      >
struct zip<Evaluator, list<Head1, Tail1...>, list<Head2, Tail2...>, list<Passed...>>
{
    using passed = typename std::conditional<
                                Evaluator<Head1, Head2>::result     ,      // Check if we must zip
                                list<Passed..., list<Head1, Head2>> ,      // Zip head elements if true
                                list<Passed...>                             // Don't zip if false
                                    >::type;
    
    // Recurse until we reach the base case (pattern)
    using result = typename zip<Evaluator, list<Tail1...>, list<Tail2...>, passed>::result;
};

// Base case - not more elements to check in List1 or List 2
template <template <typename...> class Evaluator, typename... Passed>
struct zip<Evaluator, empty_list, empty_list, list<Passed...>>
{
    using result = list<Passed...>;
};


}           // End namespace nano

#endif      // NANO_HIGHER_ORDER_FUNCTIONS
