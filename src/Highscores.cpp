#include "Highscores.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

int Highscores::GetScore(int idx)
{
	return scores[idx].GetScore();
}
void Highscores::GetLine(int idx, char rank[], char score[], char name[])
{
	itoa(idx + 1, rank, 10);
	itoa(scores[idx].GetScore(), score, 10);

	char *nm = scores[idx].GetName();
	for (int i = 0; i < 3; ++i)
	{
		name[i] = nm[i];
	}
	name[3] = 0;
}

void Highscores::ReadScores(void)
{
	ifstream file;
	file.open(filename, fstream::in);

	for (int i = 0; i < 5; i++)
	{
		char line[255];
		file >> line;
		scores[i].Set(line);
	}

	file.close();
}
void Highscores::WriteScores(int rank, int score, char *name)
{
	ofstream file;
	file.open(filename, fstream::out);

	bool shift = false;
	for (int i = 0; i < 5; i++)
	{
		if (i == rank)
		{
			file << i + 1 << ",";
			file << score << ",";
			file << name << "\n";

			shift = true;
		}
		else
		{
			int idx = i;
			if (shift)
			{
				--idx;
			}

			file << i + 1 << ",";
			file << scores[idx].GetScore() << ",";
			file << scores[idx].GetName() << "\n";
		}
	}

	file.close();
}