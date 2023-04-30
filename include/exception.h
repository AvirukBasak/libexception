#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>

typedef int ex_sig_t;

typedef struct {
    char *msg;
    ex_sig_t sig;
    jmp_buf buf;
} _exception_t;

typedef struct {
    _exception_t *v;
    _exception_t *top;
    _exception_t *free_top;
    int len;
    int cap;
} _exception_stack_t;

extern _exception_stack_t _exception_stack;

_exception_t *_exception_stack_push(void);
_exception_t *_exception_stack_pop(void);

char *_ex_throw_validate_args(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

#define throw(fmt, ...) do {                                                                 \
    _ex_throw_validate_args(fmt, ##__VA_ARGS__);                                             \
    size_t sz = snprintf(NULL, 0, fmt, ##__VA_ARGS__);                                       \
    char *msg = (char*) malloc(sz +2);                                                       \
    snprintf(msg, sz +1, fmt, ##__VA_ARGS__);                                                \
    if (_exception_stack.top) {                                                              \
        _exception_stack.top->msg = msg;                                                     \
        longjmp(_exception_stack.top->buf, _exception_stack.top->sig = 1);                   \
        break;                                                                               \
    }                                                                                        \
    fprintf(stderr, "%s:%s:%d: exception: %s\n", __FILE__, __func__, __LINE__, msg);         \
    free(msg);                                                                               \
    abort();                                                                                 \
} while (0);

#define try                                                                                  \
    _exception_stack_push();                                                                 \
    if (!(_exception_stack.top->sig = setjmp(_exception_stack.top->buf)))

#define catch(e)                                                                             \
    char *e = _exception_stack.top->msg;                                                     \
    if (_exception_stack_pop()->sig)

#define finally if (1)
