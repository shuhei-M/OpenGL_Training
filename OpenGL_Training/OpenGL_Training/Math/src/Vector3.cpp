/**
 * @file   : Vector3.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : 3D�x�N�g���N���X
 */

#include <math.h>
#include "Vector3.h"

 /**
  * ���
  */
Vector3&
Vector3::operator =(const Vector3& a)
{
	x = a.x; y = a.y; z = a.z;
	return *this;
}

/**
 * ������
 */
bool
Vector3::operator ==(const Vector3& a) const
{
	return x == a.x && y == a.y && z == a.z;
}

/**
 * ��v���Ȃ�
 */
bool
Vector3::operator !=(const Vector3& a) const
{
	return x != a.x || y != a.y || z != a.z;
}

/**
 * �[���x�N�g��
 */
void
Vector3::zero()
{
	x = y = z = 0.0f;
}

/**
 * �x�N�g���̔��]
 */
Vector3
Vector3::operator -() const
{
	return Vector3(-x, -y, -z);
}

/**
 * �x�N�g���̉��Z�i�j�����j
 */
Vector3
Vector3::operator +(const Vector3& a) const
{
	return Vector3(x + a.x, y + a.y, z + a.z);
}

/**
 * �x�N�g���̌��Z�i�j�����j
 */
Vector3
Vector3::operator -(const Vector3& a) const
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}

/**
 * �X�J���[�ɂ���Z
 */
Vector3
Vector3::operator *(float a) const
{
	return Vector3(x * a, y * a, z * a);
}

/**
 * �X�J���[�ɂ�鏜�Z
 */
Vector3
Vector3::operator /(float a) const
{
	float	oneOverA = 1.0f / a;
	return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
}

/**
 * ���Z������Z�q
 */
Vector3&
Vector3::operator +=(const Vector3& a)
{
	x += a.x; y += a.y; z += a.z;
	return *this;
}

/**
 * ���Z������Z�q
 */
Vector3&
Vector3::operator -=(const Vector3& a)
{
	x -= a.x; y -= a.y; z -= a.z;
	return *this;
}

/**
 * ��Z������Z�q
 */
Vector3&
Vector3::operator *=(float a)
{
	x *= a; y *= a; z *= a;
	return *this;
}

/**
 * ���Z������Z�q
 */
Vector3&
Vector3::operator /=(float a)
{
	float	oneOverA = 1.0f / a;
	x *= oneOverA; y *= oneOverA; z *= oneOverA;
	return *this;
}

/**
 * �x�N�g���̐��K��
 */
void
Vector3::normalize()
{
	float magSq = x * x + y * y + z * z;
	if (magSq > 0.0f)
	{
		float oneOverMag = 1.0f / (float)sqrt(magSq);
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
}

/**
 * �x�N�g���̓���
 */
float
Vector3::operator *(const Vector3& a) const
{
	return x * a.x + y * a.y + z * a.z;
}

/**
 * �x�N�g���̑傫�������߂�
 */
inline float vectorMag(const Vector3& a)
{
	return (float)sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

/**
 * ��̃x�N�g���̓��ς����߂�
 */
inline Vector3 crossProduct(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

/**
 * ���X�J���[����Z����
 */
inline Vector3 operator *(float k, const Vector3& v)
{
	return Vector3(k * v.x, k * v.y, k * v.z);
}

/**
 * 2�_�̋������v�Z����
 */
inline float distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

/**
 * 2�_�̋������v�Z����i��Ȃ��j
 */
inline float distanceSquared(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}