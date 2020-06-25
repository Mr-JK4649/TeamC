/*必要なやつの読み込み*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

//#include "motion.h"


#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

/********************************************************************
* 列挙体の宣言
********************************************************************/
enum GAME_MODE {
	GAME_TITLE,		//タイトル
	GAME_INIT,		//初期化
	GAME_END,		//エンド
	GAME_BATTLE,	//戦闘
	GAME_SELECT,	//キャラ選択
	GAME_RESULT,	//リザルト
	GAME_OVER,		//ゲームオーバー(？)
	END = 99		//エンド用変数
};

enum Genre {
	HORROR,			//ホラー
	ACTION,			//アクション
	RPG,			//RPG
	NOVEL,			//ノベル
	CARD,			//カード
	STEALTH,		//ステルス
	SIMULATION,		//シミュレーション
	SHOOTING,		//シューティング
	PUZZLE,			//パズル
	MUSIC,			//音楽
	RACE1,			//レース(レーサー)
	RACE2			//レース(レースオフィシャル)
};

/********************************************************************
* 定数の宣言
********************************************************************/



/*******************************************************************
*画像のあれ
********************************************************************/
int g_TitleImage;				//タイトル画像
int g_BattleImage;				//戦闘画面背景
int g_SelectImage;				//キャラ選択画像

int g_HorrorImage[4];			//ホラーキャラの画像


/********************************************************************
* 変数の宣言
********************************************************************/
//int g_OldKey;						// 前回の入力キー
//int g_NowKey;						// 今回の入力キー
//int g_KeyFlg;						// 入力キー情報
int g_key[256];						// キーの情報を格納するやつ
bool left[2], right[2], up[2], down[2],jump[2],XButton[2],YButton[2];				// キーの押下判定(添え字で判定：0が1Ｐ、1が2Ｐ)

int g_OldMouse;				//前回のマウス
int g_NowMouse;				//今回のマウス
int g_MouseFlg;				//マウスフラグ
int g_MouseX;				// マウスのX座標
int g_MouseY;				// マウスのY座標
bool mleft, mright;			// マウスの入力判定

int g_GameState;			//ゲームのシーン管理


/*サウンド*/


/********************************************************************
* 構造体の宣言
********************************************************************/
struct chara{
	int hp=100;						//体力
	int ap=0;						//アビリティのゲージ用
	float px=400, py=400;			//キャラの座標
	bool aFlg=false;				//アビリティ発動フラグ
	float jumpForce=8.0f;			//ジャンプ力
	int vector=0;					//進行ベクトル
	int oldVec = 0;					//前のベクトル
	float speed = 0;				//キャラのスピード
};

struct chara charaA[11];
struct chara charaB[11];

/***********************************************
  * 関数のプロトタイプ宣言
***********************************************/
//キー入力のやつ
void KeyInput(void);

// ゲーム初期化処理
void GameInit(void);

// キャラ選択シーン
void GameSelect(void);

// 戦闘シーン
void GameBattle(void);
void PlayerMove(int genre,struct chara *chara,int pl);

// ゲームタイトル描画処理
void DrawGameTitle(void);

// エンド描画処理
void DrawEnd(void);

// ゲームクリアーの処理
void DrawGameResult(void);

// ゲームオーバー描画処理
void DrawGameOver(void);


// 画像読み込み
int LoadImages();

//サウンド
int LoadSounds(void);

/*****************************************************
 * プログラムの開始
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("ゲームジャンル王決定戦"); // タイトルを設定

	ChangeWindowMode(TRUE);   // ウィンドウモードで起動

	SetGraphMode(1440, 810,16,60);


	if (DxLib_Init() == -1)   // DXライブラリの初期化処理
		return -1;

	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする

	// 画像読み込み
	if (LoadImages() == -1)
		return -1;

	//サウンド読み込み
	if (LoadSounds() == -1)
		return -1;

	g_GameState = GAME_TITLE;

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {

		//マウスの取得
		g_OldMouse = g_NowMouse;								//前フレームのキー取得
		g_NowMouse = GetMouseInput();							//現フレームの取得
		g_MouseFlg = g_NowMouse & ~g_OldMouse;					//マウスのフラグ
		GetMousePoint(&g_MouseX, &g_MouseY);					//マウスの位置を取得


		KeyInput();			//キーの入力を管理


		ClearDrawScreen();  // 画面の初期化

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(); break;		 //ゲームタイトル処理

		case GAME_INIT:		GameInit();  break;			 //ゲーム初期処理

		case GAME_SELECT:	GameSelect();  break;	     //キャラ選択画面処理

		case GAME_BATTLE:	GameBattle();  break;		 //戦闘画面処理

		case GAME_RESULT:	DrawGameResult(); break;	 //ゲームメイン処理

		case GAME_OVER:		DrawGameOver(); break;		 // ゲームオーバー描画処理

		case GAME_END:		DrawEnd(); break;		 // ゲームオーバー描画処理

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


	//タイトルの画像表示
	DrawExtendGraph(0, 0,1440,810, g_TitleImage, true);
	//DrawString();

	// シーンを切り替える
	if (g_MouseFlg & MOUSE_INPUT_LEFT) {
		if ((g_MouseX > 400)
			&& (g_MouseX < 570)
			&& (g_MouseY > 600)
			&& (g_MouseY < 650)) {

			g_GameState = GAME_INIT; // ゲームスタートの選択
			//StopSoundMem(g_TitleBGM);
		}
		else if ((g_MouseX > 970)
			&& (g_MouseX < 1140)
			&& (g_MouseY > 600)
			&& (g_MouseY < 650)) {

			g_GameState = GAME_END;  // ゲームエンドの選択
			//StopSoundMem(g_TitleBGM);
		}
	}

	
	DrawBox(400,600,570,650,0x0000ff,false);
	DrawBox(970,600,1140,650,0x0000ff,false);

}

/********************************************************************
* ゲーム初期化処理
********************************************************************/
void GameInit(void) {
	charaA->jumpForce = 8.0f;
	charaB->jumpForce = 8.0f;
	charaB->px = 840.0f;
	charaA->speed = 5.0f;
	g_GameState = GAME_SELECT;
}


/********************************************************************
* ゲームエンド描画処理
********************************************************************/
void DrawEnd(void) {
	SetFontSize(50);
	DrawString(705,405,"ゲームを終了します",0xffffff,1);
	g_GameState = END;
}

/********************************************************************
* キャラ選択シーン
********************************************************************/
void GameSelect(void) {
	DrawExtendGraph(0, 0, 1440, 810, g_SelectImage, true);

	if (jump[0]) {
		g_GameState = GAME_BATTLE;
	}
}

/********************************************************************
*							戦闘シーン								*
*-------------------------------------------------------------------*
* GameBattle void型　[引数無し]										*
* PlayerDisp void型　[ジャンル番号、構造体データ、プレイヤー]		*
********************************************************************/


//関数の宣言
void HorrorMotion(struct chara* chara, int pl);
int HitCheck(float x,float y,float x2,float y2,int pl);
void subHP(int pl);

void GameBattle(void) {

	const int P1 = 0, P2 = 1;

	//背景
	DrawExtendGraph(0, 0, 1440, 810, g_BattleImage, true);

	//UI
	DrawBox(5,5,5 + charaA[Genre::HORROR].hp * 5,25,0xffff00,1);
	DrawBox(1435,5,1435 - charaB[Genre::HORROR].hp * 5,25,0xffff00,1);

	PlayerMove(Genre::HORROR, charaA ,P1);
	PlayerMove(Genre::HORROR, charaB ,P2);

}

void PlayerMove(int Gnum,struct chara *chara,int pl) {
	
	float gravity = 3.0f;
	
	DrawExtendGraph(chara->px,chara->py,chara->px + 200,chara->py + 200,g_HorrorImage[pl],true);

	//移動処理
	/*if (left[pl]) { chara->px -= 1.5f; }
	if (right[pl]) { chara->px += 1.5f; }*/

	DrawFormatString(100,200,0xff0000,"vec  = %d",charaA->vector);
	DrawFormatString(100,230,0xff0000,"vecO = %d",charaA->oldVec);
	DrawFormatString(100,260,0xff0000,"spd  = %f",charaA->speed);

	if (chara->vector != 0) {
		chara->speed -= 0.03f;
		if (chara->speed <= 0.0f) { chara->speed = 5.0f; chara->oldVec = chara->vector; chara->vector = 0; }
	}
	chara->px += chara->speed * chara->vector;


	if (up[pl])		chara->hp++;
	if (chara->hp > 100) chara->hp = 100;
	if (down[pl])	chara->hp--;
	if (chara->hp < 0) { chara->hp = 0; g_GameState = GAME_RESULT; }

	//ジャンプ処理
	if (jump[pl]) {
		
		SetFontSize(30);
		DrawString(chara->px -50, chara->py-35, "＼あははははは／", 0xff0000, 1);
		chara->py -= (chara->jumpForce - gravity);
		chara->jumpForce -= 0.1f;
		
		if (chara->py > 400.0f) {
			chara->py = 400.0f;
			chara->jumpForce = 8.0f;
			jump[pl] = false;
		}

	}

	//攻撃
	if (XButton[pl]) {
		HorrorMotion(chara,pl);
		subHP(1 - pl);
		XButton[pl] = false;
	}

	
}

////関数の宣言
//void HorrorMotion(struct chara* chara, int pl);
//int HitCheck();


//変数の宣言
int g_MotionCount;

void HorrorMotion(struct chara* chara, int pl) {


	if (g_MotionCount <= 20) {
		if (pl == 0)DrawBox(chara->px + 120, chara->py + 80, chara->px + 120 + 50, chara->py + 120 + 20, 0xffffff, false);
		if (pl == 1)DrawBox(chara->px + 80, chara->py + 80, chara->px + 80 - 50, chara->py + 120 + 20, 0xffffff, false);
	}
	else { g_MotionCount = 0; XButton[pl] = false; }

	if(pl == 0)HitCheck(chara->px + 120, chara->py + 80, chara->px + 120 + 50, chara->py + 120 + 20,pl);
	if(pl == 1)HitCheck(chara->px + 30, chara->py + 80, chara->px + 30 + 50, chara->py + 120 + 20,pl);

	g_MotionCount++;

}

int HitCheck(float x, float y, float x2, float y2,int pl) {

	

	return 0;
}

void subHP(int pl) {
	switch (pl) {
		case 0:
			charaA->hp-=30;
			break;

		case 1:
			charaB->hp-=30;
			break;
	}
}


/********************************************************************
* ゲームクリア描画処理
********************************************************************/
void DrawGameResult(void) {

	SetFontSize(45);
	DrawString(720,405,"1Ｐの勝ち!!",0x00ff00,1);

}

/********************************************************************
* ゲームオーバー描画処理
********************************************************************/
void DrawGameOver(void) {
	
}


/********************************************************************
* キー入力管理
********************************************************************/
void KeyInput() {

	//プレイヤー1用
	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_PAD1), KeyFlg1;
	OldKey1 = NowKey1;									//前フレームのキー取得
	NowKey1 = GetJoypadInputState(DX_INPUT_PAD1);		//現フレームのキー取得
	KeyFlg1 = NowKey1 & ~OldKey1;						//キーフラグ

	if (NowKey1 & PAD_INPUT_LEFT) 
	{
		charaA->speed = 5.0f;
		left[0] = true; charaA->vector = -1; 
	}
	else if (NowKey1 & PAD_INPUT_RIGHT)
	{
		charaA->speed = 5.0f;
		right[0] = true; charaA->vector = 1;
	}
	else { left[0] = false; right[0] = false; charaA->oldVec = charaA->vector; /*charaA->vector = 0;*/ }
	if (NowKey1 & PAD_INPUT_UP)			up[0] = true;		else    up[0] = false;
	if (NowKey1 & PAD_INPUT_DOWN)		down[0] = true;		else  down[0] = false;
	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = true;
	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;

	//プレイヤー2用
	//static int OldKey2, NowKey2 = GetJoypadInputState(DX_INPUT_PAD2), KeyFlg2;
	//OldKey2 = NowKey2;									//前フレームのキー取得
	//NowKey2 = GetJoypadInputState(DX_INPUT_PAD2);		//現フレームのキー取得
	//KeyFlg2 = NowKey2 & ~OldKey2;						//キーフラグ

	//if (NowKey2 & PAD_INPUT_LEFT)		left[1] = true;		else  left[1] = false;
	//if (NowKey2 & PAD_INPUT_RIGHT)		right[1] = true;	else right[1] = false;
	//if (NowKey2 & PAD_INPUT_UP)			up[1] = true;		else    up[1] = false;
	//if (NowKey2 & PAD_INPUT_DOWN)		down[1] = true;		else  down[1] = false;
	//if (KeyFlg2 & PAD_INPUT_A)			jump[1] = true;
	//if (KeyFlg2 & PAD_INPUT_3)			XButton[1] = true;
	//if (KeyFlg2 & PAD_INPUT_4)			YButton[1] = true;

	if (g_NowMouse & MOUSE_INPUT_LEFT)	mleft = true;	else mleft = false;
	if (g_NowMouse & MOUSE_INPUT_RIGHT) mright = true;	else mright = false;
}


/********************************************************************
* 画像読み込み
********************************************************************/
int LoadImages() {

	FILE* soiya;
	fopen_s(&soiya,"soiya.txt", "w");

	//タイトル
	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
		fwrite("タイトルの画像読み込みでエラー", sizeof(char),50, soiya);
		return -1;
	}

	//戦闘
	if ((g_BattleImage = LoadGraph("images/戦闘背景.png")) == -1) {
		fwrite("戦闘背景読み込みでエラー", sizeof(char), 50, soiya);
		return -1;
	}

	//キャラの画像
	if ((g_HorrorImage[0] = LoadGraph("images/ホラーキャラ.png")) == -1) {
		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
		return -1;
	}

	if ((g_HorrorImage[1] = LoadGraph("images/ホラーキャラ逆.png")) == -1) {
		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
		return -1;
	}

	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
		fwrite("キャラ選択画像読み込みでエラー", sizeof(char), 50, soiya);
		return -1;
	}



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

	fclose(soiya);

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

