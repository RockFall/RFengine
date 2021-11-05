#include "Attribute.h"

Attribute::Attribute(GameObject* go, AttributeType type) :
	gameObject(go),
	transform(&(go->transform))
{

	switch (type)
	{
	case AttributeType::PLAYER:
		//this->player = new Player(gameObject);
		this->playerScript = Player(gameObject);
		break;
	case AttributeType::ENEMY:
		break;
	default:
		this->playerScript = Player();
		break;
	}
}

Attribute::~Attribute()
{
	/*
	std::cout << "Destructing ATTRIBUTE; player=" << player << std::endl;
	if (player != nullptr) {
		std::cout << "Before delete" << std::endl;
		delete player;
		std::cout << "After delete" << std::endl;
	}*/
}
