#include "Game.h"
#include <cstdlib>

// Deals with sprite rendering
SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
	: state(GameState::GAME_ACTIVE), keys(), mousePos(0.0f, 0.0f), width(width), height(height), canUpdate(true)
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
	ResourceManager::LoadTexture("Resources/Anticorpo.png", true, "Anticorpo");

	ResourceManager::LoadTexture("Resources/VirusEsfera.png", true, "VirusEsfera");
	ResourceManager::LoadTexture("Resources/VirusPoliedro.png", true, "VirusPoliedro");
	ResourceManager::LoadTexture("Resources/VirusComplexo.png", true, "VirusComplexo");
	ResourceManager::LoadTexture("Resources/Bacteria.png", true, "Bacteria");
	ResourceManager::LoadTexture("Resources/RNA.png", true, "RNA");

	ResourceManager::LoadTexture("Resources/None.png", true, "None");
	ResourceManager::LoadTexture("Resources/BackgroundBig.png", true, "Background");
	ResourceManager::LoadTexture("Resources/BackgroundHemacias.png", true, "BackgroundHemacias");
	ResourceManager::LoadTexture("Resources/Fights01.png", true, "Fights01");
	ResourceManager::LoadTexture("Resources/Fights02.png", true, "Fights02");

}

// Called every frame first
void Game::ProcessGameState(float dt)
{
	// ESC to quit game
	if (keys[GLFW_KEY_ESCAPE] == true) {
		state = GameState::GAME_CLOSE;
		return;
	}

	// If on debug mode, can do one iteration by pressing MIDDLE MOUSE BUTTON
	if (this->state == GameState::GAME_DEBUG) {
		if (keys[GLFW_MOUSE_BUTTON_MIDDLE] == true) {
			keys[GLFW_MOUSE_BUTTON_MIDDLE] = false;
			canUpdate = true;
			return;
		}
	}

	// If the game is going on
	if (this->state == GameState::GAME_ACTIVE) {
		// Check RIGHT MOUSE BUTTON for pausing
		if (keys[GLFW_MOUSE_BUTTON_RIGHT] == true) {
			keys[GLFW_MOUSE_BUTTON_RIGHT] = false;
			std::cout << "GAME PAUSED" << std::endl;
			state = GameState::GAME_PAUSE;
			return;
		}
		// Check MIDDLE MOUSE BUTTON for entering debug mode
		if (keys[GLFW_MOUSE_BUTTON_MIDDLE] == true) {
			keys[GLFW_MOUSE_BUTTON_MIDDLE] = false;
			std::cout << "GAME IN DEBUG MODE" << std::endl;
			state = GameState::GAME_DEBUG;
			return;
		}

		if (GameContext::gameOver == true) {
			state = GameState::GAME_LOSE;
		}
	}

	// Check RIGHT MOUSE BUTTON for unpausing or getting out of debug mode
	if (this->state == GameState::GAME_PAUSE || this->state == GameState::GAME_DEBUG) {
		if (keys[GLFW_MOUSE_BUTTON_RIGHT] == true) {
			keys[GLFW_MOUSE_BUTTON_RIGHT] = false;
			std::cout << "GAME RESUMED" << std::endl;
			state = GameState::GAME_ACTIVE;
			return;
		}
	}
}

// Called every frame second
void Game::Update(float dt)
{
	if (state == GameState::GAME_LOSE) {
		std::cout << "GAME OVERRRRR" << std::endl;
		return; 
	}

	// If the game is paused
	if (state == GameState::GAME_PAUSE) {
		return;
	}

	if (state == GameState::GAME_DEBUG) {
		if (canUpdate == false) {
			return;
		}
		// If can update, show info on terminal and do one iteration
		ShowGameInfo();
		canUpdate = false;
	}

	AttributeManager::Update(dt, keys, mousePos);

	// Checks and destroy gameObjects if needed
	for (auto it = GameContext::CurrentObjects.cbegin(), next_it = it; it != GameContext::CurrentObjects.cend(); it = next_it)
	{
		++next_it;
		if (it->second->hasBeenDestroyed) {
			std::string name = it->second->GetFormattedName();
			size_t eA = GameContext::CurrentAttributes.erase(name);
			size_t eO = GameContext::CurrentObjects.erase(name);

			/*
			if (eA && eO)
				std::cout << "DESTROYED: " << name << std::endl;
			else if (eO)
				std::cout << "DESTROYED OBJECT WITHOUT ATTRIBUTE: " << name << std::endl;*/
		}
	}
}

// Called every frame at last
void Game::Render()
{
	// Do the rendering of all GameObjects on Scene 
	// in their current location
	for (auto& iter : GameContext::CurrentObjects)
	{
		GameObject& go = *iter.second;
		Renderer->DrawSprite(
			go.sprite.texture,
			go.transform.position,
			go.transform.size,
			go.transform.rotation,
			go.sprite.color);
	}
}

void Game::ShowGameInfo()
{
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
	// Clears the terminal
	system(CLEAR);

	std::cout << "    GAME IN DEBUG MODE" << std::endl;

	// Prints the Player at the top
	GameObject playerGO = *GameContext::CurrentObjects["Player_0"];
	std::cout << "----------------------------\n"
		<< "GameObject: " << playerGO.GetFormattedName() << "\n"
		<< "Position:   (" << playerGO.transform.position.x << ", " << playerGO.transform.position.y << ")" << std::endl;

	// Prints anything else
	for (auto& iter : GameContext::CurrentObjects)
	{
		GameObject gameObject = *iter.second;

		if (gameObject.GetName() == "EnemyV" ||
			gameObject.GetName() == "Bullet") {
			std::cout << "----------------------------\n"
				<< "GameObject: " << gameObject.GetFormattedName() << "\n"
				<< "Position:   (" << gameObject.transform.position.x << ", " << gameObject.transform.position.y << ")" << std::endl;
		}
	}
}




