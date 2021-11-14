#include "Bullet.h"
#include "../../Editor/GameEditor.h"
#include "../GameLevel/GameLevel.h"
#include "../../../Engine/GameObject/Attribute.h";

Bullet::Bullet(GameObject* go) :  gameObject(go), speed(0.0f), targetName()
{
	Start();
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	targetName = "EnemyV";
}

void Bullet::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt);
	
	CheckOutScreen();

	DoCollisions();
}

void Bullet::DoMovement(float dt)
{
	gameObject->transform.position += speed * dt;
}

void Bullet::setSpeed(glm::vec2 speed)
{
	this->speed = speed;
}

void Bullet::CheckOutScreen() {
	if (gameObject->transform.position.y < -gameObject->transform.size.y)
	{
		GameEditor::DestroyGameObject(gameObject->GetFormattedName());
	}
}

void Bullet::DoCollisions()
{
	for (auto& enemyIt : GameContext::CurrentObjects) {
		if (enemyIt.second->hasBeenDestroyed == false 
			&& enemyIt.second->GetName() == targetName
			&& enemyIt.second->isSolid) {
			if (CheckCollision(enemyIt.second.get(), this->gameObject)) {
				GameContext::CurrentAttributes["GameLevel_0"]->gameLevelScript.EnemyDied(enemyIt.second->GetFormattedName());
				GameEditor::DestroyGameObject(enemyIt.second->GetFormattedName());
				GameEditor::DestroyGameObject(this->gameObject->GetFormattedName());
				return;
			}
		}
	}
}

bool Bullet::CheckCollision(GameObject* one, GameObject* two)
{
	// collision x-axis?
	bool collisionX = one->transform.position.x + one->transform.size.x >= two->transform.position.x &&
		two->transform.position.x + two->transform.size.x >= one->transform.position.x;
	// collision y-axis?
	bool collisionY = one->transform.position.y + one->transform.size.y >= two->transform.position.y &&
		two->transform.position.y + two->transform.size.y >= one->transform.position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}
