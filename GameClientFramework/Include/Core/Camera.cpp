#include "Camera.h"
#include "../Obj/Obj.h"

DEFINITION_SINGLE(CCamera)

void CCamera::SetTarget(CObj * pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget) {
		m_pTarget->AddRef();
	}
}

bool CCamera::Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);
	return true;
}

void CCamera::Input(float fDeltaTime)
{
	if (!m_pTarget) {

	}
}

void CCamera::Update(float fDeltaTime)
{
	if (m_pTarget) {
		POSITION	tPos = m_pTarget->GetPos();
		POSITION	tPivot = m_pTarget->GetPivot();
		_SIZE		tSize = m_pTarget->GetSize();

		// 타겟
		float fL = tPos.x - tPivot.x * tSize.x;
		float fT = tPos.y - tPivot.y * tSize.y;
		float fR = fL + tSize.x;
		float fB = fT + tSize.y;

		// 화면
		float fLeftArea = m_tClientRS.iW * m_tPivot.x;
		float fRightArea = m_tClientRS.iW - fLeftArea;
		float fTopArea = m_tClientRS.iH * m_tPivot.y;
		float fBottomArea = m_tClientRS.iH - fTopArea;

		// 카메라 위치가 움직이지 않는 좌표
		if (tPos.x <= fLeftArea) {
			// 현재 캐릭터가 Pivot 위치 까지 안오면 카메라 정지
			m_tPos.x = 0.f;
		}
		else if (tPos.x >= (m_tWorldRS.iW - fRightArea)) {
			// 계산식: 전체화면.넓이 - 보이는 화면의 오른쪽
			// 현재 캐릭터가 Pivot 위치를 넘어 끝까지 가면 카메라 정지
			m_tPos.x = static_cast<float>(m_tWorldRS.iW - m_tClientRS.iW); // 좌상 위치
		}
		else {
			// 현재 캐릭터가 Pivot 위치 까지 왔으면 이동
			m_tPos.x = tPos.x - m_tClientRS.iW * m_tPivot.x;
		}

		if (tPos.y <= fTopArea) {
			m_tPos.y = 0.f;
		}
		else if (tPos.y >= (m_tWorldRS.iH - fBottomArea)) {
			m_tPos.y = static_cast<float>(m_tWorldRS.iH - m_tClientRS.iH);
		}
		else {
			m_tPos.y = tPos.y - m_tClientRS.iH * m_tPivot.y;
		}
	}
}

CCamera::CCamera() :
	m_pTarget(NULL)
{
}


CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget);
}
