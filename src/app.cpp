#include "app.hpp"

void App::main_loop() {
    set_scene(std::make_shared<axolote::Scene>());
    while (!should_close()) {
        poll_events();
        process_input();

        clear();
        flush();
    }
}
