#pragma once

#include <axolote/engine.hpp>

class App : public axolote::Window {
public:
    void main_loop();

private:
    bool is_fill = true;
    void process_input(float dt);
};
