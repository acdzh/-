//
//  黑白棋_c.cpp   
//  黑白棋   
//  
//  Created by acdzh on 2017/12/02.  
//  Copyright © 2017年 acdzh. All rights reserved.
//                                              




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chess[16][16] = { 0,0 };//棋盘初始化;
int chess_1[16][16] = { 0 };
int score[16][16] = { 0 };
int action_power = 0;//行动力大小；
int i_ai, j_ai;//AI输出的位置
int my_color = 1;//己方执子颜色
int i_plat, j_plat = 0;//储存平台发送的位置;


int feasibility(int c[][16], int color);
void ai(int color);
void play_step(int c[][16], int m, int n, int color);
void out();
int ok(int c[][16], int i, int j, int color);

int main()
{
	memset(*chess, 0, sizeof(chess));
	chess[7][8] = 1;			//将黑棋放在 (7,8) 上;
	chess[8][7] = 1;			//将黑棋放在 (8,7) 上;
	chess[7][7] = -1;			//将黑棋放在 (7,7) 上;
	chess[8][8] = -1;			//将黑棋放在 (8,8) 上;

	char text_plat[20];

	out();

	scanf_s("START %d", &my_color);
	printf("OK");
	fflush(stdout);

	//数组初始化;
	my_color = -2 * my_color + 3;//将平台的表示转化为自己的表示;

								 //若己方执白棋，则等待对方先走一步，并对棋盘做出改变;
	if (my_color = -1)
	{
		scanf_s("PLACE %d %d", &i_plat, &j_plat);
		play_step(chess, i_plat, j_plat, 1);//表示在棋盘上放置对手棋子（黑棋）;
	}

	out();

	while (1)
	{
		fgets(text_plat, 19, stdin);
		fgets(text_plat, 19, stdin);
		if (strcmp(text_plat, "TURN") == 1)
		{
			ai(my_color);
			printf("%d %d", i_ai, j_ai);
			fflush(stdout);
			play_step(chess, i_ai, j_ai, my_color);
			text_plat[2] = '3';//变一下标识文本。。。

		}

		//若平台发送PLACE（即对手下子）
		if (text_plat[0] == 'P')
		{
			scanf_s("PLACE %d %d", &i_plat, &j_plat);
			play_step(chess, i_plat, j_plat, my_color * (-1));
			text_plat[2] = '3';
		}

		//若平台发送END（游戏结束）
		if (text_plat[0] == 'E')
		{
			break;
		}
		printf("\n");

		out();

	}
	return 0;
}

//检测一个位置是否可以下子；
int ok(int c[][16], int i, int j, int color)
{
	int ok = 0;
	int i_opp = 0;
	int j_opp = 0;//存储对手棋子的位置；

	if (c[i][j] != 0) { ok = 0; } //若当前位置已有棋子,返回 0；
	else//搜索该处四周是否有对手棋子；
	{
		for (int i_delta = -1; i_delta <= 1; i_delta++)
		{
			for (int j_delta = -1; j_delta <= 1; j_delta++)
			{
				//若越出棋盘或者与当前点重合，跳过；
				if (i + i_delta < 0 || i + i_delta > 15 ||
					j + j_delta < 0 || j + j_delta > 15 ||
					((i_delta == 0) && (j_delta == 0))) {
					continue;
				}
				//若四周有对手的棋子；
				if (c[i + i_delta][j + j_delta] == (-1) * color)
				{
					i_opp = i + i_delta;//获得对手棋子位置；
					j_opp = j + j_delta;

					//以当前点与对手棋子的连线，继续向前寻找；
					while (1)
					{
						i_opp += i_delta;//向前走一步；
						j_opp += j_delta;

						//若越出边界或为空格，跳出；
						if (i_opp < 0 || i_opp > 15 ||
							j_opp < 0 || j_opp > 15 || c[i_opp][j_opp] == 0)
						{
							continue;
						}

						//如果是己方棋子，ok 返回值 1；
						if (c[i_opp][j_opp] = color)
						{
							ok = 1;
							break;//该方向检测完毕，跳出；
						}
					}
				}
			}
		}
	}
	return ok;
}

//此函数用来求行动力大小；
int  feasibility(int c[][16], int color)//color用来代表求的是哪种棋子的行动力（1，-1）,chess获取当前棋盘
{
	int action_power = 0;
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (ok(c, i, j, color) == 1)
			{
				action_power += 1;
			}
		}
	}
	return action_power;
}

//用于变更棋盘
void play_step(int c[][16], int m, int n, int color)
{
	int i_delta = 0;
	int j_delta = 0;
	int i_opp = 0;
	int j_opp = 0;

	c[m][n] = color;    //保存所下位置的棋盘的棋子

						//检查所下子四周的棋子
	for (i_delta = -1; i_delta <= 1; i_delta++)
	{
		for (j_delta = -1; j_delta <= 1; j_delta++)
		{
			//若坐标超过棋盘界限,跳过
			if (m + i_delta < 0 || n + i_delta >= 16 || n + j_delta < 0
				|| n + j_delta >= 16 || (i_delta == 0 && j_delta == 0)) {
				continue;
			}

			//若该位置是对手的棋子
			if (c[m + i_delta][n + j_delta] == (-1) * color)
			{
				//以对手棋为坐标
				i_opp = m + i_delta;
				j_opp = n + j_delta;

				//在对手棋子四周寻找我方棋子 
				while (1)
				{
					i_opp += i_delta;
					j_opp += j_delta;
					//若坐标超过棋盘，跳出
					if (i_opp < 0 || i_opp >= 16 || j_opp < 0 || j_opp >= 16) { break; }

					//若对应位置为空 ,跳出;
					if (c[i_opp][j_opp] == 0) { break; }

					//若对应位置是我方棋子，循环并替换掉中间所有对方棋子;
					if (c[i_opp][j_opp] == color)
					{
						//循环处理 
						while (c[i_opp -= i_delta][j_opp -= j_delta] == (-1) * color)
						{
							//将中间的棋子都变成我方棋子
							c[i_opp][j_opp] = color;
						}
						break;  //退出循环 
					}
				}
			}
		}
	}

}

//AI得出最优解
void ai(int color)//color为ai所执子
{
	i_ai = 0;
	j_ai = 0;

	//初始化演算用棋盘
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			chess_1[i][j] = chess[i][j];
		}
	}

	//获得积分盘；
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (ok(chess, i, j, my_color) == 0)
			{
				i_ai = i;
				j_ai = j;
				continue;
			}
			else
			{
				play_step(chess_1, i, j, my_color);
				score[i][j] = feasibility(chess_1, my_color);
			}

		}
	}

	//从积分盘中找最佳点；
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (score[i][j] > score[i_ai][j_ai])
			{
				i_ai = i;
				j_ai = j;
			}
		}
	}

}

//输出棋盘
void out()
{
	printf("DEBUG \n");
	printf("DEBUG NO.M  " );
	for (int i = 0; i <= 15; i++)
		printf("%d    ", i);
	printf("\n");
	for (int i = 0; i <= 15; i++)
	{
		printf("DEBUG NO.%d  ",i);
		for (int j = 0; j <= 15; j++)
		{
			printf("%d    ", chess[i][j]);
		}
		printf("\n");
	}
}

