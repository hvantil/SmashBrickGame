#include "Game.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
using namespace std::chrono;

void Game::Run(void)
{
	spdWhite.Decode("speedupWhite.png");
	spdRed.Decode("speedupRed.png");

	glGenTextures(1, &whtTexId);
	glBindTexture(GL_TEXTURE_2D, whtTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spdWhite.wid, spdWhite.hei,
		0, GL_RGBA, GL_UNSIGNED_BYTE, spdWhite.rgba);

	glGenTextures(1, &redTexId);
	glBindTexture(GL_TEXTURE_2D, redTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spdRed.wid, spdRed.hei,
		0, GL_RGBA, GL_UNSIGNED_BYTE, spdRed.rgba);

	for (;;)
	{
		int choice;
		menu.SetPageIdx(0);
		choice = menu.Run();
		
		if (choice == -1)
		{
			// quit
			break;
		}
		if (choice == 1)
		{
			// start game
			bestScore = menu.GetScore(0);
			score = 0;
			Play();
		
			// after game menu
			int worstScore = menu.GetScore(4);
			if (score >= worstScore)
			{
				menu.SetPageIdx(3);
			}
			else
			{
				menu.SetPageIdx(2);
			}
			menu.SetGameScore(score);
			choice = menu.Run();
		
			if (choice == -1)
			{
				// quit
				break;
			}
		}
	}
}

void Game::Play(void)
{
	double tPause = 0.008;

	int gridWidth = 10;
	int gridHeight = 13;

	shooter.CleanUp();
	shooter.Setup();
	
	grid.CleanUp();
	grid.Setup(gridWidth, gridHeight);
	grid.NextRow();
	
	for (;;)
	{
		steady_clock::time_point t1 = steady_clock::now();
		FsPollDevice();
		auto key = FsInkey();

		if (key == FSKEY_ESC) 
		{
			break;
		}
		if (grid.GameOverCheck())
		{
			break;
		}

		int lb, mb, rb, mx, my;
		auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);
		if (evt == FSMOUSEEVENT_LBUTTONDOWN)
		{
			if (shooter.IsRunning())
			{
				if ((mx >= 427) && (mx <= 482) && (my >= 7) && (my <= 40))
				{
					tPause = 0.0;
				}
			}
			else
			{
				shooter.Shoot(grid, mx, my);
			}
			
		}

		bool isEndOfTurn = false;
		shooter.Move(grid, isEndOfTurn);

		if (isEndOfTurn)
		{
			score++;
			tPause = 0.008;
		}
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		DrawBackground();
		grid.DrawBlocks();
		shooter.Draw(mx, my);
		DrawIcon(mx, my);

		FsSwapBuffers();

		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		while (time_span.count() < tPause)
		{
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
		}
	}
}

void Game::DrawBackground(void)
{
	// top bar
	glColor3ub(10, 10, 10);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, 50);
	glVertex2i(500, 50);
	glVertex2i(500, 0);
	glEnd();

	// main background
	glColor3ub(34, 34, 34);
	glBegin(GL_QUADS);
	glVertex2i(0, 50);
	glVertex2i(0, 700);
	glVertex2i(500, 700);
	glVertex2i(500, 50);
	glEnd();

	// draw top bar: score, best score
	char scoreStr[64];
	sprintf(scoreStr, "SCORE: %d", score);	
	glColor3ub(255, 255, 255);
	glRasterPos2i(25, 33);
	YsGlDrawFontBitmap12x16(scoreStr);

	char bestScoreStr[64];
	if (bestScore > score)
	{
		sprintf(bestScoreStr, "BEST: %d", bestScore);
	}
	else
	{
		sprintf(bestScoreStr, "BEST: %d", score);
	}
	glColor3ub(255, 255, 255);
	glRasterPos2i(208, 33);
	YsGlDrawFontBitmap12x16(bestScoreStr);
}
void Game::DrawIcon(int mx, int my)
{
	// draw speedup icon
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);

	int x0 = 427;
	int x1 = 482;
	int y0 = 7;
	int y1 = 40;

	if ((mx >= x0) && (mx <= x1) && (my >= y0) && (my <= y1) && shooter.IsRunning())
	{
		glBindTexture(GL_TEXTURE_2D, redTexId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, whtTexId);
	}
	

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(x0, y0);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(x1, y0);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(x1, y1);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(x0, y1);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}