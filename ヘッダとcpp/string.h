#pragma once
#include <iostream>
#include <stdio.h>
#include "DxLib.h"

/*実用的な関数*/


/******************************************************************
 　　　　　　　　　文字の表示を変えるやつ
 int型		x,y		表示したい座標
 char型		str		表示したい文字
 short型	color	文字の色
 int型		ch		文字の表示形態 (0:左揃え  1:中央揃え  2:右揃え)
 int型		size	文字のサイズ   (標準は16)
******************************************************************/
void SuperString(int x, int y,const char* str, unsigned int color, int ch,int size) {

	SetFontSize(size);

	const int len = GetDrawStringWidth(str, -1);
	

	switch (ch) {
	case 0: DrawString(x, y, str, color, 1); break;				//左揃えで表示

	case 1: DrawString(x - len / 2, y, str, color, 1); break;	//中央揃えで表示

	case 2: DrawString(x - len, y, str, color, 1); break;		//右揃えで表示

	default:DrawString(x,y,"0～2のいずれかで選択してください。",color,1);				//エラー
	}

	SetFontSize(16);

}