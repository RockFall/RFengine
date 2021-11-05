#ifndef BULLET_H
#define BULLET_H

#include "../../Engine/GameObject/GameObject.h"
//#include "../GameManager/GameManager.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Bullet
{
public:
	Bullet() : speed(0), bulletGO(nullptr) { }
	Bullet(GameObject* go);
	~Bullet();

	void Start();

	void Update(float dt);

	void DoMovement(float dt);

private:
	GameObject* bulletGO;
	float speed;
};

#endif

