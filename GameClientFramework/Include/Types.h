
#pragma once

typedef struct _tagResolution
{
	LONG iW;
	LONG iH;

	_tagResolution() :
		iW(0),
		iH(0) {
	}

	_tagResolution(long x, long y) :
		iW(x),
		iH(y) {
	}

} RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition {
	float x, y;

	_tagPosition() :
		x(0.f),
		y(.0f) {

	}

	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y) {}

	_tagPosition(const _tagPosition& pos) {
		x = pos.x;
		y = pos.y;
	}

	_tagPosition(const POINT& pt) {
		x = static_cast<float>(pt.x);
		y = static_cast<float>(pt.y);
	}

	// ======================= =
	void operator=(const _tagPosition& pos) {
		x = pos.x;
		y = pos.y;
	}

	void operator=(const POINT& pt) {
		x = static_cast<float>(pt.x);
		y = static_cast<float>(pt.y);
	}

	void operator=(float f[2]) {
		x = f[0];
		y = f[1];
	}

	// ======================= +
	_tagPosition operator+(const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator+(const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x + static_cast<float>(pos.x);
		tPos.y = y + static_cast<float>(pos.y);
		return tPos;
	}

	_tagPosition operator+(float f[2]) const {
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}

	_tagPosition operator+(float f) const {
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	void operator+=(const _tagPosition& pos) {
		x += pos.x;
		y += pos.y;
	}

	// ======================= -
	_tagPosition operator-(const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator-(const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x - static_cast<float>(pos.x);
		tPos.y = y - static_cast<float>(pos.y);
		return tPos;
	}

	_tagPosition operator-(float f[2]) const {
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator-(float f) const {
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	void operator-=(const _tagPosition& pos) {
		x -= pos.x;
		y -= pos.y;
	}

	// ======================= *
	_tagPosition operator*(const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator*(const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x * static_cast<float>(pos.x);
		tPos.y = y * static_cast<float>(pos.y);
		return tPos;
	}

	_tagPosition operator*(float f[2]) const {
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator*(float f) const {
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}

	// ======================= /
	_tagPosition operator/(const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator/(const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x / static_cast<float>(pos.x);
		tPos.y = y / static_cast<float>(pos.y);
		return tPos;
	}

	_tagPosition operator/(float f[2]) const {
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator/(float f) const {
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}
} POSITION, *PPOSITION, _SIZE, *_PSIZE;

typedef struct _tagRectangle {
	float left;
	float top;
	float right;
	float bottom;

	_tagRectangle() :
		left(0.f),
		top(0.f),
		right(0.f),
		bottom(0.f) {

	}
} RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere {
	POSITION	tCenter;
	float		fRadius;

	_tagSphere() :
		tCenter(0.f, 0.f),
		fRadius(0.f) {
	}
} SPHERE, *PSPHERE;

typedef struct _tagPixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} PIXEL, *PPIXEL;

