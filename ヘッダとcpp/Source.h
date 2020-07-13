#pragma once
#include "DxLib.h"
#include <stdio.h>

struct Title {
	int image=0;
	int logo=0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image = LoadGraph("images/ƒ^ƒCƒgƒ‹ˆÄ‚P.jpg");
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
	int background;
	bool flg = true;
	int move=0;

	void ImageInput(struct Bace* p) {
		p->background = LoadGraph("images/’¬‚Ì•—Œi1.png");
	}

};

struct Chara {
	int hp=100;
	int atk=0;
	int def=0;
};