#include "Attribute.h"

Attribute::Attribute(GameObject& go, std::string type) : gameObject(&go)
{
	this->type = type;

	if (type == "Player") {
		//this->player = new Player(gameObject);
		this->playerScript = Player(gameObject);
	}
	else if (type == "Enemy") {

	}
	else if (type == "Bullet") {
		this->bulletScript = Bullet(gameObject);
	}
	else{
		this->playerScript = Player();
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

void Attribute::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (type == "Player") {
		//this->player = new Player(gameObject);
		this->playerScript.Update(dt, keys, mousePos);
	}
	else if (type == "Enemy") {

	}
	else if (type == "Bullet") {
		this->bulletScript.Update(dt, keys, mousePos);
	}
}
