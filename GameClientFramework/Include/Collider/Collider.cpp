#include "Collider.h"
#include "../Obj/Obj.h"
#include "../Core/Math.h"

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

bool CCollider::CollisionRectToSphere(const RECTANGLE & src, const SPHERE & dest)
{
	// 원의 중점의 x좌표가 사각형의 가로 영역 안에 있는지,
	// 원의 중점의 y좌표가 사각형의 세로 영역 안에 있는지 체크
	//     둘중 하나라도 맞다면 사각형의 위, 아래, 좌, 우, 영역 안에 존재
	if ((src.left <= dest.tCenter.x && dest.tCenter.x <= src.right) ||
		(src.top <= dest.tCenter.y && dest.tCenter.y <= src.bottom)) {
		RECTANGLE tRC = src;
		tRC.left	-= dest.fRadius;
		tRC.top		-= dest.fRadius;
		tRC.right	+= dest.fRadius;
		tRC.bottom	+= dest.fRadius;

		if (dest.tCenter.x < tRC.left) {
			return false;
		}
		else if (dest.tCenter.x > tRC.right) {
			return false;
		}
		else if (dest.tCenter.y < tRC.top) {
			return false;
		}
		else if (dest.tCenter.y > tRC.bottom) {
			return false;
		}

		return true;
	}

	// 대각선 영역
	// 사각형의 양 끝의 4개의 점이 하나라도 원 안에 있을 경우 충돌
	POSITION tPos[4];
	tPos[0] = POSITION(src.left,  src.top);
	tPos[1] = POSITION(src.right, src.top);
	tPos[2] = POSITION(src.left,  src.bottom);
	tPos[3] = POSITION(src.right, src.bottom);

	float fDist = 0.f;
	for (int i = 0; i < 4; i++) {
		fDist = CMath::Distance(dest.tCenter, tPos[i]);

		if (fDist <= dest.fRadius) {
			return true;
		}
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest)
{
	float fDist = CMath::Distance(src.tCenter, dest.tCenter);

	return fDist <= (src.fRadius + dest.fRadius);
}
