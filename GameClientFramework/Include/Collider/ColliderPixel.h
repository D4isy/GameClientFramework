#pragma once

#include "Collider.h"

class CColliderPixel :
	public CCollider
{
protected:
	friend class CObj;

public:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& coll);
	virtual ~CColliderPixel();

private:
	vector<PIXEL>	m_vecPixel;
	int				m_iWidth;
	int				m_iHeight;

public:
	const vector<PIXEL>& GetPixel() const {
		return m_vecPixel;
	}

	int GetWidth() const {
		return m_iWidth;
	}

	int GetHeight() const {
		return m_iHeight;
	}

public:
	bool SetPixelInfo(const char* pFileName, const string& strPathKey = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderPixel* Clone();
};

