#include "Layer.h"
#include "../Obj/Obj.h"


CLayer::CLayer() :
	m_iZOrder(0),
	m_strTag(""),
	m_pScene(NULL),
	m_bEnable(true),
	m_bLife(true)
{
}


CLayer::~CLayer()
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();
	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter) {
		CObj::EraseObj(*iter);
		SAFE_RELEASE((*iter));
	}

	m_ObjList.clear();
	// CScene 에서는
	// 접근 불가는 CLayer 의 ~CLayer() 이 private 면 접근 불가 이지만
	// 하지만, CLayer 에서는 
	// 자기 자신을 호출하기 때문에 접근 가능
	//Safe_Release_VecList(m_ObjList);
}

void CLayer::AddObject(CObj * pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();

	m_ObjList.push_back(pObj);
}

void CLayer::Input(float fDeltaTime)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);

		if (!(*iter)->GetLife()) {
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else {
			++iter;
		}
	}
}

int CLayer::Update(float fDeltaTime)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife()) {
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else {
			++iter;
		}
	}
	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife()) {
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else {
			++iter;
		}
	}
	return 0;
}

void CLayer::Collision(float fDeltaTime)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);

		if (!(*iter)->GetLife()) {
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else {
			++iter;
		}
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife()) {
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else {
			++iter;
		}
	}
}
