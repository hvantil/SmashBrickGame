#ifndef SHOOTER_H_IS_INCLUDED
#define SHOOTER_H_IS_INCLUDED

#include <vector>
#include "Ball.h"
#include "Grid.h"

using namespace std;

class Shooter
{
private:
	double windowWid, windowHei, xShoot, yShoot;
	double vMag, dt, ballRad, vxInit, vyInit;
	bool isRunning;
	int spacing, spacingCounter, powerupCounter;
	vector<Ball> balls;
public:
	void Setup(void);
	void CleanUp(void);

	bool IsRunning(void);

	void Shoot(Grid &grid, int mx, int my);
	void Move(Grid &grid, bool &isEndOfTurn);
	bool Bounce(Ball &ball, Grid &grid);
	void Draw(int mx, int my);
};

#endif