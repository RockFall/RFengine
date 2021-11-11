#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "../BaseBehaviour.h"

#include <vector>

class GameLevel : BaseBehaviour
{
public:
	// Level State data
	std::vector<std::string> enemies;

	// ------ CONSTRUCTORS ------
	GameLevel() : gameObject(nullptr), enemies() { };
	GameLevel(std::shared_ptr<GameObject> go);
	~GameLevel();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void Load(const char* file);

	void GenerateLevel(std::vector<std::vector<char>> enemyData);

private:
	std::shared_ptr<GameObject> gameObject;
};

#endif
