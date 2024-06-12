#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"
#include "chunk.hpp"

void App::main_loop() {
    set_vsync(false);
    std::string original_title = title();
    // set window color to white
    set_color(1.0f, 1.0f, 1.0f, 1.0f);

    axolote::gl::Shader shader{
        "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"
    };

    axolote::Camera camera{};
    camera.pos = glm::vec3{(float)CHUNK_XZ_SIZE / 2, (float)CHUNK_Y_SIZE / 2, 100.0f};
    camera.speed = 5.0f;
    camera.sensitivity = 65000.0f;

    auto chunk = std::make_shared<Chunk>();
    std::vector<Block> blocks;
    for (int x = 0; x < CHUNK_XZ_SIZE; ++x) {
        for (int y = 0; y < CHUNK_Y_SIZE; ++y) {
            for (int z = 0; z < CHUNK_XZ_SIZE; ++z) {
                Block block{};
                block.type = y == CHUNK_Y_SIZE - 1 ? Block::Type::Grass
                                                   : Block::Type::Dirt;
                chunk->blocks.blocks[x][y][z] = block;
            }
        }
    }
    chunk->setup_instanced_vbo();
    chunk->bind_shader(shader);

    auto scene = std::make_shared<axolote::Scene>();
    scene->add_drawable(chunk);
    scene->camera = camera;

    double before = get_time();
    set_scene(scene);
    while (!should_close()) {
        // get dt
        double now = get_time();
        double dt = now - before;
        before = now;

        int fps = 1.0 / (dt);
        std::stringstream ss;
        ss << original_title << " | " << fps << " fps";
        set_title(ss.str());

        poll_events();
        process_input(dt);
        clear();

        update(dt);
        update_camera((float)width() / (float)height());
        render();

        flush();
    }
}

void App::process_input(float dt) {
    KeyState polygon_mode = get_key_state(Key::P);
    bool is_pressed = is_key_pressed(Key::P);
    if (polygon_mode == KeyState::PRESSED && !is_pressed) {
        is_fill = !is_fill;
        set_key_pressed(Key::P, true);

        GLint type = is_fill ? GL_FILL : GL_LINE;
        glPolygonMode(GL_FRONT_AND_BACK, type);
    }
    else if (polygon_mode == KeyState::RELEASED && is_pressed) {
        set_key_pressed(Key::P, false);
    }
    Window::process_input(dt);
}
