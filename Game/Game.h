#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "Editor/GameEditor.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_WIN,
    GAME_LOSE
};

class Game
{
public:
    // Game State
    GameState    state;
    // Hold input data
    bool         keys[1024];
    // Resolution of the game
    unsigned int width, height;

    // ---- CONSTRUCTOR/DESTRUCTOR ----
    Game(unsigned int width, unsigned int height);
    ~Game();

    // Initialize Game State (load all shaders/textures/levels)
    void Init();

    // Deals with input of the game
    void ProcessInput(float dt);

    // Update is called every frame
    // 'dt': the deltaTime between the last frame and current
    void Update(float dt);
    // Called after Update
    // Do the rendering of current frame
    void Render();
private:

    void LoadAllTextures();
};

#endif