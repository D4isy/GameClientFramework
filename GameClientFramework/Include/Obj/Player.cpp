#include "Player.h"
#include "../Core/Timer.h"
#include "../Core/Camera.h"
#include "../Resource/Texture.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer & player) :
	CMoveObj(player)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	m_bFire = false;
	SetPos(70.f, 113.f);
	SetSize(140.f, 226.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"Pig.bmp");

	m_pTexture->SetColorKey(0, 248, 0);
	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (GetAsyncKeyState('S') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (GetAsyncKeyState('A') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}

	if (GetAsyncKeyState('D') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		GET_SINGLE(CTimer)->SetTimeScale(max(GET_SINGLE(CTimer)->GetTimeScale() - 0.001f, 0));
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		GET_SINGLE(CTimer)->SetTimeScale(min(GET_SINGLE(CTimer)->GetTimeScale() + 0.001f, 1.f));
	}

	if (!m_bFire && GetAsyncKeyState(VK_SPACE) & 0x8000) {
		Fire();
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	//Rectangle(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), 
	//	static_cast<int>(m_tPos.x + m_tSize.x), static_cast<int>(m_tPos.y + m_tSize.y));
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Fire()
{
	m_bFire = true;
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	//pBullet->SetPos(m_tPos.x + m_tSize.x, m_tPos.y + (m_tSize.y - pBullet->GetSize().y) / 2.f);
	pBullet->SetPos(tPos);

	// 총알 쏠 때 카메라 설정
	GET_SINGLE(CCamera)->SetTarget(pBullet);

	SAFE_RELEASE(pBullet);
}
