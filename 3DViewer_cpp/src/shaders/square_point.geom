#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform float point_size;
uniform vec2 resolution;

void main() {
	vec2 halfsize = vec2(point_size) / vec2(2.0) / resolution;
	gl_Position = gl_in[0].gl_Position + vec4(-halfsize.x, halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(halfsize.x, halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-halfsize.x, -halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(halfsize.x, -halfsize.y, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}
