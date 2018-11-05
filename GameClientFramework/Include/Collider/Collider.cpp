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
	// ���� ������ x��ǥ�� �簢���� ���� ���� �ȿ� �ִ���,
	// ���� ������ y��ǥ�� �簢���� ���� ���� �ȿ� �ִ��� üũ
	//     ���� �ϳ��� �´ٸ� �簢���� ��, �Ʒ�, ��, ��, ���� �ȿ� ����
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

	// �밢�� ����
	// �簢���� �� ���� 4���� ���� �ϳ��� �� �ȿ� ���� ��� �浹
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
