# libexception
Static library to facilitate exception handling in C.

## Demo
```c
#include "exception.h"

void foo() {
    throw("ERRCODE_%d", 5);
}

int main() {
    try {
        try {
            foo();
        } catch (ex) {
            throw("THROW_%s", ex);
        }
    } catch (ex) {
        printf("%s\n", ex);
    }
}
```
