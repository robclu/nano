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
