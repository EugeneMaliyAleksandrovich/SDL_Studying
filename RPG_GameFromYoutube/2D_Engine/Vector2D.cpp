#include "Vector2D.hpp"

Vector2D::Vector2D(float mx, float my) : x(mx), y(my) { }

Vector2D& Vector2D::add(const Vector2D& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}
Vector2D& Vector2D::substract(const Vector2D& vector) {
	x -= vector.x;
	y -= vector.y;

	return *this;
}
Vector2D& Vector2D::multiply(const Vector2D& vector) {
	x *= vector.x;
	y *= vector.y;

	return *this;
}
Vector2D& Vector2D::divide(const Vector2D& vector) {
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Vector2D& operator+(Vector2D& vector1, const Vector2D& vector2) { return vector1.add(vector2); }
Vector2D& operator-(Vector2D& vector1, const Vector2D& vector2) { return vector1.substract(vector2); }
Vector2D& operator*(Vector2D& vector1, const Vector2D& vector2) { return vector1.multiply(vector2); }
Vector2D& operator/(Vector2D& vector1, const Vector2D& vector2) { return vector1.divide(vector2); }

Vector2D& Vector2D::operator+=(const Vector2D& vector) { return this->add(vector); }
Vector2D& Vector2D::operator-=(const Vector2D& vector) { return this->substract(vector); }
Vector2D& Vector2D::operator*=(const Vector2D& vector) { return this->multiply(vector); }
Vector2D& Vector2D::operator/=(const Vector2D& vector) { return this->divide(vector); }

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector) {
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}