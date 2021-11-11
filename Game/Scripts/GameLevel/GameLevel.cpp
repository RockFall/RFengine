#include "GameLevel.h"
#include "../../Editor/GameEditor.h"

GameLevel::GameLevel(std::shared_ptr<GameObject> go) : gameObject(go), enemies()
{
	Start();
}

GameLevel::~GameLevel()
{

}

void GameLevel::Start()
{
	Load("Resources/Levels/level01.txt");
}

void GameLevel::Update(float dt, bool keys[], glm::vec2 mousePos)
{

}

void GameLevel::Load(const char* file)
{
	// Clear old data
	enemies.clear();

	char enemyCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<char>> enemyData;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<char> row;
			while (sstream >> enemyCode)
				row.push_back(enemyCode);
			enemyData.push_back(row);
		}
		if (enemyData.size() > 0) {
			GenerateLevel(enemyData);
		}
    }
    else {
        std::cout << "GAMELEVEL::Load: Arquivo não encontrado: " << file << std::endl;
    }
}

void GameLevel::GenerateLevel(std::vector<std::vector<char>> enemyData)
{
    // calculate dimensions
    unsigned int verticalCount = enemyData.size();
    unsigned int horizontalCount = enemyData[0].size();

    unsigned int lvlWidth = 500;
    unsigned int distanceBetween = 10;
    unsigned int topOffset = 20;

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
                unsigned int xPos = (50 + x * (distanceBetween + unit_size));

                glm::vec2 pos(xPos, yPos);
                glm::vec2 size(unit_size, unit_size);
                
                std::string ID = GameEditor::CreateGameObject("EnemyV", pos, true, size);
                GameEditor::GameObjectSetSolid(ID, true);
                
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


