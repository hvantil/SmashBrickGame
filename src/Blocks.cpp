#include <stdio.h>
#include <math.h>
#include "Blocks.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"

double ChopOff(double d)
{
	if (d < 0.0)
	{
		return 0.0;
	}
	else if (d > 1.0)
	{
		return 1.0;
	}
	return d;
}

Block::Block()
{
	lives = 0;
	maxLevel = 0;
	x = 0;
	y = 0;
	wid = 0;
	hei = 0;
	r = 0;
	g = 0;
	b = 0;
}

int Block::GetLives(void)
{
	return lives;
}
void Block::GetXY(int &xOut, int &yOut)
{
	xOut = x;
	yOut = y;
}
void Block::GetSize(int &wOut, int &hOut)
{
	wOut = wid;
	hOut = hei;
}
void Block::GetColor(int &rOut, int &gOut, int &bOut)
{
	rOut = r;
	gOut = g;
	bOut = b;
}
int Block::GetMaxLevel(void)
{
	return maxLevel;
}
void Block::SetLives(int livesIn)
{
	lives = livesIn;
}
void Block::SetMaxLevel(int levelIn)
{
	maxLevel = levelIn;
}
void Block::SetXY(int xIn, int yIn)
{
	x = xIn;
	y = yIn;
}
void Block::SetSize(int wIn, int hIn)
{
	wid = wIn;
	hei = hIn;
}
void Block::SetColor(void)
{
	double val = (double)lives / (double)maxLevel;

	double r_ = -7.0274*val*val + 10.6892*val - 3.0598;
	double g_ = -7.2750*val*val + 7.5712*val - 0.9248;
	double b_ = -6.9400*val*val + 3.4288*val + 0.5721;

	b = ChopOff(b_) * 255.0;
	r = ChopOff(r_) * 255.0;
	g = ChopOff(g_) * 255.0;
}

void Block::DrawBlock(void)
{
	if (lives > 0)
	{
		// regular block
		SetColor();

		// draw filled square
		glColor3d(r, g, b);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + wid, y);
		glVertex2i(x + wid, y + hei);
		glVertex2i(x, y + wid);
		glEnd();

		// draw outline
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x + wid, y);
		glVertex2i(x + wid, y + hei);
		glVertex2i(x, y + wid);
		glEnd();

		// draw number of lives
		char lifeStr[64];
		sprintf(lifeStr, "%d", lives);

		int y0 = y + ((hei / 2) + 6);
		int x0;
		if (lives < 10)
		{
			x0 = x + ((wid / 2) - 4);
		}
		else if (lives < 100)
		{
			x0 = x + ((wid / 2) - 7);
		}
		else
		{
			x0 = x + ((wid / 2) - 10);
		}		

		glColor3ub(0, 0, 0);
		glRasterPos2i(x0, y0);
		YsGlDrawFontBitmap8x12(lifeStr);
	}

	if (lives < 0)
	{
		// powerup
		const double pi = 3.14159265;

		int rad = 15;
		double cx = x + 25;
		double cy = y + 25;

		// draw filled circle
		glColor3ub(255, 255, 255);
		glBegin(GL_TRIANGLE_FAN);

		for (int i = 0; i <= 64; ++i)
		{
			double angle = (double)i * pi / 32.0;
			double c = cos(angle);
			double s = sin(angle);
			glVertex2d((double)cx + c*rad, (double)cy + s*rad);
		}

		glEnd();
		
		// draw outline
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);

		for (int i = 0; i <= 64; ++i)
		{
			double angle = (double)i * pi / 32.0;
			double c = cos(angle);
			double s = sin(angle);
			glVertex2d((double)cx + c*rad, (double)cy + s*rad);
		}

		glEnd();
	}
}
