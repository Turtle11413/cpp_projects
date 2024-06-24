#version 330 core

out vec4 color;
uniform vec4 vertex_color;

void main() {
  color = vertex_color;
}
