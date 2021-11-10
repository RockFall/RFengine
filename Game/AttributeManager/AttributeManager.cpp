#include "AttributeManager.h"
#include "../../Engine/GameObject/Attribute.h"

// Initialize static variable
//std::map<std::string, Attribute> AttributeManager::CurrentAttributes;

void AttributeManager::InitializeAttributes()
{
	AddGameObjectAttribute("Player_0", "Player");
}

void AttributeManager::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	// Calling Updates on every script
	//GameContext::CurrentAttributes["Player_0"]->playerScript.Update(dt, keys, mousePos);
	for (auto iter : GameContext::CurrentAttributes)
	{
		Attribute &go = *iter.second;
		go.Update(dt, keys, mousePos);
	}
}

void AttributeManager::AddGameObjectAttribute(std::string GOName, std::string type) {
	std::shared_ptr<GameObject> playerGO = GameContext::CurrentObjects[GOName];
	GameContext::CurrentAttributes[GOName] = std::make_shared<Attribute>(playerGO, type);
}
