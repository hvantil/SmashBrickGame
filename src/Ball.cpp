#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Ball.h"

Ball::Ball(double xIn, double yIn, double radIn)
{
	x = xIn;
	y = yIn;
	vx = 0;
	vy = 0;
	rad = radIn;
	r = 255;
	g = 0;
	b = 0;
	isActive = false;
}

void Ball::GetPosition(double &xOut, double &yOut)
{
	xOut = x;
	yOut = y;
}
void Ball::GetVelocity(double &vxOut, double &vyOut)
{
	vxOut = vx;
	vyOut = vy;
}
double Ball::GetRad(void)
{
	return rad;
}
bool Ball::IsActive(void)
{
	return isActive;
}
void Ball::SetPosition(double xIn, double yIn)
{
	x = xIn;
	y = yIn;
}
void Ball::SetVelocity(double vxIn, double vyIn)
{
	vx = vxIn;
	vy = vyIn;
}
void Ball::SetActivity(bool activity)
{
	isActive = activity;
}

void Ball::Move(double dt)
{	
	// psuedo-gravity
	// to discourage spamming the sideways shot
	if (y < 600)
	{
		vy += 0.01 * dt; 
	}

	x += vx * dt;
	y += vy * dt;
}
void Ball::BounceWalls(double wid, double hei, double x0, double y0)
{
	if (((x - rad) < 0) && (vx < 0))
	{
		// left wall
		vx *= -1;
	}	
	else if (((x + rad) > wid) && (vx > 0))
	{
		// right wall
		vx *= -1;
	}

	if (((y - rad) < 50) && (vy < 0))
	{
		// top wall
		vy *= -1;
	}
	else if (y > hei)
	{
		// bottom wall
		x = x0;
		y = y0;
		vx = 0;
		vy = 0;
	}
}
bool Ball::BounceBlock(double bX1, double bX2, double bY1, double bY2, int &bLives)
{
	bool hitPowerUp = false;

	// ball velocity directions
	bool movingDown = vy > 0.0;
	bool movingUp = vy < 0.0;
	bool movingRight = vx > 0.0;
	bool movingLeft = vx < 0.0;

	// check ball relative to block
	bool crossesBottom =
		((y - rad) <= bY2) &&
		(y >= (bY2 - 2*rad));
	bool crossesTop =
		((y + rad) >= bY1) &&
		(y <= (bY1 + 2*rad));
	bool crossesRight =
		((x - rad) <= bX2) &&
		(x >= (bX2 - 2*rad));
	bool crossesLeft =
		((x + rad) >= bX1) &&
		(x <= (bX1 + 2*rad));
	bool isInWidth = (x > bX1) && (x < bX2);
	bool isInHeight = (y > bY1) && (y < bY2);

	if (bLives > 0)
	{
		// regular block
		if (crossesRight && movingLeft && isInHeight)
		{
			vx *= -1;
			--bLives;
		}
		if (crossesLeft && movingRight && isInHeight)
		{
			vx *= -1;
			--bLives;
		}
		if (crossesTop && movingDown && isInWidth)
		{
			vy *= -1;
			--bLives;
		}
		if (crossesBottom && movingUp && isInWidth)
		{
			vy *= -1;
			--bLives;
		}

		if (bLives < 0)
		{
			bLives = 0;
		}
	}
	else if (bLives == -1)
	{
		// powerup
		int dx = x - ((bX1+bX2) / 2);
		int dy = y - ((bY1+bY2) / 2);

		if ((dx >= -15) && (dx <= 15) &&
			(dy >= -15) && (dy <= 15))
		{
			bLives = 0;
			hitPowerUp = true;
		}
	}

	return hitPowerUp;
}
void Ball::Draw(void)
{
	const double pi = 3.14159265;

	glColor3ub(r, g, b);
	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i <= 64; ++i)
	{
		double angle = (double)i * pi / 32.0;
		double c = cos(angle);
		double s = sin(angle);
		glVertex2d((double)x + c*rad, (double)y + s*rad);
	}

	glEnd();
}
