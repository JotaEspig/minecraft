#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 instancedColor;
layout(location = 4) in mat4 instancedMatrix;

out vec3 color;
out vec2 tex_coord;
out vec3 normal;
out vec3 current_pos;

uniform mat4 projection;
uniform mat4 view;

mat4 camera() {
    return projection * view;
}

void main() {
    color = instancedColor;
    tex_coord = aTex;
    // This operation fix the "rotation problem"
    // but it's considered costly
    // normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = camera() * instancedMatrix * vec4(aPos, 1.0f);
}
