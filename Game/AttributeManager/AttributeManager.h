#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../../Engine/GameObject/Attribute.h"

// Responsible for creating attributes that unite
// Script and GameObject
// Also responsible for calling all Scripts Updates
class AttributeManager
{
public:
	static std::map<std::string, Attribute> CurrentAttributes;

	// Creates all attributes of the initial scene
	static void InitializeAttributes();
	// Calls every Script Update
	static void Update(float dt, bool keys[], glm::vec2 mousePos);
	// Creates and Adds an Attribute on a GameObject
	static void AddGameObjectAttribute(std::string GOName, AttributeType type);
};

#endif

