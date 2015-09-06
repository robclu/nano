// ----------------------------------------------------------------------------------------------------------
/// @file   nano_tests.cpp
/// @brief  Test suites for the nano library using Bost.Unit.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE       NanoTests
#include <boost/test/unit_test.hpp>

#include <nano/nano.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( NumericTypeTestSuite )
    
BOOST_AUTO_TEST_CASE( canCreateStaticNanoIntType )
{
    nano::int_t<2> static_int;
    
    BOOST_CHECK( static_int.runtime_value() == 2 );
}

BOOST_AUTO_TEST_CASE( canCreateStaticNanoSizeType )
{
    nano::size_t<0> static_size_type;
    
    BOOST_CHECK( static_size_type.runtime_value() == 0 );
}

BOOST_AUTO_TEST_CASE( canUseDefinedDimensionTypes )
{
    using namespace nano::dim;                    // To access dimension variables
    
    BOOST_CHECK( i.runtime_value() == 0 );
    BOOST_CHECK( j.runtime_value() == 1 );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------------------------------- List Tests ------------------------------------------------------

BOOST_AUTO_TEST_SUITE( ListTestSuite )
    
BOOST_AUTO_TEST_CASE( canCreateAList )
{
    using test_list = nano::list<nano::int_t<3>, nano::size_t<9>>;
    using type_one  = nano::get<0, test_list>;   // Should be nano::int_t<3>   
    using type_two  = nano::get<1, test_list>;   // Should be nano::size_t<9>
    
    // Decalre elements of the types to get their runtime values
    type_one elem_zero;         
    type_two elem_one;
    
    BOOST_CHECK( elem_zero.runtime_value() == 3 );
    BOOST_CHECK( elem_one.runtime_value()  == 9 );
}

BOOST_AUTO_TEST_CASE( canGetSizeOfList )
{
    using test_list = nano::list<nano::int_t<4>, nano::int_t<12>>;
  
    BOOST_CHECK( test_list::size == 2 );
}

BOOST_AUTO_TEST_CASE( canFindTypeInList )
{
    using test_list = nano::list<nano::size_t<2>, nano::size_t<4>, nano::int_t<6>>;
    
    std::size_t size_two_index  = nano::find_type<nano::size_t<2>, test_list>::result;
    std::size_t size_four_index = nano::find_type<nano::size_t<4>, test_list>::result;
    std::size_t int_six_index   = nano::find_type<nano::int_t<6>, test_list>::result;
    
    BOOST_CHECK( size_two_index   == 0 );
    BOOST_CHECK( size_four_index  == 1 );
    BOOST_CHECK( int_six_index    == 2 );
}

BOOST_AUTO_TEST_CASE( findTypeIsCorrectWhenTypeNotInList )
{
    using test_list             = nano::list<nano::size_t<3>, nano::int_t<77>, nano::size_t<12>>;
    using not_found_type        = nano::find_type<nano::int_t<9>, test_list>;
    
    int not_found_type_index    = not_found_type::result;
    
    BOOST_CHECK( not_found_type_index == -1 );
}

BOOST_AUTO_TEST_CASE( canFindCommonElementsInTwoLists )
{
    using list_1 = nano::list<nano::int_t<2>, nano::int_t<3>, nano::int_t<7>, nano::int_t<22>>;
    using list_2 = nano::list<nano::int_t<7>, nano::int_t<4>, nano::int_t<3>>;
    
    // Look through all elements in list_1 and see if each of the elements exist
    // in list_2. If the element exists in list 2, then a 2 element list is added to 
    // a new list with the index in list one and it's corresponding index in list_2.
    // 
    // So for the list's above, the final list will be:
    // 
    // [ {1, 2}, {2, 0} ]
    // 
    // Since element 1 is found at index 2 of list_2 and element 2 is found at index 0
    using common_list = typename nano::find_common<list_1, list_2>::result;
    
    using first_pair    = nano::get<0, common_list>;              // Gets {1, 2}
    using second_pair   = nano::get<1, common_list>;              // Gets {2, 0}

    using first_index   = nano::get<0, first_pair>;
    using first_result  = nano::get<1, first_pair>;
    using second_index  = nano::get<0, second_pair>;
    using second_result = nano::get<1, second_pair>;
   
    // Declare variables of these types
    first_index     fi;
    first_result    fr;
    second_index    si;
    second_result   sr;
    
    BOOST_CHECK( fi.runtime_value() == 1 );
    BOOST_CHECK( fr.runtime_value() == 2 );
    BOOST_CHECK( si.runtime_value() == 2 );
    BOOST_CHECK( sr.runtime_value() == 0 );
}

BOOST_AUTO_TEST_CASE( canCreateListOfUncommonElementsInList )
{
    using list_1 = nano::list<nano::int_t<2>, nano::int_t<3>, nano::int_t<7>, nano::int_t<22>>;
    using list_2 = nano::list<nano::int_t<3>, nano::int_t<22>, nano::int_t<14>, nano::int_t<42>>;
    
    // Make a new list of all elements in list 1 that are not in list 2, so those with value 2 and 7
    using uncommon_list = typename nano::find_uncommon<list_1, list_2>::result;
    
    // Get the elements
    using first_type  = nano::get<0, uncommon_list>;
    using second_type = nano::get<1, uncommon_list>;
    
    // Declare variables of these types
    first_type  ft;
    second_type st;
    
    BOOST_CHECK( ft.runtime_value() == 2 );
    BOOST_CHECK( st.runtime_value() == 7 );
}

BOOST_AUTO_TEST_CASE( canCreateListOfUncommonElementIndices )
{
    using list_1 = nano::list<nano::int_t<3>, nano::int_t<2>, nano::int_t<7>, nano::int_t<22>>;
    using list_2 = nano::list<nano::int_t<3>, nano::int_t<22>, nano::int_t<14>, nano::int_t<42>>;
    
    // Make a new list of all elements in list 1 that are not in list 2, so those with value 2 and 7
    using uncommon_indices = typename nano::find_uncommon_indices<list_1, list_2>::result;
    
    // Get the elements
    using first_type  = nano::get<0, uncommon_indices>;
    using second_type = nano::get<1, uncommon_indices>;
    
    // Declare variables of these types
    first_type  ft;
    second_type st;
    
    
    BOOST_CHECK( ft.runtime_value() == 1 );     // 0 element with value 2 in list_1
    BOOST_CHECK( st.runtime_value() == 2 );     // 2 element with value 7 in list_1
}

BOOST_AUTO_TEST_CASE( canGetListProductOfIntList )
{
    using int_list = nano::list<nano::int_t<2>, nano::int_t<4>, nano::int_t<6>>;
    
    // Do multiplication using the default start value of 1
    int default_result = nano::multiplies<int_list>::result;
    
    // Specify a starting value
    int other_result = nano::multiplies<int_list, nano::int_t<2>>::result;
    
    BOOST_CHECK( default_result == 48 );
    BOOST_CHECK( other_result   == 96 );
}

BOOST_AUTO_TEST_CASE( canGetListProductOfSizetList )
{
    using sizet_list = nano::list<nano::size_t<2>, nano::size_t<4>, nano::size_t<6>>;
    
    // Do multiplication using the default start value of 1
    int default_result = nano::multiplies<sizet_list>::result;
    
    // Specify a starting value
    int other_result = nano::multiplies<sizet_list, nano::size_t<2>>::result;
    
    BOOST_CHECK( default_result == 48 );
    BOOST_CHECK( other_result   == 96 );
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------ Function Tests ------------------------------------------------------

BOOST_AUTO_TEST_SUITE( FunctionTestSuite )

BOOST_AUTO_TEST_CASE( canGetSizeOfStruct )
{
    using test_struct = nano::list<nano::int_t<1>, nano::int_t<2>>;
    using size_struct = nano::size_of<test_struct>; 
    // Get size 
    constexpr int struct_size = size_struct::result;
    
    BOOST_CHECK( struct_size == 2 );
}

BOOST_AUTO_TEST_CASE( canMultiplyTwoNanoNumericTypes )
{
    using int_1 = nano::int_t<4>;
    using int_2 = nano::int_t<3>;
   
    int result = nano::multiply<int_1, int_2>::result;
    
    BOOST_CHECK( result == 12 );
}
    
BOOST_AUTO_TEST_SUITE_END()
    
// ------------------------------------ Container Tests ------------------------------------------------------

BOOST_AUTO_TEST_SUITE( ContainerTestSuite )

BOOST_AUTO_TEST_CASE( canCreateRange )
{
    using range = nano::range<-4, 4, 2>::result;         // This makes a range [-4, 4, 2] of nano::int_t types 
                                                        // and the range is just a list of the int_t types
    
    // So we should now have :
    // range = [ -4, -2, 0, 2, 4 ] or list< int_t<-4>, int_t<-2>, ..., int_t<4> >
    
    // Get some of the elements to test
    using range_0_type = nano::get<0, range>;
    using range_2_type = nano::get<2, range>;
    using range_4_type = nano::get<4, range>;
    
    range_0_type range_0;           // Will be nano::int_t< -4 > if correct
    range_2_type range_2;           // Will be nano::int_t<  0 > if correct
    range_4_type range_4;           // Will be nano::int_t<  4 > if correct
    
    // Since these are nano::int_t elements, we can get their runtime values
    BOOST_CHECK( range_0.runtime_value() == -4 );
    BOOST_CHECK( range_2.runtime_value() ==  0 );
    BOOST_CHECK( range_4.runtime_value() ==  4 );
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------- Higher Order Function Tests ----------------------------------------------

BOOST_AUTO_TEST_SUITE( HigherOrderFunctionTestSuite )

BOOST_AUTO_TEST_CASE( zipHigherOrderFunctionWorks )
{ 
    using range_one     = nano::range<-10, 10, 2>::result;          // range of [-10, -8 , ..., 8 , 10 ]
    
    // This will make a list of [ {-10, -10}, {-8, -8}, ..., {10, 10} ]
    // since the equal_value comparator function is used
    using zipped_range  = nano::zip<nano::equal_value, range_one, range_one, nano::empty_list>::result;
    
    // Get the first element in the zipped list which will be list< nano::int_t<-10>, nano::int_t<-10> >
    using first_zipped = nano::get<0, zipped_range>;
    
    // And we can not get the element from the sub list
    using first_zipped_element = nano::get<0, first_zipped>;
    
    // This should be nano::int_t<-10> so we can declare a type like that
    first_zipped_element first_element;
    
    BOOST_CHECK( first_element.runtime_value() == -10 );
}

BOOST_AUTO_TEST_SUITE_END()
    
// --------------------------------- Runtime Converter Tests ------------------------------------------------

BOOST_AUTO_TEST_SUITE( RuntimeConverterTestSuite )
    
BOOST_AUTO_TEST_CASE( canCreateStdVectorFromNanoList )
{
    using int_list = nano::list<nano::int_t<3>, nano::int_t<7>, nano::int_t<12>>;
 
    // Create a runtime vector from the converter
    std::vector<int> test_vector = nano::runtime_converter<int_list>::to_vector();
        
    BOOST_CHECK( test_vector.size() == 3  );
    BOOST_CHECK( test_vector[0]     == 3  );
    BOOST_CHECK( test_vector[1]     == 7  );
    BOOST_CHECK( test_vector[2]     == 12 );
}
    
BOOST_AUTO_TEST_SUITE_END()

