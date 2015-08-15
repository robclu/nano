// ----------------------------------------------------------------------------------------------------------
/// @file   nano_tests.cpp
/// @brief  Test suites for the nano library using Bost.Unit.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE       NanoTests
#include <boost/test/unit_test.hpp>

#include <nano/numeric_types.hpp>
#include <nano/functions.hpp>
#include <nano/containers.hpp>

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

BOOST_AUTO_TEST_CASE( canZipListElementsWithEqualityEvaluator )
{ 
}

BOOST_AUTO_TEST_SUITE_END()
