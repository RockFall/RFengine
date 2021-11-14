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

	// 'name': Name of the GameObject; must be the same as the Script and (optionally) Texture
	// 'pos': glm::vec2 position where the GameObject will be created on
	// 'hasSprite': Must be false if the GameObject is supposed to be invisible
	// 'size': glm::vec2 of the size of the object, conventionally multiple of 10 and a square
	// 'texName': Used for cases when the name of the Texture is different from the name
	static std::string CreateGameObject(std::string name, glm::vec2 pos, bool hasSprite = true, glm::vec2 size = glm::vec2(100.0f, 100.0f), bool hasScript = true, std::string texName = "default");

	static void DestroyGameObject(std::string name);

	static void GameObjectSetSolid(std::string name, bool isSolid);
private:
	// Private constructor so this static class cannot be wrongfully instantiated
	GameEditor() { }
};

#endif