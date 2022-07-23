#pragma once

template <typename T>
class Vector3
{
	Vector3();
	Vector3(T x, T y, T z);

	template <typename U>
	explicit Vector3(const Vector3<U>& vector);

	Vector3<T> operator - (const Vector3<T>& right);
	Vector3<T> operator + (const Vector3<T>& right);
	Vector3<T> operator * (const Vector3<T>& right);
	Vector3<T> operator / (const Vector3<T>& right);
	Vector3<T>& operator += (const Vector3<T>& right);
	Vector3<T>& operator -= (const Vector3<T>& right);
	Vector3<T>& operator *= (const Vector3<T>& right);
	Vector3<T>& operator /= (const Vector3<T>& right);
	bool operator == (const Vector3<T>& right);
	bool operator != (const Vector3<T>& right);

	// Member Variables
	T x, y, z;


};

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<unsigned int> Vector3u;