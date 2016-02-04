// Main documentatio for Nano

/*!

@mainpage Overview 

@tableofcontents

@section nano-overview Overview 

-------------------------------------------------------------------------------
Nano is a C++ tempalte metaprogramming library which provides a collection of
metaclasses and metafruntions which are designed to mimic the stl classes as 
well as functional programming constructs, but can be executed at compile time
for improved performance.

__Why Nano? :__ 

- Firstly, I created Nano so that I could learn metaprogramming. Once I
started, I realised that there are many similarities between metaprogramming
and functional programming, and then thought that a clean interface for
functional concepts in C++ might be useful.

- Secondly, to document the process of creating a metaprogramming library.
Initially I found it quite difficult, so at the very least this may help
someone else grasp the concept more easily than they otherwise would have.

@section nano-setup Setup 

__Nano__ is header only and can be built very simply, without any external
dependancies. However, the tests which come with __nano__ require prerequisits.
If you want to run the tests to ensure that __nano__ is working correctly,
please see the [prerequisits](@ref nano-prerequisits) section.

@subsection nano-prerequisits Prerequisits

@subsubsection nano-boost-unit Boost.Unit [Testing Only]

Boost.Unit is the testing library used to run the tests provided with __nano__.
The tests link dynamically with Boost.Unit. To install the tests first download
and install Boost.

... Rest to follow ...

@subsubsection nano-cmake CMake

@subsection nano-compiler-support Compiler and OS Support

Currently, the following compilers have been tested;

Compiler                     |  OS        |Status 
-----------------------------|------------|------------------------------------
g++ (>=5.3, C++11,14))       | linux, osx | Fully supported
clang++ (>=3.7 C++11,14)     | linux, osx | Fully supported (fastest compile times)
msvc (>=14. C++11,14)        | windows    | Not supported (testing soon)

@subsection nano-installation

To install __nano__, you just need to make sure that the headers are on your
`PATH`. 

@subsubsection nano-manual-install Manual Installation

To install __nano__ manually, simply copy the contents of `/include` to the
directory of our choosing, and then add the directory to your `PATH`.

@subsubsection nano-auto-install Automatic Installation

You can also install __nano__ using CMake. If you do not have CMake, see [CMake
prerequisit](@ref nano-cmake). If you do have CMake, then you can perform an
out-of-source build.

First create a build directory, and change into the directory:

__Linux or OSX:__ @code{.sh} mkdir build && cd build@endcode
__Windows:__ @code{.sh} md build && cd build @endcode

*/

 