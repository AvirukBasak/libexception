#include "exception.h"

_ex_sig_t _ex_sig = 0;
char *_ex_msg = NULL;
_exjmpbuf_stack_t _exjmpbuf_stack = { NULL, NULL, 0, 0 };

jmp_buf *_ex_exjmpbuf_add(void) {
    if (_ex_msg) free(_ex_msg);
    if (_exjmpbuf_stack.len >= _exjmpbuf_stack.cap) {
        _exjmpbuf_stack.cap = _exjmpbuf_stack.cap * 2 + 1;
        _exjmpbuf_stack.v = realloc(_exjmpbuf_stack.v, _exjmpbuf_stack.cap * sizeof(jmp_buf));
    }
    jmp_buf *buf_ptr = &(_exjmpbuf_stack.v[_exjmpbuf_stack.len++]);
    _exjmpbuf_stack.top = buf_ptr;
    return _exjmpbuf_stack.top;
}

jmp_buf *_ex_exjmpbuf_rem(void) {
    if (!_exjmpbuf_stack.len) return NULL;
    jmp_buf *buf_ptr = &(_exjmpbuf_stack.v[--_exjmpbuf_stack.len]);
    _exjmpbuf_stack.top = buf_ptr;
    return _exjmpbuf_stack.top;
}

char *_ex_throw_validate_args(const char* fmt, ...) { return (char*) fmt; }
