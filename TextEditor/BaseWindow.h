#pragma once
#include "stdafx.h"
#include <map>
#include <iostream>
#include "TextEditor.h"

class BaseWindow
{
public:
	typedef LRESULT (*FuncPointer)(BaseWindow*, LPARAM,WPARAM); 
	struct POINTER
	{
	BaseWindow* wnd;//��������� �� �����, �������� ����������� ����������
	FuncPointer func;
	};
	BaseWindow();
	~BaseWindow(void);


	  virtual bool Create(
	HINSTANCE hInstance,
    HWND parent,//������������ ����, ���� 0 - �� ������� ����
    LPCWSTR text,//��������� ����
	LPCWSTR className,
    DWORD style, DWORD exStyle,//����� ����
    int x,int y,int w,int h//������� � ���������
    ) = 0;

	 public:
		 static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,	LPARAM lparam);

		 bool AddMessage(UINT message,FuncPointer pointer);
			
  HWND _hwnd;//����� ������ ����
  std::map<UINT,POINTER> _msgmap;//����� ���������
};

