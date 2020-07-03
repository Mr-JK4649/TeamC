#pragma once

#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>


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

/*ゲームクリアシーンで使う画像*/
struct ClearImage {
	int Clear;					//クリアシーンの画像

	void ImageInput(struct ClearImage* p) {
		p->Clear = LoadGraph("images/クリアシーン.png");
	}
};

/*ゲームオーバーシーンで使う画像*/
struct OverImage {
	int Over;					//クリアシーンの画像

	void ImageInput(struct OverImage* p) {
		p->Over = LoadGraph("images/オーバーシーン.png");
	}
};