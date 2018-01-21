#include "Score.h"
#include <stdlib.h>

void Score::Set(char line[])
{
	score = atoi(line + 2);

	int idx;
	for (idx = 2; idx < 255; idx++)
	{
		if (line[idx] == ',')
		{
			break;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		name[i] = line[idx + i + 1];
	}
	name[3] = 0;
}
int Score::GetScore(void)
{
	return score;
}
char *Score::GetName(void)
{
	return name;
}