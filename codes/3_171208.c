//
//  main.cpp(demo 3) 
//  黑白棋   
//  
//  Created by acdzh on 2017/12/08.  
//  Copyright © 2017年 acdzh. All rights reserved.
//

//x是行，y是列（数组表示里x在前，y在后，与平面直角坐标系没有半毛钱关系;
//改来改去我自己都看不懂了。。。
//不过能跑起来就行，传上去就不改了
//大佬们都用了深度搜索，emmmm为啥我不会用fffffffffffffff
//我真的写不出来啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 1
#define WHITE -1
#define ALL 0
#define opp_color (-1)*my_color



int  board_0[16][16] = { 0 };
int board_backups[16][16] = { 0 };
float score[16][16] = { 0 };
float score_value[16][16] = { 
	{ 25, 7,21,19,18,18,18,17,		17,18,18,18,19,21, 7,25},//0
	{  7, 6,13,12,11,10,10, 9,		 9,10,10,11,12,13, 6, 7},//1
	{ 21,13,18,17,17,16,16,16,		16,16,16,17,17,18,13,21},//2
	{ 19,12,17,16,18,18,18,18,		18,18,18,18,16,17,12,19},//3
	{ 18,11,16,15,15,14,14,14,		14,14,14,15,15,16,11,18},//4
	{ 18,10,16,15,15,14,14,14,		14,14,14,15,15,16,10,18},//5
	{ 18,10,16,15,15,14,14,14,		14,14,14,15,15,16,10,18},//6
	{ 17, 9,16,15,15,14,14,14,		14,14,14,15,15,16, 9,17},//7


	{ 17, 9,16,15,15,14,14,14,		14,14,14,15,15,16, 9,17 },//8
	{ 18,10,16,15,15,14,14,14,		14,14,14,15,15,16,10,18 },//9
	{ 18,10,16,15,15,14,14,14,		14,14,14,15,15,16,10,18 },//10
	{ 18,11,16,15,15,14,14,14,		14,14,14,15,15,16,11,18 },//11
	{ 19,12,17,16,18,18,18,18,		18,18,18,18,16,17,12,19 },//12
	{ 21,13,18,17,17,16,16,16,		16,16,16,17,17,18,13,21 },//13
	{ 7, 6,13,12,11,10,10, 9,		 9,10,10,11,12,13, 6, 7 },//14
	{ 25, 7,21,19,18,18,18,17,		17,18,18,18,19,21, 7,25 }//15

};
float score_action_power_me[16][16] = { 0 };
float score_action_power_opp[16][16] = { 0 };
float score_eaten_power[16][16] = { 0 };

float rate_value = 13;
float rate_action_power_me = 2;
float rate_action_power_opp = 2;


int my_color = BLACK;
int x_ai, y_ai;
int x_plat, y_plat;











//*********************************************
//***********basic_function********************
//*********************************************


//判断是否越界，未越界返回1；
int legal(int i, int j)
{
	if (
		(i < 16) && (i >= 0) && (j < 16) && (j >= 0)
		)
		return 1;
	else
		return 0;
}

//判断是否可以下子,可下子返回1；
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

//在一个数组里找最大的数对应的x与y(输入为1时输出行，2输出列);
int find(float a[][16],int b)
{
	int x_max = 0;
	int y_max = 0;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (a[i][j] >= a[x_max][y_max])
			{
				x_max = i;
				y_max = j;
			}

		}
	}
	if (b == 1) { return x_max; }
	if (b == 2) { return y_max; }
	if (b == 3) { return a[x_max][y_max]; }
}

//落子(直接改变board_0)
void place( int i, int j, int color)
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

//DEBUG时用，1输出棋盘，2输出分值表
int out(int a)
{
	for (int i = 0; i <= 15; i++)
	{
		printf("DEBUG");
		for (int j = 0; j <= 15; j++)
		{
			if (a == 1) { printf("%d   ", board_0[i][j]); }
			if (a == 2) { printf("%f   ", score[i][j]); }
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}

//数一下棋盘上有多少子,返回不同颜色的数量，当输入为ALL时返回总数量
int count(int board[][16],int color)
{
	int b = 0;
	int w = 0;
	int all = 0;
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (board[i][j] == 1)
			{
				b++;
			}
			else if (board[i][j] == -1)
			{
				w++;
			}
		}
	}
	all = w + b;
	if (color == BLACK) { return b; }
	else if (color == WHITE) { return w; }
	else if (color == ALL) { return all; }
}








//******************************************
//f1_function*******************************
//******************************************
//基于棋盘上不同点价值不同，权重为 rate_1;


//其实我觉得这里的函数没啥好写的QAQ；




//******************************************
//f2_function*******************************
//******************************************
//基于棋盘上落子在不同点之后，我方的行动力，与对方的行动力，权重为 rate_2;

//获得以上，输入棋盘，颜色，返回行动力;
int action_power(int board[][16], int color)
{
	int a = 0;

	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (judge(board, i, j, color > 0))
			{
				a++;
			}
		}
	}
	return a;
}

void get_action_power()
{
	
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (judge(board_0, i, j, my_color) == 0) 
			{ 
				score_action_power_me[i][j] = 0;
				score_action_power_opp[i][j] = 0;
			}
			else
			{
			memcpy(board_backups, board_0, 256 * sizeof(int));
			place(i,j,my_color);
			score_action_power_me[i][j] = action_power(board_0,my_color);
			score_action_power_opp[i][j] = action_power(board_0,opp_color);
			memcpy(board_0, board_backups, 256 * sizeof(int));
			}
		}
	}

}


//******************************************
//f3_function*******************************
//******************************************
//若在某处落子，可吃掉对方多少子 //最后几步用

int eaten_power(int i, int j)
{
	int before, after = 0;
	int a = 0;
	before = count(board_0, my_color);
	memcpy(board_backups, board_0, 256 * sizeof(int));
	place(i, j, my_color);
	after = count(board_0, my_color);
	a = after - before - 1;
	memcpy(board_0, board_backups, 256 * sizeof(int));
	return a;
}




//******************************************
//f_ai_function*******************************
//******************************************
//FIND

void ai()
{
	x_ai = 0;
	y_ai = 0;
	get_action_power();
	if (count(board_0,ALL) >= 180)//当最后几步时采用贪心算法
	{
		//获取score[][]
		for (int i = 0; i <= 15; i++)
		{
			for (int j = 0; j <= 15; j++)
			{
				if (judge(board_0,i,j,my_color) > 0) { score[i][j] = eaten_power( i, j) + 0.5*score_value[i][j]; }
				else { score[i][j] = -1; }
			}
		}
		x_ai = find(score, 1);
		y_ai = find(score, 2);
	}
	else
	{
		for (int i = 0; i <= 15; i++)
		{
			for (int j = 0; j <= 15; j++)
			{
				if (judge(board_0, i, j, my_color) > 0) 
				{
					score[i][j] = rate_value * score_value[i][j] + rate_action_power_me * score_action_power_me[i][j] - rate_action_power_opp * (find(score_action_power_opp,3) - score_action_power_opp[i][j]);
				}
				else { score[i][j] = -1; }
			}
		}
		x_ai = find(score, 1);
		y_ai = find(score, 2);
	}
}




//
//main_function
//
int main()
{
	//初始化
	board_0[7][8] = BLACK;			//将黑棋放在 (7,8) 上;
	board_0[8][7] = BLACK;			//将黑棋放在 (8,7) 上;
	board_0[7][7] = WHITE;			//将白棋放在 (7,7) 上;
	board_0[8][8] = WHITE;			//将白棋放在 (8,8) 上;

	int temp[16][16];
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
		scanf_s("%s", text_plat,8);
		//若平台发送TURN（即我方下子）
		if (strcmp(text_plat, "TURN") == 0)
		{
			ai();
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
