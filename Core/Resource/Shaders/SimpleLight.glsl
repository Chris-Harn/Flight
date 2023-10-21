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
	gl_Position = u_projection * u_view * u_model * vec4( VertexPosition, 1.0 );
	FragPos = vec3( u_model * vec4( VertexPosition, 1.0 ) );
	Normal = mat3( transpose( inverse( u_model ) ) ) * VertexNormal;
}

#shader fragment
#version 460 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;


uniform vec3 u_viewPos;
uniform Material u_material;
uniform Light u_light;

out vec4 FragColor;

void main() {
	// Diffuse Light
	vec3 norm = normalize( Normal );
	vec3 lightDir = normalize( u_light.position - FragPos );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = ( diff  * u_material.diffuse ) * u_light.diffuse;

	// Ambient Light
	vec3 ambient = u_material.ambient * u_light.ambient;

	// Specular Light
	vec3 viewDir = normalize( u_viewPos - FragPos );
	vec3 reflectDir = reflect( -lightDir, norm );
	float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), u_material.shininess );
	vec3 specular = ( u_material.specular * spec ) * u_light.specular;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4( result, 1.0 );
}