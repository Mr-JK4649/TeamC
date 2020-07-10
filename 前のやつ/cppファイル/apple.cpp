/*必要なやつの読み込み*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>


/*ヘッダファイルの読み込み*/



#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)


/********************************************************************
* 変数の宣言
********************************************************************/

int g_GameState;			//ゲームのシーン管理



/********************************************************************
* 構造体の宣言
********************************************************************/



/*****************************************************
 * プログラムの開始
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("ジャンルで遊ぼう!!");		// タイトルを設定

	ChangeWindowMode(TRUE);							// ウィンドウモードで起動

	/**********************画像の大きさを変えるやつ*************************/
	/**/struct WindowScaler scale;
	/**/scale.GetWindwScale(&scale);
	/**/SetGraphMode(scale.Width, scale.Height,16);
	/***********************************************************************/


	if (DxLib_Init() == -1)							// DXライブラリの初期化処理
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏にする


	//サウンド読み込み
	if (LoadSounds() == -1)
		return -1;

	g_GameState = GAME_TITLE;

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {


		inp.InputKey(&inp);
		inp.InputMouse(&inp);


		ClearDrawScreen();														// 画面の初期化

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(scale.Width,scale.Height); break;		//ゲームタイトル処理

		case GAME_INIT:		GameInit();  break;									//ゲーム初期処理

		case GAME_C_SELECT:	GameCSelect(scale.Width, scale.Height);  break;	    //キャラ選択画面処理

		case GAME_S_SELECT:	GameSSelect(scale.Width, scale.Height);  break;		//ステージ選択画面処理

		case GAME_MAIN:		DrawGameMain(scale.Width, scale.Height);  break;	//ゲームメイン画面処理

		case GAME_RESULT:	DrawGameResult(scale.Width, scale.Height); break;	//ゲームメイン処理

		case GAME_OVER:		DrawGameOver(scale.Width, scale.Height); break;		// ゲームオーバー描画処理

		case GAME_END:		DrawEnd(scale.Width, scale.Height); break;			// ゲームオーバー描画処理

		}

		if (inp.Cclick) DebugMode(scale.Width, scale.Height, inp.MouseX, inp.MouseY);
		

		ScreenFlip();    // 裏画面の内容を表画面に反映

		

	}

	DxLib_End(); // DXライブラリ使用の終了処理

	return 0; // ソフトの終了
}



/********************************************************************
* ゲーム初期化処理
********************************************************************/
void GameInit(void) {
	charaA->jumpForce = 8.0f;
	charaB->jumpForce = 8.0f;
	charaB->px = 840.0f;
	charaA->speed = 5.0f;
	g_GameState = GAME_C_SELECT;
}


/********************************************************************
* ゲームエンド描画処理
********************************************************************/
void DrawEnd(int width, int height) {
	SetFontSize(50);
	DrawString(705,405,"ゲームを終了します",0xffffff,1);
	g_GameState = END;
}

/********************************************************************
* キャラ選択シーン
********************************************************************/
void GameCSelect(int width, int height) {

	struct WindowScaler scale;
	scale.GetWindwScale(&scale);

	inp.InputKey(&inp);
	inp.InputMouse(&inp);

	struct SelectImage chara;
	chara.ImageInput(&chara);

	if (inp.MouseX >= width - 65 && inp.MouseX <= width && inp.MouseY >= 315 && inp.MouseY <= 372)chara.Num = 1;
	else if (inp.MouseX >= 0 && inp.MouseX <= 65 && inp.MouseY >= 315 && inp.MouseY <= 372)chara.Num = 2;
	else if (inp.MouseX >= 470 && inp.MouseX <= 685 && inp.MouseY >= 580 && inp.MouseY <= 670) chara.Num = 3;
	else { chara.Num = 0; DrawString(width / 2, height / 2, "なんかおかしい", 0xffffff); }

	DrawExtendGraph(0, 0, width, height, chara.SadaoSelectImage[chara.Num], true);

	if (inp.MouseX >= 470 && inp.MouseX <= 685 && inp.MouseY >= 580 && inp.MouseY <= 670) {
		if (inp.NowMouse & MOUSE_INPUT_LEFT)g_GameState = GAME_S_SELECT;
	}
	/*DrawLine(0,inp.MouseY,width,inp.MouseY,0x0000ff,1);
	DrawLine(inp.MouseX,0,inp.MouseX,height,0xff0000,1);
	DrawFormatString(3, 5, 0x0000ff, "MouseX = %d", inp.MouseX);
	DrawFormatString(3, 25, 0xff0000, "MouseY = %d", inp.MouseY);
	DrawFormatString(3, 45, 0x0000ff, "MouseX = %04d %", inp.MouseX/scale.hiX);
	DrawFormatString(3, 65, 0xff0000, "MouseY = %04d %", inp.MouseY/scale.hiY);*/
	
}


/*******************************************************************
* ステージセンタk
********************************************************************/
void GameSSelect(int width, int height) {
	g_GameState = GAME_MAIN;
}

/********************************************************************
*							ゲームシーン							*
*-------------------------------------------------------------------*
*										*
*		*
********************************************************************/

float SetAngle(int angle);			//度数法で角度を得る
void Flashing(int paturn);			//電気の点滅をつかさどる	

//void DrawGameMain(int width, int height) {
//
//	struct Escape esc;
//	esc.ImageInput(&esc);
//
//	static int VecNum = 0;
//	
//	//背景
//	DrawExtendGraph(0, 0, width, height, esc.EscapeRoom[g_GraphNum], true);
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
//	}
	/*struct SelectImage chara;
	chara.ImageInput(&chara);

	DrawExtendGraph(0, 0, width, height, chara.SelectImage, true);

	if (jump[0] || inp.MouseFlg & MOUSE_INPUT_LEFT) {
		g_GameState = GAME_MAIN;
	}*/
//}




/********************************************************************
* ゲームクリア描画処理
********************************************************************/
void DrawGameResult(int width, int height) {

	SetFontSize(45);
	DrawString(width/2-100,height/2,"脱出成功！！！！",0x00ff00,1);

}

/********************************************************************
* ゲームオーバー描画処理
********************************************************************/
void DrawGameOver(int width, int height) {
	
}


/********************************************************************
* キー入力管理
********************************************************************/
void KeyInput() {

	//プレイヤー1用
	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1), KeyFlg1;
	OldKey1 = NowKey1;									//前フレームのキー取得
	NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//現フレームのキー取得
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
	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = !jump[0];
	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_B)			kettei = true;		else kettei = false;

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

}


/********************************************************************
* 画像読み込み
********************************************************************/
//int LoadImages() {
//
//	FILE* soiya;
//	fopen_s(&soiya,"soiya.txt", "w");
//
//	//タイトル
//	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
//		fwrite("タイトルの画像読み込みでエラー", sizeof(char),50, soiya);
//		return -1;
//	}
//
//	//ステージ
//	if ((g_Dh[0] = LoadGraph("images/h1.png")) == -1) {
//		fwrite("脱出画像1読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Dh[1] = LoadGraph("images/h2-3.png")) == -1) {
//		fwrite("脱出画像2読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Arrow = LoadGraph("images/矢印.png")) == -1) {
//		fwrite("矢印読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Ohuda = LoadGraph("images/お札2.png")) == -1) {
//		fwrite("お札読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//
//	//キャラの画像
//	if ((g_HorrorImage[0] = LoadGraph("images/ホラーキャラ.png")) == -1) {
//		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_HorrorImage[1] = LoadGraph("images/ホラーキャラ逆.png")) == -1) {
//		fwrite("ホラーキャラ画像読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
//		fwrite("キャラ選択画像読み込みでエラー", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//
//
//	////ステージ
//	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;
//
//	////ゲームクリア
//	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;
//
//	////ゲームオーバー
//	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;
//
//	////ブロック画像
//	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
//
//	////ナンバー画像の読み込み
//	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;
//
//	fclose(soiya);
//
//	return 0;
//}

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

