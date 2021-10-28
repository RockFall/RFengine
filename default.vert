#version 330 core

// location defines attribute's position on VAO position
// Position (coordinates)
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture data (coordinates)
layout (location = 2) in vec2 aTex;

// Outputting the color to the Fragment Shader
out vec3 color;
// and the texture coordinates
out vec2 texCoord;

uniform float uScale;

void main()
{
	
   gl_Position = vec4(aPos.x + aPos.x * uScale, aPos.y + aPos.y * uScale, aPos.z + aPos.z * uScale, 1.0);
   // Assigns the colors from Vertex Data to "color" in fragement shader
   color = aColor;
   // Assigns the texture coordinates from Vertex Data to "texCoord" in fragement shader
   texCoord = aTex;
}

