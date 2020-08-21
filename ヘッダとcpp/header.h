#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <windows.h>

#pragma warning(disable : 4244)

/*ゲームシーン一覧*/
enum GAME_MODE {
	GAME_TITLE,		//タイトル
	GAME_INIT,		//初期化
	GAME_STORY,		//シーケンス？
	GAME_END,		//エンド
	GAME_BASE,		//拠点
	GAME_HATAKE,	//畑のやつ
	GAME_SHOP,		//店のやつ
	GAME_HOME,		//自宅
	GAME_WORK,		//仕事紹介所
	GAME_CASINO,	//カジノ
	GAME_S_SELECT,	//ステージ選択
	CAME_ENDING,	//3ボス倒した後のやつ
	GAME_CREDIT,	//クレジット
	GAME_RESULT,	//リザルト
	GAME_CREAR,		//ゲームクリア
	GAME_OVER,		//ゲームオーバー(？)
	END = 99,		//エンド用変数
	GAME_DUNGEON	//ダンジョン
};


/*画面のサイズを全画面にしないためのやつ 1920x1080 ～ 1528x810*/
struct WindowScaler {
	int Width, Height;
	RECT recDisplay;
	HWND hDeskWnd;

	void GetWindwScale(struct WindowScaler* p) {
		p->hDeskWnd = GetDesktopWindow();
		GetWindowRect(p->hDeskWnd, &p->recDisplay);

		p->Width = p->recDisplay.right;
		p->Height = p->recDisplay.bottom;

		do {
			p->Width *= 0.8;
			p->Height *= 0.8;
		} while (Width >= 1500);

	}

};

extern WindowScaler scale;
extern int g_GameState;

