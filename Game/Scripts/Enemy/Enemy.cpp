#include "Enemy.h"
#include "../../Editor/GameEditor.h"

Enemy::Enemy(GameObject* go) : gameObject(go), speed(0.0f), movementRange(0.0f), originalPos(0.0f), diving(false), initialMove(false)
{
	Start();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	speed = glm::vec2(40.0f, 10.0f);
	movementRange = 40.0f;
	originalPos = gameObject->transform.position;
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (diving) {
		
		//return;
	}

	if (gameObject->transform.position.y >= 700 && diving == false) {
		GameContext::gameOver = true;
		GameEditor::DestroyGameObject(this->gameObject->GetFormattedName());
	}

	DoMovement(dt);
}

void Enemy::DoMovement(float dt)
{
	if (diving) {
		//return;
	}

	if (gameObject->transform.position.x > originalPos.x + movementRange){
		gameObject->transform.position.x = originalPos.x + movementRange;
		speed.x *= -1;
		return;
	}
	else if (gameObject->transform.position.x < originalPos.x - movementRange) {
		gameObject->transform.position.x = originalPos.x - movementRange;
		speed.x *= -1;
		return;
	}

	gameObject->transform.position.x -= speed.x * dt;
	gameObject->transform.position.y += speed.y * dt;
}

void Enemy::SetYSpeed(float speed)
{
	this->speed.y = speed;
}

void Enemy::SetSpeed(glm::vec2 speed)
{
	this->speed = speed;
}

void Enemy::Dive()
{
	this->speed = glm::vec2(60.0f, 150.0f);
	diving = true;
}
