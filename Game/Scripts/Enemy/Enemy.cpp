#include "Enemy.h"
#include "../../Editor/GameEditor.h"

Enemy::Enemy(std::shared_ptr<GameObject> go) : gameObject(go), speed(0.0f), movementRange(0.0f), originalPos(0.0f)
{
	Start();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	speed = 40.0f;
	movementRange = 40.0f;
	originalPos = gameObject->transform.position;
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt);
}

void Enemy::DoMovement(float dt)
{
	
	if (gameObject->transform.position.x > originalPos.x + movementRange){
		gameObject->transform.position.x = originalPos.x + movementRange;
		speed *= -1;
		return;
	}
	else if (gameObject->transform.position.x < originalPos.x - movementRange) {
		gameObject->transform.position.x = originalPos.x - movementRange;
		speed *= -1;
		return;
	}

	gameObject->transform.position.x -= speed * dt;
}
