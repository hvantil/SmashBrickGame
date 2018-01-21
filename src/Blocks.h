#ifndef BLOCKS_H_IS_INCLUDED
#define BLOCKS_H_IS_INCLUDED

class Block {
private:
	int lives, maxLevel;
	int x, y, wid, hei;
	double r, g, b;
public:	
	Block();

	int GetLives(void);
	void GetXY(int &xOut, int &yOut);
	void GetSize(int &wOut, int &hOut);
	void GetColor(int &rOut, int &gOut, int &bOut);
	int GetMaxLevel(void);
	void SetLives(int livesIn);
	void SetMaxLevel(int levelIn);
	void SetXY(int xIn, int yIn);
	void SetSize(int wIn, int hIn);
	void SetColor(void);

	void DrawBlock(void);
};

#endif

