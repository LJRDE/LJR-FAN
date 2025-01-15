#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <graphics.h>
#include <math.h>
#include <socketapi.h>
#include "overall.h"
using namespace std;
void load_chunk(int x,bool RL);//这里x是区块坐标
void load_map(int x);//这里x是玩家坐标
void drawmap(int x,int y);
void zerochunk();
void SETblock(int x, int y,BLOCK TYPE);
void command();
bool ifload(int x);
BLOCK GETblock(int x,int y);
IMAGE istone;
IMAGE idirt;
IMAGE igrass_block;
IMAGE ierrow;
IMAGE ifan;
IMAGE iair;
IMAGE iiron_ore;
int main()
{
	load_map(player[0].x);
	zerochunk();
	cin.get();
	initgraph(1380, 720);
	//setorigin(0, -480);
	//setaspectratio(2, 2);
	loadimage(&istone, _T("stone.png"));
	loadimage(&idirt, _T("dirt.png"));
	loadimage(&ierrow, _T("errow.png"));
	loadimage(&igrass_block, _T("grass_side.png"));
	loadimage(&ifan, _T("fan.png"));
	loadimage(&iair, _T("air.png"));
	loadimage(&iiron_ore, _T("iron_ore.png"));
	//putimage(100, -100, &img_stone);
	player[0].x = 0;
	player[0].y = 77;
	char wasd='0';
	int FPS = 0;
	int iFPS = 0;
	int T = time(NULL);
	for (;;)
	{
		outtextxy(1298, 20, "X:");
		outtextxy(1298, 40, "Y:");
		outtextxy(1298, 60, "FPS:");
		if (T + 1 <= time(NULL))
		{
			FPS = iFPS / 1;
			iFPS = 0;
			T = time(NULL);
		}
		iFPS++;
		drawmap(player[0].x, player[0].y);
		char xnum[20];
		sprintf(xnum, "%d", player[0].x);
		outtextxy(1315, 20, xnum);
		char ynum[20];
		sprintf(ynum, "%d", player[0].y);
		outtextxy(1315, 40, ynum);
		char FPSnum[20];
		sprintf(FPSnum, "%d", FPS);
		outtextxy(1340, 60, FPSnum);
		if (_kbhit())//检测键盘判定
			wasd = _getch();//读取键盘 
			if (wasd == 'w') player[0].y--;
			else if (wasd == 's')player[0].y++;
			else if (wasd == 'a')player[0].x--;
			else if (wasd == 'd')player[0].x++;
			else if (wasd == '8') SETblock(player[0].x, player[0].y, stone);
			else if (wasd == 't') command();
		wasd = '0';
		if (ifload(player[0].x) == false)
		{
			load_map(player[0].x);
		}
	}
	

	cin.get();
	return 0;
}
bool ifload(int x)
{
	int i = floor(x / 32);
	if (i >= 0) return Rworld[i].finished;
	else if (i<0) return Lworld[abs(i)].finished;
}
void command()
{
	closegraph();
	string _command[16];
	int x, y, z, i, a, b, c;
	cout << "输入'help'以获得帮助\n";
	cin >> _command[0];
	if (_command[0] == "help")
	{
		cout << "1.help -帮助\n" << "2.tp X Y -传送\n";
	}
	else if (_command[0] == "tp")
	{
		cin >> x;
		cin >> y;
		player[0].x = x;
		player[0].y = y;
	}
	initgraph(1280, 720);
}
void SETblock(int x,int y,BLOCK TYPE)
{
	if (x > -1)
	{
		int i = floor(x / 32);
		Rworld[abs(i)].chunks[abs(x) % 32][abs(y)] = TYPE;
	}
	else if (x < 0)
	{
		int i = floor(x / 32);
		Lworld[abs(i)].chunks[abs(x) % 32][abs(y)] = TYPE;
	}
}
BLOCK GETblock(int x, int y)
{
	BLOCK GET;
	int i = 0;
	if (y > 129) return air;
	else if (y <0) return air;
	else if (x > -1)
	{
		i = floor(x / 32);
		int t = i * 32;
		GET = Rworld[abs(i)].chunks[abs(x) % 32][abs(y)];
	}
	else if (x < 0)
	{
		i = floor(x / 32);
		int t = i * 32;
		GET = Lworld[abs(i)].chunks[abs(x) % 32][abs(y)];
	}
	return GET;
}
void zerochunk()
{
	int lx = 0;
	int ly = 0;
	int x = 0;
	for (;;)
	{
		if (ly < 78) Lworld[x].chunks[lx][ly] = air;
		else if (ly == 78) Lworld[x].chunks[lx][ly] = grass_block;
		else if (ly < 84) Lworld[x].chunks[lx][ly] = dirt;
		else if (ly < 129) Lworld[x].chunks[lx][ly] = stone;
		else Lworld[x].chunks[lx][ly] = air;
		lx++;
		if (lx == 33)
		{
			lx = 0;
			ly++;
		}
		if (ly > 128)
			break;

	}
	lx = 0;
	ly = 0;
	x = 0;
	for (;;)
	{
		if (ly < 78) Rworld[x].chunks[lx][ly] = air;
		else if (ly == 78) Rworld[x].chunks[lx][ly] = grass_block;
		else if (ly < 84) Rworld[x].chunks[lx][ly] = dirt;
		else if (ly < 129) Rworld[x].chunks[lx][ly] = stone;
		else Rworld[x].chunks[lx][ly] = air;
		lx++;
		if (lx == 33)
		{
			lx = 0;
			ly++;
		}
		if (ly > 129)
			break;

	}
}
void drawmap(int x, int y)
{
	BLOCK draw[40][30];
	int ix = 0;
	int iy = 0;
	int ex = x - 20;
	int ey = y - 15;
		for(;;)
		{
			draw[ix][iy] = GETblock(ex, ey);
			ix++;
			ex++;
			if (ix==40)
			{
				iy++;
				ey++;
				ex = x - 20;
				ix = 0;
			}
			if (iy == 30) break;
		}
		int iix = 0;
		int iiy = 0;
		for (;;)
		{
			if (draw[iix][iiy] == air) putimage(iix * 32, iiy * 32, &iair);
			else if (draw[iix][iiy] == stone) putimage(iix * 32,iiy * 32, &istone);
			else if (draw[iix][iiy] == dirt) putimage(iix * 32, iiy * 32, &idirt);
			else if (draw[iix][iiy] == grass_block) putimage(iix * 32, iiy * 32, &igrass_block);
			else if (draw[iix][iiy] == iron_ore) putimage(iix * 32, iiy * 32, &iiron_ore);
			else  putimage(iix * 32, iiy * 32, &ierrow);
			putimage(20 * 32, 15 * 32, &ifan);
			iix++;
			if (iix == 40)
			{
				iix = 0;
				iiy++;
			}
			if (iiy == 31) break;
		}
}
void load_map(int x)
{
	double cx = x / 32;
	int chunk_x = floor(cx);
	int lx = chunk_x - load_range;
	int rx = chunk_x + load_range;
	cout << "lx" << lx << "  rx" << rx;
	for(;;)
	{
		if (rx > -1) load_chunk(rx, true);
		else if(rx<0) load_chunk(abs(rx), false);//当rx小于0时取绝对值
		if (rx == lx) break;
		rx--;
		cout << "lx" << lx << "  rx" << rx;
	}
}
void load_chunk(int x,bool RL)
{
	int lx = 0;
	int ly = 0;
	if (RL == true&& Rworld[x].finished==false)
		{
		for (;;) 
			{
				if (ly < 78) Rworld[x].chunks[lx][ly] = air;
				else if (ly == 78) Rworld[x].chunks[lx][ly] = grass_block;
				else if (ly < 84) Rworld[x].chunks[lx][ly] = dirt;
				else if (ly <= 128) Rworld[x].chunks[lx][ly] = stone;
				else Rworld[x].chunks[lx][ly] = air;
				if (ly > 90&&rand()%1000>990)
				{
					Rworld[x].chunks[lx][ly] = iron_ore;
				}
				lx++;
			if (lx == 33)
			{
				lx = 0;
				ly++;
			}
			if (ly == 129)
				break;

			}
			cout <<x<< "R\n";
			Rworld[x].finished = true;
		}
	else if (RL == false&& Lworld[x].finished == false)
		{
		for (;;) 
			{
				if (ly < 78) Lworld[x].chunks[lx][ly] = air;
				else if (ly == 78) Lworld[x].chunks[lx][ly] = grass_block;
				else if (ly < 84) Lworld[x].chunks[lx][ly] = dirt;
				else if (ly < 129) Lworld[x].chunks[lx][ly] = stone;
				else Lworld[x].chunks[lx][ly] = air;
				lx++;
				if (lx == 33)
				{
					lx = 0;
					ly++;
				}
				if (ly > 128)
					break;
				
			}
			cout <<x<< "L\n";
			Lworld[x].finished = true;
		}
}