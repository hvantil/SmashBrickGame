#ifndef GAME_H_IS_INCLUDED
#define GAME_H_IS_INCLUDED

#include "Grid.h"
#include "Menu.h"
#include "Shooter.h"
#include "yspng.h"
#include "fssimplewindow.h"

class Game
{
public:
	Menu menu;
	Grid grid;
	Shooter shooter;
	int score, bestScore;
	YsRawPngDecoder spdWhite, spdRed;
	GLuint whtTexId, redTexId;

	void Run(void);
	void Play(void);
	void DrawBackground(void);
	void DrawIcon(int mx, int my);
};

#endif