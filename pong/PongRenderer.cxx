/**
 * Pong! - (c) Joshua Farr <j.wgasa@gmail.com>
 */

#include "PongRenderer.h"

#include <vertical3d/3dtypes/3dtypes.h>
#include <vertical3d/gl/GLFontRenderer.h>
#include <vertical3d/gl/Shader.h>

#include <stark/AssetLoader.h>
#include <stark/ProgramFactory.h>

#include <boost/lexical_cast.hpp>

#include <GL/glew.h>

#include <cmath>
#include <iostream>

PongRenderer::PongRenderer(boost::shared_ptr<PongScene> scene, boost::shared_ptr<AssetLoader> & loader) : scene_(scene), fonts_(new v3D::FontCache())
{
	ProgramFactory factory(loader);
	boost::shared_ptr<v3D::Program> program = factory.create(v3D::Shader::SHADER_TYPE_VERTEX|v3D::Shader::SHADER_TYPE_FRAGMENT, "shaders/canvas");

	canvas_.reset(new v3D::Canvas(program));

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_CLAMP);
	// CCW winding is default
	glFrontFace(GL_CCW);
	glActiveTexture(GL_TEXTURE0);
}

boost::shared_ptr<v3D::FontCache> PongRenderer::fonts() const
{
	return fonts_;
}

void PongRenderer::resize(int width, int height)
{
	scene_->resize(width, height);

	canvas_->resize(width, height);
}

void PongRenderer::draw(Hookah::Window * window)
{
	canvas_->clear();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int width = window->width();
	int height = window->height();

	// draw the scoreboard
	boost::shared_ptr<v3D::Font2D> scoreFont = fonts_->get("score");
	v3D::GLFontRenderer fontRenderer(*scoreFont);

	// left score
	std::string txt = boost::lexical_cast<std::string>(scene_->left().score());
	fontRenderer.print(txt, (width / 4.0f), (height / 4.0f));

	// right score
	txt = boost::lexical_cast<std::string>(scene_->right().score());
	fontRenderer.print(txt, ((width / 4.0f) * 3.0f), (height / 4.0f));

	// draw the gameboard

	// center line
	glm::vec3 color(0.35f, 0.35f, 0.35f);
	canvas_->rect(((width / 2) - 7), ((width / 2) + 7), 0, height, color);

	// bottom wall
	canvas_->rect(0, width, height - 15, height, color);

	// top wall
	canvas_->rect(0, width, 0, 15, color);

	// draw the paddles and ball
	drawPaddle(scene_->left());
	drawPaddle(scene_->right());

	drawBall();

	// upload to GPU & render
	canvas_->upload();
	canvas_->render();
}

void PongRenderer::drawBall()
{
	int sides = 32;
	glm::vec2 position = scene_->ball().position();

	canvas_->push();
	canvas_->translate(position);
	glm::vec3 color(1.0f, 1.0f, 1.0f);
	canvas_->circle(sides, scene_->ball().size(), color);

	canvas_->pop();
}

void PongRenderer::drawPaddle(const Paddle & paddle)
{
	canvas_->push();
	glm::vec3 color1 = paddle.color1();
	glm::vec3 color2 = paddle.color2();
	// use a translation to get to object space
	// offsetting y so our origin is the left corner
	// x is adjusted depending on which side of the screen the paddle is on
	canvas_->translate(glm::vec2(paddle.offset(), paddle.position() - 25));
	canvas_->rect(0, 15, 0, 50, color1);
	canvas_->pop();
}
