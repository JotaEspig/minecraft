#include <iostream>

#include <axolote/engine.hpp>

#include "app.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    App app{};
    app.main_loop();
    return 0;
}
