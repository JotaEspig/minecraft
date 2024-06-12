/**
 * \file chunk.hpp
 * \brief Chunk class definition.
 * \author João Vitor Espig (JotaEspig)
 * \date June 06, 2024
 * \version June 06, 2024
 **/
#pragma once

#include <axolote/engine.hpp>

#include "blocks_matrix.hpp"

/** Chunk X and Z size **/
#define CHUNK_XZ_SIZE 10
/** Chunk Y size **/
#define CHUNK_Y_SIZE 10
/** Max amount of blocks possible according to the chunk size **/
#define MAX_BLOCKS (CHUNK_XZ_SIZE * CHUNK_Y_SIZE * CHUNK_XZ_SIZE)

/**
 * \brief Chunk class
 * \author João Vitor Espig (JotaEspig)
 * \date June 06, 2024
 * \version June 06, 2024
 **/
class Chunk : public axolote::Drawable {
public:
    /** Chunk position **/
    glm::vec3 pos{0.0f, 0.0f, 0.0f};
    /** Chunk blocks **/
    BlockMatrix<CHUNK_XZ_SIZE, CHUNK_Y_SIZE, CHUNK_XZ_SIZE> blocks;

    /**
     * \brief Chunk constructor
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     **/
    Chunk();

    // TODO: Optimize this, rendering just the faces that are visible. At this
    // moment, all the blocks adjacent to an air block are drawn. I dont know
    // how to do this yet. :)

    /**
     * \brief setup instanced VBOs
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     **/
    void setup_instanced_vbo();
    /**
     * \brief bind shader
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     * \param shader Shader to bind
     **/
    void bind_shader(const axolote::gl::Shader &shader) override;
    /**
     * \brief get shader
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     * \returns Shader
     **/
    axolote::gl::Shader get_shader() const override;
    /**
     * \brief update chunk
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     * \param dt - Delta time
     **/
    void update(double dt) override;
    /**
     * \brief draw chunk
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     **/
    void draw() override;
    /**
     * \brief draw chunk with model matrix
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     * \param mat Model matrix
     *
     * It just calls draw() without glm::mat4
     **/
    void draw(const glm::mat4 &mat) override;

private:
    /** VAO **/
    axolote::gl::VAO vao;
    /** VBO **/
    axolote::gl::VBO vbo;
    /** Instanced offset VBO **/
    axolote::gl::VBO instanced_offset_vbo;
    /** Instanced color VBO **/
    axolote::gl::VBO instanced_color_vbo;
    /** EBO **/
    axolote::gl::EBO ebo;
    /** Shader **/
    axolote::gl::Shader shader;
    /** Indices size **/
    std::size_t indices_size = 0;
    /** Drawable blocks amount **/
    std::size_t drawable_blocks_amount = 0;

    /**
     * \brief setup instanced offset VBO
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     **/
    void setup_instanced_offset_vbo();
    /**
     * \brief setup instanced color VBO
     * \author João Vitor Espig (JotaEspig)
     * \date June 06, 2024
     * \version June 06, 2024
     **/
    void setup_instanced_color_vbo();
};
