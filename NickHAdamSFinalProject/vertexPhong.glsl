#version 330  core

in  vec4 vPosition;
in  vec3 vNormal;
in  vec4 vColor;
in  vec2 vTexture;
out vec2 texCoord;

// output values that will be interpreted per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL;
out vec4 color;


uniform vec4 light_position;
uniform mat4 projection;
uniform mat4 model_view;

void main()
{
    color = vColor;

    fN = normalize( model_view*vec4(vNormal, 0.0) ).xyz;
    fE = -(model_view*vPosition).xyz;
    fL = light_position.xyz - (model_view*vPosition).xyz;

    texCoord    = vTexture;

    gl_Position = projection*model_view*vPosition;
}
