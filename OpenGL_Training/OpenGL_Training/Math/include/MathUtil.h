/**
 * @file   : MathUtil.h
 * @author : Shuhei Matsushima
 *
 * @berief : ���w���[�e�B���e�B
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

// -�΁`�΂Ƀ��b�v
extern float wrapPi(float theta);

// -�΁`�΂Ƀ��b�v
extern float wrapDegPi(float deg);

// �t�O�p�֐�
extern float safeAcos(float x);

// ���W�A���̃f�O���[
inline float degToRad(float deg);
inline float radToDeg(float rad);

// ����̊p�x�̃T�C���ƃR�T�C���v�Z
inline void sinCos(float* returnSin, float* returnCos, float theta);

// ����ƃY�[���̕ϊ�
//����p�̓��W�A���P�ʂŎw�肷��B
inline float fovToZoom(float fov);
inline float zoomToFov(float zoom);

#endif // #ifndef __MATHUTIL_H_