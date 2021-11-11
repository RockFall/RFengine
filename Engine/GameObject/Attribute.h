#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../Game/Scripts/Player/Player.h"
#include "../../Game/Scripts/Bullet/Bullet.h"
#include "../../Game/Scripts/GameLevel/GameLevel.h"
#include "../../Game/Scripts/Enemy/Enemy.h"

class GameObject;

class Attribute {
public:
	std::shared_ptr<GameObject> gameObject;

	std::string type;

	Player playerScript;
	Enemy enemyScript;
	Bullet bulletScript;
	GameLevel gameLevelScript;

	Attribute() : gameObject(nullptr), playerScript(nullptr) { }

	Attribute(const Attribute& a) : gameObject(a.gameObject), playerScript(a.playerScript) { }

	Attribute(std::shared_ptr<GameObject> go, std::string type);

	~Attribute();

	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void Start();
};

#endif