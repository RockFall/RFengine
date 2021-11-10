#ifndef PLAYER_H
#define PLAYER_H

#include "../../Engine/GameObject/GameObject.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Player
{
public:
	// ------ CONSTRUCTOR ------
	Player() : timeSinceLastShot(0.0f), shootingRate(0), lives(0), playerGO(nullptr) { }
	Player(std::shared_ptr<GameObject> go);
	~Player();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the player GameObject move in the X-axis following the mouse
	void DoMovement(float dt, bool keys[], glm::vec2 mousePos);
	// Creates a bullet object when Mouse Left Click is pressed
	// Has a cooldown rate
	void Shoot(bool clicking, float dt);

private:
	// Player GameObject
	std::shared_ptr<GameObject> playerGO;

	int lives;

	// Shooting variables
	float timeSinceLastShot;
	int shootingRate; // in bullets/second
};

#endif

