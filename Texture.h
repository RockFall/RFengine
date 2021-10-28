#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "shaderClass.h"

class Texture {
public:
	// Reference ID to the Texture Object
	GLuint ID;
	// Type of texture (i.e. GL_TEXTURE_2D)
	GLenum type;
	
	//	Imports an image, creates one Texture Object, which it's reference
	//	is stored on class's variable, and assigns the image to given slot
	//
	//	'imagePath': String path to image to be stored into texture
	// 	'texType'  : i.e.: GL_TEXTURE_2D
	//  'slot'     : Specifies which texture unit to make active. Starts in GL_TEXTURE0
	// 	'format'   : Specifies the format of the pixel data. i.e.: GL_RGBA
	// 	'pixelType': Specifies the data type of the pixel data.
	//
	Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Sets the frag. shader uniform 'uTex0' to given unit
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// Binds the Texture Object
	void Bind();
	// Unbinds the Texture Object
	void Unbind();
	// Deletes the Texture Object
	void Delete();
};

#endif