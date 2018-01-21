#ifndef HIGHSCORES_H_IS_INCLUDED
#define HIGHSCORES_H_IS_INCLUDED

#include "Score.h"

class Highscores
{
private:
	Score scores[5];
	char filename[255] = "highscores.txt";
public:
	int GetScore(int idx);
	void GetLine(int idx, char rank[], char score[], char name[]);

	void ReadScores(void);
	void WriteScores(int rank, int score, char *name);
};

#endif