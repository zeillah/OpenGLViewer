#version 330

in vec4 vColor;

layout(location = 0, index = 0) out vec4 fragColor;

void main() {

	fragColor = vColor;
}
