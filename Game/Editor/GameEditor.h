#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

#include <map>
#include <string>

#include "../../Engine/GameObject/GameObject.h"
#include "../GameContext/GameContext.h"

class AttributeManager;

// Responsible for dealing with the selection of Textures to load
// and creation of GameObjects
class GameEditor
{
public:
	// Creates and loads all GameObjects defined
	static void LoadInitialScene(unsigned int width, unsigned int height);

	static std::string CreateGameObject(std::string name, glm::vec2 pos, bool hasSprite = true, glm::vec2 size = glm::vec2(100.0f, 100.0f), bool hasScript = true);

	static void DestroyGameObject(std::string name);

	static void GameObjectSetSolid(std::string name, bool isSolid);
private:
	// Private constructor so this static class cannot be wrongfully instantiated
	GameEditor() { }
};

#endif