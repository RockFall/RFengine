#include "AttributeManager.h"
#include "../../Engine/GameObject/Attribute.h"

void AttributeManager::StartAttributes()
{
	for (auto iter : GameContext::CurrentAttributes)
	{
		Attribute& attr = *iter.second;
		attr.Start();
	}
}

void AttributeManager::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	// Calling Updates on every script
	//GameContext::CurrentAttributes["Player_0"]->playerScript.Update(dt, keys, mousePos);
	for (auto iter : GameContext::CurrentAttributes)
	{
		Attribute &attr = *iter.second;
		attr.Update(dt, keys, mousePos);
	}
}

void AttributeManager::AddGameObjectAttribute(std::string GOName, std::string type) {
	std::shared_ptr<GameObject> gameObject = GameContext::CurrentObjects[GOName];
	GameContext::CurrentAttributes[GOName] = std::make_shared<Attribute>(gameObject, type);
}
