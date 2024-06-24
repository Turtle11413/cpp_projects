#version 330 core

layout(location = 0) in vec4 position;
uniform vec2 resolution;
uniform mat4x4 world;
uniform mat4x4 transform;

flat out vec3 startPos;
out vec3 vertPos;

void main() {
	float aspect = resolution.x / resolution.y;
	gl_Position = transform * world * position;
	gl_Position.x /= aspect;

	vertPos = gl_Position.xyz / gl_Position.w;
	startPos = vertPos;
}
