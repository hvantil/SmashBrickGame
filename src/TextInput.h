#ifndef TEXTINPUT_H_IS_INCLUDED
#define TEXTINPUT_H_IS_INCLUDED

class TextInput
{
protected:
	char name[4];
	int idx;
public:
	void Clear(void);

	char *GetName(void);
	void GetInput(int key);

	bool CheckName(void);
	void Draw(int x0, int y0);
};

#endif
