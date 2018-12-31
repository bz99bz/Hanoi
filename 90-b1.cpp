/*1751151 计1 郭思远*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstdio>
#include<windows.h>
#include<iomanip>
#include <conio.h>
#include<cmath>
#include "cmd_console_tools.h"
using namespace std;
void CD();//菜单
int get_int(char *prompt, int min_value, int max_value, char *p1, char *p2);//输入
void hengchushihua();//横式初始化
void shuchushihua();//竖式初始化
void CSHzhuzi();//初始化图形柱子
void CSHpanzi(int n, char qsz);//初始化盘子图形
void DG(int n, char one, char two, char three, int sleep, int choice, int t);//递归函数
int hanoidg(char from, char to, int sleep, int n, int choice, int t);//内部数组
void go(char from, char to, int h, int num, int choice);//横向输出
void shu();//纵向输出
void move(int n, char qsz, char mbz, int h, int choice);//移动
void game(int n, char qsz, char mbz, int choice);//游戏版
void setcursor(const HANDLE hout, const int options);
#define N 10
int a[N], b[N], c[N];
int atop = 0, btop = 0, ctop = 0;

int main()
{
	CD();
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hout, 0, 20);
	return 0;
}

int get_int(char *prompt, int min_value, int max_value, char *p1, char *p2)//输入
{
	const int BASE_X = 10;
	const int BASE_Y = 28;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char a[3];
	int value1;
	char value2;
	if (min_value == 'a')
	{

		while (1)
		{
			gotoxy(hout, BASE_X, BASE_Y + 14);
			cout << "                                                                                   " << endl;
			gotoxy(hout, BASE_X, BASE_Y + 14);
			cout << prompt;
			cin >> a;
			if (a[0] >= 'a'&&a[0] <= 'z'&&a[1] >= 'a'&&a[1] <= 'z')
			{
				a[0] = a[0] - 32;
				a[1] = a[1] - 32;
			}
			if ((a[0] >= 'A'&&a[0] <= 'C'&&a[1] >= 'A'&&a[1] <= 'C' && (a[0] != a[1])) || (a[0] == 'Q'))
			{
				*p1 = a[0];
				*p2 = a[1];
				break;
			}
		}
		return 0;
	}
	if (min_value == 'A')
	{
		while (1)
		{
			cout << prompt << "(" << (char)min_value << "-" << (char)max_value << ")" << endl;
			cin >> value2;
			if (value2 == 'a' || value2 == 'b' || value2 == 'c')
			{
				value2 = value2 - 32;
				break;
			}
			else if (value2 == 'A' || value2 == 'B' || value2 == 'C')
				break;
		}
		return value2;
	}
	else
	{
		while (1)
		{
			if (max_value == 9)
			{
				gotoxy(hout, 0, 13);
				cout << "                            ";
				gotoxy(hout, 0, 13);
				cout << prompt;
			}
			else
			{
				cout << prompt << endl;
			}
			cin >> value1;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				continue;
			}
			if (value1 >= min_value&&value1 <= max_value)
				break;
		}
		return value1;
	}

}
void CSHzhuzi()//初始化图形柱子
{
	int i, j;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	const int BASE_X = 10;
	const int BASE_Y = 28;
	const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
	const int fg_color = COLOR_WHITE;
	const char ch = ' ';        //字符为空格(注意：如果是空格，则前景色无法显示)
	for (i = 0; i < 3; i++)
	{
		showch(hout, BASE_X + i * 36, BASE_Y, ch, bg_color, fg_color, 26);
		showch(hout, (BASE_X + 26) + 36 * i, BASE_Y, ch, COLOR_BLACK, fg_color, 10);
	}
	for (j = 0; j < 15; j++)
	{
		showch(hout, BASE_X + 13, BASE_Y - j, ch, bg_color, fg_color, 1);
		showch(hout, BASE_X + 13 + 1 * 36, BASE_Y - j, ch, bg_color, fg_color, 1);
		showch(hout, BASE_X + 13 + 2 * 36, BASE_Y - j, ch, bg_color, fg_color, 1);
		Sleep(100);
	}
	showch(hout, 100, BASE_Y + 100, ' ', COLOR_BLACK, COLOR_WHITE, 1);
}
void CD()
{
	int num = 1;
	int choice;
	char gsy;
	cout << "----------------------------" << endl;
	cout << "1、基本解" << endl;
	cout << "2、基本解(步数记录)" << endl;
	cout << "3、内部数组显示（横向）" << endl;
	cout << "4、内部数组显示（纵向+横向）" << endl;
	cout << "5、图形解—预备—画三个圆柱" << endl;
	cout << "6、图形解—预备—在起始柱上画n个盘子" << endl;
	cout << "7、图形解—预备—第一次移动" << endl;
	cout << "8、图形解—自动移动版本" << endl;
	cout << "9、图形解—游戏版" << endl;
	cout << "0、退出" << endl;
	cout << "----------------------------" << endl;
	choice = get_int("请选择[0-9]", 0, 9, 0, 0);
	if (choice != 0)
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		int n, i = 0;
		int sleep;
		char qsz, mbz, zjz;
		const int BASE_X = 10;
		const int BASE_Y = 40;
		if (choice != 5)
		{
			n = get_int("请输入塔的层数(1-10):", 1, 10, 0, 0);
			qsz = get_int("请输入起始柱", 'A', 'C', 0, 0);
			while (1)
			{
				mbz = get_int("请输入目标柱", 'A', 'C', 0, 0);
				if (mbz == qsz)
					continue;
				else
					break;
			}
			zjz = 'A' + 'B' + 'C' - mbz - qsz;

			if (qsz == 'A')
				atop = n;
			if (qsz == 'B')
				btop = n;
			if (qsz == 'C')
				ctop = n;

			for (i = 0; i < N; i++)//初始化
				a[i] = b[i] = c[i] = 0;

			for (i = 0; i < n; i++)//进栈
			{
				if (qsz == 'A')
					a[i] = n - i;
				else if (qsz == 'B')
					b[i] = n - i;
				else if (qsz == 'C')
					c[i] = n - i;
			}
		}
		if (choice == 4 || choice == 8)
		{
			sleep = get_int("请输入移动速度（0-5：0-按回车单步演示 1-延时最长 5-延时最短)", 0, 5, 0, 0);
		}
		setcursor(hout, CURSOR_INVISIBLE);
		setconsoleborder(hout, 120, 50);
		if (choice == 4 || choice == 8 || choice == 9)
			hengchushihua();
		if (choice == 4 || choice == 8 || choice == 9)
			shuchushihua();
		if (choice >= 5)
		{
			CSHzhuzi();
			if (choice == 5)
			{
				gotoxy(hout, 0,36 );
				cout << "按回车键继续" << endl;
				gsy = _getch();
				system("cls");
				CD();
			}
		}
		if (choice >= 6)
		{
			CSHpanzi(n, qsz);
			if (choice == 6)
			{
				gotoxy(hout, 0, 36);
				cout << "按回车键继续" << endl;
				gsy = _getch();
				system("cls");
				CD();
			}
		}
		if (choice == 7)
			move(n, qsz, mbz, 1, choice);
		if (choice != 9 && choice != 5 && choice != 6 && choice != 7)
		{
			if (choice == 4 || choice == 8)
				DG(n, qsz, zjz, mbz, sleep, choice, 1);
			else
				DG(n, qsz, zjz, mbz, 6, choice, 1);
			if (choice == 4 || choice == 8)
				DG(n, qsz, zjz, mbz, sleep, choice, 0);
			else
				DG(n, qsz, zjz, mbz, 6, choice, 0);
			if(choice==8||choice==4)
			    gotoxy(hout, 0, 45);
			cout << "按回车键继续" << endl;
			gsy = _getch();
			system("cls");
			CD();
		}
		if (choice == 9)
		{
			game(n, qsz, mbz, choice);
			gotoxy(hout, 0, 45);
			cout << "按回车键继续" << endl;
			gsy = _getch();
			system("cls");
			CD();
		}
	}
}
void CSHpanzi(int n, char qsz)//初始化盘子图形
{
	int i, j = 1;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	const int BASE_X = 10;
	const int BASE_Y = 28;
	const int fg_color = COLOR_WHITE;
	const char ch = ' ';        //字符为空格(注意：如果是空格，则前景色无法显示)
	for (i = 10; i >= 1; i--)
	{
		if (n == i)
		{
			showch(hout, BASE_X + (12 - n) + (qsz - 'A') * 36, BASE_Y - j, ch, 2 + i, fg_color, 25 - 2 * (11 - n));
			j++;
			n--;
		}
	}
	showch(hout, BASE_X, BASE_Y + 40, ' ', COLOR_BLACK, COLOR_WHITE, 1);
}
void move(int n, char qsz, char mbz, int h, int choice)//移动
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	const int BASE_X = 10;
	const int BASE_Y = 28;
	const int fg_color = COLOR_HBLUE;
	int y, x, luo, m;
	if (qsz == 'A')
		m = atop;
	if (qsz == 'B')
		m = btop;
	if (qsz == 'C')
		m = ctop;
	if (choice == 7)
	{
		/* 将第一个盘子从下向上移动 */
		for (y = 0; y < 19 - n; y++)
		{
			showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2, BASE_Y - n - y, ' ', 3, fg_color, 5);
			Sleep(100);
			if (y < 15 - n)
			{
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 4, BASE_Y - n - y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2, BASE_Y - n - y, ' ', COLOR_BLACK, COLOR_WHITE, 2);
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 5, BASE_Y - n - y, ' ', COLOR_BLACK, COLOR_WHITE, 2);
			}
			if (y >= 15 - n && y < 18 - n)
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2, BASE_Y - n - y, ' ', COLOR_BLACK, COLOR_WHITE, 5);
		}
		/* 将第一个盘子从当前柱子平移到另一根柱子 */
		for (x = 0; x < 37; x++)
		{
			if (qsz != 'B')
			{
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1), BASE_Y - n - y + 1, ' ', 3, fg_color, 5);

				Sleep(100);
				if (x < 36)
					showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1), BASE_Y - n - y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 5);
			}
			if (qsz == 'B')
			{
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz), BASE_Y - n - y + 1, ' ', 3, fg_color, 5);

				Sleep(100);
				if (x < 36)
					showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz), BASE_Y - n - y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 5);
			}
		}
		/* 将第一个盘子从当前柱子下落到另一根柱子 */
		for (luo = 0; luo < 18; luo++)
		{
			if (qsz != 'B')
			{
				showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1) + (qsz - 'A'), BASE_Y - n - y + 1 + luo, ' ', 3, fg_color, 5);
				Sleep(100);
				if (luo < 4)
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1) + (qsz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5);
				if (luo >= 4 && luo < 17)
				{
					showch(hout, BASE_X + 10 + 36 + 3, BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
					showch(hout, BASE_X + 10 + 36 + 4, BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2);
					showch(hout, BASE_X + 10 + 36 + 1, BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2);
				}
			}
			if (qsz == 'B')
			{
				showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*('A' - qsz) + 4, BASE_Y - n - y + 1 + luo, ' ', 3, fg_color, 5);
				Sleep(100);
				if (luo < 4)
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*('A' - qsz) + 4, BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5);
				if (luo >= 4 && luo < 17)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*('A' - qsz) + 4, BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*('A' - qsz) + 5, BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2);
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*('A' - qsz) + 2, BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2);
				}
			}
		}
	}
	if (choice == 8 || choice == 9)
	{
		/* 将盘子从下向上移动 */
		for (y = m; y < 19 - n; y++)
		{
			showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 - (h - 1), BASE_Y - y - 1, ' ', 3 + h - 1, fg_color, 5 + 2 * (h - 1));
			if (choice == 8)
				Sleep(100);
			if (y < 15 - n)
			{
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 4, BASE_Y - y - 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 - (h - 1), BASE_Y - y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 5, BASE_Y - y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
			}
			if (y >= 15 - n&& y < 19 - n)
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 - (h - 1), BASE_Y - y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
		}
		/* 将第一个盘子从当前柱子平移到另一根柱子 */
		for (x = 0; x < 37 * abs((int)(mbz - qsz)); x++)
		{
			if (qsz != 'B')
			{
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1), BASE_Y - n - y + 1, ' ', 3 + (h - 1), fg_color, 5 + 1 * (h - 1));
				if (choice == 8)
					Sleep(100);
				if (x < 37 * abs((int)(mbz - qsz)))
					showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*('A' - qsz + 1), BASE_Y - n - y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 1 * (h - 1));
			}
			if (qsz == 'B')
			{
				showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz), BASE_Y - n - y + 1, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
				if (choice == 8)
					Sleep(100);
				if (x < 37)
					showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz), BASE_Y - n - y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
			}
		}
		/* 将第一个盘子从当前柱子下落到另一根柱子 */



		if (qsz == 'A')
		{
			if (mbz == 'B')
			{
				for (luo = 0; luo < 18 - btop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 1 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 1 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - btop)
					{
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 2 + ('C' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 3 + ('C' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
			}
			else
			{
				for (luo = 0; luo < 18 - ctop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 1 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 1 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - ctop)
					{
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 2 + ('C' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 3 + ('C' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + ('C' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
			}
		}
		if (qsz == 'C')
		{
			if (mbz == 'A')
			{
				for (luo = 0; luo < 18 - atop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 5 + x*('A' - qsz + 1) - (h - 1) + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 5 + x*('A' - qsz + 1) - (h - 1) + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - atop)
					{
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 6 + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 7 + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 4 - (h - 1) + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
			}
			else
			{
				for (luo = 0; luo < 18 - btop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 5 + x*('A' - qsz + 1) + ('A' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 5 + x*('A' - qsz + 1) + ('A' - mbz) - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - btop)
					{
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 6 + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 7 + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 9 + (qsz - 'A') * 36 + x*('A' - qsz + 1) + 4 - (h - 1) + ('A' - mbz), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
			}
		}
		if (qsz == 'B')
		{
			if (mbz == 'A')
			{
				for (luo = 0; luo < 18 - atop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*(mbz - qsz) + 4 - (mbz - 'A') - (h - 1), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*(mbz - qsz) + 4 - (mbz - 'A') - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - atop)
					{
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 4 - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 5 - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 2 - (h - 1) - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
			}
			else
				for (luo = 0; luo < 18 - ctop + 1; luo++)
				{
					showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*(mbz - qsz) + 4 - (mbz - 'A') - (h - 1), BASE_Y - n - y + 1 + luo, ' ', 3 + (h - 1), fg_color, 5 + 2 * (h - 1));
					if (choice == 8)
						Sleep(100);
					if (luo < 4)
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + x*(mbz - qsz) + 4 - (mbz - 'A') - (h - 1), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 5 + 2 * (h - 1));
					if (luo >= 4 && luo < 18 - ctop)
					{
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 4 - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 5 - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
						showch(hout, BASE_X + 8 + (qsz - 'A') * 36 + 2 + x*(mbz - qsz) + 2 - (h - 1) - (mbz - 'A'), BASE_Y - n - y + 1 + luo, ' ', COLOR_BLACK, COLOR_WHITE, 2 + 1 * (h - 1));
					}
				}
		}

	}

	showch(hout, BASE_X, BASE_Y + 40, ' ', COLOR_BLACK, COLOR_WHITE, 1);
}
void hengchushihua()
{
	const int BASE_X = 10;
	const int BASE_Y = 40;
	int i, j;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	gotoxy(hout, BASE_X, BASE_Y + 2);
	cout << "初始:";//输出初始行
	cout << "A: ";
	for (i = 0, j = 0; i < N; i++)
	{
		if (a[i] == 0)
		{
			for (j; j < N - i; j++)
				cout << setw(2) << " ";
			break;
		}
		else
			cout << setw(1) << a[i] << " ";
	}
	cout << setiosflags(ios::right) << setw(2) << "B: ";
	for (i = 0, j = 0; i < N; i++)
	{
		if (b[i] == 0)
		{
			for (j; j < N - i; j++)
				cout << setw(2) << " ";
			break;
		}
		else
			cout << setw(1) << b[i] << " ";
	}
	cout << setiosflags(ios::right) << setw(2) << "C: ";
	for (i = 0; i < N; i++)
	{
		if (c[i] == 0)
		{
			for (j; j < N - i; j++)
				cout << setw(2) << " ";
			break;
		}
		else
			cout << setw(1) << c[i] << " ";
	}
	cout << endl;

}
void shuchushihua()
{
	const int BASE_X = 10;
	const int BASE_Y = 40;
	int y, k;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	gotoxy(hout, BASE_X, BASE_Y);
	cout << "A";
	gotoxy(hout, BASE_X + 1 * 10, BASE_Y);
	cout << "B";
	gotoxy(hout, BASE_X + 2 * 10, BASE_Y);
	cout << "C";
	gotoxy(hout, BASE_X - 10, BASE_Y - 1);
	cout << "===========================================" << endl;
	for (k = 0; k < N; k++)
	{
		gotoxy(hout, BASE_X, BASE_Y - k - 2);

		if (k >= 0 && k <= atop - 1)
			cout << a[k];
		if (k >= atop && k <= 10)
			cout << "  ";
	}
	for (k = 0; k < N; k++)
	{
		gotoxy(hout, BASE_X + 10, BASE_Y - k - 2);

		if (k >= 0 && k <= btop - 1)
			cout << b[k];
		if (k >= btop&& k <= 10)
			cout << "  ";
	}
	for (y = 19, k = 0; y > 9 && k < N; y--, k++)
	{
		gotoxy(hout, BASE_X + 20, BASE_Y - k - 2);

		if (k >= 0 && k <= ctop - 1)
			cout << c[k];
		if (k >= ctop && k <= 10)
			cout << "  ";
	}
}

void shu()//纵向输出
{
	const int BASE_X = 10;
	const int BASE_Y = 40;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	int y, k;

	for (k = 0; k < N; k++)
	{
		gotoxy(hout, BASE_X, BASE_Y - k - 2);

		if (k >= 0 && k <= atop - 1)
			cout << a[k];
		if (k >= atop && k <= 10)
			cout << "  ";
	}
	for (k = 0; k < N; k++)
	{
		gotoxy(hout, BASE_X + 10, BASE_Y - k - 2);

		if (k >= 0 && k <= btop - 1)
			cout << b[k];
		if (k >= btop&& k <= 10)
			cout << "  ";
	}
	for (y = 19, k = 0; y > 9 && k < N; y--, k++)
	{
		gotoxy(hout, BASE_X + 20, BASE_Y - k - 2);

		if (k >= 0 && k <= ctop - 1)
			cout << c[k];
		if (k >= ctop && k <= 10)
			cout << "  ";
	}

}
int hanoidg(char from, char to, int sleep, int n, int choice, int t)//内部数组
{
	static int num = 1;
	if (t == 0)
		num = 1;
	if (t == 1)
	{
		int h;//盘号
		int gsy;
		const int BASE_X = 10;
		const int BASE_Y = 40;
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

		if (from == 'A'&&to == 'C')
		{
			h = c[ctop++] = a[--atop];
			a[atop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;
		}

		if (from == 'A'&&to == 'B')
		{
			h = b[btop++] = a[--atop];
			a[atop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;
		}
		if (from == 'B'&&to == 'C')
		{
			h = c[ctop++] = b[--btop];
			b[btop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;
		}
		if (from == 'B'&&to == 'A')
		{
			h = a[atop++] = b[--btop];
			b[btop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;

		}
		if (from == 'C'&&to == 'A')
		{
			h = a[atop++] = c[--ctop];
			c[ctop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;
		}

		if (from == 'C'&&to == 'B')
		{
			h = b[btop++] = c[--ctop];
			c[ctop] = 0;
			if (sleep == 0)
				gsy = _getch();
			else
				Sleep((6 - sleep) * 100);
			if (choice >= 4)
				gotoxy(hout, BASE_X, BASE_Y + 2);
			if (choice == 3)
				gotoxy(hout, 0, num - 1);
			go(from, to, h, num, choice);
			if (choice >= 4)
				shu();
			move(n, from, to, h, choice);
			num++;

		}
	}
	return 0;
}
void DG(int n, char one, char two, char three, int sleep, int choice, int t)//递归函数
{
	char jl = three;
	if (n == 1)
		hanoidg(one, three, sleep, n, choice, t);
	else
	{

		DG(n - 1, one, three, two, sleep, choice, t);
		hanoidg(one, three, sleep, n, choice, t);
		DG(n - 1, two, one, three, sleep, choice, t);

	}
}

void go(char from, char to, int h, int num, int choice)//横向输出
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	if (choice == 1)
	{
		gotoxy(hout, 0, num - 1);
		cout << h << "#: " << from << "-->" << to << endl;
	}
	if (choice == 2)
	{
		gotoxy(hout, 0, num - 1);
		cout << "第" << setiosflags(ios::right) << setw(4) << num << " 步" << "(" << setiosflags(ios::right) << setw(2) << h << "#: " << from << "-->" << to << ") " << endl;
	}
	if (choice >= 3)
	{

		cout << "第" << setiosflags(ios::right) << setw(4) << num << " 步" << "(" << setiosflags(ios::right) << setw(2) << h << "#: " << from << "-->" << to << ") ";
		cout << "A: ";
		for (i = 0, j = 0; i < N; i++)
		{
			if (a[i] == 0)
			{
				for (j; j < N - i; j++)
					cout << setw(2) << " ";
				break;
			}
			else
				cout << setw(1) << a[i] << " ";
		}
		cout << setiosflags(ios::right) << setw(2) << "B: ";
		for (i = 0, j = 0; i < N; i++)
		{
			if (b[i] == 0)
			{
				for (j; j < N - i; j++)
					cout << setw(2) << " ";
				break;
			}
			else
				cout << setw(1) << b[i] << " ";
		}
		cout << setiosflags(ios::right) << setw(2) << "C: ";
		for (i = 0; i < N; i++)
		{
			if (c[i] == 0)
			{
				for (j; j < N - i; j++)
					cout << setw(2) << " ";
				break;
			}
			else
				cout << setw(1) << c[i] << " ";
		}
		cout << endl;
	}
}

void game(int n, char qsz, char mbz, int choice)
{
	static int num = 1, h;

	while (1)
	{
		const int BASE_X = 10;
		const int BASE_Y = 28;
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		gotoxy(hout, BASE_X, BASE_Y + 14);
		cout << "                                                                 " << endl;
		gotoxy(hout, BASE_X, BASE_Y + 14);
		get_int("请输入移动的柱号（命令形式：AC=A顶端的盘子移动到C,Q=退出）:", 'a', 'c', &qsz, &mbz);
		if (qsz == 'q' || qsz == 'Q')
		{
			gotoxy(hout, BASE_X + 4, BASE_Y + 15);
			cout << "游戏中止！！！！" << endl;
			break;
		}
		int m, j, k;
		if (mbz == 'A')
		{
			m = atop;
			k = a[atop - 1];
		}
		if (mbz == 'B')
		{
			m = btop;
			k = b[btop - 1];
		}
		if (mbz == 'C')
		{
			m = ctop;
			k = c[ctop - 1];
		}
		if (qsz == 'A')
		{
			j = a[atop - 1];
		}
		if (qsz == 'B')
		{
			j = b[btop - 1];
		}
		if (qsz == 'C')
		{
			j = c[ctop - 1];
		}
		if (j == 0)
		{
			gotoxy(hout, BASE_X + 4, BASE_Y + 15);
			cout << "源柱为空！" << endl;
			Sleep(300);
			gotoxy(hout, BASE_X + 4, BASE_Y + 15);
			cout << "          " << endl;
			continue;
		}
		if (k != 0)
			if (j > k)
			{
				gotoxy(hout, BASE_X + 4, BASE_Y + 15);
				cout << "大盘压小盘，非法移动！" << endl;
				Sleep(300);
				gotoxy(hout, BASE_X + 4, BASE_Y + 15);
				cout << "                                             " << endl;
				continue;
			}

		if (qsz == 'A'&&mbz == 'C')
		{
			h = c[ctop++] = a[--atop];
			a[atop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;
		}

		if (qsz == 'A'&&mbz == 'B')
		{
			h = b[btop++] = a[--atop];
			a[atop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;
		}
		if (qsz == 'B'&&mbz == 'C')
		{
			h = c[ctop++] = b[--btop];
			b[btop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;
		}
		if (qsz == 'B'&&mbz == 'A')
		{
			h = a[atop++] = b[--btop];
			b[btop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;

		}
		if (qsz == 'C'&&mbz == 'A')
		{
			h = a[atop++] = c[--ctop];
			c[ctop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;
		}
		if (qsz == 'C'&&mbz == 'B')
		{
			h = b[btop++] = c[--ctop];
			c[ctop] = 0;
			gotoxy(hout, BASE_X, BASE_Y + 16);
			go(qsz, mbz, h, num, choice);
			shu();
			num++;
		}

		move(n, qsz, mbz, h, choice);
		if (m + 1 == n)
		{
			gotoxy(hout, BASE_X + 4, BASE_Y + 15);
			cout << "游戏结束!!!!" << endl;
			break;
		}
	}

}
