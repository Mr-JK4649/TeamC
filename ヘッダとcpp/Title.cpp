#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

Title title;

void DrawGameTitle(int Width, int Height) {

	//一回だけ初期化
	if (title.flg) { title.ImageInput(&title); title.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, title.image, 1);
	//DrawGraph(50,150,title.logo,1);
	
	//DrawBox(Width / 10 * 1, Height / 10 * 7, Width / 10 * 3, Height / 10 * 8,0x0000ff,1);//でバックよう

	DrawFormatString(0, 0, 0x0000ff,"x=%d y=%d",inp.MouseX,inp.MouseY);
	
	if (inp.MouseX >= 750 &&
		inp.MouseX <= 1000 &&
		inp.MouseY >= 400 &&
		inp.MouseY <= 450 ) {
		
		if (inp.Lclick)
		{
			g_GameState = GAME_BASE;//titleの始めるを押した場合、ゲームメインへ進む
		}   
		//if (inp.Lclick)SuperString(200,200,"シーンを切り替えました。",0x000000,0,16);
	}

	if (inp.MouseX >= 760 &&
		inp.MouseX <= 900 &&
		inp.MouseY >= 500 &&
		inp.MouseY <= 540) {

		if (inp.Lclick) {
			DxLib_End(); // titleの終わるを押した場合、ゲームDXライブラリ使用の終了処理終了へ進む
		}
		//if (inp.Lclick)SuperString(200,200,"シーンを切り替えました。",0x000000,0,16);
	}

	/*DrawLine(0,Height/2,Width,Height/2,0xffffff,1);
	DrawLine(Width/2,0,Width/2,Height,0xffffff,1);*/
	//SuperString(Width / 3, Height / 4, "ＪＫ伝",0x000000,1,100);
	
}