// BubbleGame.cpp : 定义应用程序的入口点。
//

//#include "stdafx.h"
#include "BubbleGame.h"
using namespace std;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

HBITMAP bmp_Grass;			//背景图像资源
HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_Unit_Me_1;
HBITMAP bmp_Unit_Rival_1;
HBITMAP bmp_Unit_Me_2;
HBITMAP bmp_Unit_Rival_2;
HBITMAP bmp_Unit_Me;
HBITMAP bmp_Unit_Rival;
HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_Bubble;			//泡泡图像资源
HBITMAP bmp_health;			//血量图像资源
HBITMAP bmp_block;			//地图砖块图像
HBITMAP bmp_block_2;		//地图砖块图像2
HBITMAP bmp_block_3;		//地图砖块图像3
HBITMAP bmp_help;           //帮助按钮资源
HBITMAP bmp_title;          //标题资源
HBITMAP bmp_return;         //返回主页面图像
HBITMAP bmp_menu;           //返回主页面图像2
HBITMAP bmp_again;          //重新游戏按钮
HBITMAP bmp_return_game;    //返回游戏按钮
HBITMAP bmp_boom;           //炸弹爆炸资源
HBITMAP bmp_choose;         //选择背景图像
HBITMAP bmp_stage_1;        //第一关按钮
HBITMAP bmp_stage_2;        //第二关按钮
HBITMAP bmp_stage_3;        //第三关按钮
HBITMAP bmp_stage_4;        //第四关按钮
HBITMAP bmp_choose_title;	//选择关卡界面标题
HBITMAP bmp_skin_choose_title;//选择皮肤关卡界面标题
HBITMAP bmp_skin_me_1;		//我方皮肤按钮1
HBITMAP bmp_skin_me_2;		//我方皮肤按钮2
HBITMAP bmp_skin_rival_1;	//敌方皮肤按钮1
HBITMAP bmp_skin_rival_2;	//敌方皮肤按钮2
HBITMAP bmp_mode_choose;	//模式选择按钮图像
HBITMAP bmp_mode_1;			//单人模式按钮图像
HBITMAP bmp_mode_2;			//双人模式按钮图像
HBITMAP bmp_return_menu;	//返回首页按钮图像
HBITMAP bmp_regame;			//重新游戏按钮图像
HBITMAP bmp_lose;			//游戏失败图像
HBITMAP bmp_win;			//游戏胜利图像
HBITMAP bmp_end;			//双人游戏结束图像
HBITMAP bmp_wudi;			//无敌状态翅膀图像
HBITMAP bmp_addbubble;		//添加泡泡道具图像
HBITMAP bmp_power;			//力量药水图像
HBITMAP bmp_speed;			//速度鞋图像
HBITMAP bmp_help_stage;		//帮助界面图像	



Stage* currentStage = NULL; //当前场景状态
vector<Unit*> units;		//单位
vector<Button*> buttons;	//按钮	
vector<Bubble*> bubbles;	//泡泡
vector<Boom*> booms;        //爆炸
vector<Item*> items;		//道具
int next_bubble_timer_id = 1001;		//下一个泡泡的计时器id
int net_boom_timer_id = 6001;           //下一个爆炸的计时器id
int STAGE_NOW;              //当前关卡
int stop_time;				//暂停时间
int mode = 1;				//当前模式:1为单人，2为双人

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyWDown = false;
bool keySDown = false;
bool keyADown = false;
bool keyDDown = false;
bool keyESC = false;
bool giveitem = false;


//帧
int FRAMES_HOLD[] = { 0 };
int FRAMES_HOLD_COUNT = sizeof(FRAMES_HOLD) / sizeof(int);
int FRAMES_WALK[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, };
int FRAMES_WALK_COUNT = sizeof(FRAMES_WALK) / sizeof(int);
int FRAMES_BUBBLE[] = { 0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5, };
int FRAMES_BUBBLE_COUNT = sizeof(FRAMES_BUBBLE) / sizeof(int);
int FRAMES_BOOM[] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };
int FRAMES_BOOM_COUNT = sizeof(FRAMES_BOOM) / sizeof(int);

//地图
int map[][16] = 
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
};
int map1[][16] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
	{2,3,3,0,0,0,3,3,3,3,0,0,0,3,3,2,},
	{2,3,0,0,0,0,0,0,0,0,0,0,0,0,3,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,0,0,0,0,0,1,1,1,1,0,0,0,0,0,2,},
	{2,2,2,0,0,0,1,1,1,1,0,0,0,2,2,2,},
	{2,2,2,0,0,0,1,1,1,1,0,0,0,2,2,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,3,0,0,0,0,3,3,3,3,0,0,0,0,3,2,},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
};
int map2[][16] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
	{2,3,1,0,0,0,0,1,1,0,0,0,0,1,3,2,},
	{2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,0,0,0,0,1,0,0,0,0,1,0,0,0,0,2,},
	{2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,},
	{2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,},
	{2,0,0,0,0,1,0,0,0,0,1,0,0,0,0,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,},
	{2,3,1,0,0,0,0,1,1,0,0,0,0,1,3,2,},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
};
int map3[][16] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
	{2,3,3,1,0,0,0,1,1,0,0,0,1,3,3,2,},
	{2,3,1,0,0,0,0,1,1,0,0,0,0,1,3,2,},
	{2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,0,0,1,0,0,0,2,2,0,0,0,1,0,0,2,},
	{2,0,0,1,0,0,0,2,2,0,0,0,1,0,0,2,},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
	{2,1,0,0,1,1,0,0,0,0,1,1,0,0,1,2,},
	{2,3,1,0,0,0,0,1,1,0,0,0,0,1,3,2,},
	{2,3,3,1,0,0,0,1,1,0,0,0,1,3,3,2,},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
};
int map4[][16] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
	{2,3,3,1,0,1,3,1,1,0,0,0,1,3,3,2,},
	{2,3,1,0,0,2,0,0,1,0,0,2,0,1,3,2,},
	{2,1,0,0,1,0,2,0,0,2,0,0,0,0,1,2,},
	{2,1,0,1,0,1,0,1,0,2,0,0,0,3,0,2,},
	{2,0,1,0,2,0,0,2,2,0,0,2,1,0,0,2,},
	{2,1,0,1,0,1,0,2,2,0,0,0,1,0,0,2,},
	{2,0,0,0,1,0,0,0,0,0,0,3,0,3,0,2,},
	{2,1,0,1,0,1,0,1,0,1,0,0,0,0,1,2,},
	{2,3,0,2,0,0,0,2,0,2,0,2,0,1,3,2,},
	{2,3,3,1,0,1,0,1,0,1,0,0,1,3,3,2,},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
};
int map_now[12][16];

// TODO: 在此添加其它全局变量

double const PI = acos(double(-1));



// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BUBBLEGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BUBBLEGAME));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//  函数: MyRegisterClass()
//  目的: 注册窗口类。
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TITLEBAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BUBBLEGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TITLEBAR));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowW(szWindowClass, szTitle, 
	   WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
	   CW_USEDEFAULT,
	   CW_USEDEFAULT,
	   WINDOW_WIDTH,
	   WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // 初始化游戏窗体
        InitGame(hWnd, wParam, lParam);
        break;
    case WM_KEYDOWN:
        // 键盘按下事件
        KeyDown(hWnd, wParam, lParam);
        break;
    case WM_KEYUP:
        // 键盘松开事件
        KeyUp(hWnd, wParam, lParam);
        break;
    case WM_MOUSEMOVE:
        // 鼠标移动事件
        MouseMove(hWnd, wParam, lParam);
        break;
    case WM_LBUTTONDOWN:
        // 鼠标左键按下事件
        LButtonDown(hWnd, wParam, lParam);
        break;
    case WM_LBUTTONUP:
        // 鼠标左键松开事件
        LButtonUp(hWnd, wParam, lParam);
        break;
    case WM_TIMER:
        // 定时器事件
		EndWudi(hWnd, wParam);
        if (currentStage != NULL && currentStage->timerOn && wParam == 1) TimerUpdate(hWnd, wParam, lParam);
		if (wParam == TIMER_ITEM) giveitem = FALSE;
		BubbleBoom(hWnd,wParam);
		Boomtimer(hWnd, wParam);
		CountDown(hWnd, wParam);
        break;
    case WM_PAINT:
        // 绘图
        Paint(hWnd);
		DrawCountDown(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_Grass = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GRASS));
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_START));
	bmp_Unit_Me_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ME));
	bmp_Unit_Rival_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RIVAL));
	bmp_Unit_Me_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ME_2));
	bmp_Unit_Rival_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RIVAL_2));
	bmp_Bubble = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUBBLE));
	bmp_block = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BLOCK));
	bmp_block_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BLOCK_2));
	bmp_block_3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BLOCK_3));
	bmp_help = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HELP));
	bmp_title = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_TITLE));
	bmp_return = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RETURN));
	bmp_menu = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MENU));
	bmp_again = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_AGAIN));
	bmp_return_game = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RETURN_GAME));
	bmp_boom = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BOOM));
	bmp_choose = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_CHOOSE));
	bmp_stage_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_STAGE_1));
	bmp_stage_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_STAGE_2));
	bmp_stage_3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_STAGE_3));
	bmp_stage_4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_STAGE_4));
	bmp_choose_title = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_CHOOSE_TITLE));
	bmp_skin_choose_title = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_SKIN_CHOOSE_TITLE));
	bmp_skin_me_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ME_SKIN_1));
	bmp_skin_me_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ME_SKIN_2));
	bmp_skin_rival_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RIVAL_SKIN_1));
	bmp_skin_rival_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RIVAL_SKIN_2));
	bmp_mode_choose = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MODE_CHOOSE));
	bmp_mode_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MODE_1));
	bmp_mode_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MODE_2));
	bmp_end = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_END));
	bmp_lose = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_LOSE));
	bmp_win = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WIN));
	bmp_return_menu = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RETURN_MENU));
	bmp_regame = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_REGAME));
	bmp_wudi = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WUDI));
	bmp_health = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HEALTH));
	bmp_addbubble = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ADDBUBBLE));
	bmp_speed = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_SPEED));
	bmp_power = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_POWER));
	bmp_help_stage = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HELP_STAGE));
	bmp_return_game = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RETURN_GAME));
	bmp_return_game = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_RETURN_GAME));
	
	//添加按钮

	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2);
	buttons.push_back(startButton);
	Button* helpButton = CreateButton(BUTTON_HELP, bmp_help, BUTTON_HELP_WIDTH, BUTTON_HELP_HEIGHT,
		1024- BUTTON_HELP_WIDTH, 0);
	buttons.push_back(helpButton);
	Button* returnButton = CreateButton(BUTTON_RETURN, bmp_return, BUTTON_RETURN_WIDTH, BUTTON_RETURN_HEIGHT,
		0, 0);
	buttons.push_back(returnButton);
	Button* menuButton = CreateButton(BUTTON_MENU, bmp_menu, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT,
		(WINDOW_WIDTH - BUTTON_MENU_WIDTH) / 2-14, 150);
	buttons.push_back(menuButton);
	Button* againButton = CreateButton(BUTTON_AGAIN, bmp_again, BUTTON_AGAIN_WIDTH, BUTTON_AGAIN_HEIGHT,
		(WINDOW_WIDTH - BUTTON_AGAIN_WIDTH) / 2 -10, 300);
	buttons.push_back(againButton);
	Button* returngameButton = CreateButton(BUTTON_RETURN_GAME, bmp_return_game, BUTTON_RETURN_GAME_WIDTH, BUTTON_RETURN_GAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RETURN_GAME_WIDTH) / 2 - 8, 450);
	buttons.push_back(returngameButton);
	Button* stage1Button = CreateButton(BUTTON_STAGE_1, bmp_stage_1, BUTTON_STAGE_1_WIDTH, BUTTON_STAGE_1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STAGE_1_WIDTH) / 4 , 200);
	buttons.push_back(stage1Button);
	Button* stage2Button = CreateButton(BUTTON_STAGE_2, bmp_stage_2, BUTTON_STAGE_1_WIDTH, BUTTON_STAGE_1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STAGE_1_WIDTH) / 4 * 3, 200);
	buttons.push_back(stage2Button);
	Button* stage4Button = CreateButton(BUTTON_STAGE_4, bmp_stage_4, BUTTON_STAGE_1_WIDTH, BUTTON_STAGE_1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STAGE_1_WIDTH) / 4 * 3, 400);
	buttons.push_back(stage4Button);
	Button* stage3Button = CreateButton(BUTTON_STAGE_3, bmp_stage_3, BUTTON_STAGE_1_WIDTH, BUTTON_STAGE_1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STAGE_1_WIDTH) / 4, 400);
	buttons.push_back(stage3Button);
	Button* choosetitle_Button = CreateButton(BUTTON_CHOOSE_TITLE, bmp_choose_title, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 2, 20);
	buttons.push_back(choosetitle_Button);
	Button* chooseskintitle_Button = CreateButton(BUTTON_SKIN_CHOOSE_TITLE, bmp_skin_choose_title, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 2, 20);
	buttons.push_back(chooseskintitle_Button);
	Button* meskin1_Button = CreateButton(BUTTON_SKIN_CHOOSE_ME_1, bmp_skin_me_1, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 4, 200);
	buttons.push_back(meskin1_Button);
	Button* meskin2_Button = CreateButton(BUTTON_SKIN_CHOOSE_ME_2, bmp_skin_me_2, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 4*3, 200);
	buttons.push_back(meskin2_Button);
	Button* rivalskin1_Button = CreateButton(BUTTON_SKIN_CHOOSE_RIVAL_1, bmp_skin_rival_1, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 4, 400);
	buttons.push_back(rivalskin1_Button);
	Button* rivalskin2_Button = CreateButton(BUTTON_SKIN_CHOOSE_RIVAL_2, bmp_skin_rival_2, BUTTON_CHOOSE_TITLE_WIDTH, BUTTON_CHOOSE_TITLE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CHOOSE_TITLE_WIDTH) / 4 * 3, 400);
	buttons.push_back(rivalskin2_Button);
	Button* modechooseButton = CreateButton(BUTTON_MODE_CHOOSE, bmp_mode_choose, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, BUTTON_STARTGAME_HEIGHT+50);
	buttons.push_back(modechooseButton);
	Button* mode1Button = CreateButton(BUTTON_MODE_1, bmp_mode_1, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 4, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2-100);
	buttons.push_back(mode1Button);
	Button* mode2Button = CreateButton(BUTTON_MODE_2, bmp_mode_2, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 4 * 3, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2-100);
	buttons.push_back(mode2Button);
	Button* regameButton = CreateButton(BUTTON_REGAME, bmp_regame, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2-30);
	buttons.push_back(regameButton);
	Button* returnmenuButton = CreateButton(BUTTON_RETURN_MENU, bmp_return_menu, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2+60);
	buttons.push_back(returnmenuButton);

	//初始化背景
	bmp_Background = InitBackGround(hWnd, bmp_Grass);


	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_W:
		keyWDown = true;
		break;
	case VK_A:
		keyADown = true;
		break;
	case VK_S:
		keySDown = true;
		break;
	case VK_D:
		keyDDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_RETURN:
		if (units[0]->bubblenum > 0 && mode == 2)
			PlaceBubble(hWnd, units[0]);		//默认第0个人是自己
		break;
	case VK_SPACE:
		if (units[0]->bubblenum > 0 && mode == 1)
			PlaceBubble(hWnd, units[0]);
		if (units[1]->bubblenum > 0 && mode == 2)
			PlaceBubble(hWnd, units[1]);
		break;
	case VK_ESCAPE:
		if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_4)
		{
			stop_time = currentStage->timeCountDown;
			InitStage(hWnd, STAGE_STOP);
		}
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_W:
		keyWDown = false;
		break;
	case VK_A:
		keyADown = false;
		break;
	case VK_S:
		keySDown = false;
		break;
	case VK_D:
		keyDDown = false;
		break;
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID)
				{
				case BUTTON_STARTGAME:
				{
					InitStage(hWnd, STAGE_MODE_CHOOSE);
					break;
				}
				case BUTTON_MODE_1:
				{
					mode = 1;
					InitStage(hWnd, STAGE_CHOOSESKIN_1);
					break;
				}
				case BUTTON_MODE_2:
				{
					mode = 2;
					InitStage(hWnd, STAGE_CHOOSESKIN_1);
					break;
				}
				case BUTTON_SKIN_CHOOSE_ME_1:
				{
					bmp_Unit_Me = bmp_Unit_Me_1;
					InitStage(hWnd, STAGE_CHOOSESKIN_2);
					break;
				}
				case BUTTON_SKIN_CHOOSE_ME_2:
				{
					bmp_Unit_Me = bmp_Unit_Me_2;
					InitStage(hWnd, STAGE_CHOOSESKIN_2);
					break;
				}
				case BUTTON_SKIN_CHOOSE_RIVAL_1:
				{
					bmp_Unit_Rival = bmp_Unit_Rival_1;
					InitStage(hWnd, STAGE_CHOOSE);
					break;
				}
				case BUTTON_SKIN_CHOOSE_RIVAL_2:
				{
					bmp_Unit_Rival = bmp_Unit_Rival_2;
					InitStage(hWnd, STAGE_CHOOSE);
					break;
				}
				case BUTTON_RETURN:
				{
					DeleteItem(hWnd);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_MENU:
				{
					DeleteItem(hWnd);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_RETURN_MENU:
				{
					DeleteItem(hWnd);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_STAGE_1:
				{
					SetTimer(hWnd, TIMER_COUNTDOWN, 1000, NULL);
					STAGE_NOW = STAGE_1;
					Copymap(map1);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_NOW);
					break;
				}

				case BUTTON_STAGE_2:
				{
					SetTimer(hWnd, TIMER_COUNTDOWN, 1000, NULL);
					STAGE_NOW = STAGE_2;
					Copymap(map2);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_NOW);
					break;
				}
				case BUTTON_STAGE_3:
				{
					SetTimer(hWnd, TIMER_COUNTDOWN, 1000, NULL);
					STAGE_NOW = STAGE_3;
					Copymap(map3);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_NOW);
					break;
				}
				case BUTTON_STAGE_4:
				{
					SetTimer(hWnd, TIMER_COUNTDOWN, 1000, NULL);
					STAGE_NOW = STAGE_4;
					Copymap(map4);
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_NOW);
					break;
				}
				case BUTTON_AGAIN:
				{
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					switch (STAGE_NOW)
					{
					case STAGE_1: {Copymap(map1); break; }
					case STAGE_2: {Copymap(map2); break; }
					case STAGE_3: {Copymap(map3); break; }
					case STAGE_4: {Copymap(map4); break; }
					}
					DeleteItem(hWnd);
					InitStage(hWnd, STAGE_NOW);
					break;
				}
				case BUTTON_HELP:
				{
					InitStage(hWnd, STAGE_HELP);
					break;
				}
				case BUTTON_RETURN_GAME:
				{
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					InitStage(hWnd, STAGE_NOW);
					currentStage->timeCountDown = stop_time;
					break;
				}
				case BUTTON_REGAME:
				{
					PlaySound(MAKEINTRESOURCE(IDR_TOUCH), NULL, SND_RESOURCE | SND_SYNC);
					DeleteItem(hWnd);
					switch (STAGE_NOW)
					{
					case STAGE_1: {Copymap(map1); break; }
					case STAGE_2: {Copymap(map2); break; }
					case STAGE_3: {Copymap(map3); break; }
					case STAGE_4: {Copymap(map4); break; }
					}
					InitStage(hWnd, STAGE_NOW);
					break;
				}
				}
			}
		}
	}

}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	UpdateUnits(hWnd);

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}

//退出游戏删除对应内容函数
void DeleteItem(HWND hWnd)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		if (bubbles[i] != nullptr) {
			delete bubbles[i];  // 删除对象  
			bubbles[i] = nullptr;  // 避免悬挂指针  
		}
	}
	for (int i = 0; i < units.size(); i++)
	{
		if (units[i] != nullptr) {
			delete units[i];    
			units[i] = nullptr;  // 避免悬挂指针  
		}
	}
	for (int i = 0; i < booms.size(); i++)
	{
		if (booms[i] != nullptr) {
			delete booms[i];    
			booms[i] = nullptr;  // 避免悬挂指针  
		}
	}
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] != nullptr) {
			delete items[i];
			items[i] = nullptr;  // 避免悬挂指针  
		}
	}
	if(!units.empty())units.clear();
	if (!bubbles.empty())bubbles.clear();
	if (!booms.empty())booms.clear();
	if (!items.empty())items.clear();
}

//地图复制函数
void Copymap(int map[][16])
{
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 16; j++)
			map_now[i][j] = map[i][j];
	return;
}

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = false;
	return button;
}

// 添加主角函数
Unit* CreateUnit(int side, int x, int y, int health)
{
	Unit* unit = new Unit();
	unit->side = side;
	if (side == UNIT_SIDE_ME) {
		unit->img = bmp_Unit_Me;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 4;
		unit->vy = 4;
	}
	else if (side == UNIT_SIDE_RIVAL) {
		unit->img = bmp_Unit_Rival;
		unit->direction = UNIT_DIRECT_LEFT;
		if (mode == 2){unit->vx = 4;unit->vy = 4;}
		else if (mode == 1) { unit->vx = 3; unit->vy = 3; }
		if (STAGE_NOW == STAGE_4) unit->wudi = TRUE;
	}

	unit->state = UNIT_STATE_HOLD;

	unit->bubblenum = 2;

	unit->frame_row = unit->direction;
	unit->frame_column = 0;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->x = x;
	unit->y = y;

	unit->health = health;
	return unit;
}



// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) 
	{
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_CHOOSESKIN_1)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_SKIN_CHOOSE_TITLE)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_SKIN_CHOOSE_ME_1)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_SKIN_CHOOSE_ME_2)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_CHOOSESKIN_2)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_SKIN_CHOOSE_TITLE)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_SKIN_CHOOSE_RIVAL_1)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_SKIN_CHOOSE_RIVAL_2)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_MODE_CHOOSE)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_MODE_CHOOSE)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_MODE_1)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_MODE_2)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_CHOOSE)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_STAGE_1)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_STAGE_2)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_STAGE_3)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_STAGE_4)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_CHOOSE_TITLE)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_HELP)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_WIN)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		PlaySound(NULL, NULL, SND_PURGE);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_REGAME)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN_MENU)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_LOSE)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		PlaySound(NULL, NULL, SND_PURGE);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_REGAME)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN_MENU)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_END)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		PlaySound(NULL, NULL, SND_PURGE);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_REGAME)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN_MENU)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		}
	else if (stageID == STAGE_STOP)
	{
		currentStage->bg = bmp_Grass;
		currentStage->timerOn = false;
		PlaySound(NULL, NULL, SND_PURGE);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_MENU)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_AGAIN)
			{
				button->visible = true;
			}
			else if (button->buttonID == BUTTON_RETURN_GAME)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID >= STAGE_1 && stageID <= STAGE_4) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Grass;
		currentStage->timeCountDown = 100;
		currentStage->timerOn = true;
		PlaySound(NULL, NULL, SND_PURGE);
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


		// 按场景初始化单位
		switch (stageID) {
		case STAGE_1:
			PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			units.push_back(CreateUnit(UNIT_SIDE_ME, 200, 200, 1));
			if(mode==1) units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 2));
			else units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 1));
			break;
		case STAGE_2:
			PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			units.push_back(CreateUnit(UNIT_SIDE_ME, 200, 350, 1));
			if (mode == 1) units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 350, 2));
			else units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 350, 1));
			break;
		case STAGE_3:
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			units.push_back(CreateUnit(UNIT_SIDE_ME, 200, 200, 1));
			if (mode == 1) units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 2));
			else units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 1));
			break;
		case STAGE_4:
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			units.push_back(CreateUnit(UNIT_SIDE_ME, 200, 200, 1));
			if (mode == 1) units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 2));
			else units.push_back(CreateUnit(UNIT_SIDE_RIVAL, 800, 200, 1));
			break;
		default:
			break;
		}


	}

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	UnitBehaviour_Me(hWnd);
	if (mode == 1) UnitBehaviour_Rival(hWnd);
	if (mode == 2) UnitBehaviour_Rival_2(hWnd);
	UpdateBubbles(hWnd);
	UpdateBoom(hWnd);
	Itemhave(hWnd);
	if (rand()%400 == 0) PlaceItem(hWnd);
	for (int i = 0; i < units.size(); i++)
	{
		if (units[i]->health == 0)
		{
			PlaySound(MAKEINTRESOURCE(IDR_BOOM), NULL, SND_RESOURCE | SND_SYNC);
			if (i == 0 && mode == 1) InitStage(hWnd, STAGE_LOSE);
			if (i == 1 && mode == 1) InitStage(hWnd, STAGE_WIN);
			if (mode == 2) InitStage(hWnd, STAGE_END);
		}
	}
	for (int i = 0; i < booms.size(); i++)
	{
		Boomunit(hWnd, booms[i]);
	}
}


//单位行为函数
void UnitBehaviour_Me(HWND hWnd) {
	Unit* unit = units[0];
	//改变状态
	//如果键盘按下，设置状态为WALK
	if (keyLeftDown || keyUpDown || keyRightDown || keyDownDown) 
	{
		unit->state = UNIT_STATE_WALK;
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		if (keyLeftDown) {
			unit->direction = UNIT_DIRECT_LEFT;
		}
		else if (keyUpDown) {
			unit->direction = UNIT_DIRECT_UP;
		}
		else if (keyRightDown) {
			unit->direction = UNIT_DIRECT_RIGHT;
		}
		else if (keyDownDown) {
			unit->direction = UNIT_DIRECT_DOWN;
		}
		unit->frame_row = unit->direction;
	}
	else 
	{
		unit->state = UNIT_STATE_HOLD;
		unit->frame_sequence = FRAMES_HOLD;
		unit->frame_count = FRAMES_HOLD_COUNT;
	}

	//更新位置
	if (unit->state == UNIT_STATE_WALK) {
		switch (unit->direction) {
		case UNIT_DIRECT_LEFT:
			if(map_now[(unit->y+33)/64][(unit->x- 36)/64]==0)
			unit->x -= unit->vx;
			break;
		case UNIT_DIRECT_UP:
			if (map_now[(unit->y-10) / 64][unit->x/ 64] == 0)
			unit->y -= unit->vy;
			break;
		case UNIT_DIRECT_RIGHT:
			if (map_now[(unit->y+33) / 64][(unit->x + 36) / 64]==0)
			unit->x += unit->vx;
			break;
		case UNIT_DIRECT_DOWN:
			if (map_now[(unit->y+45) / 64][unit->x / 64] == 0)
			unit->y += unit->vy;
			break;
		default:
			break;
		};
	}

	//动画运行到下一帧
	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;
	unit->frame_column = unit->frame_sequence[unit->frame_id];
}
void UnitBehaviour_Rival_2(HWND hWnd) {
	Unit* unit = units[1];
	if (keyWDown || keyADown || keySDown || keyDDown)
	{
		unit->state = UNIT_STATE_WALK;
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		if (keyADown) {
			unit->direction = UNIT_DIRECT_LEFT;
		}
		else if (keyWDown) {
			unit->direction = UNIT_DIRECT_UP;
		}
		else if (keyDDown) {
			unit->direction = UNIT_DIRECT_RIGHT;
		}
		else if (keySDown) {
			unit->direction = UNIT_DIRECT_DOWN;
		}
		unit->frame_row = unit->direction;
	}
	else
	{
		unit->state = UNIT_STATE_HOLD;
		unit->frame_sequence = FRAMES_HOLD;
		unit->frame_count = FRAMES_HOLD_COUNT;
	}

	if (unit->state == UNIT_STATE_WALK) {
		switch (unit->direction) {
		case UNIT_DIRECT_LEFT:
			if (map_now[(unit->y + 33) / 64][(unit->x - 36) / 64] == 0||STAGE_NOW==STAGE_4)
				unit->x -= unit->vx;
			break;
		case UNIT_DIRECT_UP:
			if (map_now[(unit->y - 10) / 64][unit->x / 64] == 0 || STAGE_NOW == STAGE_4)
				unit->y -= unit->vy;
			break;
		case UNIT_DIRECT_RIGHT:
			if (map_now[(unit->y + 33) / 64][(unit->x + 36) / 64] == 0 || STAGE_NOW == STAGE_4)
				unit->x += unit->vx;
			break;
		case UNIT_DIRECT_DOWN:
			if (map_now[(unit->y + 45) / 64][unit->x / 64] == 0 || STAGE_NOW == STAGE_4)
				unit->y += unit->vy;
			break;
		default:
			break;
		};
	}

	//动画运行到下一帧
	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;
	unit->frame_column = unit->frame_sequence[unit->frame_id];
}

//AI行为
void UnitBehaviour_Rival(HWND hWnd) {
	Unit* me = units[0];
	Unit* rival = units[1];
	int dist_x = me->x - rival->x;
	int dist_y = me->y - rival->y;
	int dist = sqrt(dist_x * dist_x + dist_y * dist_y);

	//更新状态
	if (dist <= 20) {
		rival->state = UNIT_STATE_HOLD;
		rival->frame_sequence = FRAMES_HOLD;
		rival->frame_count = FRAMES_HOLD_COUNT;
	}
	else {
		rival->state = UNIT_STATE_WALK;
		rival->frame_sequence = FRAMES_WALK;
		rival->frame_count = FRAMES_WALK_COUNT;
		if (dist_x < -20) 		//turn left
			rival->direction = UNIT_DIRECT_LEFT;
		else if (dist_y < -20)
			rival->direction = UNIT_DIRECT_UP;
		else if (dist_x > 20)
			rival->direction = UNIT_DIRECT_RIGHT;
		else if (dist_y > 20)
			rival->direction = UNIT_DIRECT_DOWN;
		rival->frame_row = rival->direction;
	}

	//更新位置
	if (rival->state == UNIT_STATE_WALK) {
		switch (rival->direction) {
		case UNIT_DIRECT_LEFT:
			if (map_now[(rival->y + 33) / 64][(rival->x - 36) / 64] == 0||STAGE_NOW==STAGE_4)
			rival->x -= rival->vx;
			break;
		case UNIT_DIRECT_UP:
			if (map_now[(rival->y - 10) / 64][rival->x / 64] == 0 || STAGE_NOW == STAGE_4)
			rival->y -= rival->vy;
			break;
		case UNIT_DIRECT_RIGHT:
			if (map_now[(rival->y + 33) / 64][(rival->x + 36) / 64] == 0 || STAGE_NOW == STAGE_4)
			rival->x += rival->vx;
			break;
		case UNIT_DIRECT_DOWN:
			if (map_now[(rival->y + 45) / 64][rival->x / 64] == 0 || STAGE_NOW == STAGE_4)
			rival->y += rival->vy;
			break;
		default:
			break;
		};
	}

	if (STAGE_NOW!=STAGE_4&&rand() % 60 == 0 && units[1]->bubblenum > 0||
		STAGE_NOW == STAGE_4 && rand() % 40 == 0)
	{
		PlaceBubble(hWnd, rival);
	}

	//动画运行到下一帧
	rival->frame_id++;
	rival->frame_id = rival->frame_id % rival->frame_count;
	rival->frame_column = rival->frame_sequence[rival->frame_id];
}

// 放置泡泡
void PlaceBubble(HWND hWnd, Unit* unit)
{
	Bubble* newBubble = new Bubble();
	int x = unit->x;
	int y = unit->y + 0.5 * UNIT_SIZE_Y - 0.5 * BUBBLE_SIZE_Y;		//应放置在脚下
	while (map_now[(int)(BG_CELL_HEIGHT * (y / BG_CELL_HEIGHT + 0.5) / 64)][x/64] != 0) y += 32;
	newBubble->x = BG_CELL_WIDTH * (x / BG_CELL_WIDTH + 0.5);		 //把泡泡调整在格子中间
	newBubble->y = BG_CELL_HEIGHT * (y / BG_CELL_HEIGHT + 0.5);

	//若此处已有泡泡，则不创建
	bool hasBubble = false;
	int curx = newBubble->x / BG_CELL_WIDTH;
	int cury = newBubble->y / BG_CELL_HEIGHT;
	for (int i = 0; i < bubbles.size(); i++) 
	{
		if (bubbles[i]->x == newBubble->x && bubbles[i]->y == newBubble->y) {
			hasBubble = true;
			break;
		}
	}
	if (!hasBubble)
	{
		newBubble->count_down_duration = 3000;		//爆炸时长
		newBubble->range = unit->bubble_range;						//爆炸半径
		newBubble->frame_id = 0;
		newBubble->frame_colume = 0;                //

		newBubble->img = bmp_Bubble;
		newBubble->timer_id = next_bubble_timer_id;
		next_bubble_timer_id += 1;
		if (unit->side == UNIT_SIDE_ME) { newBubble->owner = ME; units[ME]->bubblenum--; }
		if (unit->side == UNIT_SIDE_RIVAL) { newBubble->owner = RIVAL; if(STAGE_NOW!=STAGE_4)units[RIVAL]->bubblenum--; }
		bubbles.push_back(newBubble);
		SetTimer(hWnd, newBubble->timer_id, newBubble->count_down_duration, NULL);
	}
	else delete newBubble;
}


// 产生道具
void PlaceItem(HWND hWnd)
{
	Item* newItem = new Item();
	int x = rand() % 700 + 100;
	int y = rand() % 500 + 50;		//应放置在脚下
	while (map_now[(int)(BG_CELL_HEIGHT * (y / BG_CELL_HEIGHT + 0.5) / 64)][x / 64] != 0) y += 32;
	newItem->x = BG_CELL_WIDTH * (x / BG_CELL_WIDTH + 0.5);		 //把泡泡调整在格子中间
	newItem->y = BG_CELL_HEIGHT * (y / BG_CELL_HEIGHT + 0.5);

	//若此处已有道具，则不创建
	bool hasItem = false;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->x == newItem->x && items[i]->y == newItem->y) {
			hasItem = true;
			break;
		}
	}
	if (!hasItem&&giveitem==FALSE)
	{
		newItem->item_ID = rand() % 4;
		switch (newItem->item_ID)
		{
		case SPEED:newItem->img = bmp_speed; break;
		case HEALTH:newItem->img = bmp_health; break;
		case POWER:newItem->img = bmp_power; break;
		case ADDBUBBLE:newItem->img = bmp_addbubble; break;
		}
		items.push_back(newItem);
		SetTimer(hWnd, 20, 1000, NULL);
		giveitem = TRUE;
	}
	else delete newItem;
}

//泡泡爆炸计时函数
void BubbleBoom(HWND hWnd, WPARAM wParam)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		Bubble* bubble = bubbles[i];
		if (wParam == bubble->timer_id)
		{
			
			Boom* boom = new Boom();
			boom->x = bubble->x;
			boom->y = bubble->y;
			boom->range = bubble->range;
			boom->frame_id = 0;
			boom->frame_colume = 0;
			boom->count_down_duration = 840;
			boom->img = bmp_boom;
			ConnectBoom(hWnd, boom);
			Changeblock(boom);
			if (!units.empty())
			{
				KillTimer(hWnd, bubble->timer_id);
				boom->timer_id = bubble->timer_id + 10000;
				booms.push_back(boom);
				SetTimer(hWnd, boom->timer_id, boom->count_down_duration, NULL);
				if(!(bubble->owner==RIVAL&&STAGE_NOW==4))
				units[bubble->owner]->bubblenum++;
				delete bubble;
				vector<Bubble*>::iterator it = bubbles.begin();
				advance(it, i);
				bubbles.erase(it);
			}
		}
	}
}

//爆炸结束计时函数
void Boomtimer(HWND hWnd, WPARAM wParam)
{
	for (int i = 0; i < booms.size(); i++)
	{
		Boom* boom = booms[i];
		if (wParam == boom->timer_id)
		{
			KillTimer(hWnd, boom->timer_id);
			delete boom;
			vector<Boom*>::iterator it = booms.begin();
			advance(it, i);
			booms.erase(it);
		}
	}
}

//倒计时函数
void CountDown(HWND hWnd, WPARAM wParam)
{
	if (wParam == TIMER_COUNTDOWN && currentStage->timerOn == TRUE)
	{
		if (currentStage->timeCountDown > 1)
		{
			currentStage->timeCountDown--;
			KillTimer(hWnd, TIMER_COUNTDOWN);
			SetTimer(hWnd, TIMER_COUNTDOWN, 1000, NULL);
		}
		else
		{
			currentStage->timerOn = FALSE;
			DeleteItem(hWnd);
			if(STAGE_NOW==STAGE_4) InitStage(hWnd, STAGE_WIN);
			else
			{
				if (mode == 1) InitStage(hWnd, STAGE_LOSE);
				else if (mode == 2) InitStage(hWnd, STAGE_END);
			}
		}
	}
}

//连锁爆炸的函数
void ConnectBoom(HWND hWnd, Boom* boom)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		Bubble* bubble = bubbles[i];
		int x1 = bubble->x,x2 = boom->x;
		int y1 = bubble->y, y2 = boom->y;
		bool up = FALSE, down = FALSE, left = FALSE, right = FALSE, boomed = FALSE;
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
				up = TRUE;
			if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 <= y2 && y1 >= y2 - (i - 0.5) * 64) && up == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
				down = TRUE;
			if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 >= y2 && y1 <= y2 + (i - 0.5) * 64) && down == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 1)
				left = TRUE;
			if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 <= x2 && x1 >= x2 - (i - 0.5) * 64) && left == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 1)
				right = TRUE;
			if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 >= x2 && x1 <= x2 + (i - 0.5) * 64) && right == FALSE) boomed = TRUE;
		}
		if (boomed == TRUE)
		{
			KillTimer(hWnd, bubble->timer_id);
			SetTimer(hWnd, bubble->timer_id, 40, NULL);
		}
	}
}

//无敌时间结束函数
void EndWudi(HWND hWnd, WPARAM wParam)
{
	if (!units.empty())
	{
		if (wParam == 10) units[0]->wudi = FALSE;
		else if (wParam == 11 && STAGE_NOW != STAGE_4) units[1]->wudi = FALSE;
	}
}

//检测炸弹炸到人的函数
void Boomunit(HWND hWnd, Boom* boom)


{
	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units[i];
		int x1 = unit->x, x2 = boom->x;
		int y1 = unit->y, y2 = boom->y;
		if (unit->wudi == FALSE)
		{
			bool up = FALSE, down = FALSE, left = FALSE, right = FALSE, boomed = FALSE;
			for (int i = 2; i <= boom->range; i++)
			{
				if (map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
					map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
					up = TRUE;
				if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 <= y2 && y1 >= y2 - (i - 0.5) * 64) && up == FALSE) boomed = TRUE;
			}
			for (int i = 2; i <= boom->range; i++)
			{
				if (map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
					map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
					down = TRUE;
				if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 >= y2 && y1 <= y2 + (i - 0.5) * 64) && down == FALSE) boomed = TRUE;
			}
			for (int i = 2; i <= boom->range; i++)
			{
				if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i- 0.5) * 64 + 30) / 64] != 0 &&
					map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 1)
					left = TRUE;
				if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 <= x2 && x1 >= x2 - (i - 0.5) * 64) && left == FALSE) boomed = TRUE;
			}
			for (int i = 2; i <= boom->range; i++)
			{
				if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 0 &&
					map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 1)
					right = TRUE;
				if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 >= x2 && x1 <= x2 + (i - 0.5) * 64) && right == FALSE) boomed = TRUE;
			}
			if(boomed==TRUE)
			{
				unit->wudi = TRUE;
				unit->health -= 1;
				SetTimer(hWnd, i + 10, 2500, NULL);
			}
		}
	}
	for (int i = 0; i < items.size(); i++)
	{
		Item* item = items[i];
		int x1 = item->x, x2 = boom->x;
		int y1 = item->y, y2 = boom->y;
		bool up = FALSE, down = FALSE, left = FALSE, right = FALSE, boomed = FALSE;
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
				up = TRUE;
			if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 <= y2 && y1 >= y2 - (i - 0.5) * 64) && up == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
				down = TRUE;
			if ((x1 >= x2 - 32 && x1 <= x2 + 32 && y1 >= y2 && y1 <= y2 + (i - 0.5) * 64) && down == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 1)
				left = TRUE;
			if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 <= x2 && x1 >= x2 - (i - 0.5) * 64) && left == FALSE) boomed = TRUE;
		}
		for (int i = 2; i <= boom->range; i++)
		{
			if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 0 &&
				map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 1)
				right = TRUE;
			if ((y1 >= y2 - 32 && y1 <= y2 + 32 && x1 >= x2 && x1 <= x2 + (i - 0.5) * 64) && right == FALSE) boomed = TRUE;
		}
		if (boomed == TRUE)
		{
			delete item;
			vector<Item*>::iterator it = items.begin();
			advance(it, i);
			items.erase(it);
		}
		
	}
}

//检测有人吃到道具函数
void Itemhave(HWND hWnd)
{
	for (int i = 0; i < units.size(); i++)
	{
		for (int j = 0; j < items.size(); j++)
		{
			Item* item = items[j];
			int x1 = units[i]->x, x2 = item->x;
			int y1 = units[i]->y + 30, y2 = item->y;
			if (x1 <= x2 + 32 && x1 >= x2 - 32 &&
				y1 <= y2 + 32 && y1 >= y2 - 32)
			{
				if (item->item_ID == SPEED)
				{
					units[i]->vx++;
					units[i]->vy++;
				}
				else if (item->item_ID == POWER)
				{
					units[i]->bubble_range++;
				}
				else if (item->item_ID == HEALTH)
				{
					units[i]->health++;
				}
				else if (item->item_ID == ADDBUBBLE)
				{
					units[i]->bubblenum++;
				}
				delete item;
				vector<Item*>::iterator it = items.begin();
				advance(it, j);
				items.erase(it);
			}
		}
	}
}

//更新爆炸的帧动画
void UpdateBoom(HWND hWnd)
{
	for (int i = 0; i < booms.size(); i++)
	{
		Boom* boom = booms[i];
		boom->frame_id = (boom->frame_id + 1) % FRAMES_BOOM_COUNT;
		boom->frame_colume = FRAMES_BOOM[boom->frame_id];
	}
}

//更新泡泡的帧动画
void UpdateBubbles(HWND hWnd)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		Bubble* bubble = bubbles[i];
		bubble->frame_id = (bubble->frame_id + 1) % FRAMES_BUBBLE_COUNT;
		bubble->frame_colume = FRAMES_BUBBLE[bubble->frame_id];
	}
}

//泡泡爆炸改变方块的函数
void Changeblock(Boom* boom)
{
	int x = boom->x, y = boom->y;
		bool up = FALSE, down = FALSE, left = FALSE, right = FALSE;
	for (int i = 1; i <= boom->range - 1; i++)
	{
		if (map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
			map_now[(int)(boom->y - (i - 0.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
			up = TRUE;
		if (map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 0 &&
			map_now[(int)(boom->y + (i - 1.5) * 64 + 30) / 64][(int)(boom->x - 0.5 * 64 + 30) / 64] != 1)
			down = TRUE;
		if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 0 &&
			map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x - (i - 0.5) * 64 + 30) / 64] != 1)
			left = TRUE;
		if (map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 0 &&
			map_now[(int)(boom->y - 0.5 * 64 + 30) / 64][(int)(boom->x + (i - 1.5) * 64 + 30) / 64] != 1)
			right = TRUE;
		if (map_now[y / 64][(x + i * 64) / 64] == 1 && right == FALSE)
			map_now[y / 64][(x + i * 64) / 64] = 0;
		if (map_now[y / 64][(x - i * 64) / 64] == 1 && left==FALSE)
			map_now[y / 64][(x - i * 64) / 64] = 0;
		if (map_now[(y - i * 64) / 64][x / 64] == 1 && up==FALSE)
			map_now[(y - i * 64) / 64][x / 64] = 0;
		if (map_now[(y + i * 64) / 64][x / 64] == 1 && down==FALSE)
			map_now[(y + i * 64) / 64][x / 64] = 0;
	}
	return;
}

// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// 绘制背景到缓存
	//SelectObject(hdc_loadBmp, currentStage->bg);
	SelectObject(hdc_loadBmp, bmp_Background);

	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU)
	{
		//绘制标题
		SelectObject(hdc_loadBmp, bmp_title);
		TransparentBlt(
			hdc_memBuffer,
			2 * BG_CELL_WIDTH, 3 * BG_CELL_HEIGHT,					// 界面上起始绘制点
			12 * BG_CELL_WIDTH, 160,					// 界面上绘制宽度高度
			hdc_loadBmp,
			0, 0,										// 位图上起始绘制点
			400, 85,								// 位图上绘制宽度高度
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_HELP) 
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_help_stage);
		TransparentBlt(
			hdc_memBuffer,
			32, 64,					// 界面上起始绘制点
			15*BG_CELL_WIDTH, 10 * BG_CELL_HEIGHT,											// 界面上绘制宽度高度
			hdc_loadBmp,
			0, 0,										// 位图上起始绘制点
			900, 600,								// 位图上绘制宽度高度
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_LOSE)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_lose);
		TransparentBlt(
			hdc_memBuffer,
			4 * BG_CELL_WIDTH, 0 * BG_CELL_HEIGHT,					// 界面上起始绘制点
			8 * BG_CELL_WIDTH, 7 * BG_CELL_HEIGHT,											// 界面上绘制宽度高度
			hdc_loadBmp,
			0, 0,										// 位图上起始绘制点
			500, 500,								// 位图上绘制宽度高度
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_WIN)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_win);
		TransparentBlt(
			hdc_memBuffer,
			4 * BG_CELL_WIDTH, 1 * BG_CELL_HEIGHT,					// 界面上起始绘制点
			8 * BG_CELL_WIDTH, 6 * BG_CELL_HEIGHT,											// 界面上绘制宽度高度
			hdc_loadBmp,
			0, 0,										// 位图上起始绘制点
			480, 360,								// 位图上绘制宽度高度
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_END)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_end);
		TransparentBlt(
			hdc_memBuffer,
			5 * BG_CELL_WIDTH, 1 * BG_CELL_HEIGHT,					// 界面上起始绘制点
			6 * BG_CELL_WIDTH, 6 * BG_CELL_HEIGHT,											// 界面上绘制宽度高度
			hdc_loadBmp,
			0, 0,										// 位图上起始绘制点
			500, 500,								// 位图上绘制宽度高度
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_MODE_CHOOSE)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block_2);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,		// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,				// 界面上绘制宽度高度
					hdc_loadBmp,
					map[i][j] * BLOCK_BITMAP_SIZE_X, 0,			// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,	// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		};
	}
	else if (currentStage->stageID == STAGE_CHOOSESKIN_1)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_Unit_Me_1);
		TransparentBlt(
			hdc_memBuffer,
			3 * BG_CELL_WIDTH, 5 * BG_CELL_HEIGHT,					
			4 * BG_CELL_WIDTH, 4 * BG_CELL_HEIGHT,											
			hdc_loadBmp,
			0, 0,										
			48, 60,								
			RGB(255, 255, 255));
		SelectObject(hdc_loadBmp, bmp_Unit_Me_2);
		TransparentBlt(
			hdc_memBuffer,
			9 * BG_CELL_WIDTH, 5 * BG_CELL_HEIGHT,					
			4 * BG_CELL_WIDTH, 4 * BG_CELL_HEIGHT,											
			hdc_loadBmp,
			0, 0,										
			48, 60,								
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_CHOOSESKIN_2)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		SelectObject(hdc_loadBmp, bmp_Unit_Rival_1);
		TransparentBlt(
			hdc_memBuffer,
			3 * BG_CELL_WIDTH, 2 * BG_CELL_HEIGHT,
			4 * BG_CELL_WIDTH, 4 * BG_CELL_HEIGHT,
			hdc_loadBmp,
			0, 0,
			48, 60,
			RGB(255, 255, 255));
		SelectObject(hdc_loadBmp, bmp_Unit_Rival_2);
		TransparentBlt(
			hdc_memBuffer,
			9 * BG_CELL_WIDTH, 2 * BG_CELL_HEIGHT,
			4 * BG_CELL_WIDTH, 4 * BG_CELL_HEIGHT,
			hdc_loadBmp,
			0, 0,
			48, 60,
			RGB(255, 255, 255));
	}
	else if (currentStage->stageID == STAGE_STOP)
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_block);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
	}
	else if (currentStage->stageID == STAGE_CHOOSE) 
	{
		//绘制背景
		for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
			for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
				SelectObject(hdc_loadBmp, bmp_choose);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					2 * BLOCK_BITMAP_SIZE_X, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
	}
	else if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_4) //TODO：添加多个游戏场景
	{
		//绘制地图
		for (int i = 0; i < sizeof(map_now) / sizeof(map_now[0]); i++) {
			for (int j = 0; j < sizeof(map_now[0]) / sizeof(map_now[0][0]); j++) {
				if (currentStage->stageID == STAGE_1) SelectObject(hdc_loadBmp, bmp_block);
				else if (currentStage->stageID == STAGE_2) SelectObject(hdc_loadBmp, bmp_block_2);
				else if (currentStage->stageID == STAGE_3) SelectObject(hdc_loadBmp, bmp_block_3);
				else if (currentStage->stageID == STAGE_4) SelectObject(hdc_loadBmp, bmp_block_3);
				TransparentBlt(
					hdc_memBuffer,
					j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,					// 界面上起始绘制点
					BG_CELL_WIDTH, BG_CELL_HEIGHT,											// 界面上绘制宽度高度
					hdc_loadBmp,
					map_now[i][j] * BLOCK_BITMAP_SIZE_X, 0,										// 位图上起始绘制点
					BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		//绘制泡泡
		for (int i = 0; i < bubbles.size(); i++)
		{
			Bubble* bubble = bubbles[i];
			SelectObject(hdc_loadBmp, bubble->img);
			TransparentBlt(
				hdc_memBuffer,
				bubble->x - 0.5 * BUBBLE_SIZE_X, bubble->y - 0.5 * BUBBLE_SIZE_Y,		// 界面上起始绘制点
				BUBBLE_SIZE_X, BUBBLE_SIZE_Y,											// 界面上绘制宽度高度
				hdc_loadBmp,
				bubble->frame_colume * BUBBLE_BITMAP_SIZE_X, 0,							// 位图上起始绘制点
				BUBBLE_BITMAP_SIZE_X, BUBBLE_BITMAP_SIZE_Y,								// 位图上绘制宽度高度
				RGB(255, 255, 255));
		}
		//绘制道具
		for (int i = 0; i < items.size(); i++)
		{
			Item* item = items[i];
			if (item->item_ID == HEALTH)
			{
				SelectObject(hdc_loadBmp, bmp_health);
				TransparentBlt(
					hdc_memBuffer,
					item->x - 20, item->y - 17,		// 界面上起始绘制点
					40, 34,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,							// 位图上起始绘制点
					40, 34,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
			else
			{
				switch (item->item_ID)
				{
				case SPEED:SelectObject(hdc_loadBmp, bmp_speed); break;
				case POWER:SelectObject(hdc_loadBmp, bmp_power); break;
				case ADDBUBBLE:SelectObject(hdc_loadBmp, bmp_addbubble); break;
				default:break;
				}
				TransparentBlt(
					hdc_memBuffer,
					item->x - 20, item->y - 20,		// 界面上起始绘制点
					40, 40,											// 界面上绘制宽度高度
					hdc_loadBmp,
					0, 0,							// 位图上起始绘制点
					50, 50,								// 位图上绘制宽度高度
					RGB(255, 255, 255));
			}
		}
		//绘制爆炸
		for (int j = 0; j < booms.size(); j++)
		{
			Boom* boom = booms[j];
			SelectObject(hdc_loadBmp, boom->img);
			bool left = TRUE, right = TRUE, up = TRUE, down = TRUE;
			for (int i = boom->range - 2; i >=1; i--)
			{
				if (map_now[(int)(boom->y - (boom->range - i - 0.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] != 0 &&
					map_now[(int)(boom->y - (boom->range - i - 0.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] != 1)
					up = FALSE;
				if (map_now[(int)(boom->y + (boom->range - i - 1.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] != 0 &&
					map_now[(int)(boom->y + (boom->range - i - 1.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] != 1)
					down = FALSE;
				if (map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x - (boom->range - i - 0.5) * BOOM_SIZE_Y + 30) / 64] != 0 &&
					map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x - (boom->range - i - 0.5) * BOOM_SIZE_Y + 30) / 64] != 1)
					left = FALSE;
				if (map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x + (boom->range - i - 1.5) * BOOM_SIZE_Y + 30) / 64] != 0 &&
					map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x + (boom->range - i - 1.5) * BOOM_SIZE_Y + 30) / 64] != 1)
					right = FALSE;
				if (up == TRUE)
					TransparentBlt(
						hdc_memBuffer,
						boom->x - 0.5 * BOOM_SIZE_X, boom->y - (boom->range - i - 0.5) * BOOM_SIZE_Y,	   // 界面上起始绘制点
						BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
						hdc_loadBmp,
						(boom->frame_colume % 2) * 40 + 120, 0,									   // 位图上起始绘制点
						40, 40,								                           // 位图上绘制宽度高度
						RGB(255, 255, 255));
				if (down == TRUE)
					TransparentBlt(
						hdc_memBuffer,
						boom->x - 0.5 * BOOM_SIZE_X, boom->y + (boom->range - i - 1.5) * BOOM_SIZE_Y,	   // 界面上起始绘制点
						BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
						hdc_loadBmp,
						(boom->frame_colume % 2) * 40 + 120, 40,								   // 位图上起始绘制点
						40, 40,								                           // 位图上绘制宽度高度
						RGB(255, 255, 255));
				if (left == TRUE)
					TransparentBlt(
						hdc_memBuffer,
						boom->x - (boom->range - i - 0.5) * BOOM_SIZE_X, boom->y - 0.5 * BOOM_SIZE_Y,	   // 界面上起始绘制点
						BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
						hdc_loadBmp,
						(boom->frame_colume % 2) * 40 + 120, 80,								   // 位图上起始绘制点
						40, 40,								                           // 位图上绘制宽度高度
						RGB(255, 255, 255));
				if (right == TRUE)
					TransparentBlt(
						hdc_memBuffer,
						boom->x + (boom->range - i - 1.5) * BOOM_SIZE_X, boom->y - 0.5 * BOOM_SIZE_Y,	   // 界面上起始绘制点
						BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
						hdc_loadBmp,
						(boom->frame_colume % 2) * 40 + 120, 120,								   // 位图上起始绘制点
						40, 40,								                           // 位图上绘制宽度高度
						RGB(255, 255, 255));
			}
			if (map_now[(int)(boom->y - (boom->range - 0.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] == 2 ||
				map_now[(int)(boom->y - (boom->range - 0.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] == 3)
				up = FALSE;
			if (map_now[(int)(boom->y + (boom->range - 1.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y + 30) / 64] == 2 ||
				map_now[(int)(boom->y + (boom->range - 1.5) * BOOM_SIZE_X + 30) / 64][(int)(boom->x - 0.5 * BOOM_SIZE_Y +30) / 64] == 3)
				down = FALSE;
			if (map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x - (boom->range - 0.5) * BOOM_SIZE_Y + 30) / 64] == 2 ||
				map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x - (boom->range - 0.5) * BOOM_SIZE_Y + 30) / 64] == 3)
				left = FALSE;
			if (map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x + (boom->range - 1.5) * BOOM_SIZE_Y + 30) / 64] == 2 ||
				map_now[(int)(boom->y - 0.5 * BOOM_SIZE_X + 30) / 64][(int)(boom->x + (boom->range - 1.5) * BOOM_SIZE_Y + 30) / 64] == 3)
				right = FALSE;
			if (up == TRUE)
				TransparentBlt(
					hdc_memBuffer,
					boom->x - 0.5 * BOOM_SIZE_X, boom->y - (boom->range - 0.5) * BOOM_SIZE_Y,	   // 界面上起始绘制点
					BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
					hdc_loadBmp,
					boom->frame_colume * 40, 0,									   // 位图上起始绘制点
					40, 40,								                           // 位图上绘制宽度高度
					RGB(255, 255, 255));
			if (down == TRUE)
				TransparentBlt(
					hdc_memBuffer,
					boom->x - 0.5 * BOOM_SIZE_X, boom->y + (boom->range - 1.5) * BOOM_SIZE_Y,	   // 界面上起始绘制点
					BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
					hdc_loadBmp,
					boom->frame_colume * 40, 40,								   // 位图上起始绘制点
					40, 40,								                           // 位图上绘制宽度高度
					RGB(255, 255, 255));
			if (left == TRUE)
				TransparentBlt(
					hdc_memBuffer,
					boom->x - (boom->range - 0.5) * BOOM_SIZE_X, boom->y - 0.5 * BOOM_SIZE_Y,	   // 界面上起始绘制点
					BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
					hdc_loadBmp,
					boom->frame_colume * 40, 80,								   // 位图上起始绘制点
					40, 40,								                           // 位图上绘制宽度高度
					RGB(255, 255, 255));
			if (right == TRUE)
				TransparentBlt(
					hdc_memBuffer,
					boom->x + (boom->range - 1.5) * BOOM_SIZE_X, boom->y - 0.5 * BOOM_SIZE_Y,	   // 界面上起始绘制点
					BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
					hdc_loadBmp,
					boom->frame_colume * 40, 120,								   // 位图上起始绘制点
					40, 40,								                           // 位图上绘制宽度高度
					RGB(255, 255, 255));
			TransparentBlt(
				hdc_memBuffer,
				boom->x - 0.5 * BOOM_SIZE_X, boom->y - 0.5 * BOOM_SIZE_Y,	   // 界面上起始绘制点
				BOOM_SIZE_X, BOOM_SIZE_Y,									   // 界面上绘制宽度高度
				hdc_loadBmp,
				(boom->frame_colume / 4) * 40, 160,								   // 位图上起始绘制点
				40, 40,								                           // 位图上绘制宽度高度
				RGB(255, 255, 255));
		}
		//绘制人物血量与弹药量
		for (int i = 0; i < units.size(); i++)
		{
			Unit* unit = units[i];
			if (i == 0)
			{
				for (int j = 0; j < unit->health; j++)
				{
					SelectObject(hdc_loadBmp, bmp_health);
					TransparentBlt(
						hdc_memBuffer,
						50 * j, 0,			// 界面上起始绘制点
						40, 34,											// 界面上绘制宽度高度
						hdc_loadBmp,
						0, 0,	// 位图上起始绘制点
						40, 34,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
				for (int j = 0; j < unit->bubblenum; j++)
				{
					SelectObject(hdc_loadBmp, bmp_Bubble);
					TransparentBlt(
						hdc_memBuffer,
						50 * j, 40,			// 界面上起始绘制点
						46, 40,											// 界面上绘制宽度高度
						hdc_loadBmp,
						0, 0,	// 位图上起始绘制点
						46, 40,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
			}
			else if (i == 1)
			{
				for (int j = 0; j < unit->health; j++)
				{
					SelectObject(hdc_loadBmp, bmp_health);
					TransparentBlt(
						hdc_memBuffer,
						970 - 50 * j, 0,			// 界面上起始绘制点
						40, 34,											// 界面上绘制宽度高度
						hdc_loadBmp,
						0, 0,	// 位图上起始绘制点
						40, 34,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
				for (int j = 0; j < unit->bubblenum; j++)
				{
					SelectObject(hdc_loadBmp, bmp_Bubble);
					TransparentBlt(
						hdc_memBuffer,
						970 - 50 * j, 40,			// 界面上起始绘制点
						46, 40,											// 界面上绘制宽度高度
						hdc_loadBmp,
						0, 0,	// 位图上起始绘制点
						46, 40,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
			}
		}
		// 绘制人物
		for (int i = 0; i < units.size(); i++)
		{
			Unit* unit = units[i];
			if (i <= 1)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer,
					unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,			// 界面上起始绘制点
					UNIT_SIZE_X, UNIT_SIZE_Y,											// 界面上绘制宽度高度
					hdc_loadBmp,
					UNIT_BITMAP_SIZE_X * unit->frame_column, UNIT_BITMAP_SIZE_Y * unit->frame_row,	// 位图上起始绘制点
					UNIT_BITMAP_SIZE_X, UNIT_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
					RGB(255, 255, 255)
				);
				if (!unit->wudi == FALSE)
				{
					SelectObject(hdc_loadBmp, bmp_wudi);
					TransparentBlt(
						hdc_memBuffer,
						unit->x - 0.4 * UNIT_SIZE_X, unit->y - 0.7 * UNIT_SIZE_Y,			// 界面上起始绘制点
						60, 40,											// 界面上绘制宽度高度
						hdc_loadBmp,
						15, 15,	// 位图上起始绘制点
						30, 30,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
			}
		}
	}


	// 绘制按钮到缓存

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

//绘制倒计时
void DrawCountDown(HWND hWnd)
{
	if (currentStage->timeCountDown != 0)
	{
		HDC hdc = GetDC(hWnd);
		TCHAR* lpString;
		switch (currentStage->timeCountDown)
		{
		case 100: {  lpString = _T("时间还剩100秒"); break; }
		case 99: {  lpString = _T("时间还剩99秒"); break; }
		case 98: {  lpString = _T("时间还剩98秒"); break; }
		case 97: {  lpString = _T("时间还剩97秒"); break; }
		case 96: {  lpString = _T("时间还剩96秒"); break; }
		case 95: {  lpString = _T("时间还剩95秒"); break; }
		case 94: {  lpString = _T("时间还剩94秒"); break; }
		case 93: {  lpString = _T("时间还剩93秒"); break; }
		case 92: {  lpString = _T("时间还剩92秒"); break; }
		case 91: {  lpString = _T("时间还剩91秒"); break; }
		case 90: {  lpString = _T("时间还剩90秒"); break; }
		case 89: {  lpString = _T("时间还剩89秒"); break; }
		case 88: {  lpString = _T("时间还剩88秒"); break; }
		case 87: {  lpString = _T("时间还剩87秒"); break; }
		case 86: {  lpString = _T("时间还剩86秒"); break; }
		case 85: {  lpString = _T("时间还剩85秒"); break; }
		case 84: {  lpString = _T("时间还剩84秒"); break; }
		case 83: {  lpString = _T("时间还剩83秒"); break; }
		case 82: {  lpString = _T("时间还剩82秒"); break; }
		case 81: {  lpString = _T("时间还剩81秒"); break; }
		case 80: {  lpString = _T("时间还剩80秒"); break; }
		case 79: {  lpString = _T("时间还剩79秒"); break; }
		case 78: {  lpString = _T("时间还剩78秒"); break; }
		case 77: {  lpString = _T("时间还剩77秒"); break; }
		case 76: {  lpString = _T("时间还剩76秒"); break; }
		case 75: {  lpString = _T("时间还剩75秒"); break; }
		case 74: {  lpString = _T("时间还剩74秒"); break; }
		case 73: {  lpString = _T("时间还剩73秒"); break; }
		case 72: {  lpString = _T("时间还剩72秒"); break; }
		case 71: {  lpString = _T("时间还剩71秒"); break; }
		case 70: {  lpString = _T("时间还剩70秒"); break; }
		case 69: {  lpString = _T("时间还剩69秒"); break; }
		case 68: {  lpString = _T("时间还剩68秒"); break; }
		case 67: {  lpString = _T("时间还剩67秒"); break; }
		case 66: {  lpString = _T("时间还剩66秒"); break; }
		case 65: {  lpString = _T("时间还剩65秒"); break; }
		case 64: {  lpString = _T("时间还剩64秒"); break; }
		case 63: {  lpString = _T("时间还剩63秒"); break; }
		case 62: {  lpString = _T("时间还剩62秒"); break; }
		case 61: {  lpString = _T("时间还剩61秒"); break; }
		case 60: {  lpString = _T("时间还剩60秒"); break; }
		case 59: {  lpString = _T("时间还剩59秒"); break; }
		case 58: {  lpString = _T("时间还剩58秒"); break; }
		case 57: {  lpString = _T("时间还剩57秒"); break; }
		case 56: {  lpString = _T("时间还剩56秒"); break; }
		case 55: {  lpString = _T("时间还剩55秒"); break; }
		case 54: {  lpString = _T("时间还剩54秒"); break; }
		case 53: {  lpString = _T("时间还剩53秒"); break; }
		case 52: {  lpString = _T("时间还剩52秒"); break; }
		case 51: {  lpString = _T("时间还剩51秒"); break; }
		case 50: {  lpString = _T("时间还剩50秒"); break; }
		case 49: {  lpString = _T("时间还剩49秒"); break; }
		case 48: {  lpString = _T("时间还剩48秒"); break; }
		case 47: {  lpString = _T("时间还剩47秒"); break; }
		case 46: {  lpString = _T("时间还剩46秒"); break; }
		case 45: {  lpString = _T("时间还剩45秒"); break; }
		case 44: {  lpString = _T("时间还剩44秒"); break; }
		case 43: {  lpString = _T("时间还剩43秒"); break; }
		case 42: {  lpString = _T("时间还剩42秒"); break; }
		case 41: {  lpString = _T("时间还剩41秒"); break; }
		case 40: {  lpString = _T("时间还剩40秒"); break; }
		case 39: {  lpString = _T("时间还剩39秒"); break; }
		case 38: {  lpString = _T("时间还剩38秒"); break; }
		case 37: {  lpString = _T("时间还剩37秒"); break; }
		case 36: {  lpString = _T("时间还剩36秒"); break; }
		case 35: {  lpString = _T("时间还剩35秒"); break; }
		case 34: {  lpString = _T("时间还剩34秒"); break; }
		case 33: {  lpString = _T("时间还剩33秒"); break; }
		case 32: {  lpString = _T("时间还剩32秒"); break; }
		case 31: {  lpString = _T("时间还剩31秒"); break; }
		case 30: {  lpString = _T("时间还剩30秒"); break; }
		case 29: {  lpString = _T("时间还剩29秒"); break; }
		case 28: {  lpString = _T("时间还剩28秒"); break; }
		case 27: {  lpString = _T("时间还剩27秒"); break; }
		case 26: {  lpString = _T("时间还剩26秒"); break; }
		case 25: {  lpString = _T("时间还剩25秒"); break; }
		case 24: {  lpString = _T("时间还剩24秒"); break; }
		case 23: {  lpString = _T("时间还剩23秒"); break; }
		case 22: {  lpString = _T("时间还剩22秒"); break; }
		case 21: {  lpString = _T("时间还剩21秒"); break; }
		case 20: {  lpString = _T("时间还剩20秒"); break; }
		case 19: {  lpString = _T("时间还剩19秒"); break; }
		case 18: {  lpString = _T("时间还剩18秒"); break; }
		case 17: {  lpString = _T("时间还剩17秒"); break; }
		case 16: {  lpString = _T("时间还剩16秒"); break; }
		case 15: {  lpString = _T("时间还剩15秒"); break; }
		case 14: {  lpString = _T("时间还剩14秒"); break; }
		case 13: {  lpString = _T("时间还剩13秒"); break; }
		case 12: {  lpString = _T("时间还剩12秒"); break; }
		case 11: {  lpString = _T("时间还剩11秒"); break; }
		case 10: {  lpString = _T("时间还剩10秒"); break; }
		case 9: {  lpString = _T("时间还剩9秒"); break; }
		case 8: {  lpString = _T("时间还剩8秒"); break; }
		case 7: {  lpString = _T("时间还剩7秒"); break; }
		case 6: {  lpString = _T("时间还剩6秒"); break; }
		case 5: {  lpString = _T("时间还剩5秒"); break; }
		case 4: {  lpString = _T("时间还剩4秒"); break; }
		case 3: {  lpString = _T("时间还剩3秒"); break; }
		case 2: {  lpString = _T("时间还剩2秒"); break; }
		case 1: {  lpString = _T("时间还剩1秒"); break; }
		}
		int nCount = lstrlen(lpString);
		// 准备矩形的坐标和格式标记  
		RECT mTextBound;
		mTextBound.left = 463;
		mTextBound.top = 20;
		mTextBound.right = 563; // 每字符宽度为10，加上间隔  
		mTextBound.bottom = 50; // 每行高度为20，加上间隔  
		DrawText(hdc, lpString, nCount, &mTextBound, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src) 
{

	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);


	for (int i = 0; i < BG_ROWS; i++) {

		int src_row = 1;
		if (i >= BG_ROWS_SKY)
			src_row = 0;

		for (int j = 0; j < BG_COLUMNS; j++) {
			int src_column = rand() % BG_SRC_COUNT;

			TransparentBlt(
				hdc_memBuffer, j * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				hdc_loadBmp, src_column * BG_CELL_WIDTH, src_row * BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				RGB(255, 255, 255)
			);

		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}
