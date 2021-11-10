#ifndef ENEMY_H
#define ENEMY_H

#include "../../Engine/GameObject/GameObject.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Enemy
{
public:
	// ------ CONSTRUCTOR ------
	Enemy() : speed(0.0f), enemyGO(nullptr) { }
	Enemy(GameObject* go);
	~Enemy();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);

private:
	// Player GameObject
	GameObject* enemyGO;

	float speed;
};

#endif

