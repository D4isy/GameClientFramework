#pragma once

#include "../Game.h"

class CCamera
{
private:
	POSITION	m_tPos;
	RESOLUTION	m_tClientRS;
	RESOLUTION	m_tWorldRS;
	POSITION	m_tPivot;
	class CObj* m_pTarget;

public:
	POSITION GetPos() const {
		return m_tPos;
	}

public:
	class CObj* GetTarget() const {
		return m_pTarget;
	}
	void SetTarget(class CObj* pObj);

	void SetPivot(const POSITION& tPivot) {
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y) {
		m_tPivot = POSITION(x, y);
	}

	void SetPos(const POSITION& tPos) {
		m_tPos = tPos;
	}

	void SetPos(float x, float y) {
		m_tPos = POSITION(x, y);
	}

	void SetClientResolution(const RESOLUTION& tRS) {
		m_tClientRS = tRS;
	}

	void SetClientResolution(long x, long y) {
		m_tClientRS = RESOLUTION(x, y);
	}

	void SetWorldResolution(const RESOLUTION& tRS) {
		m_tWorldRS = tRS;
	}

	void SetWorldResolution(long x, long y) {
		m_tWorldRS = RESOLUTION(x, y);
	}

public:
	bool Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);

	DECLARE_SINGLE(CCamera)
};

