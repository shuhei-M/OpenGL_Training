/**
 * @file   : MathUtil.cpp
 * @author : Shuhei Matsushima
 *
 * @belief : 数学ユーティリティ
 */

#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

/**
 * -π～πにラップ
 */
float wrapPi(float theta)
{
	theta += kPi;
	theta -= (float)floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

/**
 * -π～πにラップ
 */
float wrapDegPi(float deg)
{
	if (deg > 180.0f) deg -= 360.0f;
	else if (deg < -180.0f) deg += 360.0f;

	return deg;
}

/**
 * 逆三角関数
 */
float safeAcos(float x)
{
	// 制限条件をチェックする
	if (x <= -1.0f)
	{
		return kPi;
	}
	if (x >= 1.0f)
	{
		return 0.0f;
	}

	// 値が範囲内
	return (float)acos(x);
}

/**
 * ラジアン⇒デグリー
 */
inline float degToRad(float deg)
{
	return deg * kPiOver180;
}

/**
 * デグリー⇒ラジアン
 */
inline float radToDeg(float rad)
{
	return rad * k180OverPi;
}

/**
 * 特定の角度のサインとコサイン計算
 */
inline void sinCos(float* returnSin, float* returnCos, float theta)
{
	*returnSin = (float)sin(theta);
	*returnCos = (float)cos(theta);
}

/**
 * 視野⇒ズーム
 */
inline float fovToZoom(float fov)
{
	return 1.0f / (float)tan(fov * .5f);
}

/**
 * ズーム⇒視野
 */
inline float zoomToFov(float zoom)
{
	return 2.0f * (float)atan(1.0f / zoom);
}