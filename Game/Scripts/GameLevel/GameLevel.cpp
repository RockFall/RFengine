#include "GameLevel.h"
#include "../../Editor/GameEditor.h"
#include "../../../Engine/GameObject/Attribute.h"

#include <random>
#include <algorithm>

GameLevel::GameLevel(std::shared_ptr<GameObject> go) : gameObject(go), enemies(), level(0), diverCountDown(0.0f), timeBetweenDivers(0.0f), amountOfDivers(0)
{
	Start();
}

GameLevel::~GameLevel()
{

}

void GameLevel::Start()
{
    level = 1;
	Load("Resources/Levels/level01.txt");
}

void GameLevel::Update(float dt, bool keys[], glm::vec2 mousePos)
{  
    if (enemies.size() == 0) {
        level++;
        std::string fileName = "Resources/Levels/level0" + std::to_string(level) + ".txt";
        Load(fileName);
    }

    if (diverCountDown > 0) {
        diverCountDown -= dt;
    }
    else {
        // It's time for DIVERSS
        amountOfDivers = rand() % 4; // range(0 to 3)
        timeBetweenDivers = rand() % (100 / enemies.size()) + 0.5f; // range(0.5f to 7.5f)
        std::cout << amountOfDivers << " enemies are diving." << std::endl;

        for (int i = 0; i < amountOfDivers; i++)
        {
            GameContext::CurrentAttributes[enemies.back()]->enemyScript.Dive();
            enemies.pop_back();
            //GameContext::CurrentAttributes[enemies[i]]->enemyScript.SetSpeed(glm::vec2(60.0f, 150.0f));
        }

        diverCountDown = timeBetweenDivers;
    }

}

void GameLevel::Load(std::string file)
{
	// Clear old data
	enemies.clear();

	char enemyCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<char>> enemyData;

    float enemySpeed = 0.0f;

	if (fstream) {
        // First line is enemy speed
        std::getline(fstream, line);
        enemySpeed = std::stof(line);

		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<char> row;
			while (sstream >> enemyCode)
				row.push_back(enemyCode);
			enemyData.push_back(row);
		}
		if (enemyData.size() > 0) {
			GenerateLevel(enemyData, enemySpeed);
		}
    }
    else {
        std::cout << "GAMELEVEL::Load: Arquivo não encontrado: " << file << std::endl;
        level = 0;
    }
}

void GameLevel::GenerateLevel(std::vector<std::vector<char>> enemyData, float enemySpeed)
{
    // calculate dimensions
    unsigned int verticalCount = enemyData.size();
    unsigned int horizontalCount = enemyData[0].size();

    unsigned int lvlWidth = 500;
    unsigned int distanceBetween = 10;
    unsigned int topOffset = 20;
    unsigned int lateralOffset = lvlWidth / 10;

    float unit_size = ((lvlWidth) / static_cast<float>(horizontalCount))-(distanceBetween);

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < verticalCount; ++y)
    {
        for (unsigned int x = 0; x < horizontalCount; ++x)
        {
            // check block type from level data (2D level array)
            if (enemyData[y][x] == 'V') // solid
            {
                unsigned int yPos = (topOffset + y * (distanceBetween + unit_size));
                unsigned int xPos = (lateralOffset + x * (distanceBetween + unit_size));

                glm::vec2 pos(xPos, yPos);
                glm::vec2 size(unit_size, unit_size);
                
                std::string ID = GameEditor::CreateGameObject("EnemyV", pos, true, size);
                // Turns collision ON
                GameEditor::GameObjectSetSolid(ID, true);
                // Set speed to level speed
                GameContext::CurrentAttributes[ID]->enemyScript.SetYSpeed(enemySpeed);
                
                this->enemies.push_back(ID);
            }
            else if (enemyData[y][x] > 1)
            {
                /*
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(
                    GameObject(pos, size, ResourceManager::GetTexture("block"), color)
                );
                */
            }
        }
    }
}

void GameLevel::EnemyDied(std::string name) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), name), enemies.end());
}


