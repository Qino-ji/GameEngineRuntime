#include "core/core_memory.h"
#include <stdlib.h>

#if defined(GER_OS_WIN)
#include <malloc.h>
#endif

void ger_arena_init(ger_arena_t* a, void* buffer, ger_u64 size) {
    a->base = buffer;
    a->capacity = size;
    a->offset = 0;
}

void* ger_arena_alloc(ger_arena_t* a, ger_u64 size, ger_u64 align) {
    ger_u64 mask = align - 1;
    ger_u64 aligned = (a->offset + mask) & ~mask;
    if (aligned + size > a->capacity) return 0;
    void* ptr = (char*)a->base + aligned;
    a->offset = aligned + size;
    return ptr;
}

void ger_arena_reset(ger_arena_t* a) {
    a->offset = 0;
}

void ger_pool_init(ger_pool_t* p, void* buffer, ger_u64 stride, ger_u64 count) {
    p->base = buffer;
    p->stride = stride;
    p->capacity = count;
    p->free_head = 0;
    ger_u32* indices = (ger_u32*)buffer;
    for (ger_u64 i = 0; i < count - 1; i++) {
        indices[i] = (ger_u32)(i + 1);
    }
    indices[count - 1] = (ger_u32)-1;
}

ger_i32 ger_pool_alloc(ger_pool_t* p) {
    if (p->free_head == (ger_u32)-1) return -1;
    ger_i32 idx = (ger_i32)p->free_head;
    ger_u32* indices = (ger_u32*)p->base;
    p->free_head = indices[idx];
    return idx;
}

void ger_pool_free(ger_pool_t* p, ger_i32 index) {
    ger_u32* indices = (ger_u32*)p->base;
    indices[index] = p->free_head;
    p->free_head = (ger_u32)index;
}

void* ger_pool_get(ger_pool_t* p, ger_i32 index) {
    return (char*)p->base + p->stride * index;
}

void* ger_malloc_aligned(ger_u64 size, ger_u64 align) {
    void* ptr = 0;
    if (align < sizeof(void*)) align = sizeof(void*);
#if defined(GER_OS_WIN)
    ptr = _aligned_malloc((size_t)size, (size_t)align);
    return ptr;
#else
    if (posix_memalign(&ptr, (size_t)align, (size_t)size) != 0) return 0;
    return ptr;
#endif
}

void ger_free_aligned(void* ptr) {
    if (!ptr) return;
#if defined(GER_OS_WIN)
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}