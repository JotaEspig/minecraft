#pragma once

#include <glm/glm.hpp>

struct Block {
    enum class Type { Air,  Dirt, Grass, Stone, Wood };
    Type type{Type::Air};

    glm::vec4 color() const;
};
