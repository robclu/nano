---
layout: post
title: Lists
---

Defined in ```list.hpp```

This page gives an introduction to the ```nano::list``` type, see the examples and usage main page for all
functionality.

# Contents

* [Introduction](#introduction)
* [List Size](#list-size)
* [Get](#get)

# Introduction

Lists are the building block for everything that is nano. They are based off of what Alexandrescu calls *typelists* in  [Modern C++ Design](http://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315), with slightly extended functionality.

The basis of the ```nano::list``` is that it hold types, these can be types such as ```int, double, float
..```, or with the [numeric types](/nano/usage/numeric_types) defined by nano such as ```nano::int_t<> and
nano::size_t<>``` -- which enable much more powerful metaprogramming.

Declaring lists is simple, for example, using a ```nano::list``` as a typelist can be done as follows:

```cpp
using typelist = nano::list<int, float, double>;
```

But to really get the full functionality of nano, the numeric types should be used to create value lists, such
as 

```cpp
using int_list = nano::list<nano::int_t<1>, nano::int_t<2>, nano::int_t<4>>;
```

# List Size

Lists have size functionality, which is returned as ```std::size_t```, the size of a list can be determined as
follows:

```cpp
using int_list = nano::list<nano::int_t<1>, nano::int_t<2>, nano::int_t<4>>;

// Get the size of the list
std::size_t list_size = int_list::size;

// list_size = 3 
```

# Get

Nano provides the ```get``` function for gettting the value of a list element at a specific index. For
example

```cpp
using sizet_list = nano::list<nano::size_t<1>, nano::size_t<2>, nano::size_t<4>>;

// Get the first element of the list
using first_element = nano::get<0, sizet_list>;

// first_element = nano::size_t<1>;
```

