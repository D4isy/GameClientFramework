#include "Timer.h"

DEFINITION_SINGLE(CTimer)

CTimer::CTimer() :
	m_fTimeScale(1.f)
{
}


CTimer::~CTimer()
{
}

bool CTimer::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrame = 0;

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER	tTime;
	QueryPerformanceCounter(&tTime);

	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;

	m_tTime = tTime;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if (m_fFPSTime >= 1.f) {
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;

#ifdef _DEBUG
		char strFPS[64] = {};
		sprintf_s(strFPS, 64, "FPS : %.f\n", m_fFPS);

		// 콘솔창에 출력
		_cprintf(strFPS);
		
		// 타이틀바에 출력
		//SetWindowTextA(m_hWnd, strFPS);

		// 디버그창에 출력
		//OutputDebugStringA(strFPS);

#endif // _DEBUG
	}
}
