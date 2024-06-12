#include <glm/glm.hpp>

#include "block.hpp"

glm::vec4 Block::color() const {
    switch (type) {
        case Type::Air:
            return glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
        case Type::Dirt:
            return glm::vec4{0.5f, 0.3f, 0.0f, 1.0f};
        case Type::Grass:
            return glm::vec4{0.0f, 1.0f, 0.0f, 1.0f};
        case Type::Stone:
            return glm::vec4{0.5f, 0.5f, 0.5f, 1.0f};
        case Type::Wood:
            return glm::vec4{0.5f, 0.3f, 0.0f, 1.0f};
    }
    return glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
}
