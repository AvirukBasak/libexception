#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>

typedef int _ex_sig_t;

typedef struct {
    jmp_buf *v;
    jmp_buf *top;
    int len;
    int cap;
} _exjmpbuf_stack_t;

extern _ex_sig_t _ex_sig;
extern char *_ex_msg;
extern _exjmpbuf_stack_t _exjmpbuf_stack;

jmp_buf *_ex_exjmpbuf_add(void);
jmp_buf *_ex_exjmpbuf_rem(void);

char *_ex_throw_validate_args(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

#define throw(fmt, ...) do {                                                                 \
    _ex_throw_validate_args(fmt, ##__VA_ARGS__);                                             \
    size_t sz = snprintf(NULL, 0, fmt, ##__VA_ARGS__);                                       \
    _ex_msg = (char*) realloc(_ex_msg, sz +1);                                               \
    snprintf(_ex_msg, sz +1, fmt, ##__VA_ARGS__);                                            \
    if (_exjmpbuf_stack.top) {                                                               \
        longjmp(*_exjmpbuf_stack.top, 1);                                                    \
        break;                                                                               \
    }                                                                                        \
    fprintf(stderr, "%s:%s:%d: exception: %s\n", __FILE__, __func__, __LINE__, _ex_msg);     \
    free(_ex_msg);                                                                           \
    abort();                                                                                 \
} while (0);

#define try                                                                                  \
    if (_ex_msg) free(_ex_msg);                                                              \
    _ex_msg = NULL;                                                                          \
    if (!( _ex_sig = setjmp(*_ex_exjmpbuf_add()) ))

#define catch(msg)                                                                           \
    char *msg = _ex_msg;                                                                     \
    _ex_exjmpbuf_rem();                                                                      \
    if (_ex_sig)

#define finally if (1)
