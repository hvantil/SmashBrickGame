#ifndef BUTTON_H_IS_INCLUDED
#define BUTTON_H_IS_INCLUDED

class Button
{
private:
	int x0, y0, wid, hei, dxTxt, dyTxt, pageRef;
	char text[255];
	bool isSelected;
public:
	Button();

	void SetParams(char txt[], int xIn, int yIn, 
		int wIn, int dxIn, int pgRefIn);
	void SetSelection(int mx, int my);
	bool GetSelection(void);
	int GetPageRef(void);

	void Draw();
};

#endif