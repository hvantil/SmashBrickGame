#ifndef SCORE_H_IS_INCLUDED
#define SCORE_H_IS_INCLUDED

class Score
{
private:
	int score;
	char name[4];
public:
	void Set(char line[]);
	int GetScore(void);
	char *GetName(void);
};

#endif