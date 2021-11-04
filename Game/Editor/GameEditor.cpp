#include "GameEditor.h"

// Instantiation of static variable
std::map<std::string, GameObject> GameEditor::CurrentObjects;

void GameEditor::LoadInitialScene(unsigned int width, unsigned int height)
{
	// ---- Creating Player ----

	// Initial size of the player paddle
	const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);
	// Initial velocity of the player paddle
	const float PLAYER_VELOCITY(500.0f);

	glm::vec2 playerPos = glm::vec2(
		width / 2.0f - PLAYER_SIZE.x / 2.0f,	// Starts in the horizontal middle
		height - PLAYER_SIZE.y				// On the Bottom
	);
	GameObject Player(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("linfocito_b"));
	CurrentObjects["Player"] = Player;

	// --------------------------

	// Test
	const glm::vec2 ENEMY_SIZE(100.0f, 100.0f);
	const float ENEMY_VELOCITY(0.0f);

	glm::vec2 enemyPos = glm::vec2(
		width/2.0f - ENEMY_SIZE.x/2.0f,
		20 + ENEMY_SIZE.y
	);
	GameObject Enemy(enemyPos, ENEMY_SIZE, ResourceManager::GetTexture("anticorpo"));
	CurrentObjects["Test"] = Enemy;
}

void GameEditor::LoadAllTextures()
{
	ResourceManager::LoadTexture("Resources/Linfocito_B.png", true, "linfocito_b");
	ResourceManager::LoadTexture("Resources/Anticorpo.png", true, "anticorpo");
}