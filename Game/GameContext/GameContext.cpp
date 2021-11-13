#include "GameContext.h"

std::map<std::string, std::shared_ptr<GameObject>> GameContext::CurrentObjects;
std::map<std::string, std::shared_ptr<Attribute>> GameContext::CurrentAttributes;

bool GameContext::gameOver = false;