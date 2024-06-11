#pragma once

#include <axolote/engine.hpp>

#include "block.hpp"

class Chunk : public axolote::Drawable {
public:
    Chunk();

    void set_blocks(const std::vector<Block> &blocks);
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
    axolote::gl::VBO instanced_matrix_vbo;
    axolote::gl::EBO ebo;
    axolote::gl::Shader shader;
    std::size_t indices_size = 0;
    std::vector<Block> blocks;

    void setup_instanced_color_vbo();
    void setup_instanced_matrix_vbo();
};
