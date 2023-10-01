#shader vertex
#version 450 core

layout ( location = 0 ) in vec3 pos;

out vec4 vCol;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = projection * view * model * vec4( pos, 1.0f );
	vCol = vec4( clamp( pos, 0.0f, 1.0f ), 1.0f );
}

#shader fragment
#version 450 core

in vec4 vCol;

out vec4 FragColor;

void main() {
	FragColor = vCol;
	//FragColor = vec4( 1.0f, 0.0f, 0.0f, 1.0f );
}