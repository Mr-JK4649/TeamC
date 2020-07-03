/*必要なやつの読み込み*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Input.h"			//キーとマウス入力のやつ

extern int g_GameState;

bool flg = false;
int value[3] = { 255,255,0 };
char str[3][20] = { "Screen Brightness","Menu Opacity","Details" };
int selc=0;

extern struct Input inp;

void DebugMode(int width, int height, int x, int y) {
		
		SetFontSize(16);
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - value[0]);
		DrawBox(0, 0, width, height, 0x000000, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value[1]);
		DrawLine(0, y, width, y, 0x0000ff, 1);
		DrawLine(x, 0, x, height, 0xff0000, 1);
		DrawLine(0, height/2, width, height/2, 0x0000ff, 1);
		DrawLine(width/2, 0, width/2, height, 0xff0000, 1);

		DrawRoundRect(5, height - 55, width - 5, height - 5, 10, 10, 0x444444, 1);
		DrawRoundRect(5, height - 55, width - 5, height - 5, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, height - 54, width - 6, height - 6, 10, 10, 0xffffff, 0);

		/*画面関係*/
		DrawRoundRect(5, height - 240, 315, height - 60, 5, 5, 0x444444, 1);
		DrawRoundRect(5, height - 240, 315, height - 60, 5, 5, 0xaaaaaa, 0);
		DrawRoundRect(6, height - 239, 314, height - 61, 5, 5, 0xffffff, 0);

		/*シーン強制遷移*/
		DrawRoundRect(320, height - 240, 395, height - 60, 5, 5, 0x444444, 1);
		DrawRoundRect(320, height - 240, 395, height - 60, 5, 5, 0xaaaaaa, 0);
		DrawRoundRect(321, height - 239, 394, height - 61, 5, 5, 0xffffff, 0);
		DrawString(325,height - 235,"タイトル", selc == 0 ? 0xff0000 : 0xffffff,0);
		DrawString(325,height - 210,"終　　了", selc == 1 ? 0xff0000 : 0xffffff,0);
		DrawString(325,height - 185,"キャラ選", selc == 2 ? 0xff0000 : 0xffffff,0);
		DrawString(325,height - 160,"ステジ選", selc == 3 ? 0xff0000 : 0xffffff,0);
		DrawString(325,height - 135,"リザルト", selc == 4 ? 0xff0000 : 0xffffff,0);
		DrawString(325,height - 110,"オーバー", selc == 5 ? 0xff0000 : 0xffffff,0);

		/*表示*/
		for (int i = 0; i < 3; i++) {
			int addn = i * 55;

			//DrawString(15, scale.Height - 235 + addn, "Screen Brightness", 0xffffff, 1);
			DrawFormatString(15, height - 235 + addn, 0x00ffff, "%s", str[i]);
			DrawLine(45, height - 205 + addn, 310, height - 205 + addn, 0xffffff, 3);
			DrawFormatString(15, height - 210 + addn, 0xffffff, "%3d", value[i]);
			DrawCircle(50 + value[i], height - 205 + addn, 5, 0xffffff, 1, 1);

			if (inp.Rhold) {

				if (x >= 45 && x <= 310 && y >= height - 220 + addn && y <= height - 190 + addn) {
					value[i] = x - 50;
				}

				if (value[i] > 255) value[i] = 255;
				if (value[i] < 0 + 70 * (i % 2)) value[i] = 0 + 70 * (i % 2);

			}
		}

		/*シーン遷移のやつ*/
		if (x >= 325 && x <= 390 && y >= height - 235 && y <= height - 90) { selc = y - (height - 235); selc /= 25; }
		else selc = 99;

		if (inp.Rclick) {
			DrawString(400,400,"あああああ",0x000000,1);
			switch (selc) {
				case 0: g_GameState = GAME_TITLE; break;
				case 1: g_GameState = GAME_END; break;
				case 2: g_GameState = GAME_C_SELECT; break;
				case 3: g_GameState = GAME_END; break;
				case 4: g_GameState = GAME_RESULT; break;
				case 5: g_GameState = GAME_OVER; break;
			}
		}



		DrawFormatString(15, height - 50, 0xffffff, "X = %4d | selc = %d", x,selc);
		DrawFormatString(15, height - 25, 0xffffff, "Y = %4d |", y);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}