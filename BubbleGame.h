#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>

//音乐头文件
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <cstdio>

// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数


#pragma endregion


#pragma region 宏定义


#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1024		//游戏窗口宽度
#define WINDOW_HEIGHT			768			//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_2					2		//第一个游戏场景的ID
#define STAGE_3					3		//第一个游戏场景的ID
#define STAGE_4					4		//第一个游戏场景的ID
#define STAGE_HELP              10      //帮助界面的ID
#define STAGE_STOP              11      //暂停界面的ID
#define STAGE_CHOOSE            12      //选择关卡界面的ID
#define STAGE_CHOOSESKIN_1      13      //选择角色界面1的ID
#define STAGE_CHOOSESKIN_2      14      //选择角色界面2的ID
#define STAGE_MODE_CHOOSE		15      //选择模式界面的ID
#define STAGE_WIN				16		//游戏胜利界面ID
#define STAGE_LOSE				17		//游戏失败界面ID
#define STAGE_END				18		//双人模式结束界面ID


#define UNIT_SIZE_X				72		//单位的宽度
#define UNIT_SIZE_Y				90		
#define UNIT_BITMAP_SIZE_X		48		//单位在位图上的宽度
#define UNIT_BITMAP_SIZE_Y		60		
#define BUBBLE_SIZE_X			60		//泡泡
#define BUBBLE_SIZE_Y			60		
#define BOOM_SIZE_X			    64		//爆炸
#define BOOM_SIZE_Y			    64		
#define BUBBLE_BITMAP_SIZE_X	46		
#define BUBBLE_BITMAP_SIZE_Y	46		
#define BLOCK_BITMAP_SIZE_X		40		//砖块在位图上的宽度
#define BLOCK_BITMAP_SIZE_Y		40

//单位阵营定义
#define UNIT_SIDE_ME			10000	//我方
#define UNIT_SIDE_RIVAL			10001	//对手


//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击

//单位方向定义
#define UNIT_DIRECT_RIGHT		2		//向右
#define UNIT_DIRECT_LEFT		1		//向左
#define UNIT_DIRECT_UP			3		//向上
#define UNIT_DIRECT_DOWN		0		//向下

//按键定义
#define VK_W					0x57	
#define VK_S					0x53
#define VK_A					0x41
#define VK_D					0x44

//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度

//其它定义
#define BUTTON_STARTGAME			1001	//进入选择界面按钮ID
#define BUTTON_MODE_CHOOSE			1016	//选择模式按钮ID
#define BUTTON_MODE_1				1017	//单人模式按钮ID
#define BUTTON_MODE_2				1018	//双人模式按钮ID
#define BUTTON_RETURN_MENU			1019	//游戏结束界面返回菜单按钮ID
#define BUTTON_REGAME			    1020	//游戏结束界面重新游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		212		//进入选择界面按钮宽度
#define BUTTON_STARTGAME_HEIGHT		76		//进入选择界面按钮高度


#define BUTTON_HELP			    1002     //帮助按钮ID
#define BUTTON_HELP_WIDTH		120		
#define BUTTON_HELP_HEIGHT		120		

#define BUTTON_RETURN			1003	//返回主界面按钮ID
#define BUTTON_RETURN_WIDTH		120		
#define BUTTON_RETURN_HEIGHT	120	

#define BUTTON_MENU			    1004	//返回菜单按钮ID
#define BUTTON_MENU_WIDTH		400		
#define BUTTON_MENU_HEIGHT	    137	

#define BUTTON_AGAIN			1005	//重新游戏按钮ID
#define BUTTON_AGAIN_WIDTH		400		
#define BUTTON_AGAIN_HEIGHT	    136	

#define BUTTON_RETURN_GAME			1006	//重新游戏按钮ID
#define BUTTON_RETURN_GAME_WIDTH		400		
#define BUTTON_RETURN_GAME_HEIGHT	    133	

#define BUTTON_STAGE_1			1007	//进入第一关按钮ID
#define BUTTON_STAGE_2			1014	//进入第二关按钮ID
#define BUTTON_STAGE_3			1015	//进入第三关按钮ID
#define BUTTON_STAGE_4			1021	//进入第四关按钮ID
#define BUTTON_STAGE_1_WIDTH	300		
#define BUTTON_STAGE_1_HEIGHT	105	

#define BUTTON_CHOOSE_TITLE				1008	//选择界面标题
#define BUTTON_SKIN_CHOOSE_TITLE		1009	//选择界面标题
#define BUTTON_SKIN_CHOOSE_ME_1			1010	//我方皮肤1
#define BUTTON_SKIN_CHOOSE_ME_2			1011	//我方皮肤2
#define BUTTON_SKIN_CHOOSE_RIVAL_1		1012	//对手皮肤1
#define BUTTON_SKIN_CHOOSE_RIVAL_2		1013	//对手皮肤2
#define BUTTON_CHOOSE_TITLE_WIDTH	    300		
#define BUTTON_CHOOSE_TITLE_HEIGHT	    105


#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_ITEM					20		//刷新物品计时器
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度	
#define TIMER_COUNTDOWN				2		//倒计时计时器函数

#define ME                          0		//我方人物
#define RIVAL						1		//敌方人物

#define SPEED						1		//速度跑鞋
#define ADDBUBBLE					2		//弹夹增加
#define POWER						3		//力量药水
#define HEALTH						0		//生命值增加
#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};

//道具结构体
struct Item
{
	HBITMAP img;	//图片

	int item_ID;	//道具ID
	int x;			//坐标x
	int y;			//坐标y
};

// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// 单位结构体
struct Unit
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int state;		//单位状态
	int direction;	//单位方向
	int bubblenum;	//持有的泡泡数
	int bubble_range = 2;					//泡泡爆炸半径

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值
	bool wudi = FALSE;		//无敌状态
};

struct Boom
{
	HBITMAP img;						//图片

	int x;								//坐标x
	int y;								//坐标y
	int count_down_duration;			//爆炸持续时长
	int range;							//爆炸半径
	int timer_id;						//定时器id
	int frame_id;
	int frame_colume;
};

struct Bubble
{
	HBITMAP img;						//图片

	int x;								//坐标x
	int y;								//坐标y
	int owner;							//由谁放置的
	int count_down_duration;			//爆炸时长
	int range;							//爆炸半径
	int timer_id;						//定时器id
	int frame_id;
	int frame_colume;
};

//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

//倒计时函数
void CountDown(HWND hWnd, WPARAM wParam);

//绘制倒计时
void DrawCountDown(HWND hWnd);

//退出游戏删除对应内容函数
void DeleteItem(HWND hWnd);

//地图复制函数
void Copymap(int map[][16]);
#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加单位函数
Unit* CreateUnit(int side, int x, int y, int health);




// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);

//单位行为函数
void UnitBehaviour_Me(HWND hWnd);
void UnitBehaviour_Rival(HWND hWnd);
void UnitBehaviour_Rival_2(HWND hWnd);
void PlaceBubble(HWND hWnd, Unit* unit);
void UpdateBubbles(HWND hWnd);
void UpdateBoom(HWND hWnd);
void BubbleBoom(HWND hWnd, WPARAM wParam);
void Boomtimer(HWND hWnd, WPARAM wParam);
void Changeblock(Boom* boom);
void ConnectBoom(HWND hWnd, Boom* boom);
void Boomunit(HWND hWnd, Boom* boom);
void EndWudi(HWND hWnd, WPARAM wParam);
void PlaceItem(HWND hWnd);
void Itemhave(HWND hWnd);

//TODO: 添加游戏需要的更多函数
#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion