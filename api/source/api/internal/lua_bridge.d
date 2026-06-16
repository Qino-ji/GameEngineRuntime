module api.internal.lua_bridge;

import api.ger_script : ScriptEngine;

class LuaBridge {
    private ScriptEngine engine;

    this() {
        engine = new ScriptEngine();
    }

    ~this() {
        engine = null;
    }

    void loadString(string source) {
        engine.loadString(source);
    }

    void loadFile(string path) {
        engine.loadFile(path);
    }

    void call(string func) {
        engine.call(func);
    }

    void bindBuiltinApi() {
        engine.bindBuiltinApi();
    }
}
