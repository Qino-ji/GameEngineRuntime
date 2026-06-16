#include "lua_host/lua_host.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

struct ger_lua_vm {
    lua_State* L;
};

ger_error_t ger_lua_vm_create(ger_lua_vm_t** out) {
    ger_lua_vm_t* vm = (ger_lua_vm_t*)calloc(1, sizeof(ger_lua_vm_t));
    if (!vm) return GER_ERR_OUT_OF_MEMORY;
    vm->L = luaL_newstate();
    if (!vm->L) { free(vm); return GER_ERR_OUT_OF_MEMORY; }
    luaL_openlibs(vm->L);
    *out = vm;
    return GER_OK;
}

void ger_lua_vm_destroy(ger_lua_vm_t* vm) {
    if (!vm) return;
    if (vm->L) lua_close(vm->L);
    free(vm);
}

ger_error_t ger_lua_vm_load_string(ger_lua_vm_t* vm, const char* source) {
    if (luaL_loadstring(vm->L, source) != LUA_OK) return GER_ERR_UNKNOWN;
    if (lua_pcall(vm->L, 0, LUA_MULTRET, 0) != LUA_OK) return GER_ERR_UNKNOWN;
    return GER_OK;
}

ger_error_t ger_lua_vm_load_file(ger_lua_vm_t* vm, const char* path) {
    if (luaL_loadfile(vm->L, path) != LUA_OK) return GER_ERR_NOT_FOUND;
    if (lua_pcall(vm->L, 0, LUA_MULTRET, 0) != LUA_OK) return GER_ERR_UNKNOWN;
    return GER_OK;
}

ger_error_t ger_lua_vm_call(ger_lua_vm_t* vm, const char* func_name, int nargs, int nresults) {
    lua_getglobal(vm->L, func_name);
    if (!lua_isfunction(vm->L, -1)) {
        lua_pop(vm->L, 1);
        return GER_ERR_NOT_FOUND;
    }
    int base = lua_gettop(vm->L) - nargs;
    lua_insert(vm->L, base);
    if (lua_pcall(vm->L, nargs, nresults, 0) != LUA_OK) return GER_ERR_UNKNOWN;
    return GER_OK;
}

void ger_lua_vm_set_global(ger_lua_vm_t* vm, const char* name) {
    lua_setglobal(vm->L, name);
}

void ger_lua_vm_get_global(ger_lua_vm_t* vm, const char* name) {
    lua_getglobal(vm->L, name);
}

void ger_lua_vm_push_number(ger_lua_vm_t* vm, ger_f64 val) {
    lua_pushnumber(vm->L, val);
}

void ger_lua_vm_push_string(ger_lua_vm_t* vm, const char* str) {
    lua_pushstring(vm->L, str);
}

void ger_lua_vm_push_light_userdata(ger_lua_vm_t* vm, void* ptr) {
    lua_pushlightuserdata(vm->L, ptr);
}

void ger_lua_vm_register_func(ger_lua_vm_t* vm, const char* name, void (*func)(void)) {
    lua_register(vm->L, name, (lua_CFunction)func);
}