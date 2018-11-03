#include "Stage.h"
#include "../Resource/Texture.h"
#include "../Core/Core.h"
#include "../Core/Camera.h"

CStage::CStage()
{
}

CStage::CStage(const CStage & stage) :
	CStaticObj(stage)
{
}


CStage::~CStage()
{
}

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1920.f, 1080.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage1", L"Stage1.bmp");
	return true;
}

void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	//CStaticObj::Render(hDC, fDeltaTime);

	if (m_pTexture) {
		// 좌 상단측 구하기
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		// 카메라의 좌표
		POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

		// 스크롤링 하기 위하여 m_tPos -> tPos 로 변경
		BitBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y),
			GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(), static_cast<int>(tCamPos.x), static_cast<int>(tCamPos.y), SRCCOPY);
	}
}

CStage * CStage::Clone()
{
	return new CStage(*this);
}
