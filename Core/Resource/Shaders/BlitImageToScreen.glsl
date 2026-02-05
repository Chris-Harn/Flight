#shader vertex
#version 450 core

layout ( location = 0 ) in vec2 aPos;
layout ( location = 1 ) in vec2 aTexCoords;

out vec2 TexCoords;

void main() {
   gl_Position = vec4( aPos, 0.0, 1.0 );
   TexCoords = aTexCoords;
}

#shader fragment
#version 450 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main() {
   FragColor = vec4( texture(u_Texture, TexCoords).rgb, 1.0 );
}