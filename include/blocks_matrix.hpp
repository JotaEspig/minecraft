#pragma once

#include <array>
#include <cstddef>

#include "block.hpp"

template <std::size_t X_SIZE, std::size_t Y_SIZE, std::size_t Z_SIZE>
struct BlockMatrix {
    std::array<std::array<std::array<Block, Z_SIZE>, Y_SIZE>, X_SIZE> blocks;

    BlockMatrix();

    bool should_draw(std::size_t x, std::size_t y, std::size_t z) const;
    Block &operator()(std::size_t x, std::size_t y, std::size_t z);
};

template <std::size_t X_SIZE, std::size_t Y_SIZE, std::size_t Z_SIZE>
BlockMatrix<X_SIZE, Y_SIZE, Z_SIZE>::BlockMatrix() {
    for (std::size_t x = 0; x < X_SIZE; ++x) {
        for (std::size_t y = 0; y < Y_SIZE; ++y) {
            for (std::size_t z = 0; z < Z_SIZE; ++z) {
                blocks[x][y][z] = Block{};
            }
        }
    }
}

template <std::size_t X_SIZE, std::size_t Y_SIZE, std::size_t Z_SIZE>
bool BlockMatrix<X_SIZE, Y_SIZE, Z_SIZE>::should_draw(
    std::size_t x, std::size_t y, std::size_t z
) const {
    if (blocks[x][y][z].type == Block::Type::Air) {
        return false;
    }

    bool is_at_border = x == 0 || x == X_SIZE - 1 || y == 0 || y == Y_SIZE - 1
                        || z == 0 || z == Z_SIZE - 1;
    if (is_at_border) {
        return true;
    }

    // Check if any of the adjacent blocks is air, if so, draw this block.
    if (x > 0 && blocks[x - 1][y][z].type == Block::Type::Air) {
        return true;
    }
    if (x < X_SIZE - 1 && blocks[x + 1][y][z].type == Block::Type::Air) {
        return true;
    }
    if (y > 0 && blocks[x][y - 1][z].type == Block::Type::Air) {
        return true;
    }
    if (y < Y_SIZE - 1 && blocks[x][y + 1][z].type == Block::Type::Air) {
        return true;
    }
    if (z > 0 && blocks[x][y][z - 1].type == Block::Type::Air) {
        return true;
    }
    if (z < Z_SIZE - 1 && blocks[x][y][z + 1].type == Block::Type::Air) {
        return true;
    }

    return false;
}

template <std::size_t X_SIZE, std::size_t Y_SIZE, std::size_t Z_SIZE>
Block &BlockMatrix<X_SIZE, Y_SIZE, Z_SIZE>::operator()(
    std::size_t x, std::size_t y, std::size_t z
) {
    return blocks[x][y][z];
}
