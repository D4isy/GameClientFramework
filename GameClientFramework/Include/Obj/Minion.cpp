#include "Minion.h"
#include "../Resource/Texture.h"
#include "../Core/Core.h"
#include "../Collider/ColliderRect.h"
#include "Bullet.h"
#include "../Core/Camera.h"
#include "../Core/Math.h"

CMinion::CMinion() :
	m_fFireTime(0.f),
	m_fFireLimitTime(1.13f),
	m_TraceObj(NULL)
{
}

CMinion::CMinion(const CMinion & minion) :
	CMoveObj(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimitTime = minion.m_fFireLimitTime;
	m_TraceObj = minion.m_TraceObj;
}


CMinion::~CMinion()
{
}

bool CMinion::Init()
{
	SetPos(800.f, 100.f);
	SetSize(50.f, 71.f);
	SetSpeed(300.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Minion", L"enemy_01.bmp");

	m_pTexture->SetColorKey(0, 248, 0);
	m_eDir = MD_FRONT;

	CColliderRect* pRC = AddCollider<CColliderRect>("Minion");

	pRC->SetRect(-25.f, -35.5f, 25.f, 35.5f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CMinion::CollisionBullet);

	SAFE_RELEASE(pRC);

	pRC = AddCollider<CColliderRect>("TracePlayer");

	pRC->SetRect(-100.f, -142.f, 100.f, 142.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CMinion::HitTrace);

	SAFE_RELEASE(pRC);
	return true;
}

int CMinion::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	//MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_TraceObj) {
		POSITION tMinionPos = m_tPos - m_tSize * m_tPivot;
		tMinionPos -= GET_SINGLE(CCamera)->GetPos();

		POSITION tPlayerPos = m_TraceObj->GetPos() - m_TraceObj->GetSize() * m_TraceObj->GetPivot();
		tPlayerPos -= GET_SINGLE(CCamera)->GetPos();

		float fX = tMinionPos.x - tPlayerPos.x;
		float fY = tMinionPos.y - tPlayerPos.y;

		// 추적
		if (fX < 0) {
			MoveXFromSpeed(fDeltaTime, MD_FRONT);
		}
		else if (fX > 0) {
			MoveXFromSpeed(fDeltaTime, MD_BACK);
		}

		if (fY < 0) {
			MoveYFromSpeed(fDeltaTime, MD_FRONT);
		}
		else if (fY > 0) {
			MoveYFromSpeed(fDeltaTime, MD_BACK);
		}
	}

	//if ((m_tPos.y + m_tSize.y) >= GETRESOLUTION.iH) {
	//	m_tPos.y = GETRESOLUTION.iH - m_tSize.y;
	//	m_eDir = MD_BACK;
	//}
	//else if (m_tPos.y <= 0.f) {
	//	m_tPos.y = 0.f;
	//	m_eDir = MD_FRONT;
	//}

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimitTime) {
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}
	return 0;
}

int CMinion::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMinion::Render(HDC hDC, float fDeltaTime)
{
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();

	Rectangle(hDC, static_cast<int>(tPos.x - m_tSize.x * 2.f), static_cast<int>(tPos.y - m_tSize.y * 2.f),
		static_cast<int>(tPos.x + m_tSize.x * 3), static_cast<int>(tPos.y + m_tSize.y * 3));

	CMoveObj::Render(hDC, fDeltaTime);
	//Rectangle(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y),
	//	static_cast<int>(m_tPos.x + m_tSize.x), static_cast<int>(m_tPos.y + m_tSize.y));
}

CMinion * CMinion::Clone()
{
	return new CMinion(*this);
}

void CMinion::CollisionBullet(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	//MessageBox(NULL, TEXT("충돌"), TEXT("충돌"), MB_OK);
}

void CMinion::HitTrace(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pSrc->GetTag().compare("PlayerBody") == 0) {
		m_TraceObj = pSrc->GetObj();
	}
	else if (pDest->GetTag().compare("PlayerBody") == 0) {
		m_TraceObj = pDest->GetObj();
	}
}

void CMinion::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "MinionBullet", m_pLayer);

	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, dynamic_cast<CBullet*>(pBullet), &CBullet::Hit);

	(static_cast<CMoveObj*>(pBullet))->SetAngle(PI);

	float x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float y = GetCenter().y;

	pBullet->SetPos(x, y);
	SAFE_RELEASE(pBullet);
}
