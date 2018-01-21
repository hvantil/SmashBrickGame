#include "Menu.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

void DrawMainPage(Menu &menu)
{
	glColor3ub(255, 255, 255);

	glRasterPos2i(172, 200);
	YsGlDrawFontBitmap32x48("SMASH");
	glRasterPos2i(172, 260);
	YsGlDrawFontBitmap32x48("BRICK");
}
void DrawScoresPage(Menu &menu)
{
	glColor3ub(255, 255, 255);

	glRasterPos2i(135, 150);
	YsGlDrawFontBitmap24x40("HIGHSCORES");

	glRasterPos2i(70, 250);
	YsGlDrawFontBitmap20x28("RANK");
	glRasterPos2i(200, 250);
	YsGlDrawFontBitmap20x28("SCORE");
	glRasterPos2i(350, 250);
	YsGlDrawFontBitmap20x28("NAME");

	char rank[255], score[255], name[255];
	for (int i = 0; i < 5; ++i)
	{
		menu.GetHighscoreLine(i, rank, score, name);

		glRasterPos2i(70, 300 + (i * 50));
		YsGlDrawFontBitmap16x24(rank);

		glRasterPos2i(200, 300 + (i * 50));
		YsGlDrawFontBitmap16x24(score);

		glRasterPos2i(350, 300 + (i * 50));
		YsGlDrawFontBitmap16x24(name);
	}
}
void DrawAfterGamePage(Menu &menu)
{
	glColor3ub(255, 255, 255);

	char gameScoreStr[255];
	itoa(menu.GetGameScore(), gameScoreStr, 10);
	glRasterPos2i(70, 100);
	YsGlDrawFontBitmap24x40("SCORE:");
	glRasterPos2i(230, 100);
	YsGlDrawFontBitmap24x40(gameScoreStr);

	glRasterPos2i(155, 200);
	YsGlDrawFontBitmap20x28("HIGHSCORES");

	glRasterPos2i(70, 270);
	YsGlDrawFontBitmap20x28("RANK");
	glRasterPos2i(200, 270);
	YsGlDrawFontBitmap20x28("SCORE");
	glRasterPos2i(350, 270);
	YsGlDrawFontBitmap20x28("NAME");

	char rank[255], score[255], name[255];
	for (int i = 0; i < 5; ++i)
	{
		menu.GetHighscoreLine(i, rank, score, name);

		glRasterPos2i(70, 320 + (i * 50));
		YsGlDrawFontBitmap16x24(rank);

		glRasterPos2i(200, 320 + (i * 50));
		YsGlDrawFontBitmap16x24(score);

		glRasterPos2i(350, 320 + (i * 50));
		YsGlDrawFontBitmap16x24(name);
	}
}
void DrawNewHighscorePage(Menu &menu)
{
	glColor3ub(255, 255, 255);

	char gameScoreStr[255];
	itoa(menu.GetGameScore(), gameScoreStr, 10);
	glRasterPos2i(70, 100);
	YsGlDrawFontBitmap24x40("SCORE:");
	glRasterPos2i(230, 100);
	YsGlDrawFontBitmap24x40(gameScoreStr);

	glRasterPos2i(115, 200);
	YsGlDrawFontBitmap20x28("NEW HIGHSCORE!");

	glRasterPos2i(70, 270);
	YsGlDrawFontBitmap20x28("RANK");
	glRasterPos2i(200, 270);
	YsGlDrawFontBitmap20x28("SCORE");
	glRasterPos2i(350, 270);
	YsGlDrawFontBitmap20x28("NAME");

	int newRank;
	for (int i = 0; i < 5; ++i)
	{
		int hscore = menu.GetScore(i);
		if (menu.GetGameScore() >= hscore)
		{
			newRank = i;
			break;
		}
	}

	char rank[255], score[255], name[255];
	bool shift = false;
	for (int i = 0; i < 5; ++i)
	{
		if (i == newRank)
		{
			itoa(i+1, rank, 10);
			itoa(menu.GetGameScore(), score, 10);

			glRasterPos2i(70, 320 + (i * 50));
			YsGlDrawFontBitmap16x24(rank);

			glRasterPos2i(200, 320 + (i * 50));
			YsGlDrawFontBitmap16x24(score);

			menu.GetTxtInput();
			menu.DrawTxtInput(350, 320 + (i * 50));

			shift = true;
		}
		else
		{
			int idx = i;
			if (shift)
			{
				--idx;
			}

			menu.GetHighscoreLine(i, rank, score, name);
			itoa(i+1, rank, 10);

			glRasterPos2i(70, 320 + (i * 50));
			YsGlDrawFontBitmap16x24(rank);

			glRasterPos2i(200, 320 + (i * 50));
			YsGlDrawFontBitmap16x24(score);

			glRasterPos2i(350, 320 + (i * 50));
			YsGlDrawFontBitmap16x24(name);
		}		
	}
}

Menu::Menu()
{
	pages = new Page [4];
	doStartGame = false;
	doQuit = false;
	highscores.ReadScores();
	gameScore = 0;

	Button b;

	// Main Page ------------

	Page mainPage;

	b.SetParams("START GAME", 100, 455, 300, 34, -1);
	mainPage.AddButton(b);

	b.SetParams("HIGHSCORES", 100, 535, 300, 33, 1);
	mainPage.AddButton(b);

	b.SetParams("QUIT", 100, 615, 300, 102, -2);
	mainPage.AddButton(b);

	mainPage.SetDrawFxn(DrawMainPage);
	pages[0] = mainPage;

	// Highscores Page ------------

	Page scoresPage;

	b.SetParams("BACK", 150, 655, 200, 55, 0);
	scoresPage.AddButton(b);

	scoresPage.SetDrawFxn(DrawScoresPage);
	pages[1] = scoresPage;

	// Aftergame Page ------------

	Page afterGamePage;

	b.SetParams("REPLAY", 20, 635, 225, 47, -1);
	afterGamePage.AddButton(b);

	b.SetParams("QUIT", 255, 635, 225, 70, -2);
	afterGamePage.AddButton(b);

	afterGamePage.SetDrawFxn(DrawAfterGamePage); 
	pages[2] = afterGamePage;

	// New Highscore Page ------------

	Page newHighscorePage;

	b.SetParams("ENTER NAME", 86, 617, 328, 47, 2);
	newHighscorePage.AddButton(b);

	newHighscorePage.SetDrawFxn(DrawNewHighscorePage);
	pages[3] = newHighscorePage;
}

void Menu::SetPageIdx(int pgIdxIn)
{
	if ((pageIdx == 3) && (pgIdxIn == 2))
	{
		bool isValidName = SetNewHighscore();
		if (isValidName)
		{
			highscores.ReadScores();
		}
		else
		{
			pgIdxIn = 3;
		}
	}

	pageIdx = pgIdxIn;
	doStartGame = false;
	doQuit = false;
	txtInput.Clear();
}
void Menu::SetGameScore(int scoreIn)
{
	gameScore = scoreIn;
}
bool Menu::SetNewHighscore(void)
{
	if (txtInput.CheckName())
	{
		int newRank;
		for (int i = 0; i < 5; ++i)
		{
			int hscore = highscores.GetScore(i);
			if (gameScore >= hscore)
			{
				newRank = i;
				break;
			}
		}

		highscores.WriteScores(newRank, gameScore, txtInput.GetName());
		return true;
	}
	return false;
}

int Menu::GetScore(int idx)
{
	return highscores.GetScore(idx);
}
int Menu::GetGameScore(void)
{
	return gameScore;
}
void Menu::GetHighscoreLine(int idx, char rank[], char score[], char name[])
{
	highscores.GetLine(idx, rank, score, name);
}
void Menu::GetTxtInput(void)
{
	txtInput.GetInput(key);
}

void Menu::UpdateSelection(int mx, int my)
{
	pages[pageIdx].UpdateSelection(mx, my);
}
void Menu::Click(void)
{
	int clickIdx = pages[pageIdx].GetIdx();
	if (clickIdx > 0)
	{
		int newPageIdx = pages[pageIdx].GetPageRef(clickIdx);
		if (newPageIdx == -1)
		{
			doStartGame = true;
		}
		else if (newPageIdx == -2)
		{
			doQuit = true;
		}
		else
		{
			SetPageIdx(newPageIdx);
		}
	}
}

int Menu::Run(void)
{
	for (;;)
	{
		FsPollDevice();
		key = FsInkey();

		if ((key == FSKEY_ESC) || doQuit)
		{
			return -1;
		}
		if (doStartGame)
		{
			return 1;
		}

		int lb, mb, rb, mx, my;
		auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);

		UpdateSelection(mx, my);

		if (evt == FSMOUSEEVENT_LBUTTONDOWN)
		{
			Click();
		}

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		Draw(key);

		FsSwapBuffers();
		FsSleep(25);
	}
}
void Menu::Draw(int key)
{
	glColor3ub(34, 34, 34);

	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, 700);
	glVertex2i(500, 700);
	glVertex2i(500, 0);
	glEnd();

	pages[pageIdx].Draw(*this);
}
void Menu::DrawTxtInput(int x0, int y0)
{
	txtInput.Draw(x0, y0);
}