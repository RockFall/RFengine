#ifndef BASE_BEHAVIOUR_H
#define BASE_BEHAVIOUR_H


#include "../../Engine/GameObject/GameObject.h"
#include <glm/glm.hpp>

class BaseBehaviour {
public:
	// Empty virtual destructor for proper cleanup
	virtual ~BaseBehaviour() {};

	// Called first and once
	virtual void Start() = 0;

	// Called every frame
	virtual void Update(float dt, bool keys[], glm::vec2 mousePos) = 0;
private:
	std::shared_ptr<GameObject> gameObject;
};


#endif