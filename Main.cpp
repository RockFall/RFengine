#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

int main() {

	// Initializes GLFW
	glfwInit();

	// Specify the client API (OpenGL) version (in this case 3.3) that 
	// the created context must be compatible
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile (Mordern functions) or Compatibility Profile (Modern + Outdated)
	// Using CORE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Criando uma janela inicial de 800px por 800px
	GLFWwindow* window = glfwCreateWindow(800, 800, "RFengine", NULL, NULL);
	// Error check
	if (window == NULL) {
		std::cout << "Failed to create GLFW window <<" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Avisamos o glfw que o contexto atual está na janela criada
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	/* Other way
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}*/

	// Especificando o viewport do OpenGL dentro da janela (x1, y1, x2, y2)
	glViewport(0, 0, 800, 800);
	
	// Keeps track of window resizing
			//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Coordenadas dos vértices
	GLfloat vertices[] = {
		//                 COORDINATES               /         COLORS        //
		-0.5f    ,-0.5f * float(sqrt(3))     / 3, 0.0f,  0.8f, 0.3f , 0.02f, // Inferior Esquerdo
		 0.5f    ,-0.5f * float(sqrt(3))     / 3, 0.0f,  0.8f, 0.3f , 0.02f, // Inferior Direito
		 0.0f    , 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  1.0f, 0.6f , 0.32f, // Superior
		-0.5f / 2, 0.5f * float(sqrt(3))     / 6, 0.0f,  0.9f, 0.45f, 0.17f, // Centro Esquerda
		 0.5f / 2, 0.5f * float(sqrt(3))     / 6, 0.0f,  0.9f, 0.45f, 0.17f, // Centro Direita
		 0.0f    ,-0.5f * float(sqrt(3))     / 3, 0.0f,  0.8f, 0.3f , 0.02f  // Centro Inferior
	};

	// Indices que formam cada triangulo
	GLuint indices[] = {
		0, 3, 5, // Lower left  triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1, // Upper triangle
	};

	// Criação do programa de shader
	Shader shaderProgram("default.vert", "default.frag");
	// Criação da array de VBO's e bind dela internamente
	VAO VAO1;
	VAO1.Bind();
	// Criação dos buffers de vertices e de indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	// Inserção do VBO no VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind de todos
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Especifica a cor do background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Limpa o buffer e insere as cores
		glClear(GL_COLOR_BUFFER_BIT);
		// Faz o OpenGL ativar o programa
		shaderProgram.Activate();
		// Bind do VAO para uso pelo OpenGL
		VAO1.Bind();
		// Desenho da forma usando a primitiva de triangulos
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Checa e resolve/chama por qualquer evento GLFW existente
		glfwPollEvents();
	}

	// Deleção do VAO, VBO e do Programa de shaders
	shaderProgram.Delete();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	// Encerra a janela e o GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}