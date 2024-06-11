#include "app.hpp"

void App::main_loop() {
    // set window color to white
    set_color(1.0f, 1.0f, 1.0f, 1.0f);

    axolote::gl::Shader shader{
        "resources/shaders/def_vertex_shader.glsl",
        "resources/shaders/def_fragment_shader.glsl"
    };

    axolote::Camera camera{};
    camera.pos = glm::vec3{0.0f, 0.0f, 3.0f};
    camera.speed = .1f;
    camera.sensitivity = 50.0f;

    auto cube = std::make_shared<axolote::GModel>(
        "resources/models/cube.obj", glm::vec3{1.0f, 1.0f, 1.0f}
    );
    cube->bind_shader(shader);

    auto scene = std::make_shared<axolote::Scene>();
    scene->add_drawable(cube);
    scene->camera = camera;

    set_scene(scene);
    while (!should_close()) {
        poll_events();
        process_input();
        clear();

        update(1);
        update_camera((float)width() / (float)height());
        render();

        flush();
    }
}
