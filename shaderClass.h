#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// Returns the given file as a string
std::string get_file_contents(const char* filename);

class Shader {
public:
	// Reference ID of the Shader Program
	GLuint ID;

	// Creates a shader program based on given files for vertex and fragment objects
	// and stores the created shaderProgram ID's into class's variable
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();

private:
	// Checks for error on compilation or linking of shaders and prints them
	void compileErrors(unsigned int shader, const char* type);
};

#endif