#ifndef BULLET_H
#define BULLET_H

#include "../../Engine/GameObject/GameObject.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Bullet
{
public:
	// ------ CONSTRUCTOR ------
	Bullet() : speed(0.0f), bulletGO(nullptr) { }
	Bullet(GameObject* go);
	~Bullet();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);

private:
	// Player GameObject
	GameObject *bulletGO;

	float speed;
};

#endif

