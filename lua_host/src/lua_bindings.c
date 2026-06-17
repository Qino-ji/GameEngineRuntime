#include "lua_host/lua_bindings.h"
#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>

static int ger_lua_log(lua_State* L) {
    int argc = lua_gettop(L);
    for (int i = 1; i <= argc; ++i) {
        const char* text = lua_tostring(L, i);
        if (text) {
            if (i > 1) printf(" ");
            printf("%s", text);
        }
    }
    if (argc > 0) printf("\n");
    fflush(stdout);
    return 0;
}

static int ger_lua_input_is_key_down(lua_State* L) {
    (void)L;
    lua_pushboolean(L, 0);
    return 1;
}

static int ger_lua_sprite_create(lua_State* L) {
    lua_pushinteger(L, 1);
    return 1;
}

static int ger_lua_sprite_set_pos(lua_State* L) {
    lua_Integer sprite_id = luaL_checkinteger(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    (void)sprite_id;
    (void)x;
    (void)y;
    return 0;
}

static int ger_lua_sprite_set_color(lua_State* L) {
    lua_Integer sprite_id = luaL_checkinteger(L, 1);
    int r = (int)luaL_checkinteger(L, 2);
    int g = (int)luaL_checkinteger(L, 3);
    int b = (int)luaL_checkinteger(L, 4);
    int a = (int)luaL_checkinteger(L, 5);
    (void)sprite_id;
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    return 0;
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
    if (!vm) return;
    lua_State* L = ger_lua_vm_get_state(vm);
    if (!L) return;

    ensure_ger_table(L);
    lua_pushcfunction(L, ger_lua_log);
    lua_setfield(L, -2, "log");
    lua_pushcfunction(L, ger_lua_input_is_key_down);
    lua_setfield(L, -2, "input_is_key_down");
    lua_pushcfunction(L, ger_lua_sprite_create);
    lua_setfield(L, -2, "sprite_create");
    lua_pushcfunction(L, ger_lua_sprite_set_pos);
    lua_setfield(L, -2, "sprite_set_pos");
    lua_pushcfunction(L, ger_lua_sprite_set_color);
    lua_setfield(L, -2, "sprite_set_color");
    lua_pop(L, 1);
}
