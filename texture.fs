#version 330 core
out vec4 FragColor;
  
in vec3 VertColor;
in vec2 TexCoord;

uniform sampler2D Tex;

void main()
{
    FragColor = texture(Tex, TexCoord) * vec4(VertColor, 1.0);
}