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
        "resources/shaders/def_vertex_shader.glsl",
        "resources/shaders/def_fragment_shader.glsl"
    };

    axolote::Camera camera{};
    camera.pos = glm::vec3{4.5f, 4.5f, 25.0f};
    camera.speed = 5.0f;
    camera.sensitivity = 65000.0f;

    auto chunk = std::make_shared<Chunk>();
    std::vector<Block> blocks;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            for (int z = 0; z < 10; z++) {
                blocks.push_back(
                    {glm::translate(glm::mat4{1.0f}, glm::vec3{x, y, z}),
                     glm::vec3{(float)x / 10, (float)y / 10, (float)z / 10}}
                );
            }
        }
    }
    chunk->set_blocks(blocks);
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
