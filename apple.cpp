#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

#define SELECT_ITEM 7
#define WIDTH 970	//画面横サイズ
#define HEIGHT 600	//画面縦サイズ
/********************************************************************
* 列挙体の宣言
********************************************************************/
enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_END,
	GAME_MAIN,
	GAME_RESULT,
	GAME_OVER,
	END = 99
};

/********************************************************************
* 定数の宣言
********************************************************************/

/********************************************************************
* 構造体の宣言
********************************************************************/
//typedef struct {
//	int x1, y1, x2, y2;
//	int w, h;
//}Cursor;

typedef struct {
	int x, y;
	int w, h;
	int img;
	int main_img;
	int flg;
}Selectitem;


/***********************************************
  * 関数のプロトタイプ宣言
***********************************************/
// ゲーム初期化処理
void GameInit(void);
// ゲームメイン処理
void GameMain(void);
// ゲームタイトル描画処理
void DrawGameTitle(void);
// エンド描画処理
void DrawEnd(void);
// ゲームクリアーの処理
void DrawGameResult(void);
// ゲームオーバー描画処理
void DrawGameOver(void);
//キー読み込み
int UpdatKey();
//ステージセレクト画面
void Stageselect(void);
void StageselectDraw(void);

void Keyselect(void);
void Mouseselect(void);
// 画像読み込み
int LoadImages();

//サウンド
int LoadSounds(void);

/********************************************************************
* 変数の宣言
********************************************************************/
int g_OldKey;    // 前回の入力キー
int g_NowKey;    // 今回の入力キー
int g_KeyFlg;    // 入力キー情報
int Key[256];//キーが押されているフレーム数を格納

int g_MouseX;    // マウスのX座標
int g_MouseY;    // マウスのY座標

int g_GameState = GAME_INIT;

int haikeiA;//背景格納変数
int selectnum;

//Cursor cursor;
Selectitem sitem[SELECT_ITEM];


/*サウンド*/
/*****************************************************
 * プログラムの開始
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("Comin"); // タイトルを設定

	ChangeWindowMode(TRUE);   // ウィンドウモードで起動
	SetGraphMode(WIDTH, HEIGHT, 32);


	if (DxLib_Init() == -1)   // DXライブラリの初期化処理
		return -1;

	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする

	// 画像読み込み
	if (LoadImages() == -1)
		return -1;

	//サウンド読み込み
	if (LoadSounds() == -1)
		return -1;

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {


		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetMouseInput();
		g_KeyFlg = g_NowKey & ~g_OldKey;

		//マウスの位置を取得
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();  // 画面の初期化

		switch (g_GameState) {

		case GAME_TITLE:DrawGameTitle(); break;		 //ゲームタイトル処理

		case GAME_INIT: GameInit();  break;			 //ゲーム初期処理

		case GAME_END: DrawEnd();  break;			 //ランキング描画処理

		case GAME_MAIN: GameMain();  break;			 //エンド描画処理

		case GAME_RESULT:DrawGameResult(); break;		 //ゲームメイン処理

		case GAME_OVER: DrawGameOver(); break;		 // ゲームオーバー描画処理

		}

		ScreenFlip();    // 裏画面の内容を表画面に反映

	}

	DxLib_End(); // DXライブラリ使用の終了処理

	return 0; // ソフトの終了
}

/********************************************************************
* ゲームタイトル描画処理(メニュー画面)
********************************************************************/
void DrawGameTitle(void) {

}

/********************************************************************
* ゲーム初期化処理
********************************************************************/
void GameInit(void) {
	//項目初期化
	for (int i = 0; i < 6; i++) {
		sitem[i].x = 40;
		sitem[i].y = (80 * i) + 20; //+20は余白
		sitem[i].w = 300;
		sitem[i].h = 60;
		sitem[i].flg = false;
	}
	sitem[6].x = 40;
	sitem[6].y = 550;

	g_GameState = GAME_MAIN;
}


/********************************************************************
* ゲームエンド描画処理
********************************************************************/
void DrawEnd(void) {

}

/********************************************************************
* ゲームメイン
********************************************************************/
void GameMain(void) {
	UpdatKey();
	Stageselect();
	StageselectDraw();
}

/********************************************************************
* ゲームクリア描画処理
********************************************************************/
void DrawGameResult(void) {

}

/********************************************************************
* ゲームオーバー描画処理
********************************************************************/
void DrawGameOver(void) {


}


/********************************************************************
* 画像読み込み
********************************************************************/
int LoadImages() {

	//// タイトル
	//if ((g_TitleImage = LoadGraph("images/title.png")) == -1)return -1;

	////ステージ
	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;

	////ゲームクリア
	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;

	////ゲームオーバー
	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;

	////ブロック画像
	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;

	////ナンバー画像の読み込み
	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;

	//背景読み込み
	if ((haikeiA = LoadGraph("images/stageselect_backtest.png")) == -1)return -1;
	if ((sitem[0].img = LoadGraph("images/test1.png")) == -1)return -1;
	if ((sitem[1].img = LoadGraph("images/test2.png")) == -1)return -1;
	if ((sitem[2].img = LoadGraph("images/test3.png")) == -1)return -1;
	if ((sitem[3].img = LoadGraph("images/test4.png")) == -1)return -1;
	if ((sitem[4].img = LoadGraph("images/test2.png")) == -1)return -1;
	if ((sitem[5].img = LoadGraph("images/test3.png")) == -1)return -1;
	if ((sitem[5].img = LoadGraph("images/test4.png")) == -1)return -1;
	if ((sitem[6].img = LoadGraph("images/back.png")) == -1)return -1;

	if ((sitem[0].main_img = LoadGraph("images/image.png")) == -1)return -1;
	if ((sitem[1].main_img = LoadGraph("images/maintest2.png")) == -1)return -1;
	if ((sitem[2].main_img = LoadGraph("images/maintest3.png")) == -1)return -1;
	if ((sitem[3].main_img = LoadGraph("images/maintest4.png")) == -1)return -1;

	return 0;
}

/********************************************************************
* サウンド読み込み
********************************************************************/
int LoadSounds(void) {

	////タイトル
	//if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
	////クリア
	//if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
	////オーバー
	//if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
	////マウスクリック
	//if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
	////ブロック消去
	//if ((g_TitleBGM = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
	////ブロック移動
	//if ((g_TitleBGM = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;



	return 0;
}
//セレクト操作処理
void Stageselect(void) {
	Keyselect();
	Mouseselect();
}
int UpdatKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}
//キー選択
void Keyselect(void) {
	//キーで選択
	if (Key[KEY_INPUT_RETURN] == 1) {
		//g_GameState=
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectnum = (selectnum + 1) % SELECT_ITEM;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectnum = (selectnum + (SELECT_ITEM-1)) % SELECT_ITEM;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				sitem[i].x = 80;
			}
			else {
				sitem[i].x = 40;
			}
		}
	}

}
//マウス選択
void Mouseselect(void) {
	//マウス選択
	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
		if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>20 && g_MouseY < 80) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 0;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>100 && g_MouseY < 160) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 1;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>180 && g_MouseY < 240) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 2;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>260 && g_MouseY < 340) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 3;
		}
		//戻るボタン
		else if (g_MouseX > 40 && g_MouseX < 190 && g_MouseY>550 && g_MouseY < 600) {
			//g_GameState =
		}

		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				sitem[i].x = 80;
			}
			else {
				sitem[i].x = 40;
			}
		}
	}
}
void StageselectDraw(void) {
	DrawGraph(0, 0, haikeiA, TRUE);
	for (int i = 0; i < SELECT_ITEM; i++) {
		DrawGraph(sitem[i].x, sitem[i].y, sitem[i].img, FALSE);
	}
	DrawGraph(445, 100, sitem[selectnum].main_img, FALSE);
	for (int i = 1; i < 5; i++) {
		DrawFormatString(300, 100*i-50, GetColor(0, 0, 0), "flg %d", sitem[i-1].flg);
	}
	//DrawFormatString(500, 400, GetColor(255, 255, 0), "Y %d",g_MouseY);
	/*SetFontSize(50);
	DrawFormatString(480, 20, GetColor(255, 255, 0), "ステージセレクト");*/
	//for (int i = 0; i < SELECT_ITEM; i++) {
	//}
}