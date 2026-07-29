#include "Level.h"
#include "Enemies/Bee/Bee.h"
#include "StateMachine/State.h"
#include "Components/Transform.h"
#include "Enemies/Formation.h"
#include <fstream>

namespace dae
{
	void Level::OnEnter()
	{
		m_SpawnPosBees = ReadPositionsFromFile("Data/Formations/Formation1Bees.txt");
		m_SpawnPosBosses = ReadPositionsFromFile("Data/Formations/Formation1Boss.txt");
		m_SpawnPosFlies = ReadPositionsFromFile("Data/Formations/Formation1Butterflies.txt");

		//for (auto & pos: m_SpawnPosBees)
		//{
		//	auto bee = std::make_unique<dae::GameObject>();
		//	bee->AddComponent<dae::Bee>();
		//	bee->GetComponent<dae::Transform>()->SetLocalPosition(pos.x - 75, pos.y, 0.0f);
		//	bee->SetParent(m_pState->GetOwner(), false);
		//	m_pBees.push_back(std::move(bee));
		//}

		auto bee = std::make_unique<dae::GameObject>();
		bee->AddComponent<dae::Bee>();
		bee->AddComponent<dae::State>(std::make_unique<dae::Formation>(nullptr, glm::vec2(0, 512), m_SpawnPosBees[0], glm::vec2(0, 212)));
		bee->SetParent(m_pState->GetOwner(), false);
		m_pBees.push_back(std::move(bee));
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
					positions.emplace_back(x, y);
				}
			}
		}

		return positions;
	}

	void Level::Update(float)
	{

	}

	void Level::OnExit()
	{

	}

	std::unique_ptr<GameState> Level::GoToNextState()
	{
		return nullptr;
	}
}