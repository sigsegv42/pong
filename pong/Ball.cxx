#include "Ball.h"

#include <3dtypes/Vector3.h>

#include <cmath>


Ball::Ball() : size_(1.0f)
{
}


void Ball::direction(const Vector2 & dir)
{
	direction_ = dir;
}

Vector2 Ball::direction() const
{
	return direction_;
}

Vector2 Ball::position() const
{
	return position_;
}

void Ball::position(const Vector2 & pos)
{
	position_ = pos;
}

void Ball::move()
{
	position_ += direction_;
}

float Ball::size() const
{
	return size_;
}

void Ball::size(float s)
{
	size_ = s;
}

