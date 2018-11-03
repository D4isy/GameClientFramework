#include "PathManager.h"

//#include <Shlwapi.h>
//#pragma comment(lib, "shlwapi.lib")
	// 맨 마지막 파일명을 제거해 줌
	//PathRemoveFileSpec(strPath);

DEFINITION_SINGLE(CPathManager)

bool CPathManager::Init()
{
	wchar_t strPath[MAX_PATH] = {};

	// Debug시 실행 주체가 include 폴더로 잡힘
	// 그냥 실행시 실행 주체가 Bin 폴더로 잡힘
	// GetCurrentDirectory()	// 그래서 안씀

	GetModuleFileName(NULL, strPath, MAX_PATH);

	for (int i = lstrlen(strPath) - 1; i >= 0; i--) {
		if (strPath[i] == '/' || strPath[i] == '\\') {
			memset(strPath + (i + 1), 0, sizeof(wchar_t) * (MAX_PATH - (i+1)));
			break;
		}
	}

	m_mapPath.insert(make_pair(ROOT_PATH, strPath));

	// Texture 경로 설정
	if (!CreatePath(TEXTURE_PATH, TEXT("Texture\\"))) {
		return false;
	}

	return true;
}

bool CPathManager::CreatePath(const string & strKey, const wchar_t * pPath, const string & strBaseKey)
{
	const wchar_t* pBasePath = FindPath(strBaseKey);

	wstring strPath;

	if (pBasePath) {
		strPath = pBasePath;
	}

	strPath += pPath;

	m_mapPath.insert(make_pair(strKey, strPath));
	return true;
}

const wchar_t * CPathManager::FindPath(const string & strKey)
{
	unordered_map<string, wstring>::iterator iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end()) {
		return NULL;
	}
	return iter->second.c_str();
}

CPathManager::CPathManager()
{
}


CPathManager::~CPathManager()
{
}
