#include "Player.h"
#include "../../Editor/GameEditor.h"

Player::Player(std::shared_ptr<GameObject> go) :  gameObject(go), timeSinceLastShot(0.0f), shootingRate(0), lives(0)
{
	Start();
}

Player::~Player()
{
}

void Player::Start()
{
	shootingRate = 1;
}

void Player::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt, keys, mousePos);
	Shoot(keys[GLFW_MOUSE_BUTTON_1], dt);
}

void Player::DoMovement(float dt, bool keys[], glm::vec2 mousePos)
{
	gameObject->transform.position.x = mousePos.x - (gameObject->transform.size.x / 2.0f);
}

void Player::Shoot(bool clicking, float dt) {
	if (timeSinceLastShot > 0) {
		timeSinceLastShot -= dt; 
		return;
	}

	if (clicking) {
		timeSinceLastShot = shootingRate;
		GameEditor::CreateGameObject(
			"Bullet", 
			gameObject->transform.position + glm::vec2(0.0f, -50.0f)
		);
	}
}
