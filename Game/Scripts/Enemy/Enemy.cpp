#include "Enemy.h"
#include "../../Editor/GameEditor.h"

#include <random>

Enemy::Enemy(GameObject* go) : gameObject(go), speed(0.0f), movementRange(0.0f), xTargetPos(0.0f), originalPos(0.0f), diving(false), initialMove(false), timeSinceLastShot(0), shootingRate(0), bulletSize(0)
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

	shootingRate = 1.5f;
	bulletSize = 75;
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (diving && gameObject->transform.position.y <= 520) {
		//Shoot(dt);
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
	SetSpeed(glm::vec2(60.0f, 150.0f));
	this->diving = true;
}

void Enemy::Shoot(float dt)
{
	if (timeSinceLastShot > 0) {
		timeSinceLastShot -= dt;
		return;
	}

	timeSinceLastShot = 1 / shootingRate;
	std::string bulletID = GameEditor::CreateGameObject(
		"Bullet",
		gameObject->transform.position - (gameObject->transform.size + glm::vec2(0.0f, 50.0f)),
		true,
		glm::vec2(bulletSize, bulletSize),
		true,
		"Anticorpo"
	);

	//GameContext::CurrentObjects["Player"]->transform.position.x - gameObject->transform.position.x
	//GameEditor::GameObjectSetSolid(bulletID, true);
	glm::vec2 bulletDirection = glm::vec2(0.0f, 0.0f);
	GameContext::CurrentAttributes[bulletID]->bulletScript.setSpeed(bulletDirection);
}
