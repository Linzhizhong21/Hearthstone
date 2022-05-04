#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include <conio.h>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include<windows.h>
#include<dos.h>
#pragma comment(lib,"Winmm.lib")

void gotoxy(int x, int y)        //清屏函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()        //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

class Uilts {
public:
	void showStr(int x, int y, char* str) {
		int len = strlen(str);
		for (int i = x; i < len; i++)
			outtextxy(i, y, str[i]);
	}
};

class Icon {
private:
	IMAGE image;
	int x, y;
	bool isFocused = 0;
public:
	Icon(int x,int y,LPCTSTR url):x(x),y(y)
	{
		loadimage(&image, url);
	}
	void display()
	{
		putimage(x, y, &image);
	}

	bool isClickedByMouse(int x, int y) 
	{
		return 
			(
			x >= this->x && x <= this->x + image.getwidth() &&
			y >= this->y && y <= this->y + image.getheight()
			);
	}

	void moveTo(int mouse_x, int mouse_y)
	{
		this->x = x;
		this->y = y;
	}

	void changeImage();

	void mouseListener(ExMessage& mouse) {
		if (mouse.message == WM_LBUTTONDOWN && isClickedByMouse(mouse.x, mouse.y)) {
			isFocused = 1;
		}
		else {
			isFocused = 0;
		}
	}
};

class IconGroup 
{
private:
	std::vector<Icon>iconVector;
public:
	void addIcon(Icon icon) 
	{
		iconVector.push_back(icon);
	}
	void display() 
	{
		for (auto it = iconVector.begin(); it != iconVector.end(); it++) 
			(*it).display();
	}
	void mouseListener(ExMessage& mouse) 
	{
		for (auto it = iconVector.begin(); it != iconVector.end(); it++) 
		{
			(*it).mouseListener(mouse);
		}
	}


};

class Attendant 
{
private:
public:
};

class Game {
private:
	static IconGroup attendantIcons;
	void static init() 
	{
		initgraph(900, 677);

		mciSendString(L"open D:\\编程\\炉石传说1\\炉石传说1\\music\\background.mp3 alias bkmusic", NULL, 0, NULL);        //播放音乐
		mciSendString(L"play bkmusic repeat", NULL, 0, NULL);        //循环播放音乐

		Icon background = Icon(0,0,__T("Image\\background.png"));

		Icon n1 = Icon(406, 193, __T("Image\\member1.png"));

		attendantIcons.addIcon(background);
		attendantIcons.addIcon(n1);
		BeginBatchDraw();
	}
public:
	void static start() 
	{
		init();
		while (1) 
		{
			show();
			updatewithinput();
			updatewithoutinput();
		}
		gameover();
	}
	void static show();
	void static updatewithinput();
	void static updatewithoutinput();
	void static gameover();
};

void Game::show()
{
	attendantIcons.display();
	FlushBatchDraw();
}

void Game::updatewithinput() 
{
	while (MouseHit) 
	{
		ExMessage mouse = getmessage(EM_MOUSE);
		//attendantIcons.mouseListener(mouse);
		if (mouse.message == WM_LBUTTONDOWN)         //判断是否有鼠标左键
		{
			char buf[20];
			sprintf_s(buf, "x=%d,y=%d", mouse.x, mouse.y);
			outtextxy(5, 5, L"12345");
			_getch();
		}
	}
}

void Game::updatewithoutinput() 
{
}

void Game::gameover() 
{
	EndBatchDraw();
	_getch();
	closegraph();
}

IconGroup Game::attendantIcons = IconGroup();

int main()
{
	Game::start();
	return 0;
}