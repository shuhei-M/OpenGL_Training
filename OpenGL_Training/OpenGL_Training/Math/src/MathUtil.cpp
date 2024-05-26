/**
 * @file   : MathUtil.cpp
 * @author : Shuhei Matsushima
 *
 * @belief : ���w���[�e�B���e�B
 */

#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

/**
 * -�΁`�΂Ƀ��b�v
 */
float wrapPi(float theta)
{
	theta += kPi;
	theta -= (float)floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

/**
 * -�΁`�΂Ƀ��b�v
 */
float wrapDegPi(float deg)
{
	if (deg > 180.0f) deg -= 360.0f;
	else if (deg < -180.0f) deg += 360.0f;

	return deg;
}

/**
 * �t�O�p�֐�
 */
float safeAcos(float x)
{
	// �����������`�F�b�N����
	if (x <= -1.0f)
	{
		return kPi;
	}
	if (x >= 1.0f)
	{
		return 0.0f;
	}

	// �l���͈͓�
	return (float)acos(x);
}

/**
 * ���W�A���˃f�O���[
 */
inline float degToRad(float deg)
{
	return deg * kPiOver180;
}

/**
 * �f�O���[�˃��W�A��
 */
inline float radToDeg(float rad)
{
	return rad * k180OverPi;
}

/**
 * ����̊p�x�̃T�C���ƃR�T�C���v�Z
 */
inline void sinCos(float* returnSin, float* returnCos, float theta)
{
	*returnSin = (float)sin(theta);
	*returnCos = (float)cos(theta);
}

/**
 * ����˃Y�[��
 */
inline float fovToZoom(float fov)
{
	return 1.0f / (float)tan(fov * .5f);
}

/**
 * �Y�[���ˎ���
 */
inline float zoomToFov(float zoom)
{
	return 2.0f * (float)atan(1.0f / zoom);
}