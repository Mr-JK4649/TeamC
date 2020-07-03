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
	int aaaaaa;

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

/*脱出ゲームシーンで使う画像*/
struct Escape{
	int EscapeRoom[2];			//脱出部屋の画像
	int Ohuda;					//お札の画像
	int Door;					//ドア
	int Arrow;					//矢印の画像
	int Vase;					//壺
	int Vent;					//通気口

	void ImageInput(struct Escape* p) {
		LoadDivGraph("images/脱出ステージ画像2.png",2,2,1,720,405,p->EscapeRoom,0);
		p->Ohuda = LoadGraph("images/お札2.png");
		p->Door = LoadGraph("images/脱出ステージドア画像.png");
		p->Arrow = LoadGraph("images/矢印.png");
		p->Vase = LoadGraph("images/壺.png");
		p->Vent = LoadGraph("images/通気口.png");
	}
};
