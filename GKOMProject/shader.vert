#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

out vec3 fColor;
out vec2 fTexCoord;
out vec3 fNormal;
out vec3 fPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	fColor = vColor;
	fTexCoord = vTexCoord;
	fNormal = mat3(transpose(inverse(model))) * vNormal;  
	fPos = vec3(model * vec4(position, 1.0f));
}