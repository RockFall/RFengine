/*******************************************************************
** This code is part of Healthier.
**
** Esse é o trabalho prático 1 da matéria 
** Computação Gráfica - 2021/2 - UFMG
**
** Caio Rocha - 2021421893
******************************************************************/

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "./ResourceManager/ResourceManager.h"
#include "../Game/Game.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Base screen size
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 800;

Game Healthier(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {

	// -------------------- GLFW CONFIG --------------------
	// Initializes GLFW
	glfwInit();
	// Specify the client API (OpenGL) version (in this case 3.3) that 
	// the created context must be compatible
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile (Mordern functions) or Compatibility Profile (Modern + Outdated)
	// Using CORE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Disable resizing
	glfwWindowHint(GLFW_RESIZABLE, false);
	// Creating the main Window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Healthier", NULL, NULL);
	// Error check
	if (window == NULL) {
		std::cout << "Failed to create GLFW window <<" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Telling glfw that the current context has to be into 'window'
	glfwMakeContextCurrent(window);

	// -------------------- OPEN GL CONFIGS --------------------
	// Load GLAD so it configures OpenGL function pointers
	gladLoadGL();
	/* Other way
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}*/

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Specifying the OpenGL's viewport inside the window (x1, y1, x2, y2)
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// -------------------- GAME CONFIG --------------------

	// Initialization
	Healthier.Init();

	// DeltaTime variables
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Handles user input
		Healthier.ProcessInput(deltaTime);

		// Calls for Update in this tick
		Healthier.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Healthier.Render();

		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();

	glfwTerminate();
	return 0;


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


	Shader shaderProgram = ResourceManager::LoadShader("Engine/Shaders/default.vert", "Engine/Shaders/default.frag", nullptr, "Main Shader");

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
	EBO1.Unbind(); // Must be Unbind AFTER the VAO as the VAO
				   // keeps track of the EBO and it's bindance

	// Stores ID of 'uScale' uniform
	GLuint uScaleID = glGetUniformLocation(shaderProgram.ID, "uScale");

	//  ------------------------------ Textures ------------------------------

	Texture2D drama = ResourceManager::LoadTexture("Resources/drama.png", true, "Drama");
	shaderProgram.SetInteger("uTex0", 0, true);

	//  ------------------------- Shader and Uniforms -------------------------

	// Makes OpenGL use our ShaderProgram
	shaderProgram.Activate();
	// Sets uniform value -> CAUTION: has to be done after shaderProgram activation
	glUniform1f(uScaleID, 0);
	//shaderProgram.SetFloat("uScale");

	//  ------------------------- Render Loop -------------------------
	while (!glfwWindowShouldClose(window))
	{
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the buffers and inserts the color
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Texture Bind
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Healthier.keys[key] = true;
		else if (action == GLFW_RELEASE)
			Healthier.keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}