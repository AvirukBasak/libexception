#include "exception.h"

void foo() {
    throw("ERRCODE_%d", 5);
}

int main() {
    try {
        foo();
    } catch (e) {
        printf("%s\n", e);
        free(e);
    }
}
