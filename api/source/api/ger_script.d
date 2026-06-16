module api.ger_script;

import api.ger_types;
import std.string : toStringz;

extern(C) {
    alias LuaCCallback = extern(C) void function();

    i32 ger_lua_vm_create(void** output);
    void ger_lua_vm_destroy(void* vm);
    i32 ger_lua_vm_load_string(void* vm, const(char)* source);
    i32 ger_lua_vm_load_file(void* vm, const(char)* path);
    i32 ger_lua_vm_call(void* vm, const(char)* func_name, int nargs, int nresults);
    void ger_lua_vm_push_number(void* vm, f64 val);
    void ger_lua_vm_push_string(void* vm, const(char)* str);
    void ger_lua_vm_register_func(void* vm, const(char)* name, LuaCCallback func);
}

class ScriptEngine {
    private void* _vm;

    this() {
        auto err = ger_lua_vm_create(&_vm);
        assert(err == GER_OK);
    }

    ~this() {
        if (_vm) ger_lua_vm_destroy(_vm);
    }

    void loadString(string source) {
        auto err = ger_lua_vm_load_string(_vm, source.toStringz);
        assert(err == GER_OK, "Lua string load failed");
    }

    void loadFile(string path) {
        auto err = ger_lua_vm_load_file(_vm, path.toStringz);
        assert(err == GER_OK, "Lua file load failed");
    }

    void call(string func) {
        auto err = ger_lua_vm_call(_vm, func.toStringz, 0, 0);
        assert(err == GER_OK, "Lua function call failed");
    }

    void registerFunc(string name, LuaCCallback func) {
        ger_lua_vm_register_func(_vm, name.toStringz, func);
    }
}