#version 330 core

flat in vec3 startPos;
in vec3 vertPos;

out vec4 color;

uniform vec4 edge_color;
uniform vec2 resolution;
uniform float dash_threshold;

void main() {
	float dist = length((vertPos.xy - startPos.xy) * resolution / 2.0);

	if (fract(dist / 20.0) > dash_threshold) {
		discard;
	}

  color = edge_color;
}
