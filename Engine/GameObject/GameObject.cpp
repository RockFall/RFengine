#include "GameObject.h"

GameObject::GameObject()
	: isSolid(false), hasBeenDestroyed(false) {
	this->name = "";
	this->id = 0;
	this->transform.position = glm::vec2(0.0f, 0.0f);
	this->transform.size = glm::vec2(1.0f, 1.0f);
	this->transform.velocity = glm::vec2(0.0f, 0.0f);
	this->transform.rotation = 0.0f;

	this->sprite.color = glm::vec3(1.0f);
	this->sprite.texture = Texture2D();
}
GameObject::~GameObject()
{
	int a = 1;
}


GameObject::GameObject(std::string name, int id, glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: isSolid(false), hasBeenDestroyed(false) {
	this->name = name;
	this->id = id;
	this->transform.position = pos;
	this->transform.size = size;
	this->transform.velocity = velocity;
	this->transform.rotation = 0.0f;
	this->sprite.color = color;
	this->sprite.texture = texture;
}

std::string GameObject::GetName()
{
	return this->name;
}

int GameObject::GetID()
{
	return this->id;
}

std::string GameObject::GetFormattedName() {
	return (this->name + "_" + std::to_string(this->id));
}

std::string GameObject::FormattedName(std::string name, int id)
{
	return (name + "_" + std::to_string(id));
}
