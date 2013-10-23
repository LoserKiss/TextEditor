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
	int currentPositionToWrite;
	int mouseDownPosition;
	int mouseUpPosition;
	//����������� ����
	static LRESULT OnPaint(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnDestroy(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnCharPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnMenuCommand(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnSizeMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseDown(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseUp(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	//����������� ����
	 int SaveFile();
	 int OpenFile();
private:
	  int CalculatePosition(int x, int y);
};

