#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 8) out;
uniform float point_size;
uniform vec2 resolution;

const float PI = 3.141592653589;

void main() {
	vec2 halfsize = vec2(point_size) / vec2(2.0) / resolution;
	gl_Position = gl_in[0].gl_Position + vec4(0.0, halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-cos(PI / 4.0) * halfsize.x, sin(PI / 4.0) * halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(cos(PI / 4.0) * halfsize.x, sin(PI / 4.0) * halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-halfsize.x, 0.0, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(+halfsize.x, 0.0, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-cos(PI / 4.0) * halfsize.x, -sin(PI / 4.0) * halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(cos(PI / 4.0) * halfsize.x, -sin(PI / 4.0) * halfsize.y, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.0, -halfsize.y, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}
