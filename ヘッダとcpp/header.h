#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <wingdi.h>
#include <windows.h>

#pragma warning(disable : 4244)

/*ゲームシーン一覧*/
enum GAME_MODE {
	GAME_TITLE,		//タイトル
	GAME_INIT,		//初期化
	GAME_END,		//エンド
	GAME_BASE,		//拠点
	GAME_HATAKE,
	GAME_S_SELECT,	//ステージ選択
	GAME_RESULT,	//リザルト
	GAME_OVER,		//ゲームオーバー(？)
	END = 99		//エンド用変数
};


/*画面のサイズを全画面にしないためのやつ 1920x1080 〜 1528x810*/
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

struct Menu {
	bool isMenu = false;
	bool Flg = true;

	void Init_Base() {

	}

	void Init_Dungeon() {
		
	}

	void Draw() {
		const int w = scale.Width, w5 = scale.Width / 5;
		const int h = scale.Height, h4 = scale.Height / 4;
		const int size = scale.Width / 100;
		DrawRoundRect(w - w5, 5, w - 5, h - 5, 10, 10, 0x444444, 1);
		DrawRoundRect(w - w5, 5, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w - (w5 + 1), 6, w - 6, h - 6, 10, 10, 0xffffff, 0);

		SetFontSize(size*3);

		for (int i = 0; i < 3; i++)
			DrawString(w - w5 + 5, 10 + size*3 * i, Menu_String[i], 0xffffff, 1);
		//DrawFormatString(w - h5, 35, 0xffffff, "所持金： %09d", );
		
	}

private:
	char Menu_String[3][17] = {"ＸＸＸＸＸ","ＸＸＸＸＸ","ＸＸＸＸＸ"};
};