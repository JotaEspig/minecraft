/**
 * \file block.hpp
 * \brief Block struct header
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
#pragma once

#include <glm/glm.hpp>

/**
 * \brief Block struct
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
struct Block {
    /** Type of block, used for getting color  **/
    enum class Type { Air, Dirt, Grass, Stone, Wood };
    /** Block type **/
    Type type{Type::Air};

    /**
     * \brief color getter
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     * \returns Block color
     **/
    glm::vec4 color() const;
};
