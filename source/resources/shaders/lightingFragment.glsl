#version 330 core
out vec4 FragColor;

in vec2 texCoords;
uniform sampler2D texture1;
uniform vec3 aColor;

void main() {
	FragColor = texture(texture1, texCoords) * vec4(aColor, 1.0);
}

// LightSource