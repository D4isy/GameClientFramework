#include "Collider.h"
#include "../Obj/Obj.h"


CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider & coll)
{
	*this = coll;
}


CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; iter++) {
		(*iter)->EraseCollisionList(this);
	}
}

bool CCollider::Init()
{
	return false;
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}

CCollider * CCollider::Clone()
{
	return nullptr;
}

bool CCollider::CollisionRectToRect(const RECTANGLE & src, const RECTANGLE & dest)
{
	if (src.left > dest.right) {
		return false;
	}
	else if (src.right < dest.left) {
		return false;
	}
	else if (src. top > dest.bottom) {
		return false;
	}
	else if (src.bottom < dest.top) {
		return false;
	}

	return true;
}
