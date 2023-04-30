#include "exception.h"
#include <assert.h>

void foo() {
    throw("ERRCODE_%d", 5);
}

void test() {
    try {
        try {
            foo();
        } catch (ex) {
            throw("THROW_%s", ex);
        }
    } catch (ex) {
        printf("%s\n", ex);
    }
    try {
        // Push an exception
        throw("test exception");
    } catch (ex2) {
        // Pop the exception and check the message
        assert(strcmp(ex2, "test exception") == 0);
    }
    try {
        // Push more exceptions than the initial capacity of the stack
        for (int i = 0; i < 100; i++) {
            throw("test exception");
        }
    } catch (ex3) {
        // Pop the exception and check the message
        assert(strcmp(ex3, "test exception") == 0);
    }
    try {
        // Push an exception
        throw("test exception");
    } catch (ex4) {
        // Pop the exception
        _exception_stack_pop();
        // Try to pop an empty stack and assert that it returns NULL
        assert(_exception_stack_pop() == NULL);
    }
    try {
        // Push an exception
        throw("test exception");
    } catch (ex5) {
        // Pop the exception
        _exception_stack_pop();
        // Pop another exception to trigger the message free
        throw("another exception");
    }
}

int main() {
    test();
}
