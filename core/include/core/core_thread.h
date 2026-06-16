#ifndef GER_THREAD_H
#define GER_THREAD_H

#include "core_platform.h"

typedef struct ger_thread_pool ger_thread_pool_t;

ger_error_t ger_thread_pool_create(ger_thread_pool_t** out, int num_threads);
void ger_thread_pool_destroy(ger_thread_pool_t* pool);

#endif