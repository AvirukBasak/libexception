#include "exception.h"

_exception_stack_t _exception_stack = { NULL, NULL, NULL, 0, 0 };
int _ex_cnt = 0;

_exception_t *_exception_stack_push(void) {
    if (_exception_stack.len >= _exception_stack.cap) {
        _exception_stack.cap = _exception_stack.cap * 2 + 1;
        _exception_stack.v = realloc(_exception_stack.v, _exception_stack.cap * sizeof(_exception_t));
    }
    _exception_stack.top = &_exception_stack.v[_exception_stack.len++];
    _exception_stack.top->msg = NULL;
    _exception_stack.top->sig = 0;
    return _exception_stack.top;
}

_exception_t *_exception_stack_pop(void) {
    if (!_exception_stack.len) return NULL;
    _exception_t *ex = _exception_stack.top;
    _exception_stack.free_top = _exception_stack.top +1;
    if (! (--_exception_stack.len) ) _exception_stack.top = NULL;
    else --_exception_stack.top;
    ++_ex_cnt;
    if (_ex_cnt >= 2) {
        if (_exception_stack.free_top->msg) free(_exception_stack.free_top->msg);
        _exception_stack.free_top->msg = NULL;
    }
    return ex;
}

char *_ex_throw_validate_args(const char* fmt, ...) { return (char*) fmt; }
