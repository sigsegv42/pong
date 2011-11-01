#ifndef INCLUDED_PONG_RENDERER
#define INCLUDED_PONG_RENDERER

#include "PongScene.h"

#include <hookah/Window.h>
#include <font/FontCache.h>

#include <boost/shared_ptr.hpp>

class PongRenderer
{
	public:
		PongRenderer(boost::shared_ptr<PongScene> scene);

		void draw(Hookah::Window * window);
		void resize(int width, int height);

		void drawBall();
		void drawPaddle(const Paddle & paddle);

		boost::shared_ptr<v3D::FontCache> fonts() const;

	private:
		boost::shared_ptr<PongScene> scene_;
		boost::shared_ptr<v3D::FontCache> fonts_;
};

#endif // INCLUDED_PONG_RENDERER
