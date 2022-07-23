#pragma once

template <typename T>
class Vector2
{
public:
	Vector2() : x(), y() {};
	Vector2(T x, T y) : x(x), y(y) {};

	template <typename U>
	explicit Vector2(const Vector2<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {};

	Vector2<T> operator- (const Vector2<T>& right);
	Vector2<T> operator+ (const Vector2<T>& right);
	Vector2<T> operator* (const Vector2<T>& right);
	Vector2<T> operator/ (const Vector2<T>& right);
	Vector2<T>& operator+= (const Vector2<T>& right);
	Vector2<T>& operator-= (const Vector2<T>& right);
	Vector2<T>& operator*= (const Vector2<T>& right);
	Vector2<T>& operator/= (const Vector2<T>& right);
	bool operator== (const Vector2<T>& right);
	bool operator!= (const Vector2<T>& right);

	// Member data
	T x;
	T y;

};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;
