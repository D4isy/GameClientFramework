#include "Player.h"
#include "../Core/Timer.h"
#include "../Resource/Texture.h"
#include "../Core/Input.h"

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

	if (KEYPRESS("MoveFront")) {
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveBack")) {
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYPRESS("MoveLeft")) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveRight")) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYPRESS("SpeedDown")) {
		GET_SINGLE(CTimer)->SetTimeScale(max(GET_SINGLE(CTimer)->GetTimeScale() - 0.001f, 0));
	}

	if (KEYPRESS("SpeedUp")) {
		GET_SINGLE(CTimer)->SetTimeScale(min(GET_SINGLE(CTimer)->GetTimeScale() + 0.001f, 1.f));
	}

	if (KEYDOWN("Fire")) {
		Fire();
	}

	if (KEYDOWN("Skill1")) {
		MessageBox(NULL, TEXT("Skill1"), TEXT("Skill1"), MB_OK);
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
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

	// ������ ����� ���Ѵ�.
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	//pBullet->SetPos(m_tPos.x + m_tSize.x, m_tPos.y + (m_tSize.y - pBullet->GetSize().y) / 2.f);
	pBullet->SetPos(tPos);
	SAFE_RELEASE(pBullet);
}
