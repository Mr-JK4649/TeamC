#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#include "State.h"

/*関数のプロト*/


//int g_OldMouse;				//前回のマウス
//int g_NowMouse;				//今回のマウス
//int g_MouseFlg;				//マウスフラグ
//int g_MouseX;				// マウスのX座標
//int g_MouseY;				// マウスのY座標



struct Input {
	int OldKey=0;				//前回のキー入力
	int NowKey=0;				//現在のキー入力
	int KeyFlg=0;				//キー入力のフラグ

	
	int OldMouse=0;				//前回のマウス入力
	int NowMouse=0;				//現在のマウス入力
	int MouseFlg=0;				//マウス入力のフラグ
	int MouseX=0;				//マウスのＸ座標
	int MouseY=0;				//マウスのＹ座標
	bool mleft=0, mright=0;		//マウスのブール型

	struct Input InputKey(struct Input* inp) {
		inp->OldKey = inp->NowKey;									//前フレームのキー取得
		inp->NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//現フレームのキー取得
		inp->KeyFlg = inp->NowKey & ~inp->OldKey;					//キーフラグ

		

		return *inp;
	}

	struct Input InputMouse(struct Input* inp)
	{	
		inp->OldMouse = inp->NowMouse;
		inp->NowMouse = GetMouseInput();
		inp->MouseFlg = inp->NowMouse & ~inp->OldMouse;

		GetMousePoint(&inp->MouseX, &inp->MouseY);

		if (inp->MouseFlg & MOUSE_INPUT_LEFT) inp->mleft = true;	else inp->mleft = false;

		return *inp;
	}

};