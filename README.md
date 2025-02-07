# NoCopyVec
This data structure called `NoCopyVec` can be used as the C++'s `std::vector`, *there aren't many methods yet (just the constructor, grow, push, at and destructor)*.

## Principle
The principle is to have a vector of arrays that grow exponentially, which allows you to have a dynamic size, while keeping a get of O(1) and a memory efficiency like that of `std::vector` (75%). But here, the number of operations per push tends towards 1, while std::vector tends towards 3.

The memory representation of this structure having performed 5 pushes is :<br>
`< [ 1 ], [ 2, 3 ], [ 4, 5, undefined, undefined ] >`<br>
Here `< ... >` is the vector containing pointers to static arrays (`[ ... ]`). The structure first fills the last array in the vector before adding a new array to it.

In addition, there is a variant called NoCopyVecPre which pre-allocates memory for the vector containing the array pointers. However, this vector is no longer dynamic, so it's just an array; this doesn't mean that the data structure is no longer dynamic, but it does have a size limit; note that the entire memory is not allocated at initialisation but dynamically to avoid filling memory unnecessarily.

*This implementation uses a base 2 logarithm with a complexity of O(1) thanks to the GCC built-ins __builtin_clz.*

## Why
Performances.<br>
> Debug mode (`-Og`): 65 to 70% faster<br>
> Release mode (`-Ofast`): 45 to 80% faster

Anything else ? No. Performances.

## Usage
Copy `lib.hpp` in your project, the implementation is standalone.

```cpp
// For `printf`
#include <stdio.h>

// Choose the right path, you can rename the lib
#include "lib.hpp"

int main() {
  NoCopyVec<int> vec;

  for (int i = 0; i < 127; i++) {
    vec.push(i);
  }

  for (int i = 0; i < vec.len - 1; i++) {
    int n = vec.at(i);
    printf("vec[%i] -> %i\n", i, n);
  }

  // Thanks to the RAII for automatically destroying `vec`
}
```

## To do
- `iteration`
- `clear`
- `empty`
- `erase`
- `pop`
- `reserve`
- `shrink_to_fit` (very limited)
