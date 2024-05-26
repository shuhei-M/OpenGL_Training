/**
 * @file   : MathUtil.h
 * @author : Shuhei Matsushima
 *
 * @berief : 数学ユーティリティ
 */

#ifndef __MATHUTIL_H_
#define __MATHUTIL_H_

#include <math.h>

namespace
{
	const float kPi = 3.14159265f;
	const float k2Pi = kPi * 2.0f;
	const float kPiOver2 = kPi / 2.0f;
	const float k1OverPi = 1.0f / kPi;
	const float k1Over2Pi = 1.0f / k2Pi;
	const float kPiOver180 = kPi / 180.0f;
	const float k180OverPi = 180.0f / kPi;
}

// -π～πにラップ
extern float wrapPi(float theta);

// -π～πにラップ
extern float wrapDegPi(float deg);

// 逆三角関数
extern float safeAcos(float x);

// ラジアン⇔デグリー
inline float degToRad(float deg);
inline float radToDeg(float rad);

// 特定の角度のサインとコサイン計算
inline void sinCos(float* returnSin, float* returnCos, float theta);

// 視野とズームの変換
//視野角はラジアン単位で指定する。
inline float fovToZoom(float fov);
inline float zoomToFov(float zoom);

#endif // #ifndef __MATHUTIL_H_