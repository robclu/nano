---
layout: post
title: Numeric Types
---

Defined in ```numeric_types.hpp```

# Contents

* [Types](#types)
* [Attributes](#attributes)
* [Usage](#usage)

# Types

Currently, nano provides the following types 

* ```nano::int_t<int>``` - for integer types
* ```nano::size_t<std::size_t>``` - for size_t types

Additional numeric types such as floats and doubles will be added in the future.

# Attributes

Each ```numeric_type``` has two attributes

* ```type``` - which is the internal type that makes up the type, so ```int``` or ```size_t```
* ```value``` - which is the value which the type holds

# Usage

Declaring a ```numeric_type``` is done as follows

```cpp
// Create a nano integer type
using int_four = nano::int_t<4>;

// Create a nano size type
using sizet_four = nano::size_t<4>;
```

The attributes are accessed through the scope resolution operator, so they can be used to declare types of
their internal types, such as 

```cpp
using int_three = nano::int_t<3>;

// Use the internal int type of the nano::int_t to define an int
int_three::type new_int = 4;
```

or the value of the type can be used, such as

```cpp
using int_three = nano::int_t<3>;

// Use the value of the nano::int_t
if (int_three::value > 2) // Do something
```

