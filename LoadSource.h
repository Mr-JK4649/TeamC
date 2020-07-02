#pragma once

#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>


/*�^�C�g���V�[���Ŏg���摜*/
struct TitleImage {
	int TitleImage;				//�^�C�g�����

	void ImageInput(struct TitleImage *p) {
		p->TitleImage = LoadGraph("images/title.png");
	}
};

/*�L�����I���V�[���Ŏg���摜*/
struct SelectImage{
	int SadaoSelectImage[4];		//�z���[�L�����p
	int Num = 0;

	void ImageInput(struct SelectImage* p) {
		p->SadaoSelectImage[0] = LoadGraph("images/SadaoSelect.jpg");
		p->SadaoSelectImage[1] = LoadGraph("images/SadaoMigi.jpg");
		p->SadaoSelectImage[2] = LoadGraph("images/SadaoHidari.jpg");
		p->SadaoSelectImage[3] = LoadGraph("images/SadaoGo.jpg");
	}
};

/*�X�e�[�W�I���V�[���Ŏg���摜*/
struct StageImage {
	int EscapeImage;											//�E�o�X�e�[�W�p

	void ImageInput(struct StageImage* p) {
		p->EscapeImage = LoadGraph("images/h1.png");
	}
};

/*�Q�[���V�[���Ŏg���摜*/
struct Escape{
	int EscapeRoom[2];			//�E�o�����̉摜
	int Ohuda;					//���D�̉摜
	int Arrow;					//���̉摜

	void ImageInput(struct Escape* p) {
		LoadDivGraph("images/�E�o�X�e�[�W�摜.png",2,2,1,720,405,p->EscapeRoom,0);
		p->Ohuda = LoadGraph("images/���D2.png");
		p->Arrow = LoadGraph("images/���.png");
	}
};
