#include "InGameScene.h"
#include "../Obj/Player.h"
#include "../Obj/Minion.h"
#include "../Obj/Bullet.h"
#include "Layer.h"

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

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	SAFE_RELEASE(pPlayer);

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);

	// 총알 프로토타입을 만들어준다.
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet");
	pBullet->SetSize(50.f, 50.f);
	SAFE_RELEASE(pBullet);
	return true;
}
