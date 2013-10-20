#pragma once
#include "stdafx.h"
class TextEditorWindow :
	public BaseWindow
{

public:

	TextEditorWindow(void);
	~TextEditorWindow(void);	
	bool Create(
	HINSTANCE hInstance,
    HWND parent,//������������ ����, ���� 0 - �� ������� ����
    LPCWSTR text,//��������� ����
	LPCWSTR className,
    DWORD style, DWORD exStyle,//����� ����
    int x,int y,int w,int h//������� � ���������
    );
protected:	
	Text *text;
	POINT *caretLocation;
	//����������� ����
	static LRESULT OnPaint(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnDestroy(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnCharPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnMenuCommand(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnSizeMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	//����������� ����
	 int SaveFile();
	 int OpenFile();
};

