#pragma once

#include "../Game.h"

typedef struct _tagKeyInfo {
	string			strName;
	vector<DWORD>	vecKey;
	bool			bDown;
	bool			bPress;
	bool			bUp;

	_tagKeyInfo() :
		bDown(false),
		bPress(false),
		bUp(false) {

	}
} KEYINFO, *PKEYINFO;

class CInput
{
private:
	HWND		m_hWnd;
	unordered_map<string, PKEYINFO>	m_mapKey;
	PKEYINFO	m_pCreateKey;

public:
	bool Init(HWND hWnd);
	void Update(float fDeltaTime);
	bool KeyDown(const string& strKey) const;
	bool KeyPress(const string& strKey) const;
	bool KeyUp(const string& strKey) const;

public:
	template <typename T>
	bool AddKey(const T& data) {
		const char* pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 ||
			strcmp(pTType, "int") == 0) {
			// static_cast 는 template 에서 에러 있음.
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}
		else {
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}
		return true;
	}

	template <typename T, typename... Types>
	bool AddKey(const T& data, const Types&... args) {
		if (!m_pCreateKey) {
			m_pCreateKey = new KEYINFO;
		}

		// 클래스 타입의 식별번호가 들어옴
		// int 면 int가 문자열로 반환
		// KEYINFO면 KEYINFO가 문자열로 반환
		const char* pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 ||
			strcmp(pTType, "int") == 0) {
			// static_cast 는 template 에서 에러 있음.
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}
		else {
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		// 재귀 함수 (마지막에 bool AddKey(const T& data) 호출)
		AddKey(args...);

		if (m_pCreateKey) {
			m_pCreateKey = NULL;
		}
		return true;
	}

private:
	PKEYINFO FindKey(const string& strKey) const;

	DECLARE_SINGLE(CInput)
};

