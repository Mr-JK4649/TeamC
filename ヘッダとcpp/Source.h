#pragma once
#include "DxLib.h"
#include <stdio.h>


/*�^�C�g���V�[���̉摜*/
struct Title {
	int image=0;
	int logo=0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image = LoadGraph("images/�^�C�g���ĂP.jpg");
		p->logo = LoadGraph("images/Tlogo2.png");
	}
};

/*�X�e�[�W�V�[���̉摜*/
struct Stage {
	int background = 0;
	int Button;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

/*���_�V�[���̉摜*/
struct Base {
	int background = 0;
	int shadow = 0;
	bool flg = true;
	int move=0;

	void ImageInput(struct Base* p) {
		p->background = LoadGraph("images/���̕��i1.png");
		p->shadow = LoadGraph("images/�X�̉e.png");
	}

};

extern Base base;

struct Shop {
	int background[6] = {0,0,0,0,0,0};
	bool flg = true;
	

	void ImageInput(Shop* p) {
		p->background[0] = LoadGraph("images/ShopSele1.jpg");
		p->background[1] = LoadGraph("images/ShopSele2.jpg");
		p->background[2] = LoadGraph("images/ShopSele3.jpg");
		p->background[3] = LoadGraph("images/ShopSele4.jpg");
		p->background[4] = LoadGraph("images/ShopSele5.jpg");
		p->background[5] = LoadGraph("images/shop.jpg");
	}

};

extern Shop shop;