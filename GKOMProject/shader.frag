#version 330 core
in vec3 fColor;
in vec2 fTexCoord;
in vec3 fNormal;
in vec3 fPos;

out vec4 color;

uniform sampler2D myTexture;
uniform bool useTexture;
uniform vec3 lightPos;
uniform float diffuseLightIntensity;
uniform float ambientLightIntensity;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.1f * ambientLightIntensity;
    vec3 ambient = ambientStrength * lightColor;

	if (useTexture == true)
	{
		color = texture(myTexture, fTexCoord);
	}
	else
	{
		color = vec4(fColor, 1.0f);
	}
	
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor * diffuseLightIntensity;

	vec3 result = (ambient + diffuse) * vec3(color.x, color.y, color.z);
	color = vec4(result, 1.0f);
}