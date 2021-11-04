#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

#include <map>
#include <string>

#include "../../Engine/ResourceManager/ResourceManager.h"
#include "../../Engine/SpriteRenderer/SpriteRenderer.h"
#include "../../Engine/GameObject/GameObject.h"

// Responsible for dealing with the selection of Textures to load
// and creation of GameObjects
class GameEditor
{
public:
	static std::map<std::string, GameObject> CurrentObjects;

	static void LoadInitialScene(unsigned int width, unsigned int height);

	static void LoadAllTextures();
private:
	GameEditor() { }
};

#endif