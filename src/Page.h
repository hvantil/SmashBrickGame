#ifndef PAGE_H_IS_INCLUDED
#define PAGE_H_IS_INCLUDED

#include "Button.h"
#include "Menu.h"
#include <vector>
using namespace std;

class Menu;

class Page
{
protected:
	vector<Button> buttons;
	void(*drawFxn)(Menu &);
public:
	void SetDrawFxn(void(*fxn)(Menu &));
	int GetIdx(void);
	int GetPageRef(int clickIdx);

	void AddButton(Button b);
	void UpdateSelection(int mx, int my);
	
	void Draw(Menu &menu);
};

#endif