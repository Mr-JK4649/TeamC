///*必要なやつの読み込み*/
//#include "DxLib.h"
//#include <stdio.h>
//#include <iostream>
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include <wingdi.h>
//
//
///*ヘッダファイルの読み込み*/
//#include "Input.h"			//キーとマウス入力のやつ
//#include "State.h"			//ゲームのシーンを管理するやつ
//#include "LoadSource.h"		//画像とか音とかの宣言と読み込み
//
//
//#pragma warning(disable : 4244)
//#pragma warning(disable : 26812)
//#pragma warning(disable : 26451)
//
///********************************************************************
//* 列挙体の宣言
//********************************************************************/
////enum GAME_MODE {
////	GAME_TITLE,		//タイトル
////	GAME_INIT,		//初期化
////	GAME_END,		//エンド
////	GAME_BATTLE,	//戦闘
////	GAME_SELECT,	//キャラ選択
////	GAME_RESULT,	//リザルト
////	GAME_OVER,		//ゲームオーバー(？)
////	END = 99		//エンド用変数
////};
//
//enum Genre {
//	HORROR,			//ホラー
//	ACTION,			//アクション
//	RPG,			//RPG
//	NOVEL,			//ノベル
//	CARD,			//カード
//	STEALTH,		//ステルス
//	SIMULATION,		//シミュレーション
//	SHOOTING,		//シューティング
//	PUZZLE,			//パズル
//	MUSIC,			//音楽
//	RACE1,			//レース(レーサー)
//	RACE2			//レース(レースオフィシャル)
//};
//
//char genre[11][20] = {"ホラー","アクション","ＲＰＧ","ノベル","カード","ステルス","シミュ","シュート","パズル/脱出","音楽","レース"};
//
///********************************************************************
//* 定数の宣言
//********************************************************************/
//
//
//
///*******************************************************************
//*画像のあれ
//********************************************************************/
//////int g_TitleImage;				//タイトル画像
////int g_SelectImage;				//キャラ選択画像
////
//////キャラの画像
////int g_HorrorImage[4];			//ホラーキャラ
////
//////ステージの画像
////int g_Dh[2];
////int g_Ohuda;
////
////ステージの画像切り替え用
//int g_GraphNum=0; 
//
//
///********************************************************************
//* 変数の宣言
//********************************************************************/
////int g_OldKey;						// 前回の入力キー
////int g_NowKey;						// 今回の入力キー
////int g_KeyFlg;						// 入力キー情報
//int g_key[256];						// キーの情報を格納するやつ
//bool left[2], right[2], up[2], down[2],jump[2],XButton[2],YButton[2];				// キーの押下判定(添え字で判定：0が1Ｐ、1が2Ｐ)
//bool kettei;
//
////int g_OldMouse;				//前回のマウス
////int g_NowMouse;				//今回のマウス
////int g_MouseFlg;				//マウスフラグ
////int g_MouseX;				// マウスのX座標
////int g_MouseY;				// マウスのY座標
//bool mleft, mright;			// マウスの入力判定
//
//int g_GameState;			//ゲームのシーン管理
//int GenreNum;
//
////イベント用
//bool isEvent;
//int g_alpha;
//int g_EveCount;
//bool isOhuda;
//
///*サウンド*/
//
//
////デバッグ用
//bool isDebug;
//bool isStamp;
//bool isSave;
//int Ohu[20][3];
//int OhuNum;
//
///********************************************************************
//* 構造体の宣言
//********************************************************************/
//struct chara{
//	int hp=100;						//体力
//	int ap=0;						//アビリティのゲージ用
//	float px=400, py=400;			//キャラの座標
//	bool aFlg=false;				//アビリティ発動フラグ
//	float jumpForce=8.0f;			//ジャンプ力
//	int vector=0;					//進行ベクトル
//	int oldVec = 0;					//前のベクトル
//	float speed = 0;				//キャラのスピード
//};
//
//struct chara charaA[11];
//struct chara charaB[11];
//
///***********************************************
//  * 関数のプロトタイプ宣言
//***********************************************/
////キー入力のやつ
//void KeyInput(void);
//
//// ゲーム初期化処理
//void GameInit(void);
//
//// キャラ選択シーン
//void GameCSelect(void);
//
////ステージ選択シーン
//void GameSSelect(void);
//
//// 戦闘シーン
//void DrawGameMain(void);
//void PlayerMove(int genre,struct chara *chara,int pl);
//
//// ゲームタイトル描画処理
//void DrawGameTitle(void);
//
//// エンド描画処理
//void DrawEnd(void);
//
//// ゲームクリアーの処理
//void DrawGameResult(void);
//
//// ゲームオーバー描画処理
//void DrawGameOver(void);
//
//// 画像読み込み
//int LoadImages();
//
////サウンド
//int LoadSounds(void);
//
//
//Input inp;
//
///*****************************************************
// * プログラムの開始
// ****************************************************/
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
//	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
//
//
//	SetMainWindowText("ゲームジャンル王決定戦"); // タイトルを設定
//
//	ChangeWindowMode(TRUE);   // ウィンドウモードで起動
//
//	SetGraphMode(1440, 810,16,60);
//
//
//	if (DxLib_Init() == -1)   // DXライブラリの初期化処理
//		return -1;
//
//	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする
//
//	// 画像読み込み
//	/*if (LoadImages() == -1)
//		return -1;*/
//
//	//サウンド読み込み
//	if (LoadSounds() == -1)
//		return -1;
//
//	g_GameState = GAME_TITLE;
//
//	// ゲームループ
//	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {
//
//		//マウスの取得
//		//g_OldMouse = g_NowMouse;								//前フレームのキー取得
//		//g_NowMouse = GetMouseInput();							//現フレームの取得
//		//g_MouseFlg = g_NowMouse & ~g_OldMouse;					//マウスのフラグ
//		//GetMousePoint(&g_MouseX, &g_MouseY);					//マウスの位置を取得
//
//		inp.InputKey(&inp);
//		inp.InputMouse(&inp);
//
//
//		//KeyInput();			//キーの入力を管理
//
//
//		ClearDrawScreen();  // 画面の初期化
//
//		switch (g_GameState) {
//
//		case GAME_TITLE:	DrawGameTitle(); break;		 //ゲームタイトル処理
//
//		case GAME_INIT:		GameInit();  break;			 //ゲーム初期処理
//
//		case GAME_C_SELECT:	GameCSelect();  break;	     //キャラ選択画面処理
//
//	//	case GAME_S_SELECT:	GameSSelect();  break;	     //ステージ選択画面処理
//
//		case GAME_MAIN:		DrawGameMain();  break;		 //ゲームメイン画面処理
//
//		case GAME_RESULT:	DrawGameResult(); break;	 //ゲームメイン処理
//
//		case GAME_OVER:		DrawGameOver(); break;		 // ゲームオーバー描画処理
//
//		case GAME_END:		DrawEnd(); break;		 // ゲームオーバー描画処理
//
//		}
//
//		ScreenFlip();    // 裏画面の内容を表画面に反映
//
//	}
//
//	DxLib_End(); // DXライブラリ使用の終了処理
//
//	return 0; // ソフトの終了
//}
//
///********************************************************************
//* ゲームタイトル描画処理(メニュー画面)
//********************************************************************/
////void DrawGameTitle(void) {
////
////
////	//タイトルの画像表示
////	DrawExtendGraph(0, 0,1440,810, g_TitleImage, true);
////	//DrawString();
////
////	// シーンを切り替える
////	if (g_MouseFlg & MOUSE_INPUT_LEFT) {
////		if ((g_MouseX > 400)
////			&& (g_MouseX < 570)
////			&& (g_MouseY > 600)
////			&& (g_MouseY < 650)) {
////
////			g_GameState = GAME_INIT; // ゲームスタートの選択
////			//StopSoundMem(g_TitleBGM);
////		}
////		else if ((g_MouseX > 970)
////			&& (g_MouseX < 1140)
////			&& (g_MouseY > 600)
////			&& (g_MouseY < 650)) {
////
////			g_GameState = GAME_END;  // ゲームエンドの選択
////			//StopSoundMem(g_TitleBGM);
////		}
////	}
////
////	
////	DrawBox(400,600,570,650,0x0000ff,false);
////	DrawBox(970,600,1140,650,0x0000ff,false);
////
////}
//
////void DrawGameTitle(void) {
////	
////	inp.InputKey(&inp);
////	inp.InputMouse(&inp);
////
////	//タイトルの画像表示
////	DrawExtendGraph(0, 0, 1440, 810, g_TitleImage, true);
////	//DrawString();
////
////	// シーンを切り替える
////	if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
////		if ((inp.MouseX > 400)
////			&& (inp.MouseX < 570)
////			&& (inp.MouseY > 600)
////			&& (inp.MouseY < 650)) {
////
////			g_GameState = GAME_INIT; // ゲームスタートの選択
////			DrawBox(0,0,200,200,0x000000,1);
////			//StopSoundMem(g_TitleBGM);
////		}
////		else if ((inp.MouseX > 970)
////			&& (inp.MouseX < 1140)
////			&& (inp.MouseY > 600)
////			&& (inp.MouseY < 650)) {
////
////			g_GameState = GAME_END;  // ゲームエンドの選択
////			//StopSoundMem(g_TitleBGM);
////		}
////	}
////
////	DrawFormatString(5,5,0x000000,"mlef = %d",inp.mleft);
////	DrawFormatString(5,25,0x000000,"mrig = %d",inp.mright);
////	DrawFormatString(5,45,0x000000,"mouseO = %d",inp.OldMouse);
////	DrawFormatString(5,65,0x000000,"mouseN = %d",inp.NowMouse);
////	DrawFormatString(5,85,0x000000,"mouseF = %d",inp.MouseFlg);
////
////	DrawBox(400, 600, 570, 650, 0x0000ff, false);
////	DrawBox(970, 600, 1140, 650, 0x0000ff, false);
////
////}
//
///********************************************************************
//* ゲーム初期化処理
//********************************************************************/
//void GameInit(void) {
//	charaA->jumpForce = 8.0f;
//	charaB->jumpForce = 8.0f;
//	charaB->px = 840.0f;
//	charaA->speed = 5.0f;
//	g_GameState = GAME_C_SELECT;
//	g_alpha = 255;
//	g_EveCount = 0;
//	isOhuda = false;
//	isStamp = false;
//	isSave = false;
//}
//
//
///********************************************************************
//* ゲームエンド描画処理
//********************************************************************/
//void DrawEnd(void) {
//	SetFontSize(50);
//	DrawString(705,405,"ゲームを終了します",0xffffff,1);
//	g_GameState = END;
//}
//
///********************************************************************
//* キャラ選択シーン
//********************************************************************/
//void GameCSelect(void) {
//
//	struct SelectImage chara;
//	chara.ImageInput(&chara);
//
//	DrawExtendGraph(0, 0, 1440, 810, chara.SelectImage, true);
//
//	if (jump[0] || inp.MouseFlg & MOUSE_INPUT_LEFT) {
//		g_GameState = GAME_MAIN;
//	}
//}
//
///********************************************************************
//*							ゲームシーン							*
//*-------------------------------------------------------------------*
//*										*
//*		*
//********************************************************************/
//
//float SetAngle(int angle);			//度数法で角度を得る
//void Flashing(int paturn);			//電気の点滅をつかさどる	
//
//void DrawGameMain(void) {
//
//	struct Escape esc;
//	esc.ImageInput(&esc);
//
//	static int VecNum = 0;
//	
//	//背景
//	DrawExtendGraph(0, 0, 1440, 810, esc.EscapeRoom[g_GraphNum], true);
//
//	if (isOhuda) {
//		DrawRotaGraph(540, 300, 1.0f, SetAngle(200), esc.Ohuda, 1);
//		DrawRotaGraph(540, 400, 1.0f, SetAngle(225), esc.Ohuda, 1);
//		DrawRotaGraph(530, 550, 1.0f, SetAngle(30), esc.Ohuda, 1);
//
//		DrawRotaGraph(680, 300, 1.0f, SetAngle(180), esc.Ohuda, 1);
//		DrawRotaGraph(600, 200, 1.0f, SetAngle(180), esc.Ohuda, 1);
//		DrawRotaGraph(630, 200, 1.0f, SetAngle(150), esc.Ohuda, 1);
//		DrawRotaGraph(690, 200, 1.0f, SetAngle(250), esc.Ohuda, 1);
//		DrawRotaGraph(750, 200, 1.0f, SetAngle(70), esc.Ohuda, 1);
//
//		DrawRotaGraph(830, 500, 1.0f, SetAngle(135), esc.Ohuda, 1);
//		DrawRotaGraph(830, 600, 1.0f, SetAngle(45), esc.Ohuda, 1);
//		DrawRotaGraph(830, 250, 1.0f, SetAngle(135), esc.Ohuda, 1);
//	}
//	
//	if (!isEvent) {
//
//		if (inp.MouseX <= 100) {
//			DrawRotaGraph(80, 400, 0.05f, SetAngle(180), esc.Arrow, 1);
//			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
//				if (--VecNum < 0) VecNum = 3;
//
//			}
//		}
//		if (inp.MouseX >= 1340) {
//			DrawRotaGraph(1360, 400, 0.05f, SetAngle(0), esc.Arrow, 1);
//			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
//				if (++VecNum > 3) VecNum = 0;
//
//			}
//		}
//
//		g_GraphNum = VecNum == 0 ? 0 : 1;
//	}
//	else {
//		
//		Flashing(1);
//
//	}
//
//	if (inp.MouseX >= 890 && inp.MouseX <= 940 && inp.MouseY >= 760 && inp.MouseY <= 810) {
//		DrawBox(890,760,940,810,0x00ff00,true);
//		if (inp.MouseFlg & MOUSE_INPUT_LEFT) { isEvent = !isEvent; g_EveCount = 0; }
//	}
//
//	//ここから下はデバッグ用
//	if (inp.MouseFlg & MOUSE_INPUT_RIGHT) isDebug = !isDebug;
//	
//	if (isDebug) {
//		DrawString(1275,5,"Mode : デバッグ",0xff0000,1);
//		SetFontSize(20);
//		DrawFormatString(3,5,0xff0000,"VecNum = %d",VecNum);
//		DrawFormatString(3,25,0xff0000,"Graph  = %d",g_GraphNum);
//		DrawFormatString(3,45,0xff0000,"isEve  = %d",isEvent);
//		DrawFormatString(3,65,0xff0000,"ジャンル：%s × %sステージ",genre[GenreNum],genre[Genre::PUZZLE]);
//		DrawFormatString(3,85,0x0000ff,"MouseX = %d",inp.MouseX);
//		DrawFormatString(3,105,0xff0000,"MouseY = %d",inp.MouseY);
//
//		DrawLine(0,inp.MouseY,1440,inp.MouseY,0x0000ff,1);
//		DrawLine(inp.MouseX,0,inp.MouseX,810,0xff0000,1);
//
//		if (jump[0]) {
//			static int angle;
//
//			if (up[0]) angle++;
//			if (down[0]) angle--;
//
//			if (kettei) { Ohu[OhuNum][0] = inp.MouseX; Ohu[OhuNum][1] = inp.MouseY; Ohu[OhuNum++][2] = angle; }
//
//			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
//			DrawRotaGraph(inp.MouseX, inp.MouseY, 1.0f, SetAngle(angle), esc.Ohuda, 1);
//			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
//
//			for (int i = 0; i < 20; i++) {
//				if (Ohu[i][0] != 0) {
//					DrawRotaGraph(Ohu[i][0], Ohu[i][1], 1.0f, SetAngle(Ohu[i][2]), esc.Ohuda, 1);
//					DrawFormatString(3,125 + 20*i,0x000000,"%d = x:%d y:%d",i,Ohu[i][0],Ohu[i][1]);
//				}
//			}
//
//
//		}
//
//	}
//
//
//
//}
//
//float SetAngle(int angle){
//	
//	const float rad = 3.14159 / 180;
//
//	return rad * angle;
//
//}
//
//void Flashing(int paturn) {
//	++g_EveCount;
//
//	switch (paturn) {
//		case 1:
//			if (g_EveCount <= 5) g_alpha = 156;
//			else if (g_EveCount <= 40) g_alpha = 0;
//			else if (g_EveCount <= 45) g_alpha = 156;
//			else if (g_EveCount <= 55) g_alpha = 0;
//			else if (g_EveCount <= 65) g_alpha = 180;
//			else if (g_EveCount <= 80) g_alpha = 0;
//			else if (g_EveCount <= 110) { g_alpha = 230; isOhuda = true; }
//			else if (g_EveCount >= 120) g_alpha = 0;
//			break;
//
//		case 2:
//			break;
//
//		case 3:
//			break;
//	}
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_alpha);
//	DrawBox(0, 0, 1440, 810, 0x000000, true);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
//}
//
//
///********************************************************************
//* ゲームクリア描画処理
//********************************************************************/
//void DrawGameResult(void) {
//
//	SetFontSize(45);
//	DrawString(720,405,"1Ｐの勝ち!!",0x00ff00,1);
//
//}
//
///********************************************************************
//* ゲームオーバー描画処理
//********************************************************************/
//void DrawGameOver(void) {
//	
//}
//
//
///********************************************************************
//* キー入力管理
//********************************************************************/
//void KeyInput() {
//
//	//プレイヤー1用
//	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1), KeyFlg1;
//	OldKey1 = NowKey1;									//前フレームのキー取得
//	NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//現フレームのキー取得
//	KeyFlg1 = NowKey1 & ~OldKey1;						//キーフラグ
//
//	if (NowKey1 & PAD_INPUT_LEFT) 
//	{
//		charaA->speed = 5.0f;
//		left[0] = true; charaA->vector = -1; 
//	}
//	else if (NowKey1 & PAD_INPUT_RIGHT)
//	{
//		charaA->speed = 5.0f;
//		right[0] = true; charaA->vector = 1;
//	}
//	else { left[0] = false; right[0] = false; charaA->oldVec = charaA->vector; /*charaA->vector = 0;*/ }
//	if (NowKey1 & PAD_INPUT_UP)			up[0] = true;		else    up[0] = false;
//	if (NowKey1 & PAD_INPUT_DOWN)		down[0] = true;		else  down[0] = false;
//	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = !jump[0];
//	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
//	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;
//	if (KeyFlg1 & PAD_INPUT_B)			kettei = true;		else kettei = false;
//	if (KeyFlg1 & KEY_INPUT_H)			isSave = true;		else isSave = false;
//
//	//プレイヤー2用
//	//static int OldKey2, NowKey2 = GetJoypadInputState(DX_INPUT_PAD2), KeyFlg2;
//	//OldKey2 = NowKey2;									//前フレームのキー取得
//	//NowKey2 = GetJoypadInputState(DX_INPUT_PAD2);		//現フレームのキー取得
//	//KeyFlg2 = NowKey2 & ~OldKey2;						//キーフラグ
//
//	//if (NowKey2 & PAD_INPUT_LEFT)		left[1] = true;		else  left[1] = false;
//	//if (NowKey2 & PAD_INPUT_RIGHT)		right[1] = true;	else right[1] = false;
//	//if (NowKey2 & PAD_INPUT_UP)			up[1] = true;		else    up[1] = false;
//	//if (NowKey2 & PAD_INPUT_DOWN)		down[1] = true;		else  down[1] = false;
//	//if (KeyFlg2 & PAD_INPUT_A)			jump[1] = true;
//	//if (KeyFlg2 & PAD_INPUT_3)			XButton[1] = true;
//	//if (KeyFlg2 & PAD_INPUT_4)			YButton[1] = true;
//
//}
//
//
///********************************************************************
//* 画像読み込み
//********************************************************************/
////int LoadImages() {
////
////	FILE* soiya;
////	fopen_s(&soiya,"soiya.txt", "w");
////
////	//タイトル
////	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
////		fwrite("タイトルの画像読み込みでエラー", sizeof(char),50, soiya);
////		return -1;
////	}
////
////	//ステージ
////	if ((g_Dh[0] = LoadGraph("images/h1.png")) == -1) {
////		fwrite("脱出画像1読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Dh[1] = LoadGraph("images/h2-3.png")) == -1) {
////		fwrite("脱出画像2読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Arrow = LoadGraph("images/矢印.png")) == -1) {
////		fwrite("矢印読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Ohuda = LoadGraph("images/お札2.png")) == -1) {
////		fwrite("お札読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////
////	//キャラの画像
////	if ((g_HorrorImage[0] = LoadGraph("images/ホラーキャラ.png")) == -1) {
////		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_HorrorImage[1] = LoadGraph("images/ホラーキャラ逆.png")) == -1) {
////		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
////		fwrite("キャラ選択画像読み込みでエラー", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////
////
////	////ステージ
////	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;
////
////	////ゲームクリア
////	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;
////
////	////ゲームオーバー
////	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;
////
////	////ブロック画像
////	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
////
////	////ナンバー画像の読み込み
////	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;
////
////	fclose(soiya);
////
////	return 0;
////}
//
///********************************************************************
//* サウンド読み込み
//********************************************************************/
//int LoadSounds(void) {
//
//	////タイトル
//	//if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
//	////クリア
//	//if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//	////オーバー
//	//if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
//	////マウスクリック
//	//if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
//	////ブロック消去
//	//if ((g_TitleBGM = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
//	////ブロック移動
//	//if ((g_TitleBGM = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;
//
//
//
//	return 0;
//}
//
