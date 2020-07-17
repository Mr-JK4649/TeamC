#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

struct Input {
	
	/*十字キーの判定*/
	bool up = 0;				//上
	bool down = 0;				//下
	bool left = 0;				//左
	bool right = 0;				//右

	/*その他のキー*/
	bool space = 0,start = 0,x = 0, z = 0;

	int a=0;

	
	/*マウスの判定*/
	int MouseX = 0;					//マウスのＸ座標
	int MouseY = 0;					//マウスのＹ座標
	bool Lclick = 0, Rclick = 0, Cclick = 0, Lhold = 0, Rhold = 0, Ldrag = 0, Rgrag = 0;		//マウスのブール型


	/*キー入力*/
	struct Input InputKey(struct Input* inp) {
		inp->OldKey = inp->NowKey;									//前フレームのキー取得
		inp->NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//現フレームのキー取得
		inp->KeyFlg = inp->NowKey & ~inp->OldKey;					//キーフラグ

		if (NowKey & PAD_INPUT_LEFT)	inp->left = true;		else inp->left = false;
		if (NowKey & PAD_INPUT_RIGHT)	inp->right = true;		else inp->right = false;
		if (NowKey & PAD_INPUT_UP)		inp->up = true;			else inp->up = false;
		if (NowKey & PAD_INPUT_DOWN)	inp->down = true;		else inp->down = false;
		if (KeyFlg & PAD_INPUT_B)		inp->space = true;		else inp->space = false;
		if (KeyFlg & PAD_INPUT_R)		inp->start = true;		else inp->start = false;

		a = inp->NowKey;

		return *inp;
	}

	/*マウス入力*/
	struct Input InputMouse(struct Input* inp)
	{
		inp->OldMouse = inp->NowMouse;
		inp->NowMouse = GetMouseInput();
		inp->MouseFlg = inp->NowMouse & ~inp->OldMouse;

		GetMousePoint(&inp->MouseX, &inp->MouseY);

		if (inp->NowMouse & MOUSE_INPUT_LEFT) inp->Lhold = true; else inp->Lhold = false;
		if (inp->NowMouse & MOUSE_INPUT_RIGHT)inp->Rhold = true; else inp->Rhold = false;
		if (inp->MouseFlg & MOUSE_INPUT_LEFT)inp->Lclick = true; else inp->Lclick = false;
		if (inp->MouseFlg & MOUSE_INPUT_MIDDLE) inp->Cclick = !inp->Cclick;
		if (inp->MouseFlg & MOUSE_INPUT_RIGHT) inp->Rclick = true; else inp->Rclick = false;

		return *inp;
	}

private:
	int OldKey = 0;						//前回のキー入力
	int NowKey = 0;						//現在のキー入力
	int KeyFlg = 0;						//キー入力のフラグ

	int OldMouse = 0;					//前回のマウス入力
	int NowMouse = 7;					//現在のマウス入力
	int MouseFlg = 0;					//マウス入力のフラグ
};

extern Input inp;