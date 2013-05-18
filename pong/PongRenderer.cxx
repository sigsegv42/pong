#include "PongRenderer.h"

#include <vertical3d/3dtypes/3dtypes.h>
#include <vertical3d/gl/GLFontRenderer.h>

#include <boost/lexical_cast.hpp>

#include <GL/glew.h>

#include <cmath>
#include <iostream>

PongRenderer::PongRenderer(boost::shared_ptr<PongScene> scene) : scene_(scene), fonts_(new v3D::FontCache())
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

boost::shared_ptr<v3D::FontCache> PongRenderer::fonts() const
{
	return fonts_;
}

void PongRenderer::resize(int width, int height)
{
	scene_->resize(width, height);

	GLfloat ratio;

	if (height == 0)
		height = 1;

	ratio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void PongRenderer::draw(Hookah::Window * window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(0.35f, 0.35f, 0.35f);

	int width = window->width();
	int height = window->height();

	// draw the scoreboard
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// map top left to (0,0)
	glOrtho(0, (float)width, (float)height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	boost::shared_ptr<v3D::Font2D> scoreFont = fonts_->get("score");
	v3D::GLFontRenderer fontRenderer(*scoreFont);

	// left score
	std::string txt = boost::lexical_cast<std::string>(scene_->left().score());
	fontRenderer.print(txt, (width / 4.0f), (height / 4.0f));

	// right score
	txt = boost::lexical_cast<std::string>(scene_->right().score());
	fontRenderer.print(txt, ((width / 4.0f) * 3.0f), (height / 4.0f));
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// draw the gameboard

	// center line
	glBegin(GL_QUADS);
	glVertex2i(((width / 2) - 7), 0);
	glVertex2i(((width / 2) + 7), 0);
	glVertex2i(((width / 2) + 7), height);
	glVertex2i(((width / 2) - 7), height);
	glEnd();

	// top wall
	glBegin(GL_QUADS);
	glVertex2i(0, height);
	glVertex2i(width, height);
	glVertex2i(width, (height - 15));
	glVertex2i(0, (height - 15));
	glEnd();

	// bottom wall
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(width, 0);
	glVertex2i(width, 15);
	glVertex2i(0, 15);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	// draw the paddles and ball
	drawPaddle(scene_->left());
	drawPaddle(scene_->right());

	drawBall();
}

void PongRenderer::drawBall()
{
	int sides = 32;
	v3D::Vector2 position = scene_->ball().position();

	glPushMatrix();
	glTranslatef(position[0], position[1], 0.0f);

	float delta = 2.0f * PI / sides;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int k = 0; k < sides; k++)
	{
		Vector3 p;
		p[0] = 0.0;
		p[1] = cos(delta * k) * scene_->ball().size();
		p[2] = sin(delta * k) * scene_->ball().size();
		glVertex2f(p[1], p[2]);
	}
	glEnd();
	glPopMatrix();
}

void PongRenderer::drawPaddle(const Paddle & paddle)
{
	glPushMatrix();
	v3D::Color3 color1 = paddle.color1();
	v3D::Color3 color2 = paddle.color2();
	// use a translation to get to object space
	// offsetting y so our origin is the left corner
	// x is adjusted depending on which side of the screen the paddle is on
	glTranslatef(paddle.offset(), paddle.position() - 25.0f, 0.0f);
	glBegin(GL_QUADS);
    glColor3f(color1[0], color1[1], color1[2]);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 50.0f);
    glColor3f(color2[1], color2[1], color2[2]);
    glVertex2f(15.0f, 50.0f);
    glVertex2f(15.0f, 0.0f);
    glEnd();
	glPopMatrix();
}
