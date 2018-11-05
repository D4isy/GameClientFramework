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
	// 부모 Scene 클래스의 초기화 함수를 호출해준다.
	if (!CScene::Init()) {
		return false;
	}

	CLayer* pLayer = FindLayer("Default");

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// 총알 프로토타입을 만들어준다.
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet");
	pBullet->SetSize(64.f, 64.f);
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);
	SAFE_RELEASE(pStage);
	return true;
}
