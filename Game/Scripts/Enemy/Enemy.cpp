#include "Enemy.h"
#include "../../Editor/GameEditor.h"

#include <random>

Enemy::Enemy(GameObject* go) : gameObject(go), speed(0.0f), movementRange(0.0f), xTargetPos(0.0f), originalPos(0.0f), diving(false), initialMove(false), timeSinceLastShot(0.0f), shootingRate(0), bulletSize(0)
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

	shootingRate = 0.75f;
	bulletSize = gameObject->transform.size/2.0f;

	health = ceil(gameObject->transform.size.x / 50.0f);
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (diving && gameObject->transform.position.y <= 520 && gameObject->transform.position.y > originalPos.y + 200.0f) {
		Shoot(dt);
	}

	if (gameObject->transform.position.y >= GameEditor::GAME_HEIGHT && diving == false) {
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
	// random initial shooting time
	timeSinceLastShot = (rand() % 60) / 60.0f;
	std::cout << "Shoting in " << timeSinceLastShot << std::endl;
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
		(gameObject->transform.position + (gameObject->transform.size / 2.0f)),
		true,
		bulletSize,
		true,
		"RNA"
	);

	//GameContext::CurrentObjects["Player"]->transform.position.x - gameObject->transform.position.x

	glm::vec2 playerSize = GameContext::CurrentObjects["Player_0"]->transform.size;
	glm::vec2 playerPos = GameContext::CurrentObjects["Player_0"]->transform.position + playerSize/2.0f;
	glm::vec2 bulletDirection = glm::normalize(playerPos - gameObject->transform.position);

	GameContext::CurrentAttributes[bulletID]->bulletScript.setSpeed(bulletDirection * 400.0f);
	GameContext::CurrentAttributes[bulletID]->bulletScript.setTarget("Player");
	GameEditor::GameObjectSetSolid(bulletID, true);
}

void Enemy::Hit(int damage) {
	this->health -= damage;
	if (health <= 0) {
		GameContext::CurrentAttributes["GameLevel_0"]->gameLevelScript.EnemyDied(gameObject->GetFormattedName());
		GameEditor::DestroyGameObject(gameObject->GetFormattedName());
	}
}
