#include "Input.h"

DEFINITION_SINGLE(CInput)

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');
	AddKey("Fire", VK_SPACE);
	AddKey(VK_CONTROL, "Skill1", '1');
	AddKey("SpeedUp", VK_F1);
	AddKey("SpeedDown", VK_F2);
	return true;
}

void CInput::Update(float fDeltaTime)
{

	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	int iPushCount = 0;
	for (iter = m_mapKey.begin(); iter != iterEnd; iter++) {
		iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); i++) {
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000) {
				iPushCount++;
			}
		}

		if (iPushCount == iter->second->vecKey.size()) {
			// 키 입력이 들어왔을 때
			//if (!iter->second->bDown && !iter->second->bPress) {
			//	// 처음 눌렀음
			//	iter->second->bDown = true;
			//}
			//else if (iter->second->bDown && !iter->second->bPress) {
			//	// 누르는 중
			//	iter->second->bDown = false;
			//	iter->second->bPress = true;
			//}
			if (!iter->second->bDown && !iter->second->bPress) {
				// 처음 눌렀음
				iter->second->bDown = true;
				iter->second->bPress = true;
			}
			else if (iter->second->bDown) {
				// 누르는 중
				iter->second->bDown = false;
			}
		}
		else {
			// 키 입력이 안 들어왔을 때
			if (iter->second->bDown || iter->second->bPress) {
				// 누르고 있는 중 땠을 때
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPress = false;
			}
			else if (iter->second->bUp) {
				// 때고난 후
				iter->second->bUp = false;
			}
		}
	}
}

bool CInput::KeyDown(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo) {
		return false;
	}
	return pInfo->bDown;
}

bool CInput::KeyPress(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo) {
		return false;
	}
	return pInfo->bPress;
}

bool CInput::KeyUp(const string & strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo) {
		return false;
	}
	return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string & strKey) const
{
	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end()) {
		return NULL;
	}

	return iter->second;
}

CInput::CInput() :
	m_pCreateKey(NULL)
{
}


CInput::~CInput()
{
	Safe_Delete_Map(m_mapKey);
}
