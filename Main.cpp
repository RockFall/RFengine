#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<iostream>

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Base window size
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

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


	// Creating the main 800x800 Window
	GLFWwindow* window = glfwCreateWindow(800, 800, "RFengine", NULL, NULL);
	// Error check
	if (window == NULL) {
		std::cout << "Failed to create GLFW window <<" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Telling glfw that the current context has to be into 'window'
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	/* Other way
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}*/

	// Specifying the OpenGL's viewport inside the window (x1, y1, x2, y2)
	glViewport(0, 0, 800, 800);
	
	// Keeps track of window resizing
	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// ----------------------------------------------------------

	// Vertices coordinates
	GLfloat vertices[] = {
		//   COORDINATES   /     COLORS        /  TEXTURE    //
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Lower left corner
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Upper left corner
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Upper right corner
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Lower right corner
	};

	// Indices for each triangle
	GLuint indices[] = {
		0, 2, 1, // Right triangle
		0, 3, 2  // Left triangle
	};

	// ----------------------------------------------------------

	Shader shaderProgram("default.vert", "default.frag");


	// Creating array of VBO's (VAO) and internally binding it
	VAO VAO1;
	VAO1.Bind();

	// Vertices (VBO) and indices (EBO) buffers creation
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Linking VBO attributes (coordinates, colors, texture data) into VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Stores ID of 'uScale' uniform
	GLuint uScaleID = glGetUniformLocation(shaderProgram.ID, "uScale");

	//  ----------------------------------------------------------

	Texture drama("drama.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	drama.texUnit(shaderProgram, "uTex0", 0);

	//  ----------------------------------------------------------

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the buffers and inserts the color
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Makes OpenGL use our ShaderProgram
		shaderProgram.Activate();
		// Sets uniform value -> CAUTION: has to be done after shaderProgram activation
		glUniform1f(uScaleID, 0.5f);
		drama.Bind();
		// VAO bind for use in OpenGL
		VAO1.Bind();
		// Drawing while using triangles primitive and 
		// swaping buffers to show what we had draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Checks (and calls) for any GLFW existing events
		glfwPollEvents();
	}

	// Deletes all objects we've created
	drama.Delete();
	shaderProgram.Delete();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	// Ends the window and GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}