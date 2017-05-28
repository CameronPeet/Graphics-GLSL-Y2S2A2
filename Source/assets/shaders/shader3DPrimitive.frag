#version 430 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

layout (std140) uniform Lights
{
	DirLight dirLight;
	PointLight pointLight;
	SpotLight spotLight;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

vec3 CalculateDirectionLighting(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLighting(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLighting(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main(void)
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 DirLightResult = CalculateDirectionLighting(dirLight, norm, viewDir);
	vec3 PointLightResult = CalculatePointLighting(pointLight, norm, FragPos, viewDir);
	vec3 SpotLightResult = CalculateSpotLighting(spotLight, norm, FragPos, viewDir);

	vec3 TotalLighting = DirLightResult + PointLightResult + SpotLightResult;

	color = vec4(TotalLighting, 1.0f);
}


vec3 CalculateDirectionLighting(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	//Diffuse
	float diffuse = max(dot(normal, lightDir), 0.0);

	//Specular
	vec3 reflectDirection = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);

	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 Diffuse = light.diffuse * diffuse * vec3(texture(material.diffuse, TexCoord));
	vec3 Specular = light.specular * specular * vec3(texture(material.specular, TexCoord));
	return (Ambient + Diffuse + Specular);
}


vec3 CalculatePointLighting(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	//Diffuse
	float diffuse = max(dot(normal, lightDir), 0.0);

	//Specular
	vec3 reflectDirection = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);

	//Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//Results
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 Diffuse = light.diffuse * diffuse * vec3(texture(material.diffuse, TexCoord));
	vec3 Specular = light.specular * specular * vec3(texture(material.specular, TexCoord));

	return(Ambient + Diffuse + Specular);
}


vec3 CalculateSpotLighting(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	
	//Diffuse
	float diffuse = max(dot(normal, lightDir), 0.0);

	//Specular
	vec3 reflectDirection = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);

	//Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//Spotlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	//Results
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 Diffuse = light.diffuse *  diffuse * vec3(texture(material.diffuse, TexCoord));
	vec3 Specular = light.specular * specular * vec3(texture(material.specular, TexCoord));

	return ((Ambient + Diffuse + Specular) * (attenuation * intensity));

}