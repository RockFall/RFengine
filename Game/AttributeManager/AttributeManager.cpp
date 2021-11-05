#include "AttributeManager.h"

// Initialize static variable
std::map<std::string, Attribute> AttributeManager::CurrentAttributes;

void AttributeManager::InitializeAttributes()
{
	AddGameObjectAttribute("Player_0", AttributeType::PLAYER);
}

void AttributeManager::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	// Calling Updates on every script
	CurrentAttributes["Player_0"].playerScript.Update(dt, keys, mousePos);
}

void AttributeManager::AddGameObjectAttribute(std::string GOName, AttributeType type) {
	GameObject* playerGO = &GameEditor::CurrentObjects[GOName];
	Attribute attr(playerGO, type);
	CurrentAttributes.emplace(GOName, attr);
}
