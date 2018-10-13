// Simple Test Framework (testfw)

#ifndef TESTFW_H
#define TESTFW_H

#include <stdbool.h>

#define TESTFW_DEFAULT_SUITE "test"
#define TESTFW_DEFAULT_TIMEOUT 1
#define TESTFW_SEP '.'  // '_' ????

/* ********** TEST FRAMEWORK API ********** */

enum testfw_mode_t
{
    TESTFW_FORK,
    TESTFW_THREAD, // TODO: not yet implemented
    TESTFW_NOFORK
};
typedef int (*testfw_func_t)(int argc, char *argv[]);
struct test_t
{
    char *suite;
    char *name;
    testfw_func_t func;
};

struct testfw_t; /* forward decalaration */

struct testfw_t *testfw_init(char *program, int timeout, char *logfile, bool silent);
void testfw_free(struct testfw_t *fw);
struct test_t *testfw_register_func(struct testfw_t *fw, char *suite, char *name, testfw_func_t func);
struct test_t *testfw_register_symb(struct testfw_t *fw, char *suite, char *name);
int testfw_register_suite(struct testfw_t *fw, char *suite);
void testfw_iterate_all(struct testfw_t *fw, void (*callback)(struct test_t *, void *), void *data);
int testfw_run_all(struct testfw_t *fw, int testargc, char *testargv[], enum testfw_mode_t mode);

#endif