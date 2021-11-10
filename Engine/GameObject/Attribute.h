#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../Game/Scripts/Player/Player.h"
#include "../../Game/Scripts/Bullet/Bullet.h"

class GameObject;

enum class AttributeType {
	PLAYER,
	BULLET,
	ENEMY
};

class Attribute {
public:
	GameObject *gameObject;

	std::string type;

	Player playerScript;
	Bullet bulletScript;

	Attribute() : gameObject(nullptr), playerScript(nullptr) { }

	Attribute(const Attribute& a) : gameObject(a.gameObject), playerScript(a.playerScript) { }

	Attribute(GameObject &go, std::string type);

	~Attribute();

	void Update(float dt, bool keys[], glm::vec2 mousePos);
};

#endif