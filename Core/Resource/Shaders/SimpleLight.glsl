#shader vertex
#version 450 core

layout ( location = 0 ) in vec3 aPos;
layout ( location = 1 ) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = projection * view * model * vec4( aPos, 1.0f );
	FragPos = vec3( model * vec4( aPos, 1.0 ) );
	Normal = aNormal;
}

#shader fragment
#version 450 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main() {
	vec3 norm = normalize( Normal );
	vec3 lightDir = normalize( lightPos - FragPos );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = ( ambient + diffuse ) * objectColor;
	FragColor = vec4( result, 1.0 );
}