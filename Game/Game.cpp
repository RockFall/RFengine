#include "Game.h"

// Deals with sprite rendering
SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
	: state(GAME_ACTIVE), keys(), width(width), height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

// Called once before everything
void Game::Init()
{
	// Loading Shaders
	ResourceManager::LoadShader("./Engine/Shaders/sprite.vs", "./Engine/Shaders/sprite.frag", nullptr, "sprite");

	// Configuring Shaders
	// Applying orthigraphic projection over World Space (as we don't have a needed camera)
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(
		0.0f, // Left
		(GLfloat)this->width, // Right
		(GLfloat)this->height, // Bottom
		0.0f, // Top
		-1.0f, // Near
		1.0f // Far
	);

	// Set texture slot to default 0
	ResourceManager::GetShader("sprite").SetInteger("image", 0, true);
	// Set projection matrix to the created one
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection, true);

	// Creates the SpriteRenderer with the just created shader
	Shader spriteShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(spriteShader);

	// Loading tetures
	LoadAllTextures();

	GameEditor::LoadInitialScene(*this);
}

void Game::LoadAllTextures()
{
	ResourceManager::LoadTexture("Resources/Linfocito_B.png", true, "linfocito_b");
}

// Called every frame first
void Game::ProcessInput(float dt)
{
}

// Called every frame second
void Game::Update(float dt)
{
}

// Called every frame at last
void Game::Render()
{
	// Do the rendering textures in their given location
	/*Texture2D linfocitoTex = ResourceManager::GetTexture("linfocito_b");
	Renderer->DrawSprite(
		linfocitoTex,
		glm::vec2(this->width/2 - 50.0f, this->height-150.0f),
		glm::vec2(100.0f, 100.0f),
		0.0f,
		glm::vec3(1.0f, 1.0f, 1.0f));
	*/

	for (auto iter : GameEditor::CurrentObjects)
	{
		iter.second.Draw(*Renderer);
	}
}




