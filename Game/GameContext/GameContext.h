#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <map>
#include <string>
#include <memory>

#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/GameObject/Attribute.h"

class GameContext
{
public:
	static std::map<std::string, std::unique_ptr<GameObject>> CurrentObjects;
	static std::map<std::string, std::unique_ptr<Attribute>> CurrentAttributes;

	static bool gameOver;

private:
	GameContext();
};

#endif

