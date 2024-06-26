/**
 * \file blocks_matrix.hpp
 * \brief BlockMatrix struct header
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
#pragma once

#include <array>
#include <cstddef>

#include "block.hpp"

/**
 * \brief BlockMatrix struct
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
template <std::size_t X_SIZE, std::size_t Y_SIZE, std::size_t Z_SIZE>
struct BlockMatrix {
    /** Blocks matrix **/
    std::array<std::array<std::array<Block, Z_SIZE>, Y_SIZE>, X_SIZE> blocks;

    /**
     * \brief BlockMatrix constructor
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     **/
    BlockMatrix();

    /**
     * \brief Check if a block should be drawn
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     * \param x - X position
     * \param y - Y position
     * \param z - Z position
     * \returns true if the block should be drawn, false otherwise
     **/
    bool should_draw(std::size_t x, std::size_t y, std::size_t z) const;
    /**
     * \brief Block getter
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     * \param x - X position
     * \param y - Y position
     * \param z - Z position
     * \returns Block reference
     **/
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
