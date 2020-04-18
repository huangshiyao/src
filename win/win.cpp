#include <windows.h>
#include "resource.h"


/* 窗口类处理函数 */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps);
		TCHAR sz[] = TEXT("我是老K，你想跟我玩吗？");
		TextOut(hDC, 10, 10, sz, lstrlen(sz));
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);       /* 向消息队列发出WM_QUIT消息 */
		break;
	default:                      /* 不感兴趣的消息交给DefWindowProc()处理 */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

/* 入口函数 */
int WINAPI WinMain(
	HINSTANCE hInstance,      /* 实例句柄 */
	HINSTANCE hPrevInstance,  /* 先前的实例, Win32下始终为NULL */
	LPSTR lpCmdLine,          /* 命令行参数 */
	int nCmdShow)             /* 窗口显示命令参数 */
{
	WNDCLASS winc;   /* 窗口类结构体 */
	HWND hwnd0;      /* 窗口句柄 */
	MSG messages;    /* 消息结构变量 */

	/* 设置窗口类结构体 */
	winc.hInstance = hInstance;
	winc.lpszClassName = TEXT("WindowsApp");                       /* 设置窗口类名称 */
	winc.lpfnWndProc = WindowProcedure;                            /* 设置窗口类处理函数 */
	winc.style = CS_DBLCLKS;                                       /* 窗口类样式 */
	//winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);                /* 设置默认图标 */
	winc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));  /* 设置图标 */
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);                    /* 设置默认光标 */
	winc.lpszMenuName = NULL;                                      /* 菜单 */
	winc.cbClsExtra = 0;                                           /* 窗口类额外数据字节数 */
	winc.cbWndExtra = 0;                                           /* 窗口额外数据字节数 */
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);      /* 窗口默认背景 */

	/* 注册窗口类 */
	if (!RegisterClass(&winc))
		return 0;

	/* 创建窗口 */
	hwnd0 = CreateWindow(
		winc.lpszClassName,           /* 类名 */
		TEXT("win32api test"),        /* 标题文本 */
		WS_OVERLAPPEDWINDOW,          /* 窗口样式 */
		CW_USEDEFAULT,                /* X坐标 */
		CW_USEDEFAULT,                /* Y坐标 */
		//CW_USEDEFAULT,                /* 宽度px */
		//CW_USEDEFAULT,                /* 高度px */
		300,                          /* 宽度px */
		100,                          /* 高度px */
		HWND_DESKTOP,                 /* 父窗口句柄 */
		NULL,                         /* 菜单 */
		hInstance,                    /* 程序实例句柄 */
		NULL);                        /* 窗口创建参数 */

	/* 按照参数显示窗口 */
	ShowWindow(hwnd0, nCmdShow);

	/* 进入消息循环,直到GetMessage()返回0. 即WM_QUIT消息发出 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* 翻译虚拟键消息成字符消息 */
		TranslateMessage(&messages);
		/* 发送消息给窗口过程 */
		DispatchMessage(&messages);
	}

	return (int)messages.wParam;
}