#include "GameContext.h"

std::map<std::string, std::unique_ptr<GameObject>> GameContext::CurrentObjects;
std::map<std::string, std::unique_ptr<Attribute>> GameContext::CurrentAttributes;

bool GameContext::gameOver = false;