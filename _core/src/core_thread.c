#include "core/core_thread.h"
#include <stdlib.h>

#if defined(GER_OS_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct ger_thread_pool {
    void* threads;
    int count;
    int running;
};

ger_error_t ger_thread_pool_create(ger_thread_pool_t** out, int num_threads) {
    (void)num_threads;
    ger_thread_pool_t* pool = (ger_thread_pool_t*)calloc(1, sizeof(ger_thread_pool_t));
    if (!pool) return GER_ERR_OUT_OF_MEMORY;
    pool->count = 0;
    pool->running = 1;
    *out = pool;
    return GER_OK;
}

void ger_thread_pool_destroy(ger_thread_pool_t* pool) {
    if (!pool) return;
    pool->running = 0;
    free(pool);
}

#else
ger_error_t ger_thread_pool_create(ger_thread_pool_t** out, int num_threads) { (void)num_threads; *out = 0; return GER_ERR_UNSUPPORTED; }
void ger_thread_pool_destroy(ger_thread_pool_t* pool) { (void)pool; }
#endif