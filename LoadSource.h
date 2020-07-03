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
	int SadaoSelectImage[4];		//ホラーキャラ用
	int Num = 0;

	void ImageInput(struct SelectImage* p) {
		p->SadaoSelectImage[0] = LoadGraph("images/SadaoSelect.jpg");
		p->SadaoSelectImage[1] = LoadGraph("images/SadaoMigi.jpg");
		p->SadaoSelectImage[2] = LoadGraph("images/SadaoHidari.jpg");
		p->SadaoSelectImage[3] = LoadGraph("images/SadaoGo.jpg");
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
