#pragma once

#include <axolote/engine.hpp>

#include "blocks_matrix.hpp"

#define CHUNK_XZ_SIZE 16
#define CHUNK_Y_SIZE 50
#define MAX_BLOCKS (CHUNK_XZ_SIZE * CHUNK_Y_SIZE * CHUNK_XZ_SIZE)

class Chunk : public axolote::Drawable {
public:
    BlockMatrix<CHUNK_XZ_SIZE, CHUNK_Y_SIZE, CHUNK_XZ_SIZE> blocks;

    Chunk();

    // TODO: Optimize this, rendering just the faces that are visible. At this
    // moment, all the blocks adjacent to an air block are drawn. I dont know
    // how to do this yet. :)

    void setup_instanced_vbo();
    void bind_shader(const axolote::gl::Shader &shader) override;
    axolote::gl::Shader get_shader() const override;
    void update(double dt) override;
    void draw() override;
    void draw(const glm::mat4 &mat) override;

private:
    axolote::gl::VAO vao;
    axolote::gl::VBO vbo;
    axolote::gl::VBO instanced_color_vbo;
    axolote::gl::VBO instanced_offset_vbo;
    axolote::gl::EBO ebo;
    axolote::gl::Shader shader;
    std::size_t indices_size = 0;
    std::size_t drawable_blocks_amount = 0;

    void setup_instanced_offset_vbo();
    void setup_instanced_color_vbo();
};
