#include "ResourcesManager.h"
#include "Texture.h"

DEFINITION_SINGLE(CResourcesManager)

bool CResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;
	return true;
}

CTexture * CResourcesManager::LoadTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture) {
		return pTexture;
	}

	// 없으면 만들기
	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName, strPathKey)) {
		SAFE_RELEASE(pTexture);
		return NULL;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CTexture * CResourcesManager::FindTexture(const string & strKey)
{
	unordered_map<string, class CTexture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end()) {
		return NULL;
	}

	iter->second->AddRef();

	return iter->second;
}

CResourcesManager::CResourcesManager()
{
}


CResourcesManager::~CResourcesManager()
{
	Safe_Release_Map(m_mapTexture);
}
