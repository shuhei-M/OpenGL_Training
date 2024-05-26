/**
 * @file   : Vector3.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : 3Dベクトルクラス
 */

#include <math.h>
#include "Vector3.h"

 /**
  * 代入
  */
Vector3&
Vector3::operator =(const Vector3& a)
{
	x = a.x; y = a.y; z = a.z;
	return *this;
}

/**
 * 等しい
 */
bool
Vector3::operator ==(const Vector3& a) const
{
	return x == a.x && y == a.y && z == a.z;
}

/**
 * 一致しない
 */
bool
Vector3::operator !=(const Vector3& a) const
{
	return x != a.x || y != a.y || z != a.z;
}

/**
 * ゼロベクトル
 */
void
Vector3::zero()
{
	x = y = z = 0.0f;
}

/**
 * ベクトルの反転
 */
Vector3
Vector3::operator -() const
{
	return Vector3(-x, -y, -z);
}

/**
 * ベクトルの加算（ニ項式）
 */
Vector3
Vector3::operator +(const Vector3& a) const
{
	return Vector3(x + a.x, y + a.y, z + a.z);
}

/**
 * ベクトルの減算（ニ項式）
 */
Vector3
Vector3::operator -(const Vector3& a) const
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}

/**
 * スカラーによる乗算
 */
Vector3
Vector3::operator *(float a) const
{
	return Vector3(x * a, y * a, z * a);
}

/**
 * スカラーによる除算
 */
Vector3
Vector3::operator /(float a) const
{
	float	oneOverA = 1.0f / a;
	return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
}

/**
 * 加算代入演算子
 */
Vector3&
Vector3::operator +=(const Vector3& a)
{
	x += a.x; y += a.y; z += a.z;
	return *this;
}

/**
 * 減算代入演算子
 */
Vector3&
Vector3::operator -=(const Vector3& a)
{
	x -= a.x; y -= a.y; z -= a.z;
	return *this;
}

/**
 * 乗算代入演算子
 */
Vector3&
Vector3::operator *=(float a)
{
	x *= a; y *= a; z *= a;
	return *this;
}

/**
 * 除算代入演算子
 */
Vector3&
Vector3::operator /=(float a)
{
	float	oneOverA = 1.0f / a;
	x *= oneOverA; y *= oneOverA; z *= oneOverA;
	return *this;
}

/**
 * ベクトルの正規化
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
 * ベクトルの内積
 */
float
Vector3::operator *(const Vector3& a) const
{
	return x * a.x + y * a.y + z * a.z;
}

/**
 * ベクトルの大きさを求める
 */
inline float vectorMag(const Vector3& a)
{
	return (float)sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

/**
 * 二つのベクトルの内積を求める
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
 * 左スカラーを乗算する
 */
inline Vector3 operator *(float k, const Vector3& v)
{
	return Vector3(k * v.x, k * v.y, k * v.z);
}

/**
 * 2点の距離を計算する
 */
inline float distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

/**
 * 2点の距離を計算する（√なし）
 */
inline float distanceSquared(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}