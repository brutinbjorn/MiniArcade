#include "CursedArcadePCH.h"
#include "PlayerDiggerLogic.h"

#include "CellLogic.h"
#include "GameObject.h"
#include "SoundSystem.h"
#include "ObjectConstructorCursedArc.h"
#include "Scene.h"

using namespace MiniLord;
PlayerDiggerLogic::PlayerDiggerLogic(Grid* grideToInfluence, Scene* currentScene)
	:m_pGrid(grideToInfluence),m_pScene(currentScene)
{
}

void PlayerDiggerLogic::Update(const float dt)
{
	//auto pos = m_pGrid.
	auto cellImOn = m_pGrid->GetCellAtPosition(GetGameObject()->GetTransform().GetWorldPosition());

	if(cellImOn)
	if(auto val = cellImOn->GetComponent<CellLogic>())
	{
		val->SetDiggedOut(true);
	}

	if(m_BulletTimeDelta > 0)
	{
		m_BulletTimeDelta -= dt;
	}

}

void PlayerDiggerLogic::FireProjectile()
{
	if(m_BulletTimeDelta >= 0)
	{
		m_BulletTimeDelta = m_BulletTime;
		//SoundSystem::PlaySoundEffect()
		auto bullet = std::make_shared<GameObject>();
		ObjectConstructorCursedArc::PlayerBullet(bullet,m_pGrid ,m_ShotDirection, m_pGrid->GetCellSize());
		auto pos =GetGameObject()->GetTransform().GetWorldPosition();

		bullet->GetTransform().SetPosition(pos.x, pos.y, pos.z);
		m_pScene->AddGameObject(bullet);
	}
}


void PlayerDiggerLogic::GotHit()
{
	int i = -1;
	m_subject.Notify(ObserverMessage::Msg_PLAYER_LIFE_CHANGED, &i, sizeof(int));
}

bool PlayerDiggerLogic::ColliderEventBegin(GameObject* , glm::fvec2 )
{
	return false;
	//if()

}

void PlayerDiggerLogic::OverlapEventBegin(GameObject* )
{
}

