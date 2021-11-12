#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "../BaseBehaviour.h"

#include <set>
#include <vector>

class GameLevel : BaseBehaviour
{
public:
	// Level State data
	std::set<std::string> enemies;

	// ------ CONSTRUCTORS ------
	GameLevel() : gameObject(nullptr), enemies(), level(0) { };
	GameLevel(std::shared_ptr<GameObject> go);
	~GameLevel();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void Load(std::string file);

	void GenerateLevel(std::vector<std::vector<char>> enemyData);

	void EnemyDied(std::string name);

private:
	std::shared_ptr<GameObject> gameObject;
	int level;
};

#endif
