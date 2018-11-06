#include "ColliderSphere.h"
#include "../Obj/Obj.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"


CColliderSphere::CColliderSphere()
{
	m_eCollType = CT_SPHERE;
}

CColliderSphere::CColliderSphere(const CColliderSphere & coll) :
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}


CColliderSphere::~CColliderSphere()
{
}

bool CColliderSphere::Init()
{
	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;
	return 0;
}

bool CColliderSphere::Collision(CCollider * pDest)
{
	switch (pDest->GetColliderType()) {
	case CT_SPHERE:
		return CollisionSphereToSphere(m_tWorldInfo, dynamic_cast<CColliderSphere*>(pDest)->GetWorldInfo());

	case CT_RECT:
		return CollisionRectToSphere(dynamic_cast<CColliderRect*>(pDest)->GetWorldInfo(), m_tWorldInfo);

	case CT_PIXEL:
		break;
	}
	return false;
}

void CColliderSphere::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CColliderSphere * CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}
