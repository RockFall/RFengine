#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	// Gera 1 objeto de VBO
	glGenBuffers(1, &ID);
	// Bind do VBO para seu uso
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Inserção dos dados de vertices no VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}