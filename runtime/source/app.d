import api.ger_app;
import api.ger_types;

class MyGame : App {
    override void on_init() {
    }

    override void update(f32 dt) {
    }

    override void render() {
    }
}

void main() {
    auto game = new MyGame();
    game.run("GameEngineRuntime", 800, 600);
}