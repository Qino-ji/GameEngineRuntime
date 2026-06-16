#include "lua_host/lua_serializer.h"

void ger_lua_serializer_init(lua_State* L) {
    lua_newtable(L);
    lua_setglobal(L, "ger");
}

void ger_lua_serializer_push_vec2(lua_State* L, float x, float y) {
    lua_newtable(L);
    lua_pushnumber(L, x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, y);
    lua_setfield(L, -2, "y");
}

void ger_lua_serializer_push_rect(lua_State* L, float x, float y, float w, float h) {
    lua_newtable(L);
    lua_pushnumber(L, x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, w);
    lua_setfield(L, -2, "w");
    lua_pushnumber(L, h);
    lua_setfield(L, -2, "h");
}
