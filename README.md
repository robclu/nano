*Nano is a small C++ template metaprogramming libray*

# Nano

This library provides a collection of metaclasses and metafunctions, which are hopefully useful.

There are numerous other (better) metaprogramming libraries such as [Boost.MPL](http://www.boost.org/doc/libs/1_58_0/libs/mpl/doc/index.html), [Meta](https://github.com/ericniebler/meta), and [Turbo](https://github.com/Manu343726/Turbo), which is where I learnt tmp - by browsing through the code.

Most of the functionality at the moment is functionality I have needed for some other project I've been doing, which I then generalized on the off chance someone else may find it useful.

I've also tried to document the code well enough for others to learn from, since the learning curve for tmp can be steep. Additionally I have provided a test file using the [Boost Test library](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html), which should help to see how the library can be used with runtime code.

# Install 

*nano* is a header only library, so to use it you just need to include the header file:
```.cpp
#include "nano/nano.hpp"
```
so long as the dirctory is in your ```$PATH```. 

A Makefile is provided to install *nano* to ```/usr/local``` (all this does is move the ```nano``` folder to ```/usr/local``` which you can change by changing the ```INSTALL_DIR``` variable in the Makefile). Make sure to change it to a directory which is on your ```$PATH```, or add it to your ```$PATH```.

To install *nano* run:

```
sudo make install
```
You cna __uninstall__ nano as follows:
```
sudo make uninstall
```

## Compilers

*Nano* has been tested with the following compilers on ubuntu 15.04:

* g++ - version 4.9.1
* clang++ - version 3.6.1
* 
I haven't tested it on Windows yet, however, I would expect it would work.

## Tests

To run the test file you'll need to install the boost libraries from [Boost](http://www.boost.org/) and install the test library (the test file dynamically links the test library, so you'll actually have to install the library and not just include the header file).

Then you will need to install *nano* __before__ running the test suite - see [Install](#install) above.

Then you can run the tests with:

```
make                    # builds then runs
                        # or
make build_and_run      # builds then runs
```
or by
```
make build              # only builds
./nano_test_suite       
```

# Usage

The main component of the library is the ```list``` struct, which, in its most basic form, just holds a lists of types. It is what *Alexandrescu* calls a *typelist* in his book [Modern C++ Design](http://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315). 
Nano defines numeric types, which can be used as compile-time constants through the ```value``` parameter, and the
runtime values can be used through the ```runtime_value()``` function after defining an instance. 

The following types are currently available

* ```nano::int_t```
* ```nano::size_t```

```.cpp
using example_int  = nano::int_t<4>;
using example_size = nano::size_t<12>;

// Get the compile time value of the numeric type
using new_int = nano::int_t<example_int::value>;

// And the runtime values can ge used
example_int nano_int_instance;

int runtime_int = nano_int_instance.runtime_value();
```

## Functions 

Nano provides numerous compile times functions.

#### Multiplication

```.cpp
using int_1 = nano::int_t<4>;
using int_2 = nano::int_t<2;

int result = nano::multiply<int_1, int_2>::result;      // result is 8
```

## Lists

It is important to note that lists hold __types__, and __types__ can be mixed in the list, such as:
```.cpp
using list_example = nano::list<int, float, double>;
```
which may seem inconvienient as the list does not have any values. To overcome this, *nano* defines 'constant' types, which are wrappers around ```int``` and ```size_t``` from the standard library. Using the nano constant types, compile time constants can be defined:
```.cpp
using int_four = nano::int_t<4>;
using int_zero = nano::int_t<0>;
```
These values of the constant types can be used at both compile time and run time:
```.cpp
nano::int_t<VALUE>::value           // Gets the value of the int at compile time

using int_two = nano::int_t<2>;

int_two i2;                         // Declare variable of type nano::int_t<2>

// Now we can use the variable at runtime 
if (i2.runtime_value() == 2) {
  // Evaluates to true 
}
```
The constant types are more useful when used with lists, since now we can create a list of 'values' rather than just types:
```.cpp
using int_list = nano::list<nano::int_t<1>, nano::int_t<2>, nano::int_t<3>>;    // List of 3 elements
```
#### List Size

Nano defines a size parameter as part of a list, which can be used as follows
```.cpp
using example_list = nano::list<nano::int_t<2>, nano::int_t<4>>;

// The size of the list can be used as a variable
std::size_t list_size = example_list::size;

// Or as a condition
if (example_list::size > 0 ) {
    // ...
}

// And can also be used as a compile-time constant,
// for example to make a nano:range
using range = nano::range<0, example_list::size, 1>::result;
```

#### Finding Types
 
A list can be searched by type to get the type's index in the list. These types can be nano numeric types 
such as ```nano::int_t``` and ```nano::size_t``` so if you have a list of nano compile time ints for example,
then elements can be found like
```.cpp
// Create a test list
using test_list = nano::list<nano::size_t<2>, nano::size_t<4>, nano::int_t<6>>;
    
// This will return the index of nano::int_t<2> elements
std::size_t size_two_index  = nano::find_type<nano::size_t<2>, test_list>::result;  // = 0
```

#### Multiplies

The multiplies functions is the same as std::multiplies -- it multiplies all the elements of the list. It
needs a list and a starting value. If no starting value is given then 1 is used. Currently the multiplies
function supports the following types

* ```nano::int_t```
* ```nano::size_t```

To multiply all elements with a starting value of 1, you can do the following

```.cpp
using two  = nano::int_t<2>;
using four = nano::int_t<4>;
using six  = nano::int_t<6>;

using int_list = nano::list<two, four, siz>;

// result has a value of 48
int result = nano::multiplies<int_list>::result;
```

Or to start the multiplication from a different value

```.cpp
using two  = nano::int_t<2>;
using four = nano::int_t<4>;
using six  = nano::int_t<6>;

using int_list = nano::list<two, four, siz>;

// result has a value of 96, since the multiplication 
// started from a value of 2
int result = nano::multiplies<int_list, two>::result;
```

#### Runtime Conversion

```Nano``` provides a conversion class to allow nano containers (currently only lists) to be converted to
runtime containers. At present, the supported runtime containers are:

* ```std::array```
* ```std::vector```

Additionally, ```nano``` uses the types of the 'elements' in the list which is being converted, to determine
the types of the elements in the ```std::``` container. Also types which are supported by ```nano``` can be
used in the ```std::``` containers, which are:

* ```int```
* ```size_t```

```nano``` now also supports ```std``` containers inside of ```std::``` containers -- to allow N dimensional
containers -- such as:

* ```std::array<std::array<typename X, N> M>```
* ```std::vector<std::vector<typename X>>```

So both static and dynamic multi-dimensional containers can be created.

__Converting to a Runtime Array or Vector (Single Dimension):__

```.cpp

// Create a nano::list with 3 integer types
using int_list = nano::list<nano::int_t<3>, nano::int_t<7>, nano::int_t<12>>;
    
// Create a runtime containers
auto vector = nano::runtime_converter<int_list>::to_vector();
auto array  = nano::runtime_converter<int_list>::to_array();

// vector is now:
// std::vector<int>{3, 7, 12};

// array is now
// std::array<int, 3>{3, 7, 12};

```

__Converting to a Runtime Array or Vector (Multi Dimension):__

```.cpp

// Create a nano::list with 3 integer types
using list_one = nano::list<nano::int_t<3>, nano::int_t<7>, nano::int_t<12>>;
using list_two = nano::list<nano::int_t<6>, nano::int_t<14>, nano::int_t<24>>;

// Make a list of lists
using list_of_lists = nano::list<list_one, list_two>;
    
// Create a runtime containers
auto vector = nano::runtime_converter<list_of_lists>::to_vector();
auto array  = nano::runtime_converter<list_of_lists>::to_array();

// vector is now:
// std::vector<std:vector<int}>{ {3, 7, 12}, {6, 12, 24} };

// array is now
// std::array<std::array<int, 3>, 2>{ {3, 7, 12}, {6, 12, 24} };
```

