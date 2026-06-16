#include "lua_host/lua_bindings.h"
#include <lua.h>
#include <lauxlib.h>

static int ger_lua_log(lua_State* L) {
    int argc = lua_gettop(L);
    for (int i = 1; i <= argc; ++i) {
        const char* text = lua_tostring(L, i);
        if (text) {
            if (i > 1) {
                // Keep the binding lightweight; callers can concatenate in Lua.
            }
        }
    }
    return 0;
}

static int ger_lua_input_is_key_down(lua_State* L) {
    (void)L;
    lua_pushboolean(L, 0);
    return 1;
}

static void ensure_ger_table(lua_State* L) {
    lua_getglobal(L, "ger");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, "ger");
    }
}

void ger_lua_bind_register_all(ger_lua_vm_t* vm) {
    if (!vm || !vm->L) return;
    lua_State* L = vm->L;

    ensure_ger_table(L);
    lua_pushcfunction(L, ger_lua_log);
    lua_setfield(L, -2, "log");
    lua_pushcfunction(L, ger_lua_input_is_key_down);
    lua_setfield(L, -2, "input_is_key_down");
    lua_pop(L, 1);
}
