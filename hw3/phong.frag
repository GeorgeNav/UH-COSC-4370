#version 330 core
out vec4 FragColor;

in vec3 normal;  
in vec3 fragPos;

// Shading Type
uniform int shadingType;
  
// Light
uniform vec3 lightPos;
uniform vec3 lightColor;

// Camera
uniform vec3 cameraPos;

// Object
uniform vec3 objectColor;

void main()
{
  // ambient reflected light (La) calculation
  float ka = 0.2; // ambient coefficient
  vec3 La = ka * lightColor;

  // diffuse and specular support values
  vec3 n = normalize(normal); // surface normal
  vec3 l = normalize(lightPos - fragPos); // light direction

  // diffuse reflected light (Ld) calculation
  float kd = 1.0; // diffuse coefficient
  vec3 Ld = kd * lightColor * max(0.0, dot(n, l));

  // specular reflected light (Ls) calculation
  int p = 16;
  float ks = 1.0; // specular coefficient
  vec3 v = normalize(cameraPos - fragPos); // view direction
  vec3 h = (v + l) / length(v + l); // (v + l) divided by |v + l|
  vec3 Ls = ks * lightColor * pow(max(0.0, dot(n, h)), p);

  if(shadingType == 0) // ambient only
    FragColor = vec4(La * objectColor, 1.0);
  else if(shadingType == 1) // diffuse only
    FragColor = vec4(Ld * objectColor, 1.0);
  else if(shadingType == 2) // specular only
    FragColor = vec4(Ls * objectColor, 1.0);
  else if(shadingType == 3) // phong only
    FragColor = vec4((La + Ld + Ls) * objectColor, 1.0);
}