#pragma once
#include "stdafx.h"

class Text
{
public:
	Text(void);
	~Text(void);
	int DeleteSymbol(int pos);
	int DeleteSymbol(int pos1, int pos2);
	int AddBitmap(HBITMAP bitmap, int pos);
	int AddChar(TCHAR chr, HFONT font, int pos);
	std::vector<ExtendedChar> data;
};

