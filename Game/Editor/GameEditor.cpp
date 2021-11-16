#include "GameEditor.h"
#include "../AttributeManager/AttributeManager.h"

// Hard-coded: Will be replaced in the future with the addition of a Scene
// that contains all information of the current Game
unsigned int GameEditor::GAME_OFFSET = 0;
unsigned int GameEditor::GAME_WIDTH = 0;
unsigned int GameEditor::GAME_HEIGHT = 0;

void GameEditor::LoadInitialScene()
{
	// --------- BACKGROUND -------------
	float BG_HEIGHT = 2100.0f;
	CreateGameObject("Background", glm::vec2(0.0f, GAME_HEIGHT - BG_HEIGHT), true, glm::vec2(GAME_WIDTH, BG_HEIGHT));
	CreateGameObject("Background", glm::vec2(0.0f, GAME_HEIGHT - BG_HEIGHT*2), true, glm::vec2(GAME_WIDTH, BG_HEIGHT));

	std::string ID = CreateGameObject("Background", glm::vec2(0.0f, -BG_HEIGHT), true, glm::vec2(GAME_WIDTH, BG_HEIGHT), true, "Fights01");
	GameContext::CurrentAttributes[ID]->backgroundScript.setSpeed(35.0f);
	ID = CreateGameObject("Background", glm::vec2(0.0f, BG_HEIGHT * 2), true, glm::vec2(GAME_WIDTH, BG_HEIGHT), true, "Fights02");
	GameContext::CurrentAttributes[ID]->backgroundScript.setSpeed(35.0f);

	ID = CreateGameObject("Background", glm::vec2(0.0f, -BG_HEIGHT), true, glm::vec2(GAME_WIDTH, BG_HEIGHT), true, "BackgroundHemacias");
	GameContext::CurrentAttributes[ID]->backgroundScript.setSpeed(100.0f);
	ID = CreateGameObject("Background", glm::vec2(0.0f, -BG_HEIGHT * 2), true, glm::vec2(GAME_WIDTH, BG_HEIGHT), true, "BackgroundHemacias");
	GameContext::CurrentAttributes[ID]->backgroundScript.setSpeed(100.0f);

	// ---- Creating Player ----

	// Initial size of the player paddle

	const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);

	glm::vec2 playerPos = glm::vec2(
		(GAME_WIDTH / 2.0f - PLAYER_SIZE.x / 2.0f),	// Starts in the horizontal middle
		GAME_HEIGHT - PLAYER_SIZE.y				// On the Bottom
	);

	CreateGameObject("Player", playerPos);
	GameContext::CurrentObjects["Player_0"]->SetTag("Player");
	GameContext::CurrentObjects["Player_0"]->isSolid = true;

	// ----------------- GAMELEVEL GAME OBJECT -----------------

	CreateGameObject("GameLevel", glm::vec2(0.0f), false);

	// ------------------------------------------------------------
}

std::string GameEditor::CreateGameObject(std::string name, glm::vec2 pos, bool hasSprite, glm::vec2 size, bool hasScript, std::string texName) {
	int count = 0;
	// While _0 _1 _2 ... exists, keeps counting
	// ultil findind an 'name_N' that doesn't exists
	while (GameContext::CurrentObjects.find(name + "_" + std::to_string(count)) != GameContext::CurrentObjects.end()) {
		count++;
	}
	std::string formatedName = name + "_" + std::to_string(count);

	if (hasSprite == false)
		texName = "None";
	else if (texName == "default")
		texName = name;

	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>
		(name, count, pos, size, ResourceManager::GetTexture(texName));

	GameContext::CurrentObjects.emplace(formatedName, std::move(gameObject));

	if (hasScript)
		AttributeManager::AddGameObjectAttribute(formatedName, name);

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
