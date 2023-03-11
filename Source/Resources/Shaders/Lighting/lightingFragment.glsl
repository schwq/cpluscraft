#version 330 core
out vec4 FragColor;

uniform sampler2D texture_diffuse;
in vec2 texCoords;

void main() {
	FragColor = texture(texture_diffuse, texCoords);
}

// LightSource