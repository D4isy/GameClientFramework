#include "Texture.h"
#include "../Core/PathManager.h"


CTexture::CTexture() :
	m_hMemDC(NULL)
{
}


CTexture::~CTexture()
{
	// ������ �����Ǿ� �ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// Bitmap�� �����ش�.
	DeleteObject(m_hBitmap);

	// DC�� �����ش�.
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	// �޸� DC�� ����� �ش�.
	// hDC�� �޸� DC �� �������
	m_hMemDC = CreateCompatibleDC(hDC);

	// ��ü ��θ� ������ش�.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	// ���ڿ� Ŭ������ NULL�� �־��ָ� �ٷ� Crash ��! (�߿�)
	wstring strPath;

	if (pPath) {
		strPath = pPath;
	}

	strPath += pFileName;

	// cx: 0, cy: 0 ���� �ϸ� �ڵ����� �̹��� ũ�⸸ŭ ������
	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// ������ �� ��ȯ�Ǵ� ���� DC�� �⺻���� �����Ǿ� �ֶ�
	// ������ ��ȯ�ȴ�.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);
	return true;
}
