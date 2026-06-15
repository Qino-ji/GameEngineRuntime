#include "core/core_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ger_error_t ger_file_read_all(const char* path, void** out_data, ger_u64* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return GER_ERR_NOT_FOUND;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) { fclose(f); return GER_ERR_IO; }
    void* buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return GER_ERR_OUT_OF_MEMORY; }
    size_t read = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if ((long)read != sz) { free(buf); return GER_ERR_IO; }
    ((char*)buf)[sz] = 0;
    *out_data = buf;
    if (out_size) *out_size = (ger_u64)sz;
    return GER_OK;
}

void ger_file_free(void* data) {
    free(data);
}