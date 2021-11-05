#include "GameEditor.h"
//#include "../AttributeManager/AttributeManager.h"

// Instantiation of static variables
std::map<std::string, GameObject> GameEditor::CurrentObjects;

void GameEditor::LoadInitialScene(unsigned int width, unsigned int height)
{
	// ---- Creating Player ----

	// Initial size of the player paddle

	const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);

	glm::vec2 playerPos = glm::vec2(
		width / 2.0f - PLAYER_SIZE.x / 2.0f,	// Starts in the horizontal middle
		height - PLAYER_SIZE.y				// On the Bottom
	);

	CreateGameObject("Player", playerPos);

	// --------------------------

	// Test
	const glm::vec2 ENEMY_SIZE(100.0f, 100.0f);
	const float ENEMY_VELOCITY(0.0f);

	glm::vec2 enemyPos = glm::vec2(
		width/2.0f - ENEMY_SIZE.x/2.0f,
		20 + ENEMY_SIZE.y
	);

	CreateGameObject("Bullet", enemyPos);
}

void GameEditor::CreateGameObject(std::string name, glm::vec2 pos, glm::vec2 size) {
	int count = 0;
	// While _0 _1 _2 ... exists, keeps counting
	// ultil findind an 'name_N' that doesn't exists
	while (CurrentObjects.find(name + "_" + std::to_string(count)) != CurrentObjects.end()) {
		count++;
	}
	std::string formatedName = name + "_" + std::to_string(count);

	GameObject gameObject(name, count, pos, size, ResourceManager::GetTexture(name));
	CurrentObjects[formatedName] = gameObject;

	//AttributeManager::AddGameObjectAttribute()
}