#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../ResourceManager/ResourceManager.h"

#include "Transform.h"


struct Sprite {
	Texture2D texture;
	glm::vec3 color;
};

// An element of a scene. 
// The GameObject holds information of it's position, size, velocity
// color, rotation and others.
//
// Hard-coded for having the Texture2D inside it but ideally it will
// be a component that we can choose to add or not
class GameObject {
public:
	// ----- State Data -----
	Transform transform;
	Sprite sprite;
	bool isSolid;

	bool hasBeenDestroyed;

	// ----- Constructors -----
	GameObject();
	~GameObject();
	GameObject(std::string name,int id, glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));


	// ---- GETTERS ----
	std::string GetName();
	int GetID();
	std::string GetFormattedName();
	std::string GetTag();

	// ---- Setters ----
	void SetTag(std::string tagName);

	// Unites name and id into name_id
	static std::string FormattedName(std::string name, int id);

private:
	std::string name;
	std::string tag;
	int id;
};

#endif
