#version 330

// array of lights
#define MAX_LIGHTS 3
uniform int numLights;

uniform struct Light {
   vec3 position;
   vec4 color;
   float ambientCoefficient;
   float attenuation;
} allLights[MAX_LIGHTS];

uniform vec3 uEye;

in vec3 vPosition;
in vec3 vNormal;
in vec3 oldPosition;

in vec4 vAmbientMaterial;
in vec4 vDiffuseMaterial;
in vec4 vSpecularMaterial;
in float vShininess;

out vec4 fragColor;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
} material;

uniform vec3 edgeVertices[100];
in vec3 vertexColor;

vec4 calcLight(Light light, Material material, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera)
{
        vec3 lightdir = normalize(light.position - surfacePos);
        // Cosine of the angle between the normal and the light direction, clamped above 0
        //  - light is at the parallel to "object"   -> 1
        //  - light is perpendicular to "object"     -> 0
        float intensity = dot(lightdir, normal); // - diffuse coefficient
        intensity = clamp( intensity, 0, 1);

        // - old
        float dist = distance(normal, lightdir);
        /*vec4 ambientColor = material.ambient * material.diffuse;
        vec4 diffuseColor = material.diffuse * light.color * intensity / (dist * dist);
        float specularCoefficient = 0.0;
        if(intensity > 0) {
            vec3 reflection = reflect(-lightdir, normal);
            // Cosine of the angle between the Eye vector and the Reflect vector, clamped to 0
            //  - Looking into the reflection -> 1
            //  - Looking elsewhere -> < 1
            float cosAlpha = clamp( dot( surfaceToCamera, reflection ), 0, 1);
            specularCoefficient = pow(cosAlpha, material.shininess);
        }
        vec4 specularColor = material.specular * specularCoefficient * light.color * intensity / (dist * dist);

        vec4 color = ambientColor + diffuseColor + specularColor;
        return color;*/

        // - new
        vec4 ambientLight = light.ambientCoefficient * material.ambient * light.color;
        vec4 diffuseLight = material.diffuse * light.color * intensity;
        float specularCoefficient = 0.0;
        if(intensity > 0) {
            vec3 reflection = reflect(-lightdir, normal);
            // Cosine of the angle between the Eye vector and the Reflect vector, clamped to 0
            //  - Looking into the reflection -> 1
            //  - Looking elsewhere -> < 1
            float cosAlpha = clamp( dot( surfaceToCamera, reflection ), 0, 1);
            specularCoefficient = pow(cosAlpha, material.shininess);
        }
        vec4 specularLight = specularCoefficient * material.specular * light.color;

        float distanceToLight = length(light.position - vPosition);
        float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //return ambientLight + diffuseLight / (dist * dist) + specularLight / (dist * dist);
        return ambientLight + attenuation * (diffuseLight + specularLight);
}

void main() {
    vec3 normal = normalize(vNormal);
    vec3 viewDirection = normalize(uEye - vPosition);

    material.ambient = vAmbientMaterial;
    material.diffuse = vDiffuseMaterial;
    material.specular = vSpecularMaterial;
    material.shininess = vShininess;

    // - loop through all light sources and add up the calculated colors
    vec4 linearColor = vec4(0);
    for(int i = 0; i < numLights; ++i){
        linearColor += calcLight(allLights[i], material, normal, vPosition, viewDirection);
    }
    vec4 color = vec4(vertexColor, 1.0);
    fragColor = linearColor * color;

    /*int i;
    for(i=0;i<100; ++i) {
        if( oldPosition.xyz != edgeVertices[i].xyz) {
            fragColor = linearColor;
        } else {
            //fragColor = mix(vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0));
            fragColor = vec4(0.0, 1.0, 0.0, 1.0);
            //fragColor.a = 0.2;
        }
        //fragColor = vec4(0.0, 255.0, 0.0, 0.2);
    }*/
    //vec4 gamma = vec4(1.0/2.2);
    //fragColor = pow(linearColor, gamma);
}