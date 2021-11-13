#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <map>
#include <string>
#include <memory>

class Attribute;
class GameObject;

class GameContext
{
public:
	static std::map<std::string, std::shared_ptr<GameObject>> CurrentObjects;
	static std::map<std::string, std::shared_ptr<Attribute>> CurrentAttributes;

	static bool gameOver;

private:
	GameContext();
};

#endif

