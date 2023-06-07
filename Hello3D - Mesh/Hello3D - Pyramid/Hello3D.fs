//Código fonte do Fragment Shader (em GLSL)
#version 450

in vec4 finalColor;
out vec4 color;

uniform bool isContour;

void main()
{
if (!isContour)
{
    color = finalColor;
    }
    else color = vec4(0.0,0.0,0.0,1.0);
}