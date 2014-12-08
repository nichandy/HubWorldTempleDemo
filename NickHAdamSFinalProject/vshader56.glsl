#version 150

in   vec4 vPosition;
in   vec3 vNormal;
in    vec4 vColor;

// output values that will be interpretated per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL;
out vec4 color;


uniform vec4 LightPosition;
uniform mat4 projection;
uniform mat4 model_view;

void main()
{
    color = vColor;  //  not needed if we use model_color

    fN = normalize( model_view * vec4(vNormal, 0.0) ).xyz;
    fE = -(model_view * vPosition).xyz;
    fL = LightPosition.xyz;

    // if LightPosition.w =0, it is a directional light. Otherwise, it is a point light.
    if( LightPosition.w != 0.0 ) {
	   fL = LightPosition.xyz - (model_view * vPosition).xyz;
    }

    gl_Position = projection*model_view*vPosition;
}
