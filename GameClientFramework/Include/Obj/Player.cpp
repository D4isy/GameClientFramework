#include "Player.h"
#include "../Core/Timer.h"
#include "../Resource/Texture.h"
#include "../Core/Input.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"

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

	// 충돌체 추가
	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	pRC->SetRect(-70.f, -113.f, 70.f, 113.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);

	SAFE_RELEASE(pRC);

	// 체력 설정
	m_iHP = 1000;
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

	wchar_t strHP[32] = {};
	wsprintf(strHP, TEXT("HP : %d"), m_iHP);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y), strHP, lstrlen(strHP));

	//Rectangle(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), 
	//	static_cast<int>(m_tPos.x + m_tSize.x), static_cast<int>(m_tPos.y + m_tSize.y));
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	m_iHP -= 5;
}

void CPlayer::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

	// CS_ENTER 로 해놓으면 적과 충돌할 때 사라짐
	// CS_LEAVE 로 해놓으면 적과 충돌하고 끝날 때 사라짐
	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, dynamic_cast<CBullet*>(pBullet), &CBullet::Hit);
	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	//pBullet->SetPos(m_tPos.x + m_tSize.x, m_tPos.y + (m_tSize.y - pBullet->GetSize().y) / 2.f);
	pBullet->SetPos(tPos);
	SAFE_RELEASE(pBullet);
}
