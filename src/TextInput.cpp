#include "TextInput.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <time.h>

bool IsAlpha(char ch)
{
	return ((ch == 'a') ||
		(ch == 'b') ||
		(ch == 'c') ||
		(ch == 'd') ||
		(ch == 'e') ||
		(ch == 'f') ||
		(ch == 'g') ||
		(ch == 'h') ||
		(ch == 'i') ||
		(ch == 'j') ||
		(ch == 'k') ||
		(ch == 'l') ||
		(ch == 'm') ||
		(ch == 'n') ||
		(ch == 'o') ||
		(ch == 'p') ||
		(ch == 'q') ||
		(ch == 'r') ||
		(ch == 's') ||
		(ch == 't') ||
		(ch == 'u') ||
		(ch == 'v') ||
		(ch == 'w') ||
		(ch == 'x') ||
		(ch == 'y') ||
		(ch == 'z'));
}
char ForceUppercase(char ch)
{
	if (ch == 'a') return 'A';
	if (ch == 'b') return 'B';
	if (ch == 'c') return 'C';
	if (ch == 'd') return 'D';
	if (ch == 'e') return 'E';
	if (ch == 'f') return 'F';
	if (ch == 'g') return 'G';
	if (ch == 'h') return 'H';
	if (ch == 'i') return 'I';
	if (ch == 'j') return 'J';
	if (ch == 'k') return 'K';
	if (ch == 'l') return 'L';
	if (ch == 'm') return 'M';
	if (ch == 'n') return 'N';
	if (ch == 'o') return 'O';
	if (ch == 'p') return 'P';
	if (ch == 'q') return 'Q';
	if (ch == 'r') return 'R';
	if (ch == 's') return 'S';
	if (ch == 't') return 'T';
	if (ch == 'u') return 'U';
	if (ch == 'v') return 'V';
	if (ch == 'w') return 'W';
	if (ch == 'x') return 'X';
	if (ch == 'y') return 'Y';
	if (ch == 'z') return 'Z';
}

void TextInput::Clear(void)
{
	name[0] = ' ';
	name[1] = ' ';
	name[2] = ' ';
	name[3] = 0;
	idx = 0;
}

char *TextInput::GetName(void)
{
	if (name != nullptr)
	{
		return name;
	}
	return nullptr;
}
void TextInput::GetInput(int key)
{
	if (FSKEY_BS == key)
	{
		if ((idx >= 1) && (idx <= 3))
		{
			name[idx - 1] = ' ';
			--idx;
		}
	}

	auto ch = FsInkeyChar();
	if (ch != 0)
	{
		if (IsAlpha(ch) && (idx >= 0) && (idx <= 2))
		{
			name[idx] = ForceUppercase(ch);
			++idx;
		}
	}
}

bool TextInput::CheckName(void)
{
	bool isGoodName = true;
	for (int i = 0; i < 3; ++i)
	{
		if (name[i] == ' ')
		{
			isGoodName = false;
		}
	}
	return isGoodName;
}
void TextInput::Draw(int x0, int y0)
{
	glRasterPos2i(x0, y0);
	YsGlDrawFontBitmap16x24(name);

	if ((idx >= 0) && (idx <= 2))
	{
		glRasterPos2i(x0 + (idx * 16), y0);
		switch (time(NULL) % 2)
		{
		case 0:
			YsGlDrawFontBitmap16x24("_");
			break;
		case 1:
			YsGlDrawFontBitmap16x24(" ");
			break;
		}
	}
}
