#pragma once
#include "stdafx.h"
class AllWhatYouWantController;
class DrawingController: public BaseController
{
public:
	DrawingController(AllWhatYouWantController* contr);
	~DrawingController(void);
	int PaintAll();
	int PaintCaret();
private:
	int DrawBitmap(HBITMAP hBitmap);
	int DrawExtendedChar(ExtendedChar chr);
	int SetFont(ExtendedChar chr);
	int xcoord;
	int ycoord;
	int caretPosX;
	int caretPosY;
	int maxLineY;
	BOOL isSelected;
	HFONT currentFont;
	HDC hdc;
};
