#include <cstddef>
#include <iostream>

#include <axolote/glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

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

void Chunk::setup_instanced_vbo() {
    setup_instanced_color_vbo();
    setup_instanced_offset_vbo();
}

void Chunk::bind_shader(const axolote::gl::Shader &shader) {
    Chunk::shader = shader;
}

axolote::gl::Shader Chunk::get_shader() const {
    return shader;
}

void Chunk::update(double dt) {
    (void)dt;

    drawable_blocks_amount = 0;
    std::vector<glm::vec3> offsets;
    std::vector<glm::vec4> colors;
    for (std::size_t i = 0; i < CHUNK_XZ_SIZE; ++i) {
        for (std::size_t j = 0; j < CHUNK_Y_SIZE; ++j) {
            for (std::size_t k = 0; k < CHUNK_XZ_SIZE; ++k) {
                const Block &block = blocks(i, j, k);
                if (!blocks.should_draw(i, j, k)) {
                    continue;
                }

                glm::vec3 aux{(float)i, (float)j, (float)k};
                aux += pos;
                offsets.push_back(aux);
                colors.push_back(block.color());
                ++drawable_blocks_amount;
            }
        }
    }

    vao.bind();
    instanced_offset_vbo.bind();
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * offsets.size(), offsets.data()
    );
    instanced_color_vbo.bind();
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * colors.size(), colors.data()
    );
    instanced_offset_vbo.unbind();
    vao.unbind();
}

void Chunk::draw() {
    vao.bind();
    ebo.bind();
    glDrawElementsInstanced(
        GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0, drawable_blocks_amount
    );
    ebo.unbind();
    vao.unbind();
}

void Chunk::draw(const glm::mat4 &mat) {
    (void)mat;
    draw();
}

void Chunk::setup_instanced_offset_vbo() {
    std::vector<glm::vec3> offsets;
    for (std::size_t i = 0; i < CHUNK_XZ_SIZE; ++i) {
        for (std::size_t j = 0; j < CHUNK_Y_SIZE; ++j) {
            for (std::size_t k = 0; k < CHUNK_XZ_SIZE; ++k) {
                offsets.push_back(glm::vec3{(float)i, (float)j, (float)k});
            }
        }
    }

    vao.bind();
    instanced_offset_vbo.bind();
    instanced_offset_vbo.buffer_data(
        sizeof(glm::vec3) * MAX_BLOCKS, nullptr, GL_DYNAMIC_DRAW
    );
    vao.link_attrib(
        instanced_offset_vbo, 3, 3, GL_FLOAT, sizeof(glm::vec3), (void *)0
    );
    vao.attrib_divisor(instanced_offset_vbo, 3, 1);

    instanced_offset_vbo.unbind();
    vao.unbind();
}

void Chunk::setup_instanced_color_vbo() {
    std::vector<glm::vec4> colors;
    for (std::size_t i = 0; i < CHUNK_XZ_SIZE; ++i) {
        for (std::size_t j = 0; j < CHUNK_Y_SIZE; ++j) {
            for (std::size_t k = 0; k < CHUNK_XZ_SIZE; ++k) {
                const Block &block = blocks(i, j, k);
                colors.push_back(block.color());
            }
        }
    }

    vao.bind();
    instanced_color_vbo.bind();
    instanced_color_vbo.buffer_data(
        sizeof(glm::vec4) * MAX_BLOCKS, nullptr, GL_DYNAMIC_DRAW
    );
    vao.link_attrib(
        instanced_color_vbo, 4, 4, GL_FLOAT, sizeof(glm::vec4), (void *)0
    );

    vao.attrib_divisor(instanced_color_vbo, 4, 1);

    instanced_color_vbo.unbind();
    vao.unbind();
}
