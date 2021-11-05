#ifndef PLAYER_H
#define PLAYER_H

#include "../Editor/GameEditor.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Player
{
public:
	// ------ CONSTRUCTOR ------
	Player() : timeSinceLastShot(0.0f), shootingRate(0), lives(0), playerGO(nullptr) { }
	Player(GameObject* go);
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
	GameObject *playerGO;

	int lives;

	// Shooting variables
	float timeSinceLastShot;
	int shootingRate; // in bullets/second
};

#endif

