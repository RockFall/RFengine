#include "Bullet.h"
#include "../../Editor/GameEditor.h"

Bullet::Bullet(std::shared_ptr<GameObject> go) :  gameObject(go), speed(0.0f)
{
	Start();
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	speed = 200.0f;
}

void Bullet::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt);
	
	CheckOutScreen();
}

void Bullet::DoMovement(float dt)
{
	gameObject->transform.position.y -= speed * dt;
}

void Bullet::CheckOutScreen() {
	if (gameObject->transform.position.y < -gameObject->transform.size.y)
	{
		GameEditor::DestroyGameObject(gameObject->GetFormattedName());
	}
}
