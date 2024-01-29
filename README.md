## strutil
Easy to use, header only C++ 11 std::string utility library. 

Initially forked from shot511/strutil and diverged to

## Features
- [x] Generic parsing methods - from std::string and to std::string.
- [x] Splitting std::string to tokens with user defined delimiter (useful for CSV parsing).
- [x] Replace a substring with another substring.
- [x] Text manipulation functions: *repeat* (char or std::string), *to_lower*, *to_upper*, *trim* (also in-place).
- [x] Checks: *contains*, *starts_with*, *ends_with*, *matches*.
- [x] Compare two std::string with their case ignored. 
- [x] Header only library - no building required.
- [x] Does not require any dependencies.

## Adding strutil to existing project
Simply put *strutil.h* in your *include* directory. Then, in C++ file include it:

```cpp
#include <strutil.h>
```

## Example usage
See **tests/test_cases.cpp** file for example usage.

## Testing
strutil supports Google Test library ([link](https://github.com/google/googletest)). 

To build testing environment execute the following CMake commands:

```
mkdir build
cd build
cmake ..
```