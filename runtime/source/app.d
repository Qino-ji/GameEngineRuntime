import api.ger_app;
import api.ger_script;
import api.ger_types;
import std.file : exists;

class MyGame : App {
    private ScriptEngine scripts;

    override void on_init() {
        scripts = new ScriptEngine();
        if (exists("assets/scripts/main.lua")) {
            scripts.loadFile("assets/scripts/main.lua");
        } else {
            scripts.loadFile("runtime/assets/scripts/main.lua");
        }
        scripts.call("init");
    }

    override void update(f32 dt) {
        if (scripts) {
            scripts.callNumber("update", dt);
        }
    }

    override void render() {
    }
}

void main() {
    auto game = new MyGame();
    game.run("GameEngineRuntime", 800, 600);
}
