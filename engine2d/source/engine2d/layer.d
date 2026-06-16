module engine2d.layer;

import api.ger_types;

struct RenderLayer {
    u8 index;
    bool visible;
    bool locked;
}

struct RenderCommand {
    u8 layer;
    u32 textureHandle;
    u32 vertexOffset;
    u32 indexOffset;
    u32 vertexCount;
    u32 indexCount;
}

struct RenderQueue {
    RenderCommand[256] commands;
    u32 commandCount;

    void begin() {
        commandCount = 0;
    }

    void push(RenderCommand command) {
        if (commandCount >= 256) return;
        commands[commandCount] = command;
        commandCount += 1;
    }

    void sort() {
        for (u32 i = 1; i < commandCount; i += 1) {
            RenderCommand key = commands[i];
            u32 j = i;
            while (j > 0 && commands[j - 1].layer > key.layer) {
                commands[j] = commands[j - 1];
                j -= 1;
            }
            commands[j] = key;
        }
    }
}

unittest {
    RenderQueue queue;
    queue.begin();
    queue.push(RenderCommand(2, 1, 0, 0, 6, 6));
    queue.push(RenderCommand(1, 2, 6, 6, 6, 6));
    queue.sort();
    assert(queue.commands[0].layer == 1);
    assert(queue.commands[1].layer == 2);
}
