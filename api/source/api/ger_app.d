module api.ger_app;

import api.ger_window;
import api.ger_input;
import api.ger_types;
import core.thread : Thread;
import std.datetime : dur;

abstract class App {
    protected Window window;
    protected Input input;
    protected bool running;

    abstract void on_init();
    abstract void update(f32 dt);
    abstract void render();

    void run(string title, int width, int height) {
        window = new Window(title, width, height);
        input = new Input();
        running = true;
        on_init();

        while (running) {
            if (window.shouldClose()) break;
            input.beginFrame();
            window.pollEvents();
            update(0.016f);
            render();
            input.endFrame();
            Thread.sleep(dur!"msecs"(1));
        }
    }

    void quit() { running = false; }
}