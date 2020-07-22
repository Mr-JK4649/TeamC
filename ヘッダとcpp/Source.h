#pragma once
#include "DxLib.h"
#include <stdio.h>


/*タイトルシーンの画像*/
struct Title {
	int image=0;
	int logo=0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image = LoadGraph("images/タイトル案１.jpg");
		p->logo = LoadGraph("images/Tlogo2.png");
	}
};

/*ステージシーンの画像*/
struct Stage {
	int background = 0;
	int Button;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

/*拠点シーンの画像*/
struct Base {
	int background = 0;
	int shadow = 0;
	bool flg = true;
	int move=0;

	void ImageInput(struct Base* p) {
		p->background = LoadGraph("images/町の風景1.png");
		p->shadow = LoadGraph("images/街の影.png");
	}

};

extern Base base;
