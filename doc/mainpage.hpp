// Main documentatio for Nano

/*!

@mainpage Overview 

@tableofcontents

@section nano-overview Overview 

-------------------------------------------------------------------------------
Nano is a C++ tempalte metaprogramming library which provides a collection of
metaclasses and metafruntions which are designed to mimic the stl classes as 
well as functional programming constructs, but can be executed at compile time
for improved performance. Additionally, some of the functionality I think is
particularly useful for maths and physics, and numerical computation within
each.

__Why Nano?__ 

- Firstly, I created Nano so that I could learn metaprogramming. Once I
started, I realised that there are many similarities between metaprogramming
and functional programming, and then thought that a clean interface for
functional concepts in C++ might be useful. There are a few other really good
metaprogramming libraries out now, but I'm hoping that nano will provide some
additional functionality which is not part of an existing metaprogramming
library.

- Secondly, nano is completely self-standing. It does not rely on any other
libraries, it is very easy to install, and is supported with all major
compilers and for all major operating systems.

- Lastly, to document the process of creating a metaprogramming library.
Initially I found metaprogramming quite difficult, so at the very least nano 
may help someone else grasp the concept more easily than they otherwise would 
have.

@section nano-setup Setup

-------------------------------------------------------------------------------
Nano is header only, and therefore does not have any external dependancies. 
However, the build system and the tests which come with nano do have
dependancies. If you want to run the tests to ensure that nano is working 
correctly, please see the [tests](@ref nano-tests) page which provides a list of 
the prerequisits, how to build them, and how to run the tests. If you just want 
to build and install nano, then follow the steps below.

@subsection nano-build-dependancies Build Dependancies

The following dpendancies are required to build nano (automatically). If you
want to manually install nano (which is simple), then proceed to 
[manual installation](@ref nano-manual-install).

- [Cmake](@ref nano-cmake)

Please make sure to install these before performing the automatic installation.

@subsection nano-compiler-support Compiler and OS Support

Currently, the following compilers have been tested;

Compiler                     |  OS        |Status 
-----------------------------|------------|------------------------------------
g++ (>=5.3, C++11,14))       | linux, osx | Fully supported
clang++ (>=3.7 C++11,14)     | linux, osx | Fully supported (fastest compile times)
msvc (>=14. C++11,14)        | windows    | Not supported (testing soon)

@subsection nano-installation Installation

To install nano, since it is header only, you just need to make sure that the 
headers are on your ```PATH``` You can do this with either of the following two 
methods. 

@subsubsection nano-manual-install Manual Installation

To install nano manually, simply copy the contents of ```/include``` to the
directory of your choosing, and then add the directory to your ```PATH```.

@subsubsection nano-auto-install Automatic Installation

You can also install nano using Cmake. If you do not have Cmake, see 
[Cmake](@ref nano-cmake) for how to get and install it. To build and then 
install nano, create a build directory in the nano root folder, change into the
build directory and then build using Cmake, as follows:

@code{.sh} 
  mkdir build # md build for windows
  cd build
  cmake .. 
  cmake --build . --target install
@endcode

Which will build to the default install directory of the platform
(```/usr/local``` for Unix and ```C:\Program Files``` for Windows).

Alternatively, if you do not want to use the default install directory, and
would rather specify your own, then build using Cmake as follows:

@code{.sh} 
  mkdir build # md build for windows
  cd build
  cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/desired/install/directory
  cmake --build . --target install
@endcode

@note 
If you install to a a directory other than the default, make sure that the
directory is either on your ```PATH```, or that when you compile
you add the ```-I /path/to/desired/install/directory``` flag.

@section nano-design-goals Design Goals

-------------------------------------------------------------------------------
While at the moment nano provides some of the std library functionality in a
compile-time capable format, as well as some functional concepts within C++, in
the long term I would like to either use nanofor , or integrate into nano, an
interface for parallelism which supports multiple compute targets
(muli-core CPU, GPU) and can eleminate most of the complexities which
programmers in such a domain face.


@section nano-primitives Primitive Types

-------------------------------------------------------------------------------
Nano provides its own versions of traditional C++ primitive types which can be
used at both compile time and runtime. The following table defines all the nano
primitive types (in the following table, ```x``` represents a value):

Nano Type                                 | C++ version
------------------------------------------|--------------
[nano::int<x>](@ref nano-int)             | int 
[nano::size_t<x>](@ref nano-size_t)       | size_t

@note 
The following sections are simply to illustrate how to access the
components of the primitive types, not to show their ideal usage -- which is
shown later.

@subsection nano-int nano::int<x>

A ```cpp nano::int<x>``` provides an integer expression, with the value
```x```, to be used at either compile time or runtime. The attributes of 
```nano::int<x>``` can be accessed as follows:

@code{.cpp}
  //  Create a nano int with a value of 4 
  using nano_int_4 = nano::int<4>;

  // Access the type through ::type and value through ::value
  typename nano_int_4::type example_int = nano_int_4::value;
@endcode

@subsection nano-size_t nano::size_t<x>

A ```nano::size_t<x>``` provides a ```size_t```, with a type ```size_t```
and  a value ```x```, to be used at either compile time or runtime. The 
attributes of ```nano::size_t<x>``` can be accessed as follows:

@code{.cpp}
  //  Create a nano int with a value of 4 
  using nano_sizet_4 = nano::size_t<4>;

  // Access the type through ::type and value through ::value
  typename nano_sizet_4::type example_sizet = nano_sizet_4::value;
@endcode


*/

// ----------------------------------------------------------------------------

/*!
 
@page nano-prereqs Pre-requisits

@tableofcontents 

@section nano-boost-unit Boost.Unit

-------------------------------------------------------------------------------

Boost.Unit is the testing library used to run the tests provided with nano.
The tests link dynamically with Boost.Unit, so you will need to install the
headers, as well as the libraries for boost.

Boost can be found [here](http://www.boost.org/users/download/). Fllow the 
[getting started](http://www.boost.org/doc/libs/1_60_0/more/getting_started/index.html)
guide to install boost.

@section nano-cmake CMake

*/

/*!
 
@page nano-tests Tests

@tableofcontents 

*/