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

	// ������ 24bit bmp ���Ϸ� ����Ѵ� ����
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	// ���� ��� ��������
	fread(&fh, sizeof(fh), 1, pFile);
	// ���� ���� ��������
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth = ih.biWidth;
	m_iHeight = ih.biHeight;

	m_vecPixel.clear();

	m_vecPixel.resize(m_iWidth * m_iHeight);

	//int iSize = sizeof(PIXEL); // 4byte ���ķ� ������ �Ǹ� ���� ��
	// �Ӽ� -> C/C++ -> �ڵ� ���� -> ����ü ��� ����
	
	// �ȼ� ���� ��������
	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	PPIXEL pPixelWidth = new PIXEL[m_iWidth];

	// �� �Ʒ��� ���������ش�.
	for (int i = 0; i < m_iHeight / 2; i++) {
		// ���� �ε����� �ȼ� �� ���� �����صд�.
		memcpy(pPixelWidth, &m_vecPixel[i * m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i -1) * m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelWidth, sizeof(PIXEL) * m_iWidth);
	}

	delete[] pPixelWidth;
	fclose(pFile);

	// @@ �׽�Ʈ�� ���� ����
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
