#ifndef ENEMY_H
#define ENEMY_H

#include "../BaseBehaviour.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Enemy : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Enemy() : movementRange(0.0f), originalPos(0.0f), speed(0.0f), gameObject(nullptr) { }
	Enemy(std::shared_ptr<GameObject> go);
	~Enemy();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);

private:
	// Player GameObject
	std::shared_ptr<GameObject> gameObject;

	float speed;
	glm::vec2 originalPos;
	unsigned int movementRange;
};

#endif

