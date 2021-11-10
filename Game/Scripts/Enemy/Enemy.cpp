#include "Enemy.h"
#include "../../Editor/GameEditor.h"

Enemy::Enemy(GameObject* go) : enemyGO(go), speed(0.0f)
{
	Start();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	speed = 200.0f;
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt);
}

void Enemy::DoMovement(float dt)
{
	//enemyGO->transform.position.y -= speed * dt;
}
