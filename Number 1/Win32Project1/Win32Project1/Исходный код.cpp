#include <windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>
#include <tchar.h>
#include <math.h>

#define ID_Tg 1
#define ID_Ctg 2
#define ID_Clear 3
#define ID_Edit 4
#define ID_LIST 5

#define PI 3.14


HWND hWnd;

LRESULT CALLBACK message_proc(HWND,UINT,UINT,LONG);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND tg,ctg,term1,clear,list;
	WNDCLASS WndClass;
	MSG Msg;
	char szClassName[] ="Calculate";
	WndClass.style=CS_HREDRAW|CS_VREDRAW;// Регистрация класса окна
	WndClass.lpfnWndProc=message_proc;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hInstance=hInstance;
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName=NULL;
	WndClass.lpszClassName = szClassName;

	if (!RegisterClass(&WndClass))// Вывод ошибки в случае неудачной регистрации класса
	{
		MessageBox(NULL,"Cannot register class","Error",MB_OK);
		return 0;
	}
	hWnd=CreateWindow(szClassName,"Calculate",WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,600,300,NULL,NULL,hInstance,NULL);
	term1=CreateWindow("Edit","", WS_VISIBLE | WS_CHILD | WS_DLGFRAME, 175, 30, 50, 20, hWnd, (HMENU)ID_Edit, hInstance, NULL);
	tg=CreateWindow("Button","tg", WS_VISIBLE | WS_CHILD, 100, 60, 100, 30, hWnd,(HMENU)ID_Tg,hInstance,NULL);
	ctg=CreateWindow("Button","ctg", WS_VISIBLE | WS_CHILD, 250, 60, 100, 30, hWnd,(HMENU)ID_Ctg,hInstance,NULL);
	clear=CreateWindow("Button","Clear", WS_VISIBLE | WS_CHILD, 400,60, 100, 30, hWnd,(HMENU)ID_Clear,hInstance,NULL);
	list=CreateWindow("Listbox", NULL, WS_VISIBLE | WS_CHILD | WS_DLGFRAME, 100, 100, 400, 150, hWnd, (HMENU)ID_LIST, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	ShowWindow(term1,nCmdShow);
	ShowWindow(tg,nCmdShow);
	ShowWindow(ctg,nCmdShow);
	ShowWindow(clear,nCmdShow);
	UpdateWindow(term1);
	UpdateWindow(hWnd);
	UpdateWindow(tg);
	UpdateWindow(ctg);
	UpdateWindow(clear);
	while(GetMessage(&Msg,NULL,0,0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK message_proc(HWND hWnd,UINT Message, UINT wParam, LONG lParam)
{
	HDC hDC;
	int length;
	PAINTSTRUCT PaintStruct;
	char *buf;
	char *result;
	float answ, x;
	switch(Message)
	{
	case WM_PAINT:
		hDC=BeginPaint(hWnd,&PaintStruct);
		TextOut(hDC,100,10,"Graduso vvedite, da?",16);
		TextOut(hDC,100,30,"Vot suda->",10);
		EndPaint(hWnd,&PaintStruct);
		return S_OK;
	case WM_COMMAND:// Построение графика при нажатии на кнопку и очистка рабочей области
		hDC=GetDC(hWnd);
		switch(LOWORD(wParam))
		{
		case ID_Tg:
			if(HIWORD(wParam)==BN_CLICKED)
			{
				length=GetWindowTextLength(GetDlgItem(hWnd,ID_Edit));
				buf=(char*)malloc((length+1)*sizeof(char));	
				GetDlgItemText(hWnd,ID_Edit,buf,length+1);
				x=atof(buf);
				answ = tan(x*PI/180); 
				result=_gcvt(answ,3,buf);
				SendDlgItemMessage(hWnd,ID_LIST,LB_ADDSTRING,NULL,(LPARAM)result);
			}
			ReleaseDC(hWnd,hDC);
			break;
		case ID_Ctg:
			if(HIWORD(wParam)==BN_CLICKED)
			{
				length=GetWindowTextLength(GetDlgItem(hWnd,ID_Edit));		
				buf=(char*)malloc((length+1)*sizeof(char));
				GetDlgItemText(hWnd,ID_Edit,buf,length+1);
				x=atof(buf);
				answ = 1 / tan(x*PI/180);\
				result= _gcvt(answ, 3, buf);
				SendDlgItemMessage(hWnd,ID_LIST,LB_ADDSTRING,NULL,(LPARAM)result);
			}
			break;
		case ID_Clear:
			if(HIWORD(wParam)==BN_CLICKED)
			{
				SendDlgItemMessage(hWnd,ID_LIST,LB_RESETCONTENT,0,0);
			}
		}
		break;
	case WM_DESTROY:// Закрываем окно
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,Message,wParam,lParam);
}
