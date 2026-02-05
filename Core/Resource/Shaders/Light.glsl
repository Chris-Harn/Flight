#shader vertex
#version 460 core

layout ( location = 0 ) in vec3 VertexPosition;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4( VertexPosition.x, VertexPosition.y, VertexPosition.z, 1.0f );
}

#shader fragment
#version 460 core

uniform vec3 u_lightColor;

out vec4 FragColor;

void main() {
	FragColor = vec4( u_lightColor, 1.0f );
}