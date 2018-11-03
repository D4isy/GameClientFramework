#include "Obj.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Resource/ResourcesManager.h"
#include "../Resource/Texture.h"
#include "../Core/Camera.h"

list<CObj*> CObj::m_ObjList;

CObj::CObj() :
	m_pTexture(NULL)
{
}

CObj::CObj(const CObj & obj)
{
	*this = obj;

	if (m_pTexture) {
		m_pTexture->AddRef();
	}
}


CObj::~CObj()
{
	SAFE_RELEASE(m_pTexture);
}

void CObj::AddObj(CObj * pObj)
{
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObj * CObj::FindObject(const string & strTag)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return NULL;
}

void CObj::EraseObj(CObj * pObj)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string & strTag)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

void CObj::SetTexture(CTexture * pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture) {
		pTexture->AddRef();
	}
}

void CObj::SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, strPathKey);
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {
		// 좌 상단측 구하기
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		if (m_pTexture->GetColorKeyEnable()) {
			TransparentBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y),
				static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetDC(),
				0, 0, static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetColorKey());
		}
		else {
			// 스크롤링 하기 위하여 m_tPos -> tPos 로 변경
			BitBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y),
				static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetDC(), 0, 0, SRCCOPY);
		}
	}
}

CObj * CObj::CreateCloneObj(const string & strPrototypeKey, const string & strTag, class CLayer* pLayer)
{
	CObj*	pProto = CScene::FindPrototype(strPrototypeKey);

	if (!pProto) {
		return NULL;
	}

	CObj* pObj = pProto->Clone();

	pObj->SetTag(strTag);

	if (pLayer) {
		pLayer->AddObject(pObj);
	}

	AddObj(pObj);

	return pObj;
}