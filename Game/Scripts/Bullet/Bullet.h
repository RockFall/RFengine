#ifndef BULLET_H
#define BULLET_H

#include "../BaseBehaviour.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Bullet : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Bullet() : speed(0.0f), gameObject(nullptr) { }
	Bullet(std::shared_ptr<GameObject> go);
	~Bullet();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);

	// Checks if the bullet is out of the screen, is so, destroys it
	void CheckOutScreen();

	void DoCollisions();

	bool CheckCollision(std::shared_ptr<GameObject> one, std::shared_ptr<GameObject> two);

private:
	// Player GameObject
	std::shared_ptr<GameObject> gameObject;

	float speed;
};

#endif

