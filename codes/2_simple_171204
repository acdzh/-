//
//  simple.c (demo) 
//  黑白棋   
//  
//  Created by acdzh on 2017/12/03.  
//  Copyright © 2017年 acdzh. All rights reserved.
//

//x是行，y是列（数组表示里x在前，y在后，与平面直角坐标系没有半毛钱关系

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 1
#define WHITE -1

int board_0[16][16] = { 0 };
int score[16][16] = { 0 };
int score_2[16][16] = { //这只是四分之一，下面会用对称扩展到整个棋盘上;
	{ 25, 7,21,19,18,18,18,17 },
	{ 7, 6,13,12,11,10,10, 9 },
	{ 21,13,18,17,17,16,16,16 },
	{ 19,12,17,16,18,18,18,18 },
	{ 18,11,16,15,15,14,14,14 },
	{ 18,10,16,15,15,14,14,14 },
	{ 18,10,16,15,15,14,14,14 },
	{ 17, 9,16,15,15,14,14,14 }

};
int my_color = BLACK;
int x_ai, y_ai = 0;
int x_plat, y_plat;



//判断是否越界，越界返回0；
int legal(int i, int j)
{
	if (
		(i < 16) && (i >= 0) && (j < 16) && (j >= 0)
		)
		return 1;
	else
		return 0;
}

int judge(int board[][16], int i, int j, int color)
{
	int ok = 0;
	int i_opp;
	int j_opp;//沿某个方向向前搜索时所用

			  //若当前位置已有棋子，返回0；
	if (board[i][j] != 0) { ok = 0; }
	else //搜索该处四周是否有对手棋子；
	{
		for (int i_delta = -1; i_delta < 2; i_delta++)
		{
			for (int j_delta = -1; j_delta < 2; j_delta++)
			{
				//若越出棋盘或者与当前点重合，跳过；
				if (legal(i + i_delta, j + j_delta) == 0 ||
					((i_delta == 0) && (j_delta == 0)))
				{
					continue;
				}

				//若四周有对手的棋子；
				if (board[i + i_delta][j + j_delta] == ((-1)*color))
				{
					i_opp = i + i_delta;//先获得相邻对手棋子的位置
					j_opp = j + j_delta;//之后利用这个找到方向向前搜索

					while (1)
					{
						i_opp += i_delta;//向前走一步；
						j_opp += j_delta;

						//若越出边界或为空格，跳出；
						if (legal(i_opp, j_opp) == 0 || board[i_opp][j_opp] == 0)
						{
							break;
						}

						//如果是己方棋子，ok 返回值 1；
						if (board[i_opp][j_opp] == color)
						{
							ok += 1;
							break;//该方向检测完毕，跳出；
						}
					}
				}
			}
		}
	}
	return ok;
}

//对整个棋盘进行遍历，在所有的地方尝试
void score_cal()
{
	

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			//若某点不可以放置棋子
			if (judge(board_0, i, j, my_color) == 0)
			{
				//-1，存入记分数组
				score[i][j] = -1;
				
			}
			else
			{
				score[i][j] = score_2[i][j];
			}
		}
	}
}

//找到积分表里面的最优解，并存入 x_ai 与 y_ai 中
void find()
{
	x_ai = 0;
	y_ai = 0;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (score[i][j] >= score[x_ai][y_ai] && judge(board_0, i, j, my_color) > 0)
			{
				x_ai = i;
				y_ai = j;
			}


		}
	}
}

void score_2_begin()
{
	//这是右上角的赋值
	for (int i = 0; i < 8; i++)
	{
		for (int j = 8; j < 16; j++)
		{
			score_2[i][j] = score_2[i][15 - j];
		}
	}

	//这是整个下半部分的赋值
	for (int i = 8; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			score_2[i][j] = score_2[15 - i][j];
		}
	}
}


//落子（此时改变的是原有棋盘数组，如果有计算需要调用此函数进行估值演算，请提前做好棋盘的备份 ：） ）;
void place(int i, int j, int color)
{
	int i_opp;
	int j_opp;
	board_0[i][j] = color;

	//检查所下子四周的棋子;
	for (int i_delta = -1; i_delta <= 1; i_delta++)
	{
		for (int j_delta = -1; j_delta <= 1; j_delta++)
		{
			//若坐标超过棋盘界限,跳过;
			if (legal(i + i_delta, j + j_delta) == 0 ||
				(i_delta == 0 && j_delta == 0)) 
			{
				continue;
			}

			//若该位置是对手的棋子;
			if (board_0[i + i_delta][j + j_delta] == (-1) * color)
			{
				i_opp = i + i_delta;//用来以对手棋为坐标
				j_opp = j + j_delta;//在对手棋子四周寻找我方棋子 


				while (1)
				{
					i_opp += i_delta;//向前走一步；
					j_opp += j_delta;

					//若坐标超过棋盘，跳出
					if (legal(i_opp, j_opp) == 0) { break; }
					//若对应位置为空 ,跳出;
					if (board_0[i_opp][j_opp] == 0) { break; }
					//若对应位置是我方棋子，循环并替换掉中间所有对方棋子;
					if (board_0[i_opp][j_opp] == color)
					{
						while (board_0[i_opp -= i_delta][j_opp -= j_delta] == (-1) * color)
						{
							board_0[i_opp][j_opp] = color;
						}
						break;
					}
				}
			}
		}
	}
}

int out(int a)
{
	for (int i = 0; i <= 15; i++)
	{
		printf("DEBUG");
		for (int j = 0; j <= 15; j++)
		{
			if (a == 1) { printf("%d   ", board_0[i][j]); }
			if (a == 2) { printf("%d   ", score[i][j]); }
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}

int main()
{
	//初始化
	score_2_begin();
	board_0[7][8] = BLACK;			//将黑棋放在 (7,8) 上;
	board_0[8][7] = BLACK;			//将黑棋放在 (8,7) 上;
	board_0[7][7] = WHITE;			//将白棋放在 (7,7) 上;
	board_0[8][8] = WHITE;			//将白棋放在 (8,8) 上;

	char text_plat[20];

	scanf_s("START %d", &my_color);
	printf("OK\n");
	fflush(stdout);
	my_color = (-2 * my_color + 3);

	//若己方执白棋，则等待对方先走一步，并对棋盘做出改变;
	if (my_color == WHITE)
	{
		scanf_s("PLACE %d %d", &x_plat, &y_plat);
		place(x_plat, y_plat, BLACK);//表示在棋盘上放置对手棋子（黑棋）;
	}

	while (1)
	{
		scanf("%s", text_plat);
		//若平台发送TURN（即我方下子）
		if (strcmp(text_plat, "TURN") == 0)
		{
			score_cal();
			find();
			printf("%d %d\n", x_ai, y_ai);
			printf("DEBUG  ME %d\n", judge(board_0, x_ai, y_ai, my_color));
			out(2);
			fflush(stdout);
			place(x_ai, y_ai, my_color);
			out(1);
		}

		//若平台发送PLACE（即对手下子）
		else if (strcmp(text_plat, "PLACE") == 0)
		{
			scanf_s("%d %d", &x_plat, &y_plat);
			printf("DEBUG  OPP %d\n", judge(board_0, x_plat, y_plat, (-1)*my_color));
			fflush(stdout);
			place(x_plat, y_plat, (-1)*my_color);
			out(1);
		}

		//若平台发送END（游戏结束）
		else if (strcmp(text_plat, "END") == 0)
		{
			break;
		}
	}
	return 0;
}
