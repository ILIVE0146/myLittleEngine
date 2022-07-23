#include "Vector2.h"

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& right)
{
	return Vector2<T>(this->x - right.x, this->y - right.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& right)
{
	return Vector2<T>(this->x + right.x, this->y + right.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& right)
{
	return Vector2<T>(this->x * right.x, this->y * right.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& right)
{
	return Vector2<T>(this->x / right.x, this->y / right.y);
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& right)
{
	this->x += right.x;
	this->y += right.y;
	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& right)
{
	this->x -= right.x;
	this->y -= right.y;
	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& right)
{
	this->x *= right.x;
	this->y *= right.y;
	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& right)
{
	this->x /= right.x;
	this->y /= right.y;
	return *this;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& right)
{
	if (this->x == right.x && this->y == right.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& right)
{
	if (*this == right)
	{
		return false;
	}
	else
	{
		return true;
	}
}
