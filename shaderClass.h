#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;

	// Construtor do Shader a partir de um arquivo de vertices e outro de fragmentos
	Shader(const char* vertexFile, const char* fragmentFile);

	// Ativa o Shader Program
	void Activate();
	// Deleta o Shader Program
	void Delete();
};

#endif