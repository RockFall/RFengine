#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


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
	/*
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
		-0.5f  ,-0.5f * float(sqrt(3))     / 3, 0.0f, // Inferior Esquerdo
		 0.5f  ,-0.5f * float(sqrt(3))     / 3, 0.0f, // Inferior Direito
		 0.0f  , 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Superior
		-0.5f/2, 0.5f * float(sqrt(3))     / 6, 0.0f, // Centro Esquerda
		 0.5f/2, 0.5f * float(sqrt(3))     / 6, 0.0f, // Centro Direita
		 0.0f  ,-0.5f * float(sqrt(3))     / 3, 0.0f // Centro Inferior
	};

	GLuint indices[] = {
		0, 3, 5, // Lower left  triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1, // Upper triangle
	};

	// Criação de um buffer de vértices e de uma array de VBO's
	GLuint VAO, VBO, EBO;

	// Generating the VAO, VBO and EBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind do VBO e VAO internamente
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Inserção dos dados dos vértices no buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Comunica com o Vertex Shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind do VBO e VAO ao VertexAttribPointer para não mudarmos-los por função acidentalmente
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Diz ao OpenGL qual programa usar
		glUseProgram(shaderProgram);
		// Bind do VAO para uso pelo OpenGL
		glBindVertexArray(VAO);
		// Desenho da forma usando a primitiva de triangulos
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Checa e resolve/chama por qualquer evento GLFW existente
		glfwPollEvents();
	}

	// Deleção do VAO, VBO e do Programa de shaders
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Encerra a janela e o GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}