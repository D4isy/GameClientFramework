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



	return true;
}