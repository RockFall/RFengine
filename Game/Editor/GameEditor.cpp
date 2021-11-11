#include "GameEditor.h"
#include "../AttributeManager/AttributeManager.h"

void GameEditor::LoadInitialScene(unsigned int width, unsigned int height)
{
	// --------- BACKGROUND -------------
	
	CreateGameObject("Background", glm::vec2(0.0f), true, glm::vec2(600.0f, 700.0f), false);

	// ---- Creating Player ----

	// Initial size of the player paddle

	const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);

	glm::vec2 playerPos = glm::vec2(
		width / 2.0f - PLAYER_SIZE.x / 2.0f,	// Starts in the horizontal middle
		height - PLAYER_SIZE.y				// On the Bottom
	);

	CreateGameObject("Player", playerPos);

	// ----------------- GAMELEVEL GAME OBJECT -----------------

	CreateGameObject("GameLevel", glm::vec2(0.0f), false);

	// ------------------------------------------------------------
}

std::string GameEditor::CreateGameObject(std::string name, glm::vec2 pos, bool hasSprite, glm::vec2 size, bool hasScript) {
	int count = 0;
	// While _0 _1 _2 ... exists, keeps counting
	// ultil findind an 'name_N' that doesn't exists
	while (GameContext::CurrentObjects.find(name + "_" + std::to_string(count)) != GameContext::CurrentObjects.end()) {
		count++;
	}
	std::string formatedName = name + "_" + std::to_string(count);

	std::string texName = name;
	if (hasSprite == false)
		texName = "None";

	GameContext::CurrentObjects[formatedName] = std::make_shared<GameObject>
		(name, count, pos, size, ResourceManager::GetTexture(texName));

	// Calls creation of Attribute for the GameObject 'formatedName' and type 'name'
	std::string type = name;
	if (name == "EnemyV") {
		type = "Enemy";
	}

	if (hasScript)
		AttributeManager::AddGameObjectAttribute(formatedName, type);

	return formatedName;
}

void GameEditor::DestroyGameObject(std::string name)
{
	GameContext::CurrentObjects[name]->hasBeenDestroyed = true;
}

void GameEditor::GameObjectSetSolid(std::string name, bool isSolid)
{
	GameContext::CurrentObjects[name]->isSolid = isSolid;
}
