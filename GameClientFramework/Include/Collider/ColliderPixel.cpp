#include "ColliderPixel.h"
#include "../Obj/Obj.h"
#include "ColliderSphere.h"
#include "ColliderRect.h"
#include "../Core/PathManager.h"

CColliderPixel::CColliderPixel()
{
	m_eCollType = CT_PIXEL;
	m_iWidth = 0;
	m_iHeight = 0;
}

CColliderPixel::CColliderPixel(const CColliderPixel & coll) :
	CCollider(coll)
{
	m_iWidth = coll.m_iWidth;
	m_iHeight = coll.m_iHeight;
}


CColliderPixel::~CColliderPixel()
{
}

bool CColliderPixel::SetPixelInfo(const char * pFileName, const string & strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(strPathKey);
	string strPath;
	
	if (pPath) {
		strPath = pPath;
	}

	strPath += pFileName;

	FILE* pFile = NULL;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (!pFile) {
		return false;
	}

	// 무조건 24bit bmp 파일로 사용한다 가정
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	// 파일 헤더 가져오기
	fread(&fh, sizeof(fh), 1, pFile);
	// 파일 정보 가져오기
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth = ih.biWidth;
	m_iHeight = ih.biHeight;

	m_vecPixel.clear();

	m_vecPixel.resize(m_iWidth * m_iHeight);

	//int iSize = sizeof(PIXEL); // 4byte 정렬로 셋팅이 되면 에러 남
	// 속성 -> C/C++ -> 코드 생성 -> 구조체 멤버 맞춤
	
	// 픽셀 정보 가져오기
	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	PPIXEL pPixelWidth = new PIXEL[m_iWidth];

	// 위 아래를 반전시켜준다.
	for (int i = 0; i < m_iHeight / 2; i++) {
		// 현재 인덱스의 픽셀 한 줄을 저장해둔다.
		memcpy(pPixelWidth, &m_vecPixel[i * m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i -1) * m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelWidth, sizeof(PIXEL) * m_iWidth);
	}

	delete[] pPixelWidth;
	fclose(pFile);

	// @@ 테스트용 생성 파일
	//fopen_s(&pFile, "Test.bmp", "wb");

	//if (!pFile)
	//	return false;

	//fwrite(&fh, sizeof(fh), 1, pFile);
	//fwrite(&ih, sizeof(ih), 1, pFile);
	//fwrite(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	//fclose(pFile);

	return true;
}

bool CColliderPixel::Init()
{
	return true;
}

void CColliderPixel::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderPixel::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderPixel::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	//POSITION tPos = m_pObj->GetPos();
	//m_tWorldInfo.left = tPos.x + m_tInfo.left;
	//m_tWorldInfo.top = tPos.y + m_tInfo.top;
	//m_tWorldInfo.right = tPos.x + m_tInfo.right;
	//m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;

	return 0;
}

bool CColliderPixel::Collision(CCollider * pDest)
{
	switch (pDest->GetColliderType()) {
	case CT_RECT:
		return CollisionRectToPixel(dynamic_cast<CColliderRect*>(pDest)->GetWorldInfo(), m_vecPixel, m_iWidth, m_iHeight);

	case CT_SPHERE:
		//return CollisionRectToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
		break;

	case CT_PIXEL:
		break;
	}
	return false;
}

void CColliderPixel::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CColliderPixel * CColliderPixel::Clone()
{
	return new CColliderPixel(*this);
}
