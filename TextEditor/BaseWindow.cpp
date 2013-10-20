#include "stdafx.h"


BaseWindow::BaseWindow()
{
}

BaseWindow::~BaseWindow(void)
{
}

 LRESULT CALLBACK BaseWindow::_WndProc(HWND hwnd,
		UINT message,
		WPARAM wparam,
		LPARAM lparam)
{
	BaseWindow *wnd=0;
	if(message==WM_NCCREATE)
    {
      //�������� ��������� �� ��������� ������ ����, ������� �� �������� � ������� CreateWindowEx
      wnd=(BaseWindow*)LPCREATESTRUCT(lparam)->lpCreateParams;
      //� ��������� � ���� GWL_USERDATA
      SetWindowLong(hwnd,GWL_USERDATA,LONG(LPCREATESTRUCT(lparam)->lpCreateParams));
      wnd->_hwnd = hwnd;      
    }
    //������ �������� ��������� �� ��� ��������� ����, �� ��� �� ���� GWL_USERDATA
    wnd=(BaseWindow*)GetWindowLong(hwnd,GWL_USERDATA);
    if(wnd)
    {
      //���� ��������� � �����
      std::map<UINT,POINTER>::iterator it;
      it=wnd->_msgmap.find(message);

      //���� ��������� �� �������, �� ������������ ��� �� ���������
      if(it==wnd->_msgmap.end()) return DefWindowProc(hwnd,message,wparam,lparam);
      else
      {
        POINTER msg=it->second;        
        //�������� ������� ����������        
        LRESULT result=msg.func(msg.wnd,lparam,wparam);
        if(result) return result;
      }
    }
    return DefWindowProc(hwnd,message,wparam,lparam);
}


 bool BaseWindow::AddMessage(UINT message,FuncPointer pointer)
{
	if(!pointer) return false;

	POINTER msg;
	msg.wnd=this;
	msg.func=pointer;

	_msgmap.insert(std::pair<UINT,POINTER>(message,msg));
return true;
}
