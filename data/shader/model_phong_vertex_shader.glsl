#version 330

uniform mat4 uMVMatrix;
uniform mat4 uMVPMatrix;
uniform mat3 uNormalMatrix;

in vec3 aPosition;
in vec3 aNormal;

out vec3 vPosition;
out vec3 vNormal;

in vec4 ambientMaterial;
in vec4 diffuseMaterial;
in vec4 specularMaterial;
in float shininess;

out vec4 vAmbientMaterial;
out vec4 vDiffuseMaterial;
out vec4 vSpecularMaterial;
out float vShininess;

out vec3 oldPosition;

in vec3 vertColor;
out vec3 vertexColor;

void main() {

	vec4 position = uMVMatrix * vec4(aPosition, 1.0);
	vec3 normal = normalize(uNormalMatrix * aNormal);

	vPosition = position.xyz;
	vNormal = normal;

	// - material of object
	vAmbientMaterial = ambientMaterial;
	vDiffuseMaterial = diffuseMaterial;
	vSpecularMaterial = specularMaterial;
	vShininess = shininess;

	// vertex position
	gl_Position = uMVPMatrix * vec4(aPosition, 1.0);

	oldPosition = aPosition;
	vertexColor = vertColor;
}