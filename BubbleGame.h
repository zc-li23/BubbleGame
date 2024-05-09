#pragma once

#pragma region ͷ�ļ�����

// Windows ͷ�ļ�: 
#include <windows.h>

//����ͷ�ļ�
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <cstdio>

// ��Դͷ�ļ�
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//ͼ����ĺ����ӿڣ����磺͸��ɫ��λͼ�Ļ���TransparentBlt����


#pragma endregion


#pragma region �궨��


#define WINDOW_TITLEBARHEIGHT	32			//�������߶�
#define WINDOW_WIDTH			1024		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			768			//��Ϸ���ڸ߶�


#define STAGE_STARTMENU			0		//��ʼ�����ID
#define STAGE_1					1		//��һ����Ϸ������ID
#define STAGE_2					2		//��һ����Ϸ������ID
#define STAGE_3					3		//��һ����Ϸ������ID
#define STAGE_4					4		//��һ����Ϸ������ID
#define STAGE_HELP              10      //���������ID
#define STAGE_STOP              11      //��ͣ�����ID
#define STAGE_CHOOSE            12      //ѡ��ؿ������ID
#define STAGE_CHOOSESKIN_1      13      //ѡ���ɫ����1��ID
#define STAGE_CHOOSESKIN_2      14      //ѡ���ɫ����2��ID
#define STAGE_MODE_CHOOSE		15      //ѡ��ģʽ�����ID
#define STAGE_WIN				16		//��Ϸʤ������ID
#define STAGE_LOSE				17		//��Ϸʧ�ܽ���ID
#define STAGE_END				18		//˫��ģʽ��������ID


#define UNIT_SIZE_X				72		//��λ�Ŀ��
#define UNIT_SIZE_Y				90		
#define UNIT_BITMAP_SIZE_X		48		//��λ��λͼ�ϵĿ��
#define UNIT_BITMAP_SIZE_Y		60		
#define BUBBLE_SIZE_X			60		//����
#define BUBBLE_SIZE_Y			60		
#define BOOM_SIZE_X			    64		//��ը
#define BOOM_SIZE_Y			    64		
#define BUBBLE_BITMAP_SIZE_X	46		
#define BUBBLE_BITMAP_SIZE_Y	46		
#define BLOCK_BITMAP_SIZE_X		40		//ש����λͼ�ϵĿ��
#define BLOCK_BITMAP_SIZE_Y		40

//��λ��Ӫ����
#define UNIT_SIDE_ME			10000	//�ҷ�
#define UNIT_SIDE_RIVAL			10001	//����


//��λ״̬����
#define UNIT_STATE_HOLD			0		//��ֹ
#define UNIT_STATE_WALK			1		//����
#define UNIT_STATE_ATTACK		2		//����

//��λ������
#define UNIT_DIRECT_RIGHT		2		//����
#define UNIT_DIRECT_LEFT		1		//����
#define UNIT_DIRECT_UP			3		//����
#define UNIT_DIRECT_DOWN		0		//����

//��������
#define VK_W					0x57	
#define VK_S					0x53
#define VK_A					0x41
#define VK_D					0x44

//����
#define BG_SRC_COUNT			6		//������Դ����
#define BG_COLUMNS				16		//��������
#define BG_ROWS					12		//��������
#define BG_ROWS_SKY				3		//�����������
#define BG_ROWS_LAND			9		//������������
#define BG_CELL_WIDTH			64		//����������
#define BG_CELL_HEIGHT			64		//��������߶�

//��������
#define BUTTON_STARTGAME			1001	//����ѡ����水ťID
#define BUTTON_MODE_CHOOSE			1016	//ѡ��ģʽ��ťID
#define BUTTON_MODE_1				1017	//����ģʽ��ťID
#define BUTTON_MODE_2				1018	//˫��ģʽ��ťID
#define BUTTON_RETURN_MENU			1019	//��Ϸ�������淵�ز˵���ťID
#define BUTTON_REGAME			    1020	//��Ϸ��������������Ϸ��ťID
#define BUTTON_STARTGAME_WIDTH		212		//����ѡ����水ť���
#define BUTTON_STARTGAME_HEIGHT		76		//����ѡ����水ť�߶�


#define BUTTON_HELP			    1002     //������ťID
#define BUTTON_HELP_WIDTH		120		
#define BUTTON_HELP_HEIGHT		120		

#define BUTTON_RETURN			1003	//���������水ťID
#define BUTTON_RETURN_WIDTH		120		
#define BUTTON_RETURN_HEIGHT	120	

#define BUTTON_MENU			    1004	//���ز˵���ťID
#define BUTTON_MENU_WIDTH		400		
#define BUTTON_MENU_HEIGHT	    137	

#define BUTTON_AGAIN			1005	//������Ϸ��ťID
#define BUTTON_AGAIN_WIDTH		400		
#define BUTTON_AGAIN_HEIGHT	    136	

#define BUTTON_RETURN_GAME			1006	//������Ϸ��ťID
#define BUTTON_RETURN_GAME_WIDTH		400		
#define BUTTON_RETURN_GAME_HEIGHT	    133	

#define BUTTON_STAGE_1			1007	//�����һ�ذ�ťID
#define BUTTON_STAGE_2			1014	//����ڶ��ذ�ťID
#define BUTTON_STAGE_3			1015	//��������ذ�ťID
#define BUTTON_STAGE_4			1021	//������Ĺذ�ťID
#define BUTTON_STAGE_1_WIDTH	300		
#define BUTTON_STAGE_1_HEIGHT	105	

#define BUTTON_CHOOSE_TITLE				1008	//ѡ��������
#define BUTTON_SKIN_CHOOSE_TITLE		1009	//ѡ��������
#define BUTTON_SKIN_CHOOSE_ME_1			1010	//�ҷ�Ƥ��1
#define BUTTON_SKIN_CHOOSE_ME_2			1011	//�ҷ�Ƥ��2
#define BUTTON_SKIN_CHOOSE_RIVAL_1		1012	//����Ƥ��1
#define BUTTON_SKIN_CHOOSE_RIVAL_2		1013	//����Ƥ��2
#define BUTTON_CHOOSE_TITLE_WIDTH	    300		
#define BUTTON_CHOOSE_TITLE_HEIGHT	    105


#define TIMER_GAMETIMER				1		//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_ITEM					20		//ˢ����Ʒ��ʱ��
#define TIMER_GAMETIMER_ELAPSE		30		//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����
#define UNIT_SPEED					3.0		//��λ�����ٶ�	
#define TIMER_COUNTDOWN				2		//����ʱ��ʱ������

#define ME                          0		//�ҷ�����
#define RIVAL						1		//�з�����

#define SPEED						1		//�ٶ���Ь
#define ADDBUBBLE					2		//��������
#define POWER						3		//����ҩˮ
#define HEALTH						0		//����ֵ����
#pragma endregion


#pragma region �ṹ������

// �����ṹ��
struct Stage
{
	int stageID;		//�������
	HBITMAP bg;			//����ͼƬ
	int timeCountDown;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��

};

//���߽ṹ��
struct Item
{
	HBITMAP img;	//ͼƬ

	int item_ID;	//����ID
	int x;			//����x
	int y;			//����y
};

// ��ť�ṹ��
struct Button
{
	int buttonID;	//��ť���
	bool visible;	//��ť�Ƿ�ɼ�
	HBITMAP img;	//ͼƬ
	int x;			//����x
	int y;			//����y
	int width;		//���
	int height;		//�߶�
};

// ��λ�ṹ��
struct Unit
{
	HBITMAP img;	//ͼƬ

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;		//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ���


	int side;		//��λ��Ӫ
	int state;		//��λ״̬
	int direction;	//��λ����
	int bubblenum;	//���е�������
	int bubble_range = 2;					//���ݱ�ը�뾶

	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ
	bool wudi = FALSE;		//�޵�״̬
};

struct Boom
{
	HBITMAP img;						//ͼƬ

	int x;								//����x
	int y;								//����y
	int count_down_duration;			//��ը����ʱ��
	int range;							//��ը�뾶
	int timer_id;						//��ʱ��id
	int frame_id;
	int frame_colume;
};

struct Bubble
{
	HBITMAP img;						//ͼƬ

	int x;								//����x
	int y;								//����y
	int owner;							//��˭���õ�
	int count_down_duration;			//��ըʱ��
	int range;							//��ը�뾶
	int timer_id;						//��ʱ��id
	int frame_id;
	int frame_colume;
};

//TODO: �����Ϸ��Ҫ�ĸ��������ݣ����ש��ȣ�


#pragma endregion


#pragma region �¼�����������


// ��ʼ����Ϸ���庯��
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ���̰����¼�������
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����ɿ��¼�������
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ����ƶ��¼�������
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����������¼�������
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

//����ʱ����
void CountDown(HWND hWnd, WPARAM wParam);

//���Ƶ���ʱ
void DrawCountDown(HWND hWnd);

//�˳���Ϸɾ����Ӧ���ݺ���
void DeleteItem(HWND hWnd);

//��ͼ���ƺ���
void Copymap(int map[][16]);
#pragma endregion


#pragma region ������Ϸ״̬����������

// ��Ӱ�ť����
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// ��ӵ�λ����
Unit* CreateUnit(int side, int x, int y, int health);




// ��ʼ����������
void InitStage(HWND hWnd, int stageID);

// ˢ�µ�λ״̬����
void UpdateUnits(HWND hWnd);

//��λ��Ϊ����
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

//TODO: �����Ϸ��Ҫ�ĸ��ຯ��
#pragma endregion 


#pragma region ��ͼ��������

// ��ͼ����
void Paint(HWND hWnd);

// ��ʼ����������
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion