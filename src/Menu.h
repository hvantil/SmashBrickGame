#ifndef MENU_H_IS_INCLUDED
#define MENU_H_IS_INCLUDED

#include "Page.h"
#include "Highscores.h"
#include "TextInput.h"

class Page;

class Menu
{
private:
	int pageIdx, gameScore, key;
	bool doStartGame, doQuit;

	Page *pages;
	Highscores highscores;
	TextInput txtInput;
public:
	Menu();

	void SetPageIdx(int pgIdxIn);
	void SetGameScore(int scoreIn);
	bool SetNewHighscore(void);

	int GetScore(int score);
	int GetGameScore(void);
	void GetHighscoreLine(int idx, char rank[], char score[], char name[]);
	void GetTxtInput(void);

	void UpdateSelection(int mx, int my);
	void Click(void);

	int Run(void);
	void Draw(int key);
	void DrawTxtInput(int x0, int y0);
};

#endif