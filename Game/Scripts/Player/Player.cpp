#include "Player.h"
#include "../../Editor/GameEditor.h"

Player::Player(GameObject* go) :  gameObject(go), timeSinceLastShot(0.0f), shootingRate(0.0f), lives(0), speed(0)
{
	Start();
}

Player::~Player()
{
}

void Player::Start()
{
	lives = 2;

	shootingRate = 20.0f;
	bulletSize = 75;
	speed = 60.0f;
}

void Player::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt, keys, mousePos);
	Shoot(keys[GLFW_MOUSE_BUTTON_LEFT], dt);
}

void Player::DoMovement(float dt, bool keys[], glm::vec2 mousePos)
{
	float target = mousePos.x - (gameObject->transform.size.x / 2.0f);
	gameObject->transform.position.x += (target - gameObject->transform.position.x) * speed * dt;

	if (gameObject->transform.position.x >= GameEditor::GAME_WIDTH - gameObject->transform.size.x) {
		gameObject->transform.position.x = GameEditor::GAME_WIDTH - gameObject->transform.size.x;
	}
	else if (gameObject->transform.position.x <= 0) {
		gameObject->transform.position.x = 0;
	}
}

void Player::Shoot(bool clicking, float dt) {
	if (timeSinceLastShot > 0) {
		timeSinceLastShot -= dt; 
		return;
	}

	if (clicking) {
		// Resets refresh time
		timeSinceLastShot = 1/shootingRate;
		// Creates Bullet GameObject
		std::string bulletID = GameEditor::CreateGameObject(
			"Bullet",
			gameObject->transform.position + glm::vec2(0.0f, -50.0f),
			true,
			glm::vec2(bulletSize, bulletSize),
			true,
			"Anticorpo"
		);
		// Bullet variables setup
		GameContext::CurrentObjects[bulletID]->SetTag("Bullet");
		GameEditor::GameObjectSetSolid(bulletID, true);
		GameContext::CurrentAttributes[bulletID]->bulletScript.setSpeed(glm::vec2(0.0f, -1000.0f));

		// Play shoot sound
		GameContext::SoundQueue.push(std::make_pair("Player Shoot", 0.2f));
	}
}

void Player::Hit(int damage, float dt)
{
	this->lives--;
	if (lives <= 0) {
		Die(dt);
	}
}

void Player::Die(float dt)
{
	GameContext::CurrentObjects[gameObject->GetFormattedName()]->hasBeenDestroyed = true;
	GameContext::gameOver = true;

	/*
	for (auto& go : GameContext::CurrentObjects) {
		if (go.second->GetFormattedName() != "Background_0" && 
			go.second->GetFormattedName() != "Background_1" &&
			go.second->GetTag() == "Background") {
			float speed = GameContext::CurrentAttributes[go.second->GetFormattedName()]->backgroundScript.getSpeed();
			GameContext::CurrentAttributes[go.second->GetFormattedName()]->backgroundScript.setSpeed(30.0f);
		}
		
	}*/
}

glm::vec2 Player::getSpeed()
{
	return glm::vec2(this->speed, 0.0f);
}
