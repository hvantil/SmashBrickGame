#ifndef BALL_H_IS_INCLUDED
#define BALL_H_IS_INCLUDED

class Ball
{
private:
	double x, y, vx, vy, rad;
	int r, g, b;
	bool isActive;
public:
	Ball(double xIn, double yIn, double radIn);

	void GetPosition(double &xOut, double &yOut);
	void GetVelocity(double &vxOut, double &vyOut);
	double GetRad(void);
	bool IsActive(void);
	void SetPosition(double xIn, double yIn);
	void SetVelocity(double vxIn, double vyIn);
	void SetActivity(bool activity);

	void Move(double dt);
	void BounceWalls(double wid, double hei, double x0, double y0);
	bool BounceBlock(double bX1, double bX2, double bY1, double bY2, int &bLives);
	void Draw(void);
};

#endif
