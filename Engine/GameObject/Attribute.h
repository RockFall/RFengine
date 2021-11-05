#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../Game/Player/Player.h"

class GameObject;
class Transform;

enum class AttributeType {
	PLAYER,
	ENEMY
};

class Attribute {
public:
	GameObject *gameObject;
	Transform *transform;

	Player playerScript;

	Attribute() : gameObject(nullptr), transform(nullptr), playerScript(nullptr) { }

	Attribute(const Attribute& a) : gameObject(a.gameObject), transform(a.transform), playerScript(a.playerScript) { }

	Attribute(GameObject *go, AttributeType type);

	~Attribute();
};

#endif