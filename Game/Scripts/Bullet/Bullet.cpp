#include "Bullet.h"
#include "../../Editor/GameEditor.h"

Bullet::Bullet(std::shared_ptr<GameObject> go) :  bulletGO(go), speed(0.0f)
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
	bulletGO->transform.position.y -= speed * dt;
}

void Bullet::CheckOutScreen() {
	if (bulletGO->transform.position.y < -bulletGO->transform.size.y)
	{
		GameEditor::DestroyGameObject(bulletGO->GetFormattedName());
	}
}
