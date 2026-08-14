#include "Level.h"
#include "StateMachine/State.h"
#include "Components/Transform.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "Enemies/EnemyTypes.h"
#include "Explosion/ExplosionAnimation.h"
#include "Player/Player.h"
#include "Game/Start/Start.h"
#include "Health/HealthDisplay.h"
#include "GameEvents.h"
#include "LevelObserver.h"
#include "Health/HealthObserver.h"
#include "Collider/collider.h"
#include "Input/InputManager.h"
#include <fstream>


namespace dae
{
	void Level::OnEnter()
	{
		m_Parent = std::make_unique<GameObject>();
		m_Parent->SetParent(m_pState->GetOwner(), false);

		m_Parent->AddComponent<EnemiesController>();
		m_Parent->AddComponent<HealthDisplay>();

		auto soundObserver = std::make_unique<SoundObserver>();
		auto levelObserver = std::make_unique<LevelObserver>(this);
		auto healthObserver = std::make_unique<HealthObserver>(m_pState->GetOwner()->GetComponent<HealthDisplay>());

		auto player = std::make_unique<GameObject>();
		player->AddComponent<Player>(m_pState->GetOwner()->GetComponent<EnemiesController>());
		player->SetParent(m_pState->GetOwner(), false);
		player->GetComponent<Player>()->AddObserver(std::move(levelObserver));
		player->GetComponent<Player>()->AddObserver(std::move(soundObserver));
		player->GetComponent<Player>()->AddObserver(std::move(healthObserver));

		Event e{ GAME_STARTED };
		player->GetComponent<Player>()->Notify(e, m_pState->GetOwner());

		m_GameObjects.push_back(std::move(player));
		m_Parent->GetComponent<EnemiesController>()->GetPlayer(m_GameObjects[0].get());

		LoadLevel(1);
	}

	void Level::LoadLevel(int number)
	{
		m_GameObjects[0]->GetComponent<Collider>()->ResetAllTriggers();
		m_Parent->GetComponent<EnemiesController>()->ResetAllEnemies();

		m_FormationPosBees = ReadPositionsFromFile("Data/Formations/Formation" + std::to_string(number) + "Bees.txt");
		m_FormationPosBosses = ReadPositionsFromFile("Data/Formations/Formation" + std::to_string(number) + "Boss.txt");
		m_FormationPosFlies = ReadPositionsFromFile("Data/Formations/Formation" + std::to_string(number) + "Butterflies.txt");

		SpawnEnemies();
	}

	std::vector<glm::vec2> Level::ReadPositionsFromFile(const std::string& filePath)
	{
		std::string line;
		std::ifstream file{ filePath };
		std::vector<glm::vec2> positions;

		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (line.empty())
					continue;

				line.erase(std::remove(line.begin(), line.end(), '['), line.end());
				line.erase(std::remove(line.begin(), line.end(), ']'), line.end());

				std::stringstream ss(line);
				std::string xStr, yStr;

				if (std::getline(ss, xStr, ',') && std::getline(ss, yStr, ','))
				{
					float x = std::stof(xStr);
					float y = std::stof(yStr);
					x -= 75.f;
					positions.emplace_back(x, y);
				}
			}
		}

		return positions;
	}

	void Level::SpawnEnemies()
	{
		auto enemySpawner = m_Parent->GetComponent<EnemiesController>();
		std::vector<EnemiesController::EnemyInfo> enemies;

		for (int i = 0; i < 4; i++) { 
			enemies.push_back({ EnemyType::Bee, m_FormationPosBees[i] }); }
		enemySpawner->AddWave({ enemies, glm::vec2(156, -50), glm::vec2(-100, 500) });
		enemies.clear();

		for (int i = 0; i < 4; i++) { 
			enemies.push_back({ EnemyType::Flie, m_FormationPosFlies[i] }); }
		enemySpawner->AddWave({ enemies, glm::vec2(356, -50), glm::vec2(612, 500) });
		enemies.clear();

		for (int i = 0; i < 4; i++) {
			enemies.push_back({ EnemyType::Flie, m_FormationPosFlies[i + 4] });
			enemies.push_back({ EnemyType::Boss, m_FormationPosBosses[i] });}
		enemySpawner->AddWave({ enemies, glm::vec2(0, 512), glm::vec2(100, 200), 0.5f });
		enemies.clear();

		for (int i = 8; i < 16; i++) {
			enemies.push_back({ EnemyType::Flie, m_FormationPosFlies[i] });}
		enemySpawner->AddWave({ enemies, glm::vec2(512, 512), glm::vec2({412, 200}), 0.5f });
		enemies.clear();

		for (int i = 4; i < 12; i++) {
			enemies.push_back({ EnemyType::Bee, m_FormationPosBees[i] }); }
		enemySpawner->AddWave({ enemies, glm::vec2(156, -50), glm::vec2(-100, 500) });
		enemies.clear();

		for (int i = 12; i < 20; i++) {
			enemies.push_back({ EnemyType::Bee, m_FormationPosBees[i] });}
		enemySpawner->AddWave({ enemies, glm::vec2(356, -50), glm::vec2(612, 500) });
		enemies.clear();
	}

	void Level::Update(float)
	{
		if (m_LevelEnded)
		{
			m_pState->GoToNextStage();
		}
	}

	void Level::OnExit()
	{
		m_pState->GetOwner()->RemoveAllChilderen();

		InputManager::GetInstance().ResetCommands();
	}

	void Level::LevelEnded()
	{
		m_LevelEnded = true;
	}

	std::unique_ptr<GameState> Level::GoToNextState()
	{
		return std::make_unique<Start>(m_pState);
	}
}