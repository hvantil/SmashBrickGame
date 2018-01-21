#include <math.h>
#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Shooter.h"

void Shooter::Setup(void)
{
	vMag = 8.0;
	dt = 0.6;
	windowWid = 500.0;
	windowHei = 700.0;

	ballRad = 10.0;
	xShoot = windowWid / 2.0;
	yShoot = windowHei - (2.0 * ballRad);

	Ball b(xShoot, yShoot, ballRad);
	balls.push_back(b);

	isRunning = false;
	spacing = 8;
	spacingCounter = 1;
	powerupCounter = 0;
}
void Shooter::CleanUp(void)
{
	balls.clear();
}

bool Shooter::IsRunning(void)
{
	return isRunning;
}

void Shooter::Move(Grid &grid, bool &isEndOfTurn)
{
	if (isRunning)
	{
		int movingCounter = 0;
		
		for (Ball &b : balls)
		{
			if (b.IsActive())
			{
				// check if ball hits walls, blocks, powerup
				bool hitPowerUp = Bounce(b, grid);
				if (hitPowerUp)
				{
					++powerupCounter;
				}

				// move ball
				b.Move(dt);

				// increment still moving counter
				double vx, vy;
				b.GetVelocity(vx, vy);

				if ((vx == 0) && (vy == 0))
				{
					++movingCounter;
				}
			}
			else
			{								
				// shoot new ball, spaced out by spacing counter
				if (spacingCounter >= spacing)
				{
					b.SetVelocity(vxInit, vyInit);
					b.SetActivity(true);
					spacingCounter = 0;
				}
			}
		}

		++spacingCounter;
		
		// check if turn has ended
		if (movingCounter == balls.size())
		{
			spacingCounter = 1;
			isRunning = false;
			grid.NextRow();
			isEndOfTurn = true;

			for (Ball &b : balls)
			{
				b.SetActivity(false);
			}

			for (int i = 0; i < powerupCounter; ++i)
			{
				Ball b(xShoot, yShoot, ballRad);
				balls.push_back(b);
			}

			powerupCounter = 0;
		}
	}
}
void Shooter::Shoot(Grid &grid, int mx, int my)
{
	double lng = sqrt((xShoot-mx)*(xShoot-mx) + (yShoot-my)*(yShoot-my));
	vxInit = -vMag * ((xShoot - mx) / lng);
	vyInit = -vMag * ((yShoot - my) / lng);

	balls[0].SetActivity(true);
	balls[0].SetVelocity(vxInit, vyInit);
	isRunning = true;
}
bool Shooter::Bounce(Ball &ball, Grid &grid)
{
	// check bounce against external walls
	ball.BounceWalls(windowWid, windowHei, xShoot, yShoot);
	
	bool hitPowerUp = false;
	for (int j = 0; j < grid.GetN(); j++)
	{
		Block block = grid.GetBlock(j);
		int bLives = block.GetLives();

		if (bLives != 0)
		{
			// get block position
			int bX1, bY1, bWid, bHei;

			block.GetXY(bX1, bY1);
			block.GetSize(bWid, bHei);

			double bX2 = bX1 + bWid;
			double bY2 = bY1 + bHei;

			// check bounce against block
			bool pup = ball.BounceBlock(bX1, bX2, bY1, bY2, bLives);
			if (pup)
			{
				hitPowerUp = true;
			}

			// update block lives
			block.SetLives(bLives);
			grid.SetBlock(j, block);
		}
	}

	return hitPowerUp;
}
void Shooter::Draw(int mx, int my)
{
	if (isRunning)
	{
		// don't draw stipple line and draw all balls
		for (Ball b : balls)
		{
			b.Draw();
		}
	}
	else
	{
		//draw stipple line
		double stipX = (double)mx, stipY;
		if ((double)my < 50)
		{
			stipY = 50;
		}
		else
		{
			stipY = (double)my;
		}
				
		glColor3ub(255, 255, 255);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0xf0f0);
		glBegin(GL_LINES);
		glVertex2d(xShoot, yShoot);
		glVertex2d(stipX, stipY);
		glEnd();
		glDisable(GL_LINE_STIPPLE);

		// draw first ball
		balls[0].Draw();

		// draw number of balls
		char nStr[64];
		sprintf(nStr, "x%d", balls.size());
		int xAnchor = xShoot + 20;
		int yAnchor = yShoot + 7;
		glRasterPos2i(xAnchor, yAnchor);
		YsGlDrawFontBitmap10x14(nStr);
	}
}