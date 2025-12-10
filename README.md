## strutil
Easy to use, header only C++ 11 std::string utility library. 

Initially forked from shot511/strutil and diverged to improve performance and drop unused features.

## Adding strutil to existing project
Put *strutil.h* in your *include* directory. Then include it:

```cpp
#include <strutil.h>
```

## Example usage
See `tests/test_cases.cpp` file for example usage.

## Testing
Testing is done with Google Test library ([link](https://github.com/google/googletest)). 

To build testing for the environment, execute the following CMake commands:
```
mkdir build
cd build
cmake ..
```