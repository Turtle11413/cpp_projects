#version 330 core

uniform float line_size;
uniform vec2 resolution;

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

flat out vec3 startPos;
out vec3 vertPos;

void main() {
	vec2 perp = vec2(gl_in[0].gl_Position.y - gl_in[1].gl_Position.y, gl_in[1].gl_Position.x - gl_in[0].gl_Position.x);
	vec2 normal = perp / length(perp);
	vec2 halfsize = vec2(line_size) / vec2(2.0) / resolution;
	vec2 off = normal * halfsize;
	
	gl_Position = gl_in[0].gl_Position + vec4(off.x, off.y, 0.0, 0.0);
	vertPos = gl_Position.xyz / gl_Position.w;
	startPos = vertPos;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position - vec4(off.x, off.y, 0.0, 0.0);
	vertPos = gl_Position.xyz / gl_Position.w;
	startPos = vertPos;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + vec4(off.x, off.y, 0.0, 0.0);
	vertPos = gl_Position.xyz / gl_Position.w;
	startPos = vertPos;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position - vec4(off.x, off.y, 0.0, 0.0);
	vertPos = gl_Position.xyz / gl_Position.w;
	startPos = vertPos;
	EmitVertex();

	EndPrimitive();
}
