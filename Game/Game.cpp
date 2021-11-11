#include "Game.h"

// Deals with sprite rendering
SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
	: state(GameState::GAME_ACTIVE), keys(), mousePos(0.0f, 0.0f), width(width), height(height)
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

	GameEditor::LoadInitialScene(this->width, this->height);
}

void Game::LoadAllTextures()
{
	ResourceManager::LoadTexture("Resources/Linfocito_B.png", true, "Player");
	ResourceManager::LoadTexture("Resources/Anticorpo.png", true, "Bullet");
	ResourceManager::LoadTexture("Resources/Virus.png", true, "EnemyV");
	ResourceManager::LoadTexture("Resources/None.png", true, "None");
	ResourceManager::LoadTexture("Resources/Background.png", true, "Background");
}

// Called every frame first
void Game::ProcessInput(float dt)
{
	// ESC to quit game
	if (keys[GLFW_KEY_ESCAPE] == true) {
		state = GameState::GAME_CLOSE;
		return;
	}

	if (this->state == GameState::GAME_ACTIVE) {
		
	}
}

// Called every frame second
void Game::Update(float dt)
{
	AttributeManager::Update(dt, keys, mousePos);

	// Checks and destroy gameObjects if needed
	for (auto it = GameContext::CurrentObjects.cbegin(), next_it = it; it != GameContext::CurrentObjects.cend(); it = next_it)
	{
		++next_it;
		if (it->second->hasBeenDestroyed) {
			std::string name = it->second->GetFormattedName();
			int eA = GameContext::CurrentAttributes.erase(name);
			int eO = GameContext::CurrentObjects.erase(name);
			if (eA && eO)
				std::cout << "DESTROYED: " << name << std::endl;
			else if (eO)
				std::cout << "DESTROYED OBJECT WITHOUT ATTRIBUTE: " << name << std::endl;
		}
	}
}

// Called every frame at last
void Game::Render()
{
	// Do the rendering of all GameObjects on Scene 
	// in their current location
	for (auto iter : GameContext::CurrentObjects)
	{
		GameObject go = *iter.second;
		Renderer->DrawSprite(
			go.sprite.texture,
			go.transform.position,
			go.transform.size,
			go.transform.rotation,
			go.sprite.color);
	} 
}




