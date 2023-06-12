#include "CursedArcadePCH.h"
#include "DiggerManager.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "LivesDisplayComp.h"
#include "ScoreComponent.h"
#include "ObjectConstructorCursedArc.h"
#include "SceneFactoryCursedArc.h"

//MiniLord::DiggerManager::DiggerManager(GameObject* ScoreObject,GameObject* LiveBar)
//	:m_ScoreObject(ScoreObject),m_LivesObject(LiveBar)
//{
//}

MiniLord::DiggerManager::DiggerManager(GameObject* scoreHealthObject, GameObject* livesObj, Scene* sceneToControl, Grid* gridToControl, const glm::fvec2& sizeOfObject,int currentGameMode)
	:m_currentScene(sceneToControl),m_grid(gridToControl),m_sizeOfObject(sizeOfObject) ,m_ScoreObject(scoreHealthObject), m_LivesObject(livesObj), m_currentGameMode(currentGameMode)
{
}

void MiniLord::DiggerManager::OnNotify(ObserverMessage msg, void* argPointer, int )
{
	int val;
	bool scoreChanged = false;
	bool NextShouldBeLoaded = false;
	bool LivesChanged = false;
	bool NobbinHit = false;
	switch (msg)
	{
	case ObserverMessage::Msg_Bag_Added:
		m_BagsInScene++;
			break;
	case ObserverMessage::Msg_Bag_Collected:
		m_Currentscore += 250;
		scoreChanged = true;
		m_BagsInScene--;
		break;
	case ObserverMessage::Msg_bag_Destroyed:
		m_BagsInScene--;

	case ObserverMessage::Msg_Gem_Added:
		m_GemsInScene++;
		break;
	case ObserverMessage::Msg_Gem_Collected:
		m_Currentscore += 25;
		m_GemsInARow++;
		m_GemsInScene--;

		if (m_GemsInARow >= 6){
			m_GemsInARow = 0;
			m_Currentscore += 250;
		}
		if (m_GemsInScene <= 0)
			NextShouldBeLoaded = true;

		scoreChanged = true;
		break;
	case ObserverMessage::Msg_Nobbin_Hit:
		m_Currentscore += 250;
		m_nobbinsMIA++;
		NobbinHit = true;
		scoreChanged = true;
		break;

	case ObserverMessage::Msg_PLAYER_LIFE_CHANGED:
		val = *static_cast<int*>(argPointer);
		m_lives--;
		LivesChanged = true;
		break;
	}

	// check i
	if(scoreChanged)
	{
		if(m_ScoreObject)
		{
			auto scoreComp = m_ScoreObject->GetComponent<TextComponent>();
			if (scoreComp)
				scoreComp->SetText("score:  " + std::to_string(m_Currentscore));
			else
				std::cout << "No score comp found by manager" << std::endl;
		if (m_currentGameMode == 2 &&  NobbinHit)
			RespawnEnemyPlayer();
		}
		
	}
	
	else if(m_ScoreObject == nullptr) std::cout << "No score Object" << std::endl;


	if(LivesChanged)
	{
		ResetPlayerPositions();
		if (m_LivesObject)
		{
			auto lives = m_LivesObject->GetComponent<LivesDisplayComp>();
			if (lives)
				lives->DirectSetLives(m_lives);
			else
				std::cout << "No score comp found by manager" << std::endl;
		}

		if(m_lives <= 0)
		{
			SceneManager::GetInstance().AddScene(SceneFactoryCursedArc::GameOverMenu(m_Currentscore));
			m_currentScene->SetActive(false);
		}
	}



	else if (m_ScoreObject == nullptr) std::cout << "No score Object" << std::endl;

	if (m_nobbinsMIA >= m_maxNobbins)
		NextShouldBeLoaded = true;




	if (m_BagsInScene <= 0)
		NextShouldBeLoaded = true;


	if (NextShouldBeLoaded)
		m_ShouldLoadNextLevel = true;

}

void MiniLord::DiggerManager::OnNotifyDestruction(ObserverMessage , void* , int )
{
}

void MiniLord::DiggerManager::LoadNextLevel()
{
	m_grid->ResetGameField();
	m_currentLevel++;
	m_maxNobbins++;
	std::string level = m_levelnames[m_currentLevel % m_levelnames.size()];
	auto objs = m_grid->CreateCellsAndLanesFromJSONFile(level,m_sizeOfObject,this);

	for (uint32_t i = 0; i < objs.size(); i++)
		m_currentScene->AddGameObject(objs[i]);

	if(m_grid->IsPlayer1StartSpotSet())
	{
		auto newPos = m_grid->GetPlayerStartPosition();
		m_playerRespawnSpot.x = newPos.x;
		m_playerRespawnSpot.y = newPos.y;
		m_Player->GetTransform().SetPosition(m_playerRespawnSpot.x, m_playerRespawnSpot.y, 0);
		
	}

	if(m_currentGameMode == 1)
	{
		if(m_grid->IsPlayer2StartSpotSet())
		{
			auto newPos = m_grid->GetPlayerTwoStartPosition();
			m_playerTwoRespawnSpot.x = newPos.x;
			m_playerTwoRespawnSpot.y = newPos.y;
			m_playerTwo->GetTransform().SetPosition(m_playerTwoRespawnSpot.x, m_playerTwoRespawnSpot.y,0);
		}
		else
		{
			auto newPos = m_grid->GetPlayerStartPosition();
			m_playerTwoRespawnSpot.x = newPos.x;
			m_playerTwoRespawnSpot.y = newPos.y;
			m_playerTwo->GetTransform().SetPosition(m_playerTwoRespawnSpot.x, m_playerTwoRespawnSpot.y, 0);
			
		}
	}

	if(m_currentGameMode == 2)
	{
				auto newPos = m_grid->GetEnemySpawnPosition();
		m_playerTwoRespawnSpot.x = newPos.x;
		m_playerTwoRespawnSpot.y = newPos.y;
		m_playerTwo->GetTransform().SetPosition(m_playerTwoRespawnSpot.x, m_playerTwoRespawnSpot.y, 0);
	}

	if(m_grid->IsEnemySpawnSet())
	{
		m_SpawnTimeDelta = 1.f;
		m_EnemySpawnSpot = m_grid->GetEnemySpawnPosition();
	};


}

void MiniLord::DiggerManager::ResetPlayerPositions()
{
	if(m_Player)
	{
		m_Player->GetTransform().SetPosition(m_playerRespawnSpot.x,m_playerRespawnSpot.y,0);
	}

	if(m_playerTwo && m_currentGameMode == 1)
	{
		m_playerTwo->GetTransform().SetPosition(m_playerTwoRespawnSpot.x, m_playerRespawnSpot.y, 0);
	}
}

void MiniLord::DiggerManager::Update(const float dt)
{

	
	if (m_ShouldLoadNextLevel)
	{
		m_maxNobbins++;
		LoadNextLevel();
		m_ShouldLoadNextLevel = false;
	}
	if (m_currentGameMode != 2)
	{
		if(m_nobbinsSpawned < m_maxNobbins)
		{
			if(m_SpawnTimeDelta <= 0)
			{
				auto newNobbin = std::make_shared<GameObject>();
				ObjectConstructorCursedArc::DiggerNobbin(newNobbin,m_grid,m_sizeOfObject,this);
				m_currentScene->AddGameObject(newNobbin);
				newNobbin->GetTransform().SetPosition(m_EnemySpawnSpot.x,m_EnemySpawnSpot.y,0);
				m_spawnedNobbins.push_back(newNobbin.get());

				m_SpawnTimeDelta = m_SpawnTime;
				m_nobbinsSpawned++;
			}
			m_SpawnTimeDelta -= dt;
		}
	}
	else if(m_currentGameMode == 2)
	{


	}
}

void MiniLord::DiggerManager::ResetLevel()
{
	for (uint32_t i = 0; i < m_spawnedNobbins.size(); ++i)
	{
		if(auto obj = m_spawnedNobbins[i])
		{
			obj->SetMarkForDeletion();
			m_nobbinsSpawned--;
		}
	}
	m_spawnedNobbins.clear();
	m_SpawnTimeDelta = 1.f;
	
}

void MiniLord::DiggerManager::RespawnEnemyPlayer()
{
	m_playerTwo->GetTransform().SetPosition(m_EnemySpawnSpot.x, m_EnemySpawnSpot.y,0);
}



