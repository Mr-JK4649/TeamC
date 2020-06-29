#pragma once

#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>



///*変数の宣言*/
//int g_TitleImage;				//タイトル画像
//int g_SelectImage;				//キャラ選択画像
//
////キャラの画像
//int g_HorrorImage[4];			//ホラーキャラ画像
//
////ステージの画像
//int g_Dh[2];					//脱出部屋の画像
//int g_Ohuda;					//お札の画像
//int g_Arrow;					//矢印の画像


/*画像のアドレスを入れるやつ*/


/*タイトルシーンで使う画像*/
struct TitleImage {
	int TitleImage;				//タイトル画面

	void ImageInput(struct TitleImage *p) {
		p->TitleImage = LoadGraph("images/title.png");
	}
};

/*キャラ選択シーンで使う画像*/
struct SelectImage{
	int SelectImage;		//ホラーキャラ用

	void ImageInput(struct SelectImage* p) {
		p->SelectImage = LoadGraph("images/SadaoSelect.jpg");
	}
};

/*ステージ選択シーンで使う画像*/
struct StageImage {
	int EscapeImage;											//脱出ステージ用

	void ImageInput(struct StageImage* p) {
		p->EscapeImage = LoadGraph("images/h1.png");
	}
};

/*ゲームシーンで使う画像*/
struct Escape{
	int EscapeRoom[2];			//脱出部屋の画像
	int Ohuda;					//お札の画像
	int Arrow;					//矢印の画像

	void ImageInput(struct Escape* p) {
		LoadDivGraph("images/脱出ステージ画像.png",2,2,1,720,405,p->EscapeRoom,0);
		p->Ohuda = LoadGraph("images/お札2.png");
		p->Arrow = LoadGraph("images/矢印.png");
	}
};


//int LoadImages() {
//
//	FILE* soiya;
//	fopen_s(&soiya, "soiya.txt", "w");
//
//
//	switch()
//
//	//タイトル
//	if ((title->TitleImage = LoadGraph("images/title.png")) == -1) {
//		fwrite("タイトルの画像読み込みでエラー", sizeof(char), 50, soiya);
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
//	if ((LoadDivGraph("images/脱出ステージ画像.png", 2, 2, 1, 720, 405, EscapeRoom, 0)) == -1) {
//		fwrite("脱出画像の読み込みでエラー", sizeof(char), 50, soiya);
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