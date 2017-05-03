#version 430 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture;

void main()
{
	//vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoord).r); 
	//color = vec4(1.0, 1.0, 1.0, 1.0) * sampled; 
    color = texture(Texture, TexCoord);
}