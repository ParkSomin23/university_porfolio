#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <stdio.h>

#include "ddutil.h"

#include <dsound.h>
#include "dsutil.h"


#define _GetKeyState( vkey ) HIBYTE(GetAsyncKeyState( vkey ))
#define _GetKeyPush( vkey )  LOBYTE(GetAsyncKeyState( vkey ))

extern void CommInit(int argc, char **argv);
extern void CommSend(char *sending);
extern void CommRecv(char *recvData);

static int timer = 0;
int ending = 2700;

char sendData[200];
static int step[2] = { 0, 0 };
static int score=0;

HWND MainHwnd;

LPDIRECTDRAW         DirectOBJ;
LPDIRECTDRAWSURFACE  RealScreen;
LPDIRECTDRAWSURFACE  BackScreen;
LPDIRECTDRAWSURFACE  SpriteImage, SpriteImage_other;
LPDIRECTDRAWSURFACE  SpriteImage_D, SpriteImage_D_other;
LPDIRECTDRAWSURFACE  BackGround, EndScreen, SnF;

//pop
LPDIRECTDRAWSURFACE PlayerPopImage, pop_army, pop_item, pop_coin, pop_good, pop_bad, pop_meat, pop_clean, pop_sleep, pop_wait, pop_spot;
LPDIRECTDRAWSURFACE pop_one, pop_two, pop_three, pop_four;
//npc
LPDIRECTDRAWSURFACE Npc_1, Npc_2, Npc_3, Npc_4;
//item
LPDIRECTDRAWSURFACE heart, food;

LPDIRECTDRAWCLIPPER	ClipScreen;

int gFullScreen = 0, Click = 0;
int gWidth = 1280, gHeight = 780;
int MouseX = 100, MouseY = gHeight / 2;
int mX = 0, mY = 0;

////////////////////

LPDIRECTSOUND       SoundOBJ = NULL;
LPDIRECTSOUNDBUFFER SoundDSB = NULL;
DSBUFFERDESC        DSB_desc;

HSNDOBJ Sound[10];

//////
RECT BackRect = { 0, 0, 1280, 780 };
RECT DispRect = { 0, 0, gWidth, gHeight };
RECT SpriteRect, dstRect, WinRect;

RECT popPlayerRect, popRect;
RECT npcRect, foodRect;

RECT npcMoveRect[15];

int count = 0;
int colCount = 0;
static int lookDir = 1;
static int Rcount = 0;

//방 0 1 2, 식탁 3 4 5 6, 무기 7 8, 물약 9 10, 부엌 11 12 13 14
int spot[15][4] = {
	{ 17, 57, 340, 280 },{ 17, 300, 340, 500 },{ 17, 520, 340,740 },
	
	{ 450, 300, 590, 445 },{ 680, 300, 820, 445 },{ 450, 565, 590,700 },{ 680, 565, 820, 700 },
	
	{ 850, 200, 915, 320 },{ 850, 340, 915, 470 },
	{ 850, 490, 915, 600 },{ 850, 620, 915, 760 },
	
	{ 1050, 200, 1150, 350 },{ 1050, 360, 1150, 480 },{ 1050, 490, 1150, 610 },{ 1050, 620, 1150, 760 }
};

int NPCspot[11][3][2] = {
	{ { 375, 60 },{ 375, 155 },{ 15, 155 } },
	{ { 375, 60 },{ 375, 370 },{ 15, 370 } },
	{ { 375, 60 },{ 375, 600 },{ 15, 600 } }, // room

	{ { 590, 250 },{ 470, 250 },{ 470, 250 } },
	{ { 590, 250 },{ 700, 250 },{ 700, 250 } },
	{ { 590, 500 },{ 470, 500 },{ 470, 500 } },
	{ { 590, 500 },{ 700, 500 },{ 700, 500 } }, // desk

	{ { 795, 60 },{ 795, 205 },{ 835, 205 } },
	{ { 795, 60 },{ 795, 335 },{ 835, 335 } },
	{ { 795, 60 },{ 795, 500 },{ 835, 500 } },
	{ { 795, 60 },{ 795, 630 },{ 835, 630 } } // item
};


// 방마다 누른 spacebar 수 저장
static int pressedSpace[15];
// 손님이 그곳에 이미 와있는가?
// 0 : empty  1: using  2 : coin  3 : clean
static int isUsing[11];


//////
static int mx[15] = { 0, };
static int my[15] = { 0, };
static int waitTime[11] = { 0, };
static int endTime[11] = { 0, };
static int spawnTime[11] = { 0, };
static bool newGuest[11] = { true, true,true,true,true,true,true,true,true,true,true };
static int cooking[4] = { 0, 0, 0, 0 };

static bool serve = false;


BOOL _InitDirectSound(void)
{
	if (DirectSoundCreate(NULL, &SoundOBJ, NULL) == DS_OK)
	{
		if (SoundOBJ->SetCooperativeLevel(MainHwnd, DSSCL_PRIORITY) != DS_OK) return FALSE;

		memset(&DSB_desc, 0, sizeof(DSBUFFERDESC));
		DSB_desc.dwSize = sizeof(DSBUFFERDESC);
		DSB_desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;

		if (SoundOBJ->CreateSoundBuffer(&DSB_desc, &SoundDSB, NULL) != DS_OK) return FALSE;
		SoundDSB->SetVolume(DSBVOLUME_MAX); // DSBVOLUME_MIN
		SoundDSB->SetPan(DSBPAN_RIGHT);
		return TRUE;
	}
	return FALSE;
}

void _Play(int num)
{
	SndObjPlay(Sound[num], NULL);
}

////////////////////////

BOOL Fail(HWND hwnd)
{
	ShowWindow(hwnd, SW_HIDE);
	MessageBox(hwnd, "DIRECT X 초기화에 실패했습니다.", "게임 디자인", MB_OK);
	DestroyWindow(hwnd);
	return FALSE;
}

void _ReleaseAll(void)
{
	if (DirectOBJ != NULL)
	{
		if (RealScreen != NULL)
		{
			RealScreen->Release();
			RealScreen = NULL;
		}
		if (SpriteImage != NULL)
		{
			SpriteImage->Release();
			SpriteImage = NULL;
		}
		if (BackGround != NULL)
		{
			BackGround->Release();
			BackGround = NULL;
		}
		DirectOBJ->Release();
		DirectOBJ = NULL;
	}
}

// spaceBar 입력 처리
void spaceBar() {
	for (int i = 0; i < 15; i++)
	{
		int resize = 0;
		if (i > 2 && i < 7)
			resize = 20;
		else
			resize = 0;

		if (isUsing[i] >= 2)
			if (MouseX > spot[i][0] - resize * 1.5 && MouseX < spot[i][2] + resize * 1.5 && MouseY > spot[i][1] - resize && MouseY < spot[i][3] + resize) {
				pressedSpace[i]++;
				_Play(3);
			}
	}
}


long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case    WM_MOUSEMOVE:   mX = LOWORD(lParam);
		mY = HIWORD(lParam);
		break;

	case	WM_LBUTTONDOWN: 	Click++;
		_Play(3);
		break;
	case	WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_F12:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;

		case VK_LEFT:
			lookDir = 2;
			MouseX -= 5;
			return 0;

		case VK_RIGHT:
			lookDir = 1;
			MouseX += 5;
			return 0;

		case VK_UP:
			MouseY -= 5;
			return 0;

		case VK_DOWN:
			MouseY += 5;
			return 0;

		case VK_SPACE:
			spaceBar();
			break;
		}
		break;

	case    WM_DESTROY:  _ReleaseAll();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL _GameMode(HINSTANCE hInstance, int nCmdShow, int x, int y, int bpp)
{
	HRESULT result;
	WNDCLASS wc;
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	LPDIRECTDRAW pdd;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "TEST";
	RegisterClass(&wc);


	if (gFullScreen) {
		if ((MainHwnd = CreateWindowEx(0, "TEST", NULL, WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL)) == NULL)
			ExitProcess(1);
	}
	else {
		if ((MainHwnd = CreateWindow("TEST", "TEST", WS_OVERLAPPEDWINDOW, 0, 0, x,
			y, NULL, NULL, hInstance, NULL)) == NULL)
			ExitProcess(1);
		SetWindowPos(MainHwnd, NULL, 100, 100, x, y, SWP_NOZORDER);
	}

	SetFocus(MainHwnd);
	ShowWindow(MainHwnd, nCmdShow);
	UpdateWindow(MainHwnd);
	ShowCursor(TRUE);

	result = DirectDrawCreate(NULL, &pdd, NULL);
	if (result != DD_OK) return Fail(MainHwnd);

	result = pdd->QueryInterface(IID_IDirectDraw, (LPVOID *)&DirectOBJ);
	if (result != DD_OK) return Fail(MainHwnd);


	// 윈도우 핸들의 협력 단계를 설정한다.
	if (gFullScreen) {
		result = DirectOBJ->SetCooperativeLevel(MainHwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (result != DD_OK) return Fail(MainHwnd);

		result = DirectOBJ->SetDisplayMode(x, y, bpp);
		if (result != DD_OK) return Fail(MainHwnd);

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;

		result = DirectOBJ->CreateSurface(&ddsd, &RealScreen, NULL);
		if (result != DD_OK) return Fail(MainHwnd);

		memset(&ddscaps, 0, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		result = RealScreen->GetAttachedSurface(&ddscaps, &BackScreen);
		if (result != DD_OK) return Fail(MainHwnd);
	}
	else {
		result = DirectOBJ->SetCooperativeLevel(MainHwnd, DDSCL_NORMAL);
		if (result != DD_OK) return Fail(MainHwnd);

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		ddsd.dwBackBufferCount = 0;

		result = DirectOBJ->CreateSurface(&ddsd, &RealScreen, NULL);
		if (result != DD_OK) return Fail(MainHwnd);

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = x;
		ddsd.dwHeight = y;
		result = DirectOBJ->CreateSurface(&ddsd, &BackScreen, NULL);
		if (result != DD_OK) return Fail(MainHwnd);

		result = DirectOBJ->CreateClipper(0, &ClipScreen, NULL);
		if (result != DD_OK) return Fail(MainHwnd);

		result = ClipScreen->SetHWnd(0, MainHwnd);
		if (result != DD_OK) return Fail(MainHwnd);

		result = RealScreen->SetClipper(ClipScreen);
		if (result != DD_OK) return Fail(MainHwnd);

		SetWindowPos(MainHwnd, NULL, 100, 100, x, y, SWP_NOZORDER | SWP_NOACTIVATE);
	}


	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  modify here

void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
	if (timer < ending) {
		timer++;
		////////////////////////////////
		// pop 그림
		static int popFrame = 0;
		static int popCount = 0;

		popPlayerRect.left = popFrame * 48;
		popPlayerRect.top = 0;
		popPlayerRect.right = popPlayerRect.left + 48;
		popPlayerRect.bottom = 48;

		popCount++;
		if (popCount > 8) {
			popFrame++;
			if (popFrame > 2) {
				popFrame = 0;
			}
			popCount = 0;
		}

		//BackScreen->BltFast(0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		// npc 그림
		static int npcFrame = 8;

		npcRect.left = npcFrame * 96;
		npcRect.top = 96;
		npcRect.right = npcRect.left + 96;
		npcRect.bottom = 96 * 2;

		static int npcFrameCount = 0;
		npcFrameCount++;

		if (npcFrameCount > 5) {
			npcFrame--;
			if (npcFrame < 6) {
				npcFrame = 8;
			}
			npcFrameCount = 0;
		}




		// room
		for (int i = 0; i < 3; i++) {

			if (newGuest[i]) {
				npcMoveRect[i].left = 590 + mx[i];
				npcMoveRect[i].top = 60 + my[i];

				if (npcMoveRect[i].left > NPCspot[i][0][0] && npcMoveRect[i].top == NPCspot[i][0][1])
					mx[i] -= 5;
				if (npcMoveRect[i].left == NPCspot[i][1][0] && npcMoveRect[i].top < NPCspot[i][1][1])
					my[i] += 5;
				if (npcMoveRect[i].left > NPCspot[i][2][0] && npcMoveRect[i].top == NPCspot[i][2][1])
					mx[i] -= 5;

				if (npcMoveRect[i].left == NPCspot[i][2][0] && npcMoveRect[i].top == NPCspot[i][2][1]) {
					// 자는 시간
					if (waitTime[i] < 120) {
						waitTime[i]++;
						isUsing[i] = 1;
						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_sleep, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 1, 0);
						CommSend(sendData);
					}

					// 좋아
					if (waitTime[i] == 120 && endTime[i] < 60) {
						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_good, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
						endTime[i]++;

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 2, 0);
						CommSend(sendData);
					}

					// 돈 받기 준비
					if (endTime[i] == 60 && pressedSpace[i] == 0) {
						npcMoveRect[i].left = 590;
						npcMoveRect[i].top = 0;
						mx[i] = 0;
						my[i] = 0;
						isUsing[i] = 2;
					}

				}

			}

			// 돈 받는 상태
			if (pressedSpace[i] == 0 && isUsing[i] == 2) {
				BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_coin, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				newGuest[i] = false;

				sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 3, 0);
				CommSend(sendData);
			}

			// 청소해야하는 상태
			if (pressedSpace[i] == 1) {
				BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_clean, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 4, 0);
				CommSend(sendData);
			}

			// 청소 끝내면
			if (pressedSpace[i] >= 2 && spawnTime[i] < 180) {
				isUsing[i] = 0;
				waitTime[i] = 0;
				endTime[i] = 0;
				spawnTime[i]++;
				//score += 200;
			}

			if (spawnTime[i] == 180) {
				score += 200;
				newGuest[i] = true;
				pressedSpace[i] = 0;
				spawnTime[i] = 0;
			}

			BackScreen->BltFast(npcMoveRect[i].left, npcMoveRect[i].top, Npc_1, &npcRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 2, npcRect.left, npcRect.top, npcRect.right, npcRect.bottom, npcMoveRect[i].left, npcMoveRect[i].top, i, isUsing[i]);
			CommSend(sendData);
		}




		//desk
		for (int i = 3; i < 7; i++) {

			if (newGuest[i]) {
				npcMoveRect[i].left = 640 - 50 + mx[i];
				npcMoveRect[i].top = 60 + my[i];


				if (npcMoveRect[i].left == NPCspot[i][0][0] && npcMoveRect[i].top < NPCspot[i][0][1])
					my[i] += 5;

				if (i % 2 == 0) {
					if (npcMoveRect[i].left < NPCspot[i][1][0] && npcMoveRect[i].top == NPCspot[i][1][1])
						mx[i] += 5;
				}
				else
					if (npcMoveRect[i].left > NPCspot[i][1][0] && npcMoveRect[i].top == NPCspot[i][1][1])
						mx[i] -= 5;

				if (npcMoveRect[i].left == NPCspot[i][2][0] && npcMoveRect[i].top == NPCspot[i][2][1]) {

					// 음식 대기
					if (endTime[i] == 0 && waitTime[i] < 600) {
						waitTime[i]++;

						//if (serve)
							//isUsing[i] = 2;

						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_meat, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 6, 0);
						CommSend(sendData);
					}

					// 기다림
					if (pressedSpace[i] == 0 && waitTime[i] == 600 && endTime[i] < 300) {
						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_wait, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
						endTime[i]++;

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 5, 0);
						CommSend(sendData);
					}

					// 그냥 나감
					if (endTime[i] == 300 && pressedSpace[i] == 0) {
						npcMoveRect[i].left = 640 - 50;
						npcMoveRect[i].top = 0;
						mx[i] = 0;
						my[i] = 0;
						isUsing[i] = 0;
						newGuest[i] = true;
						waitTime[i] = 0;
						endTime[i] = 0;
						pressedSpace[i] = 0;
					}
				}
			}

			// 돈 받는 상태
			if (pressedSpace[i] == 1 && isUsing[i] == 2) {
				serve = false;
				isUsing[11] = 0; pressedSpace[11] = 0;
				isUsing[12] = 0; pressedSpace[12] = 0;
				isUsing[13] = 0; pressedSpace[13] = 0;
				pressedSpace[14] = 0;

				BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_coin, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

				sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 3, 0);
				CommSend(sendData);

				//newGuest[i] = false;
				npcMoveRect[i].left = 640 - 50;
				npcMoveRect[i].top = 0;
				mx[i] = 0;
				my[i] = 0;
			}

			// 청소해야하는 상태
			if (pressedSpace[i] == 2) {
				BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_clean, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				
				sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 4, 0);
				CommSend(sendData);
			}

			// 청소 끝내면
			if (pressedSpace[i] >= 3 && spawnTime[i] < 180) {
				isUsing[i] = 0;
				waitTime[i] = 0;
				endTime[i] = 0;
				pressedSpace[i] = 0;
				spawnTime[i]++;
				//score += 400;
			}


			if (spawnTime[i] == 180) {
				isUsing[i] = 0;
				newGuest[i] = true;
				pressedSpace[i] = 0;
				spawnTime[i] = 0;
				score += 400;
			}

			BackScreen->BltFast(npcMoveRect[i].left, npcMoveRect[i].top, Npc_2, &npcRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 2, npcRect.left, npcRect.top, npcRect.right, npcRect.bottom, npcMoveRect[i].left, npcMoveRect[i].top, i, isUsing[i]);
			CommSend(sendData);
		}




		//Player 요리  11 12 13 14
		foodRect.left = 0;
		foodRect.top = 0;
		foodRect.right = 2 * 61;
		foodRect.bottom = 2 * 48;

		isUsing[14] = 2;

		if (pressedSpace[14]) {
			BackScreen->BltFast((spot[14][0] + spot[14][2]) / 2, (spot[14][1] + spot[14][3]) / 2, pop_one, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, (spot[14][0] + spot[14][2]) / 2, (spot[14][1] + spot[14][3]) / 2, 8, 0);
			CommSend(sendData);

			isUsing[13] = 2;

			if (pressedSpace[13]) {
				BackScreen->BltFast((spot[13][0] + spot[13][2]) / 2, (spot[13][1] + spot[13][3]) / 2, pop_two, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, (spot[13][0] + spot[13][2]) / 2, (spot[13][1] + spot[13][3]) / 2, 9, 0);
				CommSend(sendData);
				isUsing[12] = 2;
				if (pressedSpace[12]) {
					BackScreen->BltFast((spot[12][0] + spot[12][2]) / 2, (spot[12][1] + spot[12][3]) / 2, pop_three, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
					isUsing[11] = 2;
					sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, (spot[12][0] + spot[12][2]) / 2, (spot[12][1] + spot[12][3]) / 2, 10, 0);
					CommSend(sendData);
					if (pressedSpace[11]) {
						BackScreen->BltFast(1150, 200, pop_four, &foodRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, foodRect.left, foodRect.top, foodRect.right, foodRect.bottom, 1150, 200, 11, 0);
						CommSend(sendData);
						isUsing[3] = 2;
						isUsing[4] = 2;
						isUsing[5] = 2;
						isUsing[6] = 2;
					}
				}
			}

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 4, isUsing[13], isUsing[12], isUsing[11], isUsing[3], isUsing[4], isUsing[5], isUsing[6], 0);
			CommSend(sendData);
		}







		//item
		for (int i = 7; i < 11; i++) {

			if (newGuest[i]) {
				npcMoveRect[i].left = 640 - 50 + mx[i];
				npcMoveRect[i].top = 60 + my[i];

				if (npcMoveRect[i].left < NPCspot[i][0][0] && npcMoveRect[i].top == NPCspot[i][0][1])
					mx[i] += 5;
				if (npcMoveRect[i].left == NPCspot[i][1][0] && npcMoveRect[i].top < NPCspot[i][1][1])
					my[i] += 5;
				if (npcMoveRect[i].left < NPCspot[i][2][0] && npcMoveRect[i].top == NPCspot[i][2][1])
					mx[i] += 5;

				if (npcMoveRect[i].left == NPCspot[i][2][0] && npcMoveRect[i].top == NPCspot[i][2][1]) {
					// 구경하는 시간
					if (waitTime[i] < 40) {
						waitTime[i]++;
						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_item, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 7, 0);
						CommSend(sendData);
					}
					// 돈 받기 대기
					if (waitTime[i] == 40) {
						isUsing[i] = 2;
						BackScreen->BltFast(NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, pop_coin, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

						sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 3, popPlayerRect.left, popPlayerRect.top, popPlayerRect.right, popPlayerRect.bottom, NPCspot[i][2][0] + 15, NPCspot[i][2][1] - 25, 3, 0);
						CommSend(sendData);

						if (pressedSpace[i] >= 1)
							newGuest[i] = false;
					}
				}
			}

			// 돈 받으면
			if (pressedSpace[i] >= 1 && spawnTime[i] < 300) {
				npcMoveRect[i].left = 640 - 50;
				npcMoveRect[i].top = 0;
				mx[i] = 0;
				my[i] = 0;

				//score += 100;

				isUsing[i] = 0;
				waitTime[i] = 0;
				spawnTime[i]++;
			}

			if (spawnTime[i] == 300) {
				score += 100;
				newGuest[i] = true;
				pressedSpace[i] = 0;
				spawnTime[i] = 0;
				isUsing[i] = 0;
				npcMoveRect[i].left = 640 - 50;
				npcMoveRect[i].top = 60;
			}

			BackScreen->BltFast(npcMoveRect[i].left, npcMoveRect[i].top, Npc_3, &npcRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 2, npcRect.left, npcRect.top, npcRect.right, npcRect.bottom, npcMoveRect[i].left, npcMoveRect[i].top, i, isUsing[i]);
			CommSend(sendData);
		}





		// PLAYER
		// 이동 제한
		// map 크기 안에서 이동
		if (MouseX <= 50) MouseX = 50;
		if (MouseX > gWidth - 160) MouseX = gWidth - 160;
		if (MouseY <= 110) MouseY = 110;
		if (MouseY > gHeight - 65) MouseY = gHeight - 65;

		// 방 통과 불가
		if (MouseX < spot[0][2])
		{
			if (MouseY > spot[0][3] - 20 && MouseY < spot[1][1]) MouseY = spot[0][3] - 20;
			if (MouseY < spot[1][1] + 20 && MouseY > spot[0][3] + 5) MouseY = spot[1][1] + 20;
			if (MouseY > spot[1][3] - 20 && MouseY < spot[2][1]) MouseY = spot[1][3] - 20;
			if (MouseY < spot[2][1] + 20 && MouseY > spot[1][3] + 5) MouseY = spot[2][1] + 20;
		}

		// 식탁 통과 불가
		if (MouseY > spot[3][1] + 5 && MouseY < spot[3][3] - 5) {
			if (MouseX < spot[3][2] + 15 && MouseX > spot[3][0] - 10) MouseX = spot[3][2] + 15;
			if (MouseX > spot[3][0] - 20 && MouseX < spot[3][2] - 50) MouseX = spot[3][0] - 20;

			if (MouseX < spot[4][2] + 15 && MouseX > spot[4][0] - 10) MouseX = spot[4][2] + 15;
			if (MouseX > spot[4][0] - 20 && MouseX < spot[4][2] - 50) MouseX = spot[4][0] - 20;
		}

		if (MouseY > spot[5][1] + 5 && MouseY < spot[5][3] - 5) {
			if (MouseX < spot[5][2] + 15 && MouseX > spot[5][0] - 10) MouseX = spot[5][2] + 15;
			if (MouseX > spot[5][0] - 20 && MouseX < spot[5][2] - 50) MouseX = spot[5][0] - 20;

			if (MouseX < spot[6][2] + 15 && MouseX > spot[6][0] - 10) MouseX = spot[6][2] + 15;
			if (MouseX > spot[6][0] - 20 && MouseX < spot[6][2] - 50) MouseX = spot[6][0] - 20;
		}

		if (MouseX > spot[3][0] && MouseX < spot[3][2]) {
			if (MouseY > spot[3][1] - 10 && MouseY < spot[3][3] - 20)
				MouseY = spot[3][1] - 10;
			if (MouseY < spot[3][3] + 10 && MouseY >spot[3][1] + 20)
				MouseY = spot[3][3] + 10;
		}

		if (MouseX > spot[4][0] && MouseX < spot[4][2]) {
			if (MouseY > spot[4][1] - 10 && MouseY < spot[4][3] - 20)
				MouseY = spot[4][1] - 10;
			if (MouseY < spot[4][3] + 10 && MouseY >spot[4][1] + 20)
				MouseY = spot[4][3] + 10;
		}

		if (MouseX > spot[5][0] && MouseX < spot[5][2]) {
			if (MouseY > spot[5][1] - 10 && MouseY < spot[5][3] - 20)
				MouseY = spot[5][1] - 10;
			if (MouseY < spot[5][3] + 10 && MouseY >spot[5][1] + 20)
				MouseY = spot[5][3] + 10;
		}

		if (MouseX > spot[6][0] && MouseX < spot[6][2]) {
			if (MouseY > spot[6][1] - 10 && MouseY < spot[6][3] - 20)
				MouseY = spot[6][1] - 10;
			if (MouseY < spot[6][3] + 10 && MouseY >spot[6][1] + 20)
				MouseY = spot[6][3] + 10;
		}

		// 판매대 통과 불가
		if (MouseY > 260) {
			if (MouseX > 885 && MouseX < 1000) MouseX = 885;
			if (MouseX < 1030 && MouseX > 885) MouseX = 1030;
		}
		if (MouseX > 885 && MouseX < 1030)
			if (MouseY > 200 - 35)
				MouseY = 200 - 35;

		static int frameCount = 0;
		frameCount++;

		if (lookDir == 1) {
			static int Frame = 4;

			SpriteRect.left = Frame * 96;
			SpriteRect.top = 0;
			SpriteRect.right = SpriteRect.left + 96;
			SpriteRect.bottom = 96;

			if (frameCount > 5) {
				Frame++;
				if (Frame > 10) {
					Frame = 4;
				}
				frameCount = 0;
			}

			BackScreen->BltFast(MouseX - 48, MouseY - 48, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
			BackScreen->BltFast(MouseX - 24, MouseY - 48 - 30, PlayerPopImage, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 1, SpriteRect.left, SpriteRect.top, SpriteRect.right, SpriteRect.bottom, MouseX - 48, MouseY - 48, timer, 1);
			CommSend(sendData);
		}

		if (lookDir == 2) {
			static int Frame = 20;

			SpriteRect.left = Frame * 96;
			SpriteRect.top = 0;
			SpriteRect.right = SpriteRect.left + 96;
			SpriteRect.bottom = 96;

			if (frameCount > 5) {
				Frame--;
				if (Frame < 15) {
					Frame = 20;
				}
				frameCount = 0;
			}
			BackScreen->BltFast(MouseX - 48, MouseY - 48, SpriteImage_D, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
			BackScreen->BltFast(MouseX - 24, MouseY - 48 - 30, PlayerPopImage, &popPlayerRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

			sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 1, SpriteRect.left, SpriteRect.top, SpriteRect.right, SpriteRect.bottom, MouseX - 48, MouseY - 48, timer, 2);
			CommSend(sendData);
		}

		sprintf(sendData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", 10, score,0,0,0,0,0,0,0);
		CommSend(sendData);
		///////////////////

	}
	else {
	RECT SnFRect;

		BackScreen->BltFast(0, 0, EndScreen, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

	if (score >= 10000) {
		SnFRect.left=150;
		SnFRect.top=150;
		SnFRect.right = 635;
		SnFRect.bottom = 250;
		BackScreen->BltFast(mX, mY, SnF, &SnFRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	else {
		SnFRect.left = 425;
		SnFRect.top = 387;
		SnFRect.right = 685;
		SnFRect.bottom = 474;
		BackScreen->BltFast(mX, mY, SnF, &SnFRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	}

	if (gFullScreen)
		RealScreen->Flip(NULL, DDFLIP_WAIT);
	else {
		GetWindowRect(MainHwnd, &WinRect);
		RealScreen->Blt(&WinRect, BackScreen, &DispRect, DDBLT_WAIT, NULL);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////


void _GameProcDraw(char *recvData)
{
	RECT Sprite, Display;
	int type;

	if (timer < ending) {
		sscanf(recvData, "%d, %d, %d, %d, %d, %d, %d, %d, %d", &type, &Sprite.left, &Sprite.top, &Sprite.right, &Sprite.bottom, &Display.left, &Display.top, &Display.right, &Display.bottom);


		static int count = 0;

		if (count == 0) {
			BackScreen->BltFast(0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}


		if (type == 0) {
			pressedSpace[Sprite.left] = Sprite.top;
		}

		// player
		if (type == 1) {
			if (Display.bottom == 1)
				BackScreen->BltFast(Display.left, Display.top, SpriteImage_other, &Sprite, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
			else if (Display.bottom == 2)
				BackScreen->BltFast(Display.left, Display.top, SpriteImage_D_other, &Sprite, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}

		count++;
		if (count == 3) {  // 2  // 4   //  3     // 8    // 6
			if (gFullScreen)
				RealScreen->Flip(NULL, DDFLIP_WAIT);
			else {
				GetWindowRect(MainHwnd, &WinRect);
				RealScreen->Blt(&WinRect, BackScreen, &DispRect, DDBLT_WAIT, NULL);
				count = 0;
			}
		}
	}
	
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!_GameMode(hInstance, nCmdShow, gWidth, gHeight, 32)) return FALSE;

	BackGround = DDLoadBitmap(DirectOBJ, "Inn.BMP", 0, 0);
	EndScreen = DDLoadBitmap(DirectOBJ, "End.BMP", 0, 0);
	SnF = DDLoadBitmap(DirectOBJ, "snf.BMP", 0, 0);
	DDSetColorKey(SnF, RGB(0, 0, 0));

	//player
	SpriteImage = DDLoadBitmap(DirectOBJ, "DinoSprites2_1P.BMP", 0, 0);
	SpriteImage_D = DDLoadBitmap(DirectOBJ, "DinoSprites2F_1P.BMP", 0, 0);


	SpriteImage_other = DDLoadBitmap(DirectOBJ, "DinoSprites2_2P.BMP", 0, 0);
	SpriteImage_D_other = DDLoadBitmap(DirectOBJ, "DinoSprites2F_2P.BMP", 0, 0);


	DDSetColorKey(SpriteImage, RGB(0, 0, 0));
	DDSetColorKey(SpriteImage_D, RGB(0, 0, 0));
	DDSetColorKey(SpriteImage_other, RGB(0, 0, 0));
	DDSetColorKey(SpriteImage_D_other, RGB(0, 0, 0));

	//pop
	PlayerPopImage = DDLoadBitmap(DirectOBJ, "pop_player.BMP", 0, 0);
	DDSetColorKey(PlayerPopImage, RGB(0, 0, 0));
	pop_army = DDLoadBitmap(DirectOBJ, "pop_army.BMP", 0, 0);
	DDSetColorKey(pop_army, RGB(0, 0, 0));
	pop_item = DDLoadBitmap(DirectOBJ, "pop_item.BMP", 0, 0);
	DDSetColorKey(pop_item, RGB(0, 0, 0));
	pop_coin = DDLoadBitmap(DirectOBJ, "pop_coin.BMP", 0, 0);
	DDSetColorKey(pop_coin, RGB(0, 0, 0));
	pop_good = DDLoadBitmap(DirectOBJ, "pop_good.BMP", 0, 0);
	DDSetColorKey(pop_good, RGB(0, 0, 0));
	pop_bad = DDLoadBitmap(DirectOBJ, "pop_bad.BMP", 0, 0);
	DDSetColorKey(pop_bad, RGB(0, 0, 0));
	pop_meat = DDLoadBitmap(DirectOBJ, "pop_meat.BMP", 0, 0);
	DDSetColorKey(pop_meat, RGB(0, 0, 0));
	pop_clean = DDLoadBitmap(DirectOBJ, "pop_clean.BMP", 0, 0);
	DDSetColorKey(pop_clean, RGB(0, 0, 0));
	pop_sleep = DDLoadBitmap(DirectOBJ, "pop_sleep.BMP", 0, 0);
	DDSetColorKey(pop_sleep, RGB(0, 0, 0));
	pop_wait = DDLoadBitmap(DirectOBJ, "pop_wait.BMP", 0, 0);
	DDSetColorKey(pop_wait, RGB(0, 0, 0));

	pop_one = DDLoadBitmap(DirectOBJ, "pop_1.BMP", 0, 0);
	DDSetColorKey(pop_one, RGB(0, 0, 0));
	pop_two = DDLoadBitmap(DirectOBJ, "pop_2.BMP", 0, 0);
	DDSetColorKey(pop_two, RGB(0, 0, 0));
	pop_three = DDLoadBitmap(DirectOBJ, "pop_3.BMP", 0, 0);
	DDSetColorKey(pop_three, RGB(0, 0, 0));
	pop_four = DDLoadBitmap(DirectOBJ, "food.BMP", 0, 0);
	DDSetColorKey(pop_four, RGB(0, 0, 0));

	//npc
	Npc_1 = DDLoadBitmap(DirectOBJ, "npc_1.BMP", 0, 0);
	DDSetColorKey(Npc_1, RGB(0, 0, 0));
	Npc_2 = DDLoadBitmap(DirectOBJ, "npc_2.BMP", 0, 0);
	DDSetColorKey(Npc_2, RGB(0, 0, 0));
	Npc_3 = DDLoadBitmap(DirectOBJ, "npc_3.BMP", 0, 0);
	DDSetColorKey(Npc_3, RGB(0, 0, 0));
	Npc_4 = DDLoadBitmap(DirectOBJ, "npc_4.BMP", 0, 0);
	DDSetColorKey(Npc_4, RGB(0, 0, 0));

	SetTimer(MainHwnd, 1, 30, _GameProc);
	CommInit(NULL, NULL);

	///////////////////

	if (_InitDirectSound())
	{
		Sound[0] = SndObjCreate(SoundOBJ, "ByBicycle.WAV", 1);
		Sound[1] = SndObjCreate(SoundOBJ, "LAND.WAV", 2);
		Sound[2] = SndObjCreate(SoundOBJ, "GUN1.WAV", 2);
		Sound[3] = SndObjCreate(SoundOBJ, "KNIFE1.WAV", 2);
		Sound[4] = SndObjCreate(SoundOBJ, "DAMAGE1.WAV", 2);
		Sound[5] = SndObjCreate(SoundOBJ, "DAMAGE2.WAV", 2);

		SndObjPlay( Sound[0], DSBPLAY_LOOPING );
	}
	//////////////////

	while (!_GetKeyState(VK_ESCAPE))
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0)) return msg.wParam;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//        else _GameProc();
	}
	DestroyWindow(MainHwnd);

	return TRUE;
}
