#pragma once
int load_range = 8;
struct member
{
	char name[16];
	int x = rand() % 500;
	int y = 65;
};
member player[24];
enum BLOCK { dirt, air, weater, mud, grass_block,grass,stone,golden_block,iron_ore,iron_block,wood_block,wood_plank,leaves };
struct MAP
{
	BLOCK chunks[32][128];
	int Lnumber = 0;
	int Rnumber = 0;
	bool ALWAYS = false;
	bool finished = false;
	bool RL = true;
};
int L = 1;
int R = 0;
//std::vector<MAP> Rworld;
//std::vector<MAP> Lworld;
MAP Rworld[20000];
MAP Lworld[20000];