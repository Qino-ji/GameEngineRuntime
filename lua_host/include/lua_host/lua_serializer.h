#ifndef LUA_SERIALIZER_H
#define LUA_SERIALIZER_H

#include "lua_host/lua_host.h"
#include <lua.h>

void ger_lua_serializer_init(lua_State* L);
void ger_lua_serializer_push_vec2(lua_State* L, float x, float y);
void ger_lua_serializer_push_rect(lua_State* L, float x, float y, float w, float h);

#endif
