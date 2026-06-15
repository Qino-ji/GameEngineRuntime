#ifndef GER_MEMORY_H
#define GER_MEMORY_H

#include "core_platform.h"

typedef struct {
    void* base;
    ger_u64 capacity;
    ger_u64 offset;
} ger_arena_t;

typedef struct {
    void* base;
    ger_u64 stride;
    ger_u64 capacity;
    ger_u64 free_head;
} ger_pool_t;

void ger_arena_init(ger_arena_t* a, void* buffer, ger_u64 size);
void* ger_arena_alloc(ger_arena_t* a, ger_u64 size, ger_u64 align);
void ger_arena_reset(ger_arena_t* a);

void ger_pool_init(ger_pool_t* p, void* buffer, ger_u64 stride, ger_u64 count);
ger_i32 ger_pool_alloc(ger_pool_t* p);
void ger_pool_free(ger_pool_t* p, ger_i32 index);
void* ger_pool_get(ger_pool_t* p, ger_i32 index);

void* ger_malloc_aligned(ger_u64 size, ger_u64 align);
void ger_free_aligned(void* ptr);

#endif