module api.ger_script;

import api.ger_types;
import core_sys = core;

extern(C) {
    i32 ger_lua_vm_create(void** out);
    void ger_lua_vm_destroy(void* vm);
    i32 ger_lua_vm_load_string(void* vm, const(char)* source);
    i32 ger_lua_vm_load_file(void* vm, const(char)* path);
    i32 ger_lua_vm_call(void* vm, const(char)* func_name, int nargs, int nresults);
    void ger_lua_vm_push_number(void* vm, f64 val);
    void ger_lua_vm_push_string(void* vm, const(char)* str);
    void ger_lua_vm_register_func(void* vm, const(char)* name, void function() func);
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
        auto err = ger_lua_vm_load_string(_vm, source.ptr);
        assert(err == GER_OK);
    }

    void loadFile(string path) {
        auto err = ger_lua_vm_load_file(_vm, path.ptr);
        assert(err == GER_OK);
    }

    void call(string func) {
        ger_lua_vm_call(_vm, func.ptr, 0, 0);
    }

    void registerFunc(string name, void function() func) {
        ger_lua_vm_register_func(_vm, name.ptr, func);
    }
}