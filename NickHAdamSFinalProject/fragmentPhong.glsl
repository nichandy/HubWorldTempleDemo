#version 330 core

// per-fragment interpolated values from the vertex shader
in  vec3 fN;
in  vec3 fL;
in  vec3 fE;
in  vec4 color;  //  not needed if we use model_color
in  vec2 texCoord;

out vec4 fColor;

uniform vec4  ambient_product, diffuse_product, specular_product;
uniform mat4  model_view;
uniform vec4  light_position;
uniform float shininess;
uniform vec4  model_color;
uniform int   color_source;

uniform sampler2D texture;

void main()
{

   vec4 myColor = model_color;
   if (color_source == 0) myColor = texture2D( texture, texCoord );
    else if (color_source == 1) myColor = color;
   else if (color_source == 2) myColor = model_color;

    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);

    vec3 H = normalize( L + E );

    vec4 ambient = ambient_product*myColor;

    float diffDot = max(dot(L, N), 0.0);
    vec4 diffuse = diffDot*diffuse_product*myColor;

    float specDot = pow(max(dot(N, H), 0.0), shininess);
    vec4 specular = specDot*specular_product*myColor;

    // discard the specular highlight if the light's behind the vertex
    if( dot(L, N) < 0.0 ) {
	   specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    fColor = ambient + diffuse + specular;

    fColor.a = 1.0;
}

