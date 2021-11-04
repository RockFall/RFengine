#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Texture/Texture2D.h"
#include "../SpriteRenderer/SpriteRenderer.h"

// An element of a scene. 
// The GameObject holds information of it's position, size, velocity
// color, rotation and others.
//
// Hard-coded for having the Texture2D inside it but ideally it will
// be a component that we can choose to add or not
class GameObject {
public:
	// ----- State Data -----
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	bool isSolid;
	bool hasBeenDestroyed;

	// Rendering State
	Texture2D sprite;


	// ----- Constructors -----
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	// Draw the Sprite
	virtual void Draw(SpriteRenderer& renderer);

};


#endif