#version 330

uniform mat4 uMVPMatrix;
uniform float uAlpha;

in vec3 aPosition;
in vec3 aColor;

out vec4 vColor;

void main() {
	vColor = vec4(aColor, uAlpha);
	gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
}
