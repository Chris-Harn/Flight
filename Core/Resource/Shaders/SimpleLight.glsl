#shader vertex
#version 460 core

layout ( location = 0 ) in vec3 VertexPosition;
layout ( location = 1 ) in vec3 VertexNormal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4( VertexPosition, 1.0f );
	FragPos = vec3( u_model * vec4( VertexPosition, 1.0 ) );
	Normal = VertexNormal;
	//Normal = mat3( transpose(inverse( u_model ) ) ) * VertexPosition;
}

#shader fragment
#version 460 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;

out vec4 FragColor;

void main() {
	// Diffuse Lighting
	vec3 norm = normalize( Normal );
	vec3 lightDir = normalize( u_lightPos - FragPos );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = diff * u_lightColor;

	// Ambient Lighting
	float ambientStrength = 0.15;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 result = ( ambient + diffuse ) * u_objectColor;
	FragColor = vec4( result, 1.0 );
}