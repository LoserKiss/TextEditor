#pragma once
#include "stdafx.h"
class AllWhatYouWantController;
class TextEditorWindow :
	public BaseWindow
{
public:
	TextEditorWindow(void);
	~TextEditorWindow(void);	
	/////
	bool Create(
	HINSTANCE hInstance,
    HWND parent,//������������ ����, ���� 0 - �� ������� ����
    LPCWSTR text,//��������� ����
	LPCWSTR className,
    DWORD style, DWORD exStyle,//����� ����
    int x,int y,int w,int h//������� � ���������
    );
	/////
protected:
	AllWhatYouWantController* controller;
	//����������� ����
	static LRESULT OnPaint(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnDestroy(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnCharPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnKeyPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnMenuCommand(BaseWindow* wnd,LPARAM lparam,WPARAM wparam);
	static LRESULT OnSizeMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseDown(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseUp(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnSetFocus(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnKillFocus(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseDoubleClick(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	static LRESULT OnMouseWheel(BaseWindow* wnd,LPARAM lparam,WPARAM wparam); 
	//����������� ����
};

