#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "AttributeManager/AttributeManager.h"
#include "../../Engine/ResourceManager/ResourceManager.h"
#include "../Engine/SpriteRenderer/SpriteRenderer.h"

#include "Editor/GameEditor.h"

// Represents the current state of the game
enum class GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_DEBUG,
    GAME_WIN,
    GAME_LOSE,
    GAME_CLOSE
};

class Game
{
public:
    // Game State
    GameState    state;
    // Hold input data
    bool         keys[1024];
    glm::vec2 mousePos;
    // Resolution of the game
    unsigned int width, height;

    // ---- CONSTRUCTOR/DESTRUCTOR ----
    Game(unsigned int width, unsigned int height);
    ~Game();

    // Initialize Game State (load all shaders/textures/levels)
    void Init();

    // Loads all Textures defined
	static void LoadAllTextures();

    // Deals with the game state
    void ProcessGameState(float dt);

    // Update is called every frame
    // 'dt': the deltaTime between the last frame and current
    void Update(float dt);
    // Called after Update
    // Do the rendering of current frame
    void Render();
private:
    // Tells the Update() method that, when in DEBUG MODE, wether
    // we can do one iteration or not
    bool canUpdate;

    // Prints on the terminal info about every GameObject with meaning
    void ShowGameInfo();
};

#endif