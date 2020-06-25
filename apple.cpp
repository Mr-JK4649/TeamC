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
int g_TitleImage;
int g_BattleImage;

int g_HorrorImage[4];


/********************************************************************
* 変数の宣言
********************************************************************/
int g_OldKey;						// 前回の入力キー
int g_NowKey;						// 今回の入力キー
int g_KeyFlg;						// 入力キー情報
int g_key[256];						// キーの情報を格納するやつ
bool left, right, up, down,jump;	// キーの押下判定

int g_OldMouse;				//前回のマウス
int g_NowMouse;				//今回のマウス
int g_MouseFlg;				//マウスフラグ
int g_MouseX;				// マウスのX座標
int g_MouseY;				// マウスのY座標
bool mleft, mright;			// マウスの入力判定

int g_GameState;			//ゲームのシーン管理


//キャラに関するやつ
float jumpForce = 8.0f;			//ジャンプ力


/*サウンド*/


/********************************************************************
* 構造体の宣言
********************************************************************/
struct chara{
	int hp=5;					//体力
	int ap=5;					//アビリティのゲージ用
	float px=400, py=400;	//キャラの座標
	bool aFlg;				//アビリティ発動フラグ
};

struct chara chara[11];



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
void PlayerA(int genre,float* px ,float* py);

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
	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {


		// 入力キー取得
		g_OldKey = g_NowKey;									//前フレームのキー取得
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//現フレームのキー取得
		g_KeyFlg = g_NowKey & ~g_OldKey;						//キーフラグ

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
			&& (g_MouseY > 500)
			&& (g_MouseY < 550)) {

			g_GameState = GAME_BATTLE; // ゲームスタートの選択
			//StopSoundMem(g_TitleBGM);
		}
		else if ((g_MouseX > 870)
			&& (g_MouseX < 1040)
			&& (g_MouseY > 500)
			&& (g_MouseY < 550)) {

			g_GameState = GAME_END;  // ゲームエンドの選択
			//StopSoundMem(g_TitleBGM);
		}
	}

	
	DrawBox(400,500,570,550,0x0000ff,false);
	DrawBox(870,500,1040,550,0x0000ff,false);

}

/********************************************************************
* ゲーム初期化処理
********************************************************************/
void GameInit(void) {
	jumpForce = 8.0f;
}


/********************************************************************
* ゲームエンド描画処理
********************************************************************/
void DrawEnd(void) {

}

/********************************************************************
* キャラ選択シーン
********************************************************************/
void GameSelect(void) {

}

/********************************************************************
*							戦闘シーン								*
*-------------------------------------------------------------------*
* GameBattle void型　[引数無し]										*
* PlayerDisp void型　[ジャンル番号、ｘ座標、ｙ座標]					*
********************************************************************/
void GameBattle(void) {

	DrawExtendGraph(0, 0, 1440, 810, g_BattleImage, true);

	PlayerA(Genre::HORROR, &chara[Genre::HORROR].px, &chara[Genre::HORROR].py);

}

void PlayerA(int Gnum, float* px, float* py) {
	
	float gravity = 3.0f;

	//DrawBoxAA(*px, *py, *px + 30, *py + 80, 0xffffff, true, 1.0f);
	DrawExtendGraph(*px,*py,*px + 200,*py + 200,g_HorrorImage[0],true);

	if (left)	*px -= 1.5f;
	if (right)	*px += 1.5f;
	if (jump) {
		
		SetFontSize(30);
		DrawString(*px-60, *py-35, "＼あははははは／", 0xff0000, 1);
		*py -= (jumpForce - gravity);
		jumpForce -= 0.1f;
		
		if (*py > 450.0f) {
			*py = 450.0f;
			jumpForce = 8.0f;
			jump = false; 
		}


	}
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
* キー入力管理
********************************************************************/
void KeyInput() {
	if (g_NowKey & PAD_INPUT_4 || g_NowKey & PAD_INPUT_LEFT)	 left = true;	else  left = false;
	if (g_NowKey & PAD_INPUT_6 || g_NowKey & PAD_INPUT_RIGHT)	 right = true;	else right = false;
	if (g_NowKey & PAD_INPUT_8 || g_NowKey & PAD_INPUT_UP)		 up = true;		else    up = false;
	if (g_NowKey & PAD_INPUT_5 || g_NowKey & PAD_INPUT_DOWN)	 down = true;	else  down = false;
	if (g_KeyFlg & PAD_INPUT_10)								 jump = true;	//else  jump = false;

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
	if ((g_TitleImage = LoadGraph("images/タイトル画面.png")) == -1) { 
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

