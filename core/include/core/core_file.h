#ifndef GER_FILE_H
#define GER_FILE_H

#include "core_platform.h"

ger_error_t ger_file_read_all(const char* path, void** out_data, ger_u64* out_size);
void ger_file_free(void* data);

#endif