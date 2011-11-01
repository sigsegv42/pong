#ifndef INCLUDED_PONG_SCENE
#define INCLUDED_PONG_SCENE

#include "Ball.h"
#include "Paddle.h"
#include "GameState.h"

#include <audio/SoundEngine.h>
#include <util/PropertyTree.h>

class PongScene
{
	public:
		PongScene(PropertyTree & ptree);
		~PongScene();

		void tick(unsigned int delta);
		void resize(int width, int height);

		void reset();

		Ball & ball();
		Paddle & left();
		Paddle & right();
		GameState & state();

	private:
        Ball ball_;
        Paddle left_, right_;
		GameState gameState_;
		int width_, height_;
		v3D::SoundEngine soundEngine_;
};


#endif // INCLUDED_PONG_SCENE
