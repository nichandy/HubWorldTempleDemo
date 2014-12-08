#version 330 core

in  vec4 vPosition;
in  vec4 vColor;
in  vec4 vNormal;
out vec4 Color;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 model_color;

void main()
{
    //Color = vColor;
    Color = model_color;
    //Color = vec4(1,0,0,1);

    gl_Position = projection*model_view * vPosition/vPosition.w;

}
