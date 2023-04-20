//C�digo fonte do Fragment Shader (em GLSL)
#version 450

//Informa��es recebidas do vertex shader
in vec3 finalColor;
in vec3 scaledNormal;
in vec4 fragPos;


//Propriedades do material do objeto
uniform float ka;
uniform float kd;
uniform float ks;
uniform float n;

//Propriedades da fonte de luz
uniform vec3 lightPos;
uniform vec3 lightColor;

//Posi��o da c�mera

uniform vec3 cameraPos;

//Buffer de sa�da (color Buffer)
out vec4 color;

void main()
{
    //Ambient
    vec3 ambient = lightcolor * ka;

    //Difusse
    vec3 diffuse = 0.0f;

    //specular
    vec3 specular = 0.0f;

    vec3 result = (ambient + difusse) * finalColor + specular;
    

    color = vec4(result + 1.0f);
}