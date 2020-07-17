#pragma once
#include "DxLib.h"
#include <stdio.h>

struct Title {
	int image=0;
	int logo=0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image = LoadGraph("images/タピオカミルクティー.jpg");
		p->logo = LoadGraph("images/Tlogo2.png");
	}
};

struct Stage {
	int background;
	int Button;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

struct Bace {
	
};

//畑関数用構造体
struct HATAKE {
	int image=0;
	int fremimage = 0;
	bool flg = true;
	void ImageInput(struct HATAKE* p) {
		p->image = LoadGraph("images/Hatakeimage.png");
		p->fremimage = LoadGraph("images/frem.png");
	}
};

struct Chara {
	int hp=100;
	int atk=0;
	int def=0;
};