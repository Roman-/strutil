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

## Quick examples
```cpp
#include <strutil.h>
using namespace strutil;

auto lower = to_lower("HeLLo");                     // "hello"
auto upper = to_upper("hi!");                       // "HI!"
auto parts = split("a,b,c", ',');                   // {"a","b","c"}
auto lines = split_lines_clean(" a \n\nb\r\n c ");  // {"a","b","c"}
auto joined = join(std::vector<int>{1,2,3}, "|");   // "1|2|3"
bool has_sub = contains("radix", "di");             // true
auto shorty = truncate("lorem ipsum dolor", 8, ".."); // "lore.."
auto previewed = preview("bin\0ary", 20);           // "bin\\0ary"
```

## Testing
Testing is done with Google Test library ([link](https://github.com/google/googletest)). 

To build testing for the environment, execute the following CMake commands:
```
mkdir build
cd build
cmake ..
```