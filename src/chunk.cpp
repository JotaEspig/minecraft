#include <cstddef>

#include "chunk.hpp"

struct MyVertex {
    glm::vec3 pos;
    glm::vec2 tex_UV;
    glm::vec3 normal;
};

Chunk::Chunk() {
    axolote::Model cube_model{
        "resources/models/cube.obj", glm::vec3{1.0f, 1.0f, 1.0f}
    };

    indices_size = cube_model.meshes[0].indices.size();

    std::vector<MyVertex> vertices;
    for (const auto &vertex : cube_model.meshes[0].vertices) {
        vertices.push_back({vertex.position, vertex.tex_UV, vertex.normal});
    }

    vao.bind();
    vbo = axolote::gl::VBO{vertices};
    vbo.bind();
    ebo = axolote::gl::EBO{cube_model.meshes[0].indices};
    ebo.bind();

    vao.link_attrib(vbo, 0, 3, GL_FLOAT, sizeof(MyVertex), (void *)0);
    vao.link_attrib(
        vbo, 1, 2, GL_FLOAT, sizeof(MyVertex),
        (void *)offsetof(MyVertex, tex_UV)
    );
    vao.link_attrib(
        vbo, 2, 3, GL_FLOAT, sizeof(MyVertex),
        (void *)offsetof(MyVertex, normal)
    );
    ebo.unbind();
    vbo.unbind();
    vao.unbind();
}

void Chunk::set_blocks(const std::vector<Block> &blocks) {
    Chunk::blocks = blocks;
}

void Chunk::setup_instanced_vbo() {
    setup_instanced_color_vbo();
    setup_instanced_matrix_vbo();
}

void Chunk::bind_shader(const axolote::gl::Shader &shader) {
    Chunk::shader = shader;
}

axolote::gl::Shader Chunk::get_shader() const {
    return shader;
}

void Chunk::update(double dt) {
    (void)dt;
}

void Chunk::draw() {
    vao.bind();
    ebo.bind();
    glDrawElementsInstanced(
        GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0, blocks.size()
    );
    ebo.unbind();
    vao.unbind();
}

void Chunk::draw(const glm::mat4 &mat) {
    (void)mat;
    draw();
}

void Chunk::setup_instanced_color_vbo() {
    std::vector<glm::vec3> colors;
    for (const auto &block : blocks) {
        colors.push_back(block.color);
    }

    vao.bind();
    instanced_color_vbo.bind();
    instanced_color_vbo.buffer_data(
        sizeof(glm::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW
    );
    vao.link_attrib(
        instanced_color_vbo, 3, 3, GL_FLOAT, sizeof(glm::vec3), (void *)0
    );

    vao.attrib_divisor(instanced_color_vbo, 3, 1);

    instanced_color_vbo.unbind();
    vao.unbind();
}

void Chunk::setup_instanced_matrix_vbo() {
    std::vector<glm::mat4> matrices;
    for (const auto &block : blocks) {
        matrices.push_back(block.pos);
    }

    vao.bind();
    instanced_matrix_vbo.bind();
    instanced_matrix_vbo.buffer_data(
        sizeof(glm::mat4) * matrices.size(), matrices.data(), GL_STATIC_DRAW
    );
    vao.link_attrib(
        instanced_matrix_vbo, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void *)0
    );
    vao.link_attrib(
        instanced_matrix_vbo, 5, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(sizeof(glm::vec4))
    );
    vao.link_attrib(
        instanced_matrix_vbo, 6, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(2 * sizeof(glm::vec4))
    );
    vao.link_attrib(
        instanced_matrix_vbo, 7, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(3 * sizeof(glm::vec4))
    );

    vao.attrib_divisor(instanced_matrix_vbo, 4, 1);
    vao.attrib_divisor(instanced_matrix_vbo, 5, 1);
    vao.attrib_divisor(instanced_matrix_vbo, 6, 1);
    vao.attrib_divisor(instanced_matrix_vbo, 7, 1);

    instanced_matrix_vbo.unbind();
    vao.unbind();
}
