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
	int aaaaaa;

	void ImageInput(struct TitleImage *p) {
		p->TitleImage = LoadGraph("images/title.png");
	}
};

/*�L�����I���V�[���Ŏg���摜*/
struct SelectImage{
	int SelectImage;		//�z���[�L�����p

	void ImageInput(struct SelectImage* p) {
		p->SelectImage = LoadGraph("images/SadaoSelect.jpg");
	}
};

/*�X�e�[�W�I���V�[���Ŏg���摜*/
struct StageImage {
	int EscapeImage;											//�E�o�X�e�[�W�p

	void ImageInput(struct StageImage* p) {
		p->EscapeImage = LoadGraph("images/h1.png");
	}
};

/*�E�o�Q�[���V�[���Ŏg���摜*/
struct Escape{
	int EscapeRoom[2];			//�E�o�����̉摜
	int Ohuda;					//���D�̉摜
	int Door;					//�h�A
	int Arrow;					//���̉摜
	int Vase;					//��
	int Vent;					//�ʋC��

	void ImageInput(struct Escape* p) {
		LoadDivGraph("images/�E�o�X�e�[�W�摜2.png",2,2,1,720,405,p->EscapeRoom,0);
		p->Ohuda = LoadGraph("images/���D2.png");
		p->Door = LoadGraph("images/�E�o�X�e�[�W�h�A�摜.png");
		p->Arrow = LoadGraph("images/���.png");
		p->Vase = LoadGraph("images/��.png");
		p->Vent = LoadGraph("images/�ʋC��.png");
	}
};
