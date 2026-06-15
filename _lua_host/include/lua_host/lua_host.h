#ifndef LUA_HOST_H
#define LUA_HOST_H

#include "core/core_platform.h"

typedef struct ger_lua_vm ger_lua_vm_t;

ger_error_t ger_lua_vm_create(ger_lua_vm_t** out);
void ger_lua_vm_destroy(ger_lua_vm_t* vm);
ger_error_t ger_lua_vm_load_string(ger_lua_vm_t* vm, const char* source);
ger_error_t ger_lua_vm_load_file(ger_lua_vm_t* vm, const char* path);
ger_error_t ger_lua_vm_call(ger_lua_vm_t* vm, const char* func_name, int nargs, int nresults);
void ger_lua_vm_set_global(ger_lua_vm_t* vm, const char* name);
void ger_lua_vm_get_global(ger_lua_vm_t* vm, const char* name);
void ger_lua_vm_push_number(ger_lua_vm_t* vm, ger_f64 val);
void ger_lua_vm_push_string(ger_lua_vm_t* vm, const char* str);
void ger_lua_vm_push_light_userdata(ger_lua_vm_t* vm, void* ptr);
void ger_lua_vm_register_func(ger_lua_vm_t* vm, const char* name, void (*func)(void));

#endif