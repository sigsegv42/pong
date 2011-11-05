#ifndef INCLUDED_PONG_PADDLE
#define INCLUDED_PONG_PADDLE

#include <vertical3d/3dtypes/Color3.h>

using namespace v3D;

class Paddle
{
    public:
        Paddle();

		void color(const Color3 & color1, const Color3 & color2);
        void move(float delta);
		void position(const float pos);
		void offset(const float off);
		float offset() const;
		float position() const;

		Color3 color1() const;
		Color3 color2() const;

		void reset();

		bool up();
		bool down();
		int score();
		float length();
		float size();

		void up(bool k);
		void down(bool k);
		void score(int s);

    private:
        float position_;
		float offset_;
        Color3 color1_;
        Color3 color2_;

		float length_;
		float size_;

		bool up_;
		bool down_;
		int score_;
};

#endif // INCLUDED_PONG_PADDLE
