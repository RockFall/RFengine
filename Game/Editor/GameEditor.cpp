#include "GameEditor.h"
#include "../AttributeManager/AttributeManager.h"

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

	glm::vec2 enemyPos = glm::vec2(
		width/2.0f - ENEMY_SIZE.x/2.0f,
		20 + ENEMY_SIZE.y
	);

	CreateGameObject("EnemyV", enemyPos);
}

void GameEditor::CreateGameObject(std::string name, glm::vec2 pos, glm::vec2 size) {
	int count = 0;
	// While _0 _1 _2 ... exists, keeps counting
	// ultil findind an 'name_N' that doesn't exists
	while (GameContext::CurrentObjects.find(name + "_" + std::to_string(count)) != GameContext::CurrentObjects.end()) {
		count++;
	}
	std::string formatedName = name + "_" + std::to_string(count);

	//GameObject gameObject(name, count, pos, size, ResourceManager::GetTexture(name));
	GameContext::CurrentObjects[formatedName] = std::make_shared<GameObject>
		(name, count, pos, size, ResourceManager::GetTexture(name));

	// Calls creation of Attribute for the GameObject 'formatedName' and type 'name'
	AttributeManager::AddGameObjectAttribute(formatedName, name);
}

void GameEditor::DestroyGameObject(std::string name)
{
	GameContext::CurrentObjects[name]->hasBeenDestroyed = true;
}
