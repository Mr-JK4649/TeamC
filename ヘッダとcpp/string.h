#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "DxLib.h"

/*実用的な関数*/

#pragma warning(disable : 4244)


/******************************************************************
 　　　　　　　　　文字の表示を変えるやつ
 int型		x,y		表示したい座標
 char型		str		表示したい文字
 short型	color	文字の色
 int型		ch		文字の表示形態 (0:左揃え  1:中央揃え  2:右揃え)
 int型		size	文字のサイズ   (標準は16)
******************************************************************/

struct String {


	/******************************************************************
 　　　　　　　　　	  文字の表示を変えるやつ
	 int型		x,y		表示したい座標
	 char型		str		表示したい文字
	 short型	color	文字の色
	 int型		ch		文字の表示形態 (0:左揃え  1:中央揃え  2:右揃え)
	 int型		size	文字のサイズ   (標準は16)
	******************************************************************/
	void SuperString(int x, int y, const char* str, unsigned int color, int ch, int size) {

		SetFontSize(size);

		const int len = GetDrawStringWidth(str, -1);


		switch (ch) {
		case 0: DrawString(x, y, str, color, 1); break;				//左揃えで表示

		case 1: DrawString(x - len / 2, y, str, color, 1); break;	//中央揃えで表示

		case 2: DrawString(x - len, y, str, color, 1); break;		//右揃えで表示

		default:DrawString(x, y, "0～2のいずれかで選択してください。", color, 1);	//エラー
		}

		SetFontSize(16);

	}

	/******************************************************************
　　　　　　　　　	  文字送りするやつ
	char型		str		出したい文字
	int型		x,y		表示したい座標
    ******************************************************************/
	void Serihu(char* str, int width, int height) {

		SetFontSize(16);
		DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0x444444, 1);
		DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, 6, width - 6, 54, 10, 10, 0xffffff, 0);

		const int speed = 1;

		if (count++ >= speed) { s += 1; count = 0; }
		strncpy_s(buf, str, s);
		if(count%2==0)DrawFormatString(15, 10, 0xffffff, "%s", buf);
		/*DrawFormatString(5,250,0x000000,"%d",s);
		DrawFormatString(5,275,0x000000,"%d",life);*/

		//if (strcmp(buf, str) >= 0 && inp.Lclick || life++ >= 260) { s = 0; setTex = false; life = 0; }

	}

private:
	int count = 0, s = 0, life = 0;
	char buf[500];
	bool setTex = false;
};

extern String str;