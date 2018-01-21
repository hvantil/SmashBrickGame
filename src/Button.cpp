#include "Button.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

Button::Button()
{
	hei = 45;
	dyTxt = 5;
	isSelected = false;
}

void Button::SetParams(char txt[], int xIn, int yIn, 
	int wIn, int dxIn, int pgRefIn)
{
	int i = 0;
	while (txt[i] != 0)
	{
		text[i] = txt[i];
		++i;
	}
	text[i] = 0;

	x0 = xIn;
	y0 = yIn;
	wid = wIn;
	dxTxt = dxIn;
	pageRef = pgRefIn;
}
void Button::SetSelection(int mx, int my)
{
	if ((mx >= x0) && (mx <= x0 + wid) && (my >= y0 - hei) && (my <= y0))
	{
		isSelected = true;
	}
	else
	{
		isSelected = false;
	}
}
bool Button::GetSelection(void)
{
	return isSelected;
}
int Button::GetPageRef(void)
{
	return pageRef;
}

void Button::Draw()
{
	if (isSelected)
	{
		glColor3ub(255, 34, 34);
	}
	else
	{
		glColor3ub(255, 255, 255);
	}

	glRasterPos2i(x0 + dxTxt, y0 - dyTxt);
	YsGlDrawFontBitmap24x40(text);

	glBegin(GL_LINE_LOOP);
	glVertex2i(x0           , y0     );
	glVertex2i(x0 + wid     , y0     );
	glVertex2i(x0 + wid - 30, y0 - 18);
	glVertex2i(x0 + 30      , y0 - 18);
	glEnd();
}