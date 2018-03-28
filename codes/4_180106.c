//
//  main.cpp(Vesion 2.3) 
//  黑白棋   
//  
//  Created by acdzh on 2018/01/04.  
//  Copyright © 2017年 acdzh. All rights reserved.
//

//Version 4.1
/*
	开始加深搜//2018/01/04 02:22:14
	终于写出来深搜了。。
*/


//Vesion 3.11
/*
	这是上一个版本的紧急BUG修复版本
	将不能落子的位置的score从-1改成了-2000
	//毕竟刚关上游戏发现结果出来直接爆炸能吓死人。。
	(更惨的是刚刚发现交上去的还是错的
	//2018/01/04 01:13:35

	修正上面的错误后，发现每次棋盘都会变成全0
	我在3.1里加的新函数里的if里用的都是 “ = ”
	。。。。。。。。
	已修正
	//2018/01/04 01:38:26
*/

//Vesion 3.1
/*
	咸鱼表示还能再挣扎一下
	对估值函数做了一点微小的改动
	新加入了一个插空的算法
	（这大概是一个咸鱼最后的挣扎了吧
	2018/01/03 22:37:45

	ps.直接翻车，四胜128败。。。。
	估计是score 初始的-1太高了
	//2018/01/04 01:06:44

*/

//Version 2.2
/*
	他们说把棋格表的拉差做大一些效果会好很多
	试试再说
	要是不行就回滚到上一个版本
	(真让人头大.jpg
	//2017/12/28 20:23:35

	ps.实践证明，这并没有什么用
	2018/01/03 20:24:33
*/

//Version 2.1
/*
	x是行，y是列（数组表示里x在前，y在后，与平面直角坐标系没有半毛钱关系;
	改来改去我自己都看不懂了。。。
	不过能跑起来就行，传上去就不改了
	大佬们都用了深度搜索，emmmm为啥我不会用fffffffffffffff
	我真的写不出来啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
	不写了不写了，要是两星期内再碰黑白棋我就。。。。

	2017/12/10 6:13
*/

//Version 2.0
/*
	加入了行动力，但结果总是莫名其妙
	为什么排名与行动力权重完全相反？！！！！
	提交了很多次，主要是试参数
	这应该是所谓的最好的了
	本来想顺便加一点深搜，发现写不出来XD
	( 再也不通宵了，智商下降

	2017/12/10 4:09
*/

//Version 1.0
/*
	仅仅使用了棋格表，打算先试一试
	棋格表来源：胡乱写的

	2017/12/02 大致写完
	2017/12/06 Debug失败很多次。。。重新写了一遍，提交了
*/

//Demo Version :
/*
	终于把框架写出来，不报错了，233333高兴
	2017/11/27
*/


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
	{ 80, 0,70,60,55,50,50,50,		50,50,50,55,60,70, 0,80 },//0
	{ 0, 6,25,15,15,20,20,22,		22,20,20,15,15,25, 6, 0 },//1
	{ 70,25,45,45,40,40,40,30,		30,40,40,40,45,45,25,70 },//2
	{ 60,45,45,40,39,39,38,37,		37,38,39,39,40,45,45,60 },//3
	{ 55,45,40,39,40,40,42,45,		45,42,40,40,39,40,45,55 },//4
	{ 50,20,40,39,40,45,45,45,		45,45,45,40,39,40,20,50 },//5
	{ 50,20,40,38,42,45,47,48,		48,47,45,42,38,40,20,50 },//6
	{ 50,22,30,37,45,45,47,48,		48,47,45,45,37,30,22,50 },//7


	{ 50,22,30,37,45,45,47,48,		48,47,45,45,37,30,22,50 },//8	7
	{ 50,20,40,38,42,45,47,48,		48,47,45,42,38,40,20,50 },//9	6
	{ 50,20,40,39,40,45,45,45,		45,45,45,40,39,40,20,50 },//10	5
	{ 55,45,40,39,40,40,42,45,		45,42,40,40,39,40,45,55 },//11	4
	{ 60,45,45,40,39,39,38,37,		37,38,39,39,40,45,45,60 },//12	3
	{ 70,25,45,45,40,40,40,30,		30,40,40,40,45,45,25,70 },//13	2
	{ 0, 6,25,15,15,20,20,22,		22,20,20,15,15,25, 6, 0 },//14	1
	{ 80, 0,70,60,55,50,50,50,		50,50,50,55,60,70, 0,80 }//15	0

};

float score_action_power_me[16][16] = { 0 };
float score_action_power_opp[16][16] = { 0 };
float score_eaten_power[16][16] = { 0 };

float score_blank_power[16][16] = { 0 };

//随缘的系数



#define rate_action_power_me_1 4
#define rate_action_power_opp_1  4.1
#define rate_blank_power_1  3
#define rate_count_1 0
#define rate_value_1 3

#define rate_action_power_me_2 7.3
#define rate_action_power_opp_2  3.1
#define rate_blank_power_2  0.51
#define rate_count_2 0
#define rate_value_2 4.3



int my_color = BLACK;
int x_ai, y_ai;
int x_plat, y_plat;
int depth_0 = 4;//深搜深度
int step[10][2];//存储深搜时的步骤




//*********************************************
//***********basic_function********************
//*********************************************

//初始化计分表
void score_begin()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			score[i][j] = -20000;
		}
	}
}

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

//在一个数组里找最大的数对应的x与y(输入为1时输出行，2输出列,3直接输出数组中的最大值);
int find(float a[][16], int b)
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
	else { return 0; }
	//if (b == 3) { return a[x_max][y_max]; }
}

//落子(直接改变board_0)
void place(int a[][16], int i, int j, int color)
{

	int i_opp;
	int j_opp;
	a[i][j] = color;

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
			if (a[i + i_delta][j + j_delta] == (-1) * color)
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
					if (a[i_opp][j_opp] == 0) { break; }
					//若对应位置是我方棋子，循环并替换掉中间所有对方棋子;
					if (a[i_opp][j_opp] == color)
					{
						while (a[i_opp -= i_delta][j_opp -= j_delta] == (-1) * color)
						{
							a[i_opp][j_opp] = color;
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
			if (a == 2) { printf("%.2f   ", score[i][j]); }
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}

//数一下棋盘上有多少子,返回不同颜色的数量，当输入为ALL时返回总数量
int count(int board[][16], int color)
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
	else { return 0; }
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
	//初始化数组(虽然确实没什么用
	memset(score_action_power_me, 0, sizeof(score_action_power_me));
	memset(score_action_power_opp, 0, sizeof(score_action_power_opp));

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
				place(board_0, i, j, my_color);
				score_action_power_me[i][j] = action_power(board_0, my_color);
				score_action_power_opp[i][j] = action_power(board_0, opp_color);
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
	place(board_0, i, j, my_color);
	after = count(board_0, my_color);
	a = after - before - 1;
	memcpy(board_0, board_backups, 256 * sizeof(int));
	return a;
}



//******************************************
//f4_function*******************************
//******************************************
//一个尽量使棋子往空隙里下的算法//快到deadline时加的函数，没时间琢磨代码重复的问题了/实际上可以避免但是改不动了。。。

int blank_power(int a[][16], int color)
{
	int single_str = 25;//在十字方向上相邻有子
	int single_obl = 30;//在叉形方向上相邻有子

	int double_str = 40;//在十字方向上相邻有一对子
	int double_obl = 45;//在十字方向上相邻有一对子

	int emmm = 0;

	memset(score_blank_power, 0, sizeof(score_blank_power));//初始化

	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			//如果是上边界的，检测周围棋子
			if (i == 0 && j != 0 && j != 15)
			{
				score_blank_power[i][j] += 2 * single_obl + single_str;

				if (a[i][j - 1] == (-1 * color) && a[i][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += double_str;
					emmm += 2;
				}

				if (a[i][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i + 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i + 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
				if (a[i + 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
			}

			//如果是下边界的，检测周围棋子
			if (i == 15 && j != 0 && j != 15)
			{
				score_blank_power[i][j] += 2 * single_obl + single_str;

				if (a[i][j - 1] == (-1 * color) && a[i][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += double_str;
					emmm += 2;
				}

				if (a[i][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i - 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i - 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
				if (a[i - 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
			}

			//如果是左边界的，检测周围棋子
			if (i != 0 && i != 15 && j == 0)
			{
				score_blank_power[i][j] += 2 * single_obl + single_str;

				if (a[i - 1][j] == (-1 * color) && a[i + 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += double_str;
					emmm += 2;
				}

				if (a[i - 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i + 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i - 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
				if (a[i + 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
			}

			//如果是右边界的，检测周围棋子
			if (i != 0 && i != 15 && j == 15)
			{
				score_blank_power[i][j] += 2 * single_obl + single_str;

				if (a[i - 1][j] == (-1 * color) && a[i + 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += double_str;
					emmm += 2;
				}

				if (a[i - 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i + 1][j] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				}
				if (a[i - 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
				if (a[i + 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				}
			}

			//如果是四角上的，检测周围棋子//按理说应该考虑四个方面，但是越界访问的话，数据也不太可能就是( -1 * color ) 
			//所以就直接与中间的判断合并了
			if (
				(i == 0 && j == 0) || (i == 0 && j == 15) || (i == 15 && j == 0) || (i == 15 && j == 15) ||
				(i != 0 && j != 0 && i != 15 && j != 15)
				)
			{
				if (a[i - 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				} // UL
				if (a[i - 1][j + 0] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				} // U_
				if (a[i - 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				} // UR
				if (a[i - 0][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				} // _L
				if (a[i - 0][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				} // _R
				if (a[i + 1][j - 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				} // DL
				if (a[i + 1][j + 0] == (-1 * color))
				{
					score_blank_power[i][j] += single_str;
					emmm += 1;
				} // D_
				if (a[i + 1][j + 1] == (-1 * color))
				{
					score_blank_power[i][j] += single_obl;
					emmm += 1;
				} // DR

				//如果是四角上的
				if ((i == 0 && j == 0) || (i == 0 && j == 15) || (i == 15 && j == 0) || (i == 15 && j == 15))
				{
					score_blank_power[i][j] += 3 * single_obl + 2 * single_str;
				}
				else
				{
					if (a[i - 1][j - 1] == (-1 * color) && a[i + 1][j + 1] == (-1 * color))
					{
						score_blank_power[i][j] += double_obl;
						emmm += 2;
					}
					if (a[i + 0][j - 1] == (-1 * color) && a[i + 0][j + 1] == (-1 * color))
					{
						score_blank_power[i][j] += double_str;
						emmm += 2;
					}
					if (a[i + 1][j + 0] == (-1 * color) && a[i - 1][j + 0] == (-1 * color))
					{
						score_blank_power[i][j] += double_str;
						emmm += 2;
					}
					if (a[i + 1][j - 1] == (-1 * color) && a[i - 1][j + 1] == (-1 * color))
					{
						score_blank_power[i][j] += double_obl; emmm += 2;
					}
				}
			}
		}
	}
	return emmm;
}



//******************************************
//f_function*******************************
//******************************************
//评估&搜索
//对局面进行评估
float evaluation(int a[][16], int color)
{
	float emmm;
	float emmm_count;
	float emmm_action;
	float rate_1, rate_2;

	/*
	float value_power_eva = 0;//当前局面符合棋格表的程度
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (a[i][j] = color)
			{
				value_power_eva += score_value[i][j];
			}
		}
	}
	value_power_eva /= count(a, color);

	*/

	if (count(a, ALL) <= 150)
	{
		emmm = rate_action_power_me_1 * action_power(a, color) - rate_action_power_opp_1 * action_power(a, -1 * color) + rate_blank_power_1 * blank_power(a, color);
	}
	else if (count(a, ALL) > 150 && count(a, ALL < 233))
	{
		rate_1 = (200 - count(a, ALL)) / 50;
		rate_2 = (count(a, ALL) - 150) / 50;
		rate_2 *= 0.85;

		emmm_count = count(a, color) - count(a, -1 * color);
		emmm_action =0.85* action_power(a, color) - action_power(a, -1 * color);
		emmm = rate_1*emmm_action + rate_2*emmm_count;
	}
	else if (count(a, ALL) >= 200)
	{
		emmm = count(a, color) - count(a, -1 * color);
	}



	return emmm;
}



float search(int a[][16], int depth, int color)
{
	float best_value = -4000;
	int t[16][16];

	memcpy(t, a, 256 * sizeof(int));
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (judge(t, i, j, color) > 0)
			{
				place(t, i, j, color);
				step[depth][0] = i;
				step[depth][1] = j;
				float value;
				if (depth <= 1) value = -evaluation(t, -1 * color);
				else value = -search(t, (depth - 1), (-1 * color));

				memcpy(t, a, 256 * sizeof(int));//undo
				if (value > best_value)
				{
					best_value = value;

					x_ai = step[depth_0][0];
					y_ai = step[depth_0][1];

				}
			}
		}
	}
	/*
	if (best_value == -4000)
	{
		if (pass)
		{
		}
		else
		{
			color *= -1;
			best_value = -search(t, depth - 1, -1 * color);
			color *= -1;
		}
	}
	*/
	return best_value;
}

void conturl()//控制深度
{
	if (count(board_0, ALL) < 100) { depth_0 = 2; }
	else if (count(board_0, ALL) >= 100 && count(board_0, ALL) < 150) { depth_0 = 3; }
	else if (count(board_0, ALL) >= 150 && count(board_0, ALL) < 200) { depth_0 = 4; }
	else if (count(board_0, ALL) >= 200) { depth_0 = 10; }
}


//******************************************
//f_ai_function*******************************
//******************************************
//FIND

void ai()
{
	x_ai = 0;
	y_ai = 0;
	conturl();
	search(board_0, depth_0, my_color);








	//原来的算法，不舍得删
	/*
get_action_power();
	blank_power(board_0 , my_color);
	memset(score, 0, sizeof(score));

	//当最后几步时采用贪心算法
	if (count(board_0, ALL) >= 233)
	{

		//获取score[][]
		for (int i = 0; i <= 15; i++)
		{
			for (int j = 0; j <= 15; j++)
			{
				//分值 = （在该点落子后的）我方吃子数 + 棋格表 + 该点对应的空白函数值
				if (judge(board_0, i, j, my_color) > 0) { score[i][j] = rate_eaten_power_1 * eaten_power(i, j) + rate_value * score_value[i][j] + rate_blank_power * score_blank_power[i][j]; }//估值函数1在这里
				else { score[i][j] = -4000; }
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
					//分值 =  棋格表 + （在该点落子后的）我方行动力 - （在该点落子后的）对方行动力 - （在该点落子后的）我方吃子数 + 该点对应的空白函数值
					score[i][j] = rate_value * score_value[i][j] + rate_action_power_me * score_action_power_me[i][j] - rate_action_power_opp *  score_action_power_opp[i][j] + rate_blank_power * score_blank_power[i][j] - rate_eaten_power_2 * eaten_power(i, j);//估值函数2在这里
				}
				else { score[i][j] = -4000; }
			}
		}
		x_ai = find(score, 1);
		y_ai = find(score, 2);
	}
	*/

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

//	int temp[16][16];
	char text_plat[20];

	scanf_s("START %d", &my_color);
	printf("OK\n");
	fflush(stdout);
	my_color = (-2 * my_color + 3);

	//若己方执白棋，则等待对方先走一步，并对棋盘做出改变;
	if (my_color == WHITE)
	{
		scanf_s("PLACE %d %d", &x_plat, &y_plat);
		place(board_0, x_plat, y_plat, BLACK);//表示在棋盘上放置对手棋子（黑棋）;
	}

	while (1)
	{
		scanf_s("%s", text_plat, 8);
		//若平台发送TURN（即我方下子）
		if (strcmp(text_plat, "TURN") == 0)
		{
			ai();
			printf("%d %d\n", x_ai, y_ai);
			//printf("DEBUG  ME %d\n", judge(board_0, x_ai, y_ai, my_color));
			//out(2);
			fflush(stdout);
			place(board_0, x_ai, y_ai, my_color);
			//out(1);
		}

		//若平台发送PLACE（即对手下子）
		else if (strcmp(text_plat, "PLACE") == 0)
		{
			scanf_s("%d %d", &x_plat, &y_plat);
			//printf("DEBUG  OPP %d\n", judge(board_0, x_plat, y_plat, (-1)*my_color));
			fflush(stdout);
			place(board_0, x_plat, y_plat, (-1)*my_color);
			//out(1);
		}

		//若平台发送END（游戏结束）
		else if (strcmp(text_plat, "END") == 0)
		{
			break;
		}
	}
	return 0;
}
