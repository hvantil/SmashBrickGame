#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Grid.h"

void Grid::Setup(int wIn, int hIn)
{
	level = 0;
	wid = wIn;
	hei = hIn;
	n = wid * hei;

	for (int i = 0; i < n; ++i)
	{
		int bw = 50;
		int bh = 50;
		int bx = (i % wid) * bh;
		int by = ((i / wid) * bw) + 50;

		Block b;
		b.SetXY(bx, by);
		b.SetSize(bw, bh);
		blocks.push_back(b);
	}
}
void Grid::CleanUp(void)
{
	level = 0;
	blocks.clear();
}

int Grid::GetLevel()
{
	return level;
}
Block Grid::GetBlock(int idx)
{
	return blocks[idx];
}
int Grid::GetN(void)
{
	return n;
}
void Grid::SetLevel(int levelIn)
{
	level = levelIn;
}
void Grid::SetBlock(int idx, Block blockIn)
{
	blocks[idx] = blockIn;
}

void Grid::PickColor(int &r, int &g, int &b)
{
	int rnd = rand() % 5;

	switch (rnd)
	{
	case 0:
		r = 250;
		g = 115;
		b = 110;
		break;
	case 1:
		r = 255;
		g = 170;
		b = 95;
		break;
	case 2:
		r = 245;
		g = 250;
		b = 165;
		break;
	case 3:
		r = 155;
		g = 250;
		b = 145;
		break;
	case 4:
		r = 175;
		g = 225;
		b = 245;
		break;
	}
}
void Grid::NextRow(void)
{
	++level;
	
	// move blocks down
	for (int i = n-1; i >= 0; i--)
	{
		if (blocks[i].GetLives() != 0)
		{
			blocks[i + wid].SetLives(blocks[i].GetLives());
			blocks[i + wid].SetMaxLevel(blocks[i].GetMaxLevel());
			blocks[i].SetLives(0);
		}
	}

	// determine powerup position
	int r = rand() % (wid-1);
	blocks[r].SetLives(-1);

	// fill row
	for (int i = 0; i < wid; i++)
	{
		if (blocks[i].GetLives() == 0)
		{
			int r, g, b;
			PickColor(r, g, b);

			// randomly decide whether empty space or block
			blocks[i].SetLives(rand() % 2);
		}
	}

	// determine levels
	for (int i = 0; i < wid; i++)
	{
		// level of new block is semi-random around difficulty
		double difficulty = 1.25 * (double)level;

		if (blocks[i].GetLives() > 0)
		{
			int lives = (rand() % 5) + (int)difficulty;
			blocks[i].SetLives(lives);
			blocks[i].SetMaxLevel((int)difficulty + 4);
		}
	}
}
void Grid::DrawBlocks()
{
	for (Block b : blocks)
	{
		if (b.GetLives() != 0)
		{
			b.DrawBlock();
		}
	}
}
bool Grid::GameOverCheck(void)
{
	for (int i = n-wid; i < n; i++)
	{
		if (blocks[i].GetLives() > 0)
		{
			return true;
		}
	}
	return false;
}
