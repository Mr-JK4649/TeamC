/*必要なやつの読み込み*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>


/*ヘッダファイルの読み込み*/
#include "header.h"
#include "function.h"
#include "Input.h"
#include "string.h"


#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)


/********************************************************************
* 変数の宣言
********************************************************************/
int g_GameState;			//ゲームのシーン管理

Input inp;
String str;

/*****************************************************
 * プログラムの開始
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("ＪＫ伝");		// タイトルを設定

	ChangeWindowMode(TRUE);							// ウィンドウモードで起動

	/**********************画像の大きさを変えるやつ*************************/
	/**/WindowScaler scale;											 	 /**/
	/**/scale.GetWindwScale(&scale);								 	 /**/
	/**/SetGraphMode(scale.Width, scale.Height, 16);					 /**/
	/***********************************************************************/


	if (DxLib_Init() == -1)							// DXライブラリの初期化処理
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏にする


	g_GameState = GAME_TITLE;

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {



		ClearDrawScreen();														// 画面の初期化

		inp.InputKey(&inp);
		inp.InputMouse(&inp);

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(scale.Width, scale.Height); break;		//ゲームタイトル処理

		//case GAME_INIT:		GameInit();  break;									//ゲーム初期処理

		//case GAME_S_SELECT:	GameSSelect(scale.Width, scale.Height);  break;		//ステージ選択画面処理

		case GAME_BASE:		DrawGameMain(scale.Width, scale.Height);  break;		//ゲームメイン画面処理

		//case GAME_RESULT:	DrawGameResult(scale.Width, scale.Height); break;		//ゲームメイン処理

		//case GAME_OVER:		DrawGameOver(scale.Width, scale.Height); break;		// ゲームオーバー描画処理

		//case GAME_END:		DrawEnd(scale.Width, scale.Height); break;			// ゲームオーバー描画処理

		}


		ScreenFlip();    // 裏画面の内容を表画面に反映



	}

	DxLib_End(); // DXライブラリ使用の終了処理

	return 0; // ソフトの終了
}

