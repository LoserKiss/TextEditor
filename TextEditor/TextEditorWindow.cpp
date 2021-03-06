#pragma once
#include "stdafx.h"

#define ID_NEW 0
#define ID_OPEN 1
#define ID_SAVE 2
#define ID_EXIT 3
#define ID_ABOUT 4
#define ID_CHANGE 5
#define ID_IMAGE 6
TextEditorWindow::TextEditorWindow(void)
{
	controller = new AllWhatYouWantController(this);
	AddMessage(WM_PAINT, &TextEditorWindow::OnPaint);
	AddMessage(WM_CHAR, &TextEditorWindow::OnCharPress);
	AddMessage(WM_KEYDOWN, &TextEditorWindow::OnKeyPress);////!!!
	AddMessage(WM_DESTROY, &TextEditorWindow::OnDestroy);
	AddMessage(WM_COMMAND, &TextEditorWindow::OnMenuCommand);
	AddMessage(WM_SIZE, &TextEditorWindow::OnSizeMove);
	AddMessage(WM_LBUTTONDOWN, &TextEditorWindow::OnMouseDown);
	AddMessage(WM_LBUTTONUP, &TextEditorWindow::OnMouseUp);
	AddMessage(WM_MOUSEMOVE, &TextEditorWindow::OnMouseMove);
	AddMessage(WM_SETFOCUS, &TextEditorWindow::OnSetFocus);
	AddMessage(WM_KILLFOCUS, &TextEditorWindow::OnKillFocus);
	AddMessage(WM_LBUTTONDBLCLK, &TextEditorWindow::OnMouseDoubleClick);
	AddMessage(WM_MOUSEWHEEL, &TextEditorWindow::OnMouseWheel);
}
TextEditorWindow::~TextEditorWindow(void)
{
}
//��������
bool  TextEditorWindow::Create(
	HINSTANCE hInstance,
    HWND parent,//������������ ����, ���� 0 - �� ������� ����
    LPCWSTR text,//��������� ����
	LPCWSTR className,
    DWORD style, DWORD exStyle,//����� ����
    int x,int y,int w,int h//������� � ���������
    )
{
	const int MAX_LOADSTRING = 100;			

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.lpfnWndProc=WNDPROC(_WndProc);//������� ���������
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEXTEDITOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;//MAKEINTRESOURCE(IDC_TEXTEDITOR);
	wcex.lpszClassName	= className;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
	_hwnd = CreateWindowEx(exStyle, className, text, style,
      x,y,w,h, parent, NULL, hInstance, this);
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	//---
	HMENU hMainMenu = CreateMenu();
	HMENU hPopMenu = CreatePopupMenu();
	HMENU hChangeMenu = CreatePopupMenu();
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenu, L"����"); 
	AppendMenu(hMainMenu, MF_STRING  | MF_POPUP, (UINT)hChangeMenu, L"��������");
    AppendMenu(hMainMenu, MF_STRING, ID_ABOUT, L"������");
	AppendMenu(hPopMenu, MF_STRING, ID_NEW, L"�����");
	AppendMenu(hPopMenu, MF_STRING, ID_OPEN, L"�������");
	AppendMenu(hPopMenu, MF_STRING, ID_SAVE, L"���������");
	AppendMenu(hPopMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hPopMenu, MF_STRING, ID_EXIT, L"�����");
	AppendMenu(hChangeMenu,MF_STRING, ID_CHANGE, L"�����");
	AppendMenu(hChangeMenu, MF_STRING, ID_IMAGE, L"��������� ��������");
	SetMenu(_hwnd, hMainMenu);
	InvalidateRect(_hwnd,NULL,TRUE);
	if(!_hwnd) return false;
    return true;
}
//�����������
LRESULT TextEditorWindow::OnPaint(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->drawingcontrol->PaintAll();
	return 1;
}
LRESULT TextEditorWindow::OnCharPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CharPress(lparam, wparam);
	return 1;
}
LRESULT TextEditorWindow::OnKeyPress(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->KeyPress(lparam, wparam);
	return 1;
}
LRESULT TextEditorWindow::OnDestroy(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	PostQuitMessage(0);
	return 0;
}
LRESULT TextEditorWindow::OnMenuCommand(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	switch (LOWORD(wparam))
	{
		case ID_SAVE:
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->fileman->SaveFile();
			break;

		case ID_EXIT:
			DestroyWindow(wnd -> _hwnd);
			break;

		case ID_OPEN:
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->fileman->LoadFile();
			break;

		case ID_NEW:
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->fileman->NewFile();
			break;

		case ID_CHANGE:
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->ChangeFont();
			break;

		case ID_ABOUT:
			MessageBox(wnd -> _hwnd, L"Magic people vodoo people!",L"About", NULL);
			break;
		case ID_IMAGE:
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->fileman->LoadMyImage();
			InvalidateRect(wnd->_hwnd, NULL, TRUE);
			break;
	}
	return 0;
}
LRESULT TextEditorWindow::OnSizeMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	return 1;
}
LRESULT TextEditorWindow::OnMouseDown(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	int positionpressed = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
	if (positionpressed >= min(reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->firstSelectPosition,
		 reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->secondSelectPosition)
		&&
		positionpressed < max(reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->firstSelectPosition,
		 reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->secondSelectPosition))
	{
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isMoveSelected = true;
	}
	else
	{
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->Select(positionpressed, positionpressed);
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect = true;
	}
	return 1;
}
LRESULT TextEditorWindow::OnMouseMove(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	if (reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect)
	{
		int positionpressed = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->Select( -1 , positionpressed);
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000 ))
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect = false;
	}
	else
		if (reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isMoveSelected)
		{
			//int positionpressed = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			//reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->currentPositionToWrite = positionpressed;
		}
	return 1;
}
LRESULT TextEditorWindow::OnMouseUp(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	if (reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect)
	{
		int positionpressed = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->Select( -1 , positionpressed);
		reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect = false;
	}
	else
		if(reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isMoveSelected)
		{
			int positionpressed = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->MoveSelected(positionpressed);
		}
	return 1;
}
LRESULT TextEditorWindow::OnSetFocus(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->SetFocus();
	return 1;
}
LRESULT TextEditorWindow::OnKillFocus(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	DestroyCaret();
	return 1;
}
LRESULT TextEditorWindow::OnMouseDoubleClick(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	int position = reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->CalculatePosition(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isStartedSelect = false;
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->isMoveSelected = false;
	reinterpret_cast<TextEditorWindow*>(wnd)->controller->actioncontrol->SelectWord(position);
	return 1;
}
LRESULT TextEditorWindow::OnMouseWheel(BaseWindow* wnd,LPARAM lparam,WPARAM wparam)
{
	if (GET_KEYSTATE_WPARAM(wparam) == MK_CONTROL)
	{
		if (GET_WHEEL_DELTA_WPARAM(wparam) > 0 )
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->scalingcontrol->IncreaseScale();
		else
			reinterpret_cast<TextEditorWindow*>(wnd)->controller->scalingcontrol->DecreaseScale();
	}
	return 1;
}