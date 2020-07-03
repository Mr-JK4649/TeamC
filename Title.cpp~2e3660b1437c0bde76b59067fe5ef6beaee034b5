/*必要なやつの読み込み*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

/*ヘッダファイル読み込み*/
#include "Input.h"
#include "State.h"
#include "LoadSource.h"
#include "WindowScale.h"


extern int g_GameState;

void DrawGameTitle(int width,int height) {

	struct TitleImage title;
	title.ImageInput(&title);
	
	Input inp;
	inp.InputKey(&inp);
	inp.InputMouse(&inp);


	//タイトルの画像表示
	DrawExtendGraph(0, 0, width, height, title.TitleImage, true);
	//DrawString();


	// シーンを切り替える
	if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
		if ((inp.MouseX > 400)
			&& (inp.MouseX < 570)
			&& (inp.MouseY > 600)
			&& (inp.MouseY < 650)) {

			g_GameState = GAME_INIT; // ゲームスタートの選択
			DrawBox(0, 0, 200, 200, 0x000000, 1);
			//StopSoundMem(g_TitleBGM);
		}
		else if ((inp.MouseX > 970)
			&& (inp.MouseX < 1140)
			&& (inp.MouseY > 600)
			&& (inp.MouseY < 650)) {

			g_GameState = GAME_END;  // ゲームエンドの選択
			//StopSoundMem(g_TitleBGM);
		}
	}

	DrawFormatString(5, 5, 0x000000, "mlef = %d", inp.mleft);
	DrawFormatString(5, 25, 0x000000, "mrig = %d", inp.mright);
	DrawFormatString(5, 45, 0x000000, "mouseO = %d", inp.OldMouse);
	DrawFormatString(5, 65, 0x000000, "mouseN = %d", inp.NowMouse);
	DrawFormatString(5, 85, 0x000000, "mouseF = %d", inp.MouseFlg);

	DrawBox(400, 600, 570, 650, 0x0000ff, false);
	DrawBox(970, 600, 1140, 650, 0x0000ff, false);

}

//void DrawGameTitle(void) {
//	Input inp = inp.InputKey(&inp);
//
//	//タイトルの画像表示
//	DrawExtendGraph(0, 0, 1440, 810, g_TitleImage, true);
//	//DrawString();
//
//	// シーンを切り替える
//	if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
//		if ((inp.MouseX > 400)
//			&& (inp.MouseX < 570)
//			&& (inp.MouseY > 600)
//			&& (inp.MouseY < 650)) {
//
//			g_GameState = GAME_INIT; // ゲームスタートの選択
//			//StopSoundMem(g_TitleBGM);
//		}
//		else if ((inp.MouseX > 970)
//			&& (inp.MouseX < 1140)
//			&& (inp.MouseY > 600)
//			&& (inp.MouseY < 650)) {
//
//			g_GameState = GAME_END;  // ゲームエンドの選択
//			//StopSoundMem(g_TitleBGM);
//		}
//	}
//
//
//	DrawBox(400, 600, 570, 650, 0x0000ff, false);
//	DrawBox(970, 600, 1140, 650, 0x0000ff, false);
//
//}

