#include "GameEditor.h"

void GameEditor::LoadInitialScene(Game &game)
{

	// ---- Creating Player ----

	// Initial size of the player paddle
	const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);
	// Initial velocity of the player paddle
	const float PLAYER_VELOCITY(500.0f);

	glm::vec2 playerPos = glm::vec2(
		game.width / 2.0f - PLAYER_SIZE.x / 2.0f,	// Starts in the horizontal middle
		game.height - PLAYER_SIZE.y				// On the Bottom
	);

	GameObject Player(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("linfocito_b"));
	GameEditor::CurrentObjects["Player"] = Player;
}
