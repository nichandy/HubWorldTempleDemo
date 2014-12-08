#version 330 core

in  vec4 vPosition;
in  vec3 vNormal;
in  vec4 vColor;
uniform vec4 model_color;  // use this or vColor

out vec4 color;

uniform vec4  ambient_product, diffuse_product, specular_product;
uniform vec4  light_position;  // assumes this is position in eye coord!!
uniform float shininess;

uniform mat4 model_view;
uniform mat4 projection;

void main()
{
   vec4 myColor = model_color;
   //vec4 myColor = vColor;

    // Transform vertex  position into eye coordinates
    vec3 pos = (model_view * vPosition).xyz;

    // These are parameters we need for the Phong Lighting model:  V, R, N, L. Here, the variable E represents V, and H is R
    // This assumes the light position is passed into the shader in eye coordinates
    vec3 L = normalize( (light_position).xyz - pos );  // Light direction
    vec3 E = normalize( -pos );    //  V = View direction: camera sits at the origin so "eye" direction is: origin-pos = -pos
    vec3 H = normalize( L + E );   // R = Reflected direction: this formula is an approximation of R.

    // Transform vertex normal into eye coordinates
    // Be careful - generally the normals transform slightly differently than the vertices
    // however, for rotations and uniform scale, they are the same.
    // We will have to be more careful when doing non-uniform scales.
    vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
   vec4 ambient = ambient_product*myColor;   // Ka*LightColor*SurfaceColor

    float LN = max( dot(L, N), 0.0 ); // LdotN < 0, then there is no diffuse

    vec4  diffuse = LN*diffuse_product*myColor; // kd*(NdotL)*LightColor*SurfaceColor

    float NH = pow( max(dot(N, H), 0.0), shininess );
    vec4  specular = NH * specular_product*myColor;

    if( dot(L, N) < 0.0 ) {                  // specular is also 0 if LdotN<0
	   specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    gl_Position = projection * model_view * vPosition;

    color =  ambient + diffuse + specular;

    color.a = 1.0;  // set alpha channel of color to be 1

}
