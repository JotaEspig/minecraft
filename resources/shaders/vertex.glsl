#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 3) in vec3 instancedOffset;
layout(location = 4) in vec4 instancedColor;

out vec4 color;

uniform mat4 projection;
uniform mat4 view;

mat4 camera() {
    return projection * view;
}

void main() {
    color = instancedColor;
    gl_Position = camera()  * vec4(aPos + instancedOffset, 1.0f);
}
