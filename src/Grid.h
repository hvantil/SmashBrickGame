#ifndef GRID_H_IS_INCLUDED
#define GRID_H_IS_INCLUDED

#include <vector>
#include "Blocks.h"

using namespace std;

class Grid
{
private:
	int level, wid, hei, n; 
	vector<Block> blocks;
public:
	void Setup(int wIn, int hIn);
	void CleanUp(void);

	int GetLevel();
	Block GetBlock(int idx);
	int GetN(void);
	void SetLevel(int levelIn);
	void SetBlock(int idx, Block blockIn);

	void PickColor(int &r, int &g, int &b);
	void NextRow(void);
	void DrawBlocks(void); 
	bool GameOverCheck(void); 
};

#endif