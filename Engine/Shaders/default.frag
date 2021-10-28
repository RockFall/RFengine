#version 330 core
out vec4 FragColor;

// Colors comes from Vertex Shader
in vec3 color;
// Texture coordinates from Vertex Shader
in vec2 texCoord;

// Texture unit to use (from Main func)
uniform sampler2D uTex0;

void main()
{
   FragColor = texture(uTex0, texCoord);
}

