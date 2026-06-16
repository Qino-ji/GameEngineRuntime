import api.ger_app;
import api.ger_types;

class ClearScreenGame : App {
    override void on_init() {}
    override void update(f32 dt) {}
    override void render() {}
}

void main() {
    auto game = new ClearScreenGame();
    game.run("Clear Screen", 800, 600);
}
