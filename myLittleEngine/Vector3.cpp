#include "Vector3.h"

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& right)
{
	return Vector3<T>(this->x - right.x, this->y - right.y, this->z - right.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& right)
{
	return Vector3<T>(this->x + right.x, this->y + right.y, this->z + right.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& right)
{
	return Vector3<T>(this->x * right.x, this->y * right.y, this->z * right.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& right)
{
	return Vector3<T>(this->x / right.x, this->y / right.y, this->z / right.z);
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& right)
{
	this->x *= right.x;
	this->y *= right.y;
	this->z *= right.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& right)
{
	this->x /= right.x;
	this->y /= right.y;
	this->z /= right.z;
	return *this;
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& right)
{
	return (this->x == right.x && this->y == right.y && this->z == right.z);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& right)
{
	return (this->x != right.x || this->y != right.y || this->z != right.z);
}
