#include "InGameScene.h"
#include "../Obj/Player.h"
#include "Layer.h"

CInGameScene::CInGameScene()
{
}


CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	// �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ���ؤ̤�����.
	if (!CScene::Init()) {
		return false;
	}

	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);

	SAFE_RELEASE(pPlayer);

	return true;
}
