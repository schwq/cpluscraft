#version 330 core
// defaultFragment.glsl used for normal objects that are affected by lighting settings
out vec4 FragColor;
in vec2 texCoords; // Texture Coordinates
in vec3 normalVec; // Normal Vector for the surface (mesh)
in vec3 fragPos; // Fragment Position

// struct for material properties, example gold, copper, plastic have different reactions for lighting
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct CubeLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform DirectionalLight source_dirLight;
uniform PointLight source_ptrLight[4];
uniform SpotLight source_sptLight;
uniform CubeLight source_cbLight;

uniform vec3 viewerPos;
uniform Material material;

vec3 calculateDirectionalLight(DirectionalLight dirLight, vec3 normal, vec3 viewerDir);
vec3 calculatePointLight(PointLight ptrLight, vec3 normal, vec3 fragPos, vec3 viewerDir);
vec3 calculateSpotLight(SpotLight sptLight, vec3 normal, vec3 fragPos, vec3 viewerDir);
vec3 calculateCubeLight(CubeLight cbLight, vec3 normal, vec3 fragPos, vec3 viewerDir);

void main()
{
    //vec3 norm = normalize(normalVec);
    //vec3 viewerDirection = normalize(viewerPos - fragPos);

    //vec3 result = calculateDirectionalLight(source_dirLight, norm, viewerDirection);    

    //for(int x = 0; x < 4; x++) {
    //    result += calculatePointLight(source_ptrLight[x], norm, fragPos, viewerDirection);
    //}

    //result += calculateSpotLight(source_sptLight, norm, fragPos, viewerDirection);
    //result += calculateCubeLight(source_cbLight, norm, fragPos, viewerDirection);

    FragColor = texture(material.texture_diffuse1, texCoords);
}

vec3 calculateDirectionalLight(DirectionalLight dirLight, vec3 normal, vec3 viewerDir) {

    vec3 lightDirection = normalize(vec3(-dirLight.direction));
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewerDir, reflectDirection), 0.0), material.shininess);
    // Not implemented the diffuse mapping
    vec3 ambient = dirLight.ambient * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 diffuse = dirLight.diffuse * diff * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 specular = dirLight.specular * spec * texture(material.texture_specular1, texCoords).rgb;
    return (ambient + diffuse + specular);
}
vec3 calculatePointLight(PointLight ptrLight, vec3 normal, vec3 fragPos, vec3 viewerDir) {

    vec3 lightDirection = normalize(ptrLight.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewerDir, reflectDirection), 0.0), material.shininess);
    float distance_ = length(ptrLight.position - fragPos);
    float attenuation = 1.0 / (ptrLight.constant + ptrLight.linear * distance_ + ptrLight.quadratic * (distance_ * distance_));

    vec3 ambient = ptrLight.ambient * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 diffuse = ptrLight.diffuse * diff * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 specular = ptrLight.specular * spec * texture(material.texture_specular1, texCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);

}
vec3 calculateSpotLight(SpotLight sptLight, vec3 normal, vec3 fragPos, vec3 viewerDir) {

    vec3 lightDirection = normalize(sptLight.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewerDir, reflectDirection), 0.0), material.shininess);
    float distance_ = length(sptLight.position - fragPos);
    float attenuation = 1.0 / (sptLight.constant + sptLight.linear * distance_ + sptLight.quadratic * (distance_ * distance_));
    float theta = dot(lightDirection, normalize(-sptLight.direction));
    float epsilon = sptLight.cutOff - sptLight.outerCutOff;
    float intensity = clamp((theta - sptLight.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = sptLight.ambient * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 diffuse = sptLight.diffuse * diff * texture(material.texture_diffuse1, texCoords).rgb;
    vec3 specular = sptLight.specular * spec * texture(material.texture_specular1, texCoords).rgb;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec3 calculateCubeLight(CubeLight cbLight, vec3 normal, vec3 fragPos, vec3 viewerDir) {

    vec3 lightDirection = normalize(cbLight.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewerDir, reflectDirection), 0.0), material.shininess);
    float distance_ = length(cbLight.position - fragPos);
    float attenuation = 1.0 / (cbLight.constant + cbLight.linear * distance_ + cbLight.quadratic * (distance_ * distance_));
    
    vec3 ambient = cbLight.ambient *  texture(material.texture_diffuse1, texCoords).rgb;
    vec3 diffuse = cbLight.diffuse * diff *  texture(material.texture_diffuse1, texCoords).rgb;
    vec3 specular = cbLight.specular * spec * texture(material.texture_specular1, texCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);

}
