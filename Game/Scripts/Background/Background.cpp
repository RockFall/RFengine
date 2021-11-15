#include "Background.h"
#include "../../GameContext/GameContext.h"

Background::Background(GameObject* go) : speed(), gameObject(go)
{
	Start();
}

Background::~Background()
{
}

void Background::Start()
{
	this->speed = 100.0f;
}

void Background::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (gameObject->transform.position.y <= -2100) {
		gameObject->transform.position.y += 2100*2;
	}

	gameObject->transform.position.y -= speed * dt;
}

void Background::setSpeed(float speed) {
	this->speed = speed;
}
