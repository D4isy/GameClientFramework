#include "InGameScene.h"
#include "../Obj/Player.h"
#include "../Obj/Minion.h"
#include "../Obj/Bullet.h"
#include "../Obj/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"

CInGameScene::CInGameScene()
{
}


CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	// �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init()) {
		return false;
	}

	CLayer* pLayer = FindLayer("Default");

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// �Ѿ� ������Ÿ���� ������ش�.
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet");
	pBullet->SetSize(64.f, 64.f);
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);
	SAFE_RELEASE(pStage);
	return true;
}
