#include "Page.h"
#include "Menu.h"

void Page::SetDrawFxn(void(*fxn)(Menu &))
{
	drawFxn = fxn;
}
int Page::GetIdx(void)
{
	int idx = 0;
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i].GetSelection())
		{
			idx = i + 1;
		}
	}
	return idx;
}
int Page::GetPageRef(int clickIdx)
{
	return buttons[clickIdx - 1].GetPageRef();
}

void Page::AddButton(Button b)
{
	buttons.push_back(b);
}
void Page::UpdateSelection(int mx, int my)
{
	for (Button &b : buttons)
	{
		b.SetSelection(mx, my);
	}
}

void Page::Draw(Menu &menu)
{
	for (Button b : buttons)
	{
		b.Draw();
	}
	drawFxn(menu);
}