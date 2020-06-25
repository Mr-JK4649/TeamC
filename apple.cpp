#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

#define TIME 99	//時間 99秒
#define MHP 1000	//MAX HP
#define HP0 10		//HPが0	10は座標位置
#define HPWID 325	

#define WIDTH 800	//画面横サイズ
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
struct PLAYER {
	int x, y;
	int w, h;
	int speed;		//移動スピード
	int image;		//画像
	int hp;			//プレイヤーHP
	int hp_gauge;	//HPゲージ
};


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

//戦闘画面計算
void CombatCal(void);
//戦闘画面描画
void CombatDraw(void);

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

int g_MouseX;    // マウスのX座標
int g_MouseY;    // マウスのY座標

int g_GameState = GAME_INIT;
int haikeiA;//背景格納変数
struct PLAYER player;
struct PLAYER player2;
int timecount = 0;
int timedraw = TIME;


/*サウンド*/
/*****************************************************
 * プログラムの開始
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("Comin"); // タイトルを設定

	ChangeWindowMode(TRUE);   // ウィンドウモードで起動
	SetGraphMode(800, 600, 32);


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
	//1P
	player.x = 10;
	player.y = 300;
	player.w = 150;
	player.h = 250;
	player.speed = 5;
	player.hp_gauge = 325;
	player.hp = MHP;

	//2P
	player2.w = 150;
	player2.x = WIDTH - player2.w;
	player2.y = 300;
	player2.h = 250;
	player2.speed = 5;
	player2.hp_gauge = 425;
	player2.hp = MHP;

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
	CombatCal();	//戦闘画面計算
	CombatDraw();	//戦闘画面描画

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
	if ((haikeiA = LoadGraph("images/janlgame.jpg")) == -1)return -1;
	if ((player.image = LoadGraph("images/player01.png")) == -1)return -1;
	if ((player2.image = LoadGraph("images/player01.png")) == -1)return -1;
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

/************************************************************************
* 戦闘画面計算
*************************************************************************/
void CombatCal(void) {
	//移動処理
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
		player.x += player.speed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
		player.x -= player.speed;
	}

	//画面端　処理	↓(画面幅からキャラクターの幅を引いた値)
	if (player.x >= WIDTH - player.w) {
		player.x = WIDTH - player.w;
	}
	if (player.x <= 0) {
		player.x = 0;
	}

	//テスト用HPバー
	//HPが0の処理
	if (player.hp_gauge <= HP0) {
		player.hp_gauge = HP0;
	}
	if (player2.hp_gauge >= WIDTH - 10) {
		player2.hp_gauge = WIDTH - 10;
	}

	//時間計測
	timecount++;//1秒カウント
	if (timecount >= 60) {
		timedraw--;//タイム表示
		timecount = 0;
		player2.hp_gauge += 5;
		player.hp_gauge -= 5;
		//player.hp_gauge = player.hp / MHP * HPWID;*/
	}
}
/************************************************************************
* 戦闘画面描画
*************************************************************************/
void CombatDraw(void) {
	DrawGraph(0, 0, haikeiA, FALSE);//背景描画

	DrawGraph(player.x, player.y, player.image, FALSE);//プレイヤー1P描画
	DrawGraph(player2.x, player2.y, player2.image, FALSE);//プレイヤー2P描画

	//1P HPバー描画
	DrawBox(10, 10, player.hp_gauge, 50, GetColor(0, 255, 0), TRUE);//ゲージ
	DrawBox(8, 8, 327, 52, GetColor(0, 255, 0), FALSE);//HPバー枠

	//2P HPバー描画
	DrawBox(player2.hp_gauge, 10, 790, 50, GetColor(0, 255, 0), TRUE);//ゲージ
	DrawBox(423, 8, 792, 52, GetColor(0, 255, 0), FALSE);//HPバー枠

	//時間描画
	SetFontSize(50);
	DrawFormatString(350, 10, GetColor(255, 255, 255), "%d", timedraw);
}