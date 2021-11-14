#ifndef ENEMY_H
#define ENEMY_H

#include "../BaseBehaviour.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Enemy : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Enemy() : movementRange(0.0f), xTargetPos(0.0f), initialMove(false), originalPos(0.0f), speed(0.0f), diving(false), gameObject(nullptr), timeSinceLastShot(0), shootingRate(0), bulletSize(0)  { }
	Enemy(GameObject* go);
	~Enemy();

	// Called first and once
	void Start();

	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);
	
	// Setters and Getters
	void SetYSpeed(float speed);
	void SetSpeed(glm::vec2 speed);

	void Dive();
	void Shoot(float dt);

private:
	// Player GameObject
	GameObject* gameObject;

	// Speed related
	glm::vec2 speed;

	// Movement position
	glm::vec2 originalPos;
	float xTargetPos;
	unsigned int movementRange;

	// Different behaviours
	bool diving;
	bool initialMove;

	// Shooting variables
	float timeSinceLastShot;
	float shootingRate; // in bullets/second
	int bulletSize;

};

#endif

