#ifndef INCLUDED_PONG_BALL
#define INCLUDED_PONG_BALL

#include <vertical3d/3dtypes/Vector2.h>

using namespace v3D;

class Ball
{
	public:
		Ball();

		void direction(const Vector2 & dir);
		Vector2 direction() const;

		Vector2 position() const;
		void position(const Vector2 & pos);

		void move();

		float size() const;
		void size(float s);

	private:
		Vector2 position_;
		Vector2 direction_;
		float size_;
};

#endif // INCLUDED_PONG_BALL

