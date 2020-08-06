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
	bool up = 0;				//上(長押し)
	bool down = 0;				//下(長押し)
	bool left = 0;				//左(長押し)
	bool right = 0;				//右(長押し)

	bool f_up = 0;				//上(一回)
	bool f_down = 0;			//下(一回)
	bool f_left = 0;			//右(一回)
	bool f_right = 0;			//左(一回)


	/*その他のキー*/
	bool space = 0,start = 0,sele = 0,cancel = 0,x = 0, z = 0,y = 0;

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

		if (NowKey & PAD_INPUT_LEFT)	inp->left = true;		else inp->left = false;			//左長押し
		if (NowKey & PAD_INPUT_RIGHT)	inp->right = true;		else inp->right = false;		//右長押し
		if (NowKey & PAD_INPUT_UP)		inp->up = true;			else inp->up = false;			//上長押し
		if (NowKey & PAD_INPUT_DOWN)	inp->down = true;		else inp->down = false;			//下長押し
		if (KeyFlg & PAD_INPUT_B)		inp->space = true;		else inp->space = false;		//Ｂボタン一回
		if (KeyFlg & PAD_INPUT_A)		inp->cancel = true;		else inp->cancel = false;		//Ａボタン一回
		if (NowKey & PAD_INPUT_C)		inp->y = true;			else inp->y = false;			//Ｙボタン一回
		if (NowKey & PAD_INPUT_X)		inp->x = true;			else inp->x = false;			//Ｘボタン一回
		if (KeyFlg & PAD_INPUT_R)		inp->start = true;		else inp->start = false;		//ＳＴＡＲＴボタン一回
		if (KeyFlg & PAD_INPUT_L)		inp->sele = true;		else inp->sele = false;			//ＳＥＬＥＣＴボタン一回
		if (KeyFlg & PAD_INPUT_LEFT)	inp->f_left = true;		else inp->f_left = false;		//左一回
		if (KeyFlg & PAD_INPUT_RIGHT)	inp->f_right = true;	else inp->f_right = false;		//右一回
		if (KeyFlg & PAD_INPUT_UP)		inp->f_up = true;		else inp->f_up = false;			//上一回
		if (KeyFlg & PAD_INPUT_DOWN)	inp->f_down = true;		else inp->f_down = false;		//下一回

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